////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeClientBase.cpp
//  Version:     v1.00
//  Created:     17/10/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeClientBase.inl"
#endif

extern "C"
{
#	include <lua.h>
#	include <lauxlib.h>
#	include <lualib.h>
}

#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>

using namespace RakNet;

//--------------------------------------------------------------------------
VeClientBase::VeClientBase(const VeChar8* pcName)
	: m_kName(pcName), m_u16Port(0), m_u16Align(0)
	, m_pkPeer(NULL), m_pkAddress(NULL), m_eState(STATE_DISCONNECTED)
	, m_bFlag(false)
{
	m_kNode.m_tContent = this;
	m_pkAddress = new (VeMalloc(sizeof(SystemAddress))) SystemAddress();
}
//--------------------------------------------------------------------------
VeClientBase::~VeClientBase()
{
	_Disconnect();
	VeFree(m_pkAddress);
}
//--------------------------------------------------------------------------
void VeClientBase::_Connect()
{
	_Disconnect();
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	m_pkPeer = RakPeerInterface::GetInstance();
	SocketDescriptor sd;
	m_pkPeer->Startup(1, &sd, 1);
	m_pkPeer->SetOccasionalPing(true);
	bool bPwd = m_kPassword != "null";
	if(m_pkPeer->Connect(m_kServerIp, m_u16Port,
		bPwd ? (const VeChar8*)m_kPassword : (const VeChar8*)NULL,
		bPwd ? m_kPassword.Length() : 0) != CONNECTION_ATTEMPT_STARTED)
	{
		RakPeerInterface::DestroyInstance(m_pkPeer);
		m_pkPeer = NULL;
	}
	m_eState = STATE_CONNECTING;
}
//--------------------------------------------------------------------------
void VeClientBase::_Disconnect()
{
	if(m_pkPeer)
	{
		UpdateFG();
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		m_pkPeer->Shutdown(300);
		RakPeerInterface::DestroyInstance(m_pkPeer);
		m_pkPeer = NULL;
	}
	m_eState = STATE_DISCONNECTED;
}
//--------------------------------------------------------------------------
void VeClientBase::Update()
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	m_bFlag = true;
	for(Packet* pkPacket = m_pkPeer->Receive(); pkPacket;
		m_pkPeer->DeallocatePacket(pkPacket), pkPacket = m_pkPeer->Receive())
	{
		if(pkPacket) Process(*pkPacket);
	}
	m_bFlag = false;
}
//--------------------------------------------------------------------------
void VeClientBase::UpdateBG()
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	m_bFlag = true;
	for(Packet* pkPacket = m_pkPeer->Receive(); pkPacket;
		pkPacket = m_pkPeer->Receive())
	{
		m_kPacketCache.PushBack(pkPacket);
	}
	m_bFlag = false;
}
//--------------------------------------------------------------------------
void VeClientBase::UpdateFG()
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	m_bFlag = true;
	for(VeVector<Packet*>::iterator it = m_kPacketCache.Begin();
		it != m_kPacketCache.End(); ++it)
	{
		if(*it)
		{
			Process(**it);
			m_pkPeer->DeallocatePacket(*it);
			*it = NULL;
		}
	}
	m_kPacketCache.Clear();
	m_bFlag = false;
}
//--------------------------------------------------------------------------
void VeClientBase::SendPacket(const RakNet::BitStream& kStream)
{
	VE_ASSERT(m_pkPeer);
	if(m_bFlag)
	{
		m_pkPeer->Send(&kStream, MEDIUM_PRIORITY, RELIABLE_SEQUENCED, 0, *m_pkAddress, false);
	}
	else
	{
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		m_pkPeer->Send(&kStream, MEDIUM_PRIORITY, RELIABLE_SEQUENCED, 0, *m_pkAddress, false);
	}
}
//--------------------------------------------------------------------------
void VeClientBase::Process(RakNet::Packet& kPacket)
{
	BitStream kStream((unsigned char*)kPacket.data, kPacket.length, false);
	VeUInt8 u8Event;
	kStream >> u8Event;
	switch(u8Event)
	{
	case ID_DISCONNECTION_NOTIFICATION:
		DisconnectEvent(DIS_NOTIFICATION);
		break;
	case ID_CONNECTION_BANNED:
		DisconnectEvent(DIS_BANNED);
		break;
	case ID_INVALID_PASSWORD:
		DisconnectEvent(DIS_INVALID_PWD);
		break;
	case ID_NO_FREE_INCOMING_CONNECTIONS:
		DisconnectEvent(DIS_SERVER_FULL);
		break;
	case ID_CONNECTION_LOST:
		DisconnectEvent(DIS_SERVER_LOST);
		break;
	case ID_CONNECTION_REQUEST_ACCEPTED:
		if(m_eState == STATE_CONNECTING)
		{
			(*m_pkAddress) = kPacket.systemAddress;
			if((*m_pkAddress) != UNASSIGNED_SYSTEM_ADDRESS)
			{
				m_eState = STATE_CONNECTED;
				OnConnect();
			}
			else
			{
				DisconnectEvent(DIS_UNASSIGNED_ADDRESS);
			}
		}
		break;
	case ID_CONNECTION_ATTEMPT_FAILED:
		DisconnectEvent(DIS_ATTEMPT_FAILED);
		break;
	default:
		ProcessUserEvent(u8Event, kStream);
		break;
	}
}
//--------------------------------------------------------------------------
void VeClientBase::DisconnectEvent(DisconnectType eType)
{
	if(m_eState == STATE_CONNECTING)
	{
		m_eState = STATE_DISCONNECTED;
		OnConnectFailed(eType);
	}
	else if(m_eState == STATE_CONNECTED)
	{
		m_eState = STATE_DISCONNECTED;
		OnDisconnect(eType);
	}
	else
	{
		m_eState = STATE_DISCONNECTED;
	}
}
//--------------------------------------------------------------------------
VeClient::ConfigLoader::ConfigLoader(VeClient* pkParent,
	VeDirectory* pkDir, LuaHolder kHolder)
	: m_spParent(pkParent), m_pkDir(pkDir), m_kHolder(kHolder)
{

}
//--------------------------------------------------------------------------
void VeClient::ConfigLoader::DoBackgroundTask(VeBackgroundTaskQueue& kMgr)
{
	VeVector<VeFixedString> kList;
	m_pkDir->FindFileList("*.xml", kList);
	for(VeVector<VeFixedString>::iterator it = kList.Begin();
		it != kList.End(); ++it)
	{
		VeXMLDocument kDoc;
		(*m_pkDir->OpenSync(*it)) >> kDoc;
		m_spParent->m_kEntityMgr.LoadConfig(kDoc.RootElement());
	}
	kMgr.AddMainThreadTask(this);
}
//--------------------------------------------------------------------------
void VeClient::ConfigLoader::DoMainThreadTask(VeBackgroundTaskQueue& kMgr)
{
	g_pResourceManager->DestoryDir(m_pkDir);
	m_pkDir = NULL;
	m_spParent = NULL;
	VeLuaBind::Resume(m_kHolder.m_tFirst, m_kHolder.m_tSecond,
		g_pLua->GetLua(), 0);
	m_kHolder = VeMakePair((lua_State*)NULL, 0);
}
//--------------------------------------------------------------------------
VeClient::VeClient() : VeClientBase("VeClient")
{
	
}
//--------------------------------------------------------------------------
VeClient::~VeClient()
{

}
//--------------------------------------------------------------------------
void VeClient::OnConnect()
{
	LuaHolder kHolder;
	{
		VE_ASSERT(m_kLuaCallMap.Size() == 1);
		VeMap<VeUInt32,FuncCall>::iterator it = m_kLuaCallMap.Begin();
		VE_ASSERT(it != m_kLuaCallMap.End() && it->m_tFirst == 0 && (!it->m_tSecond.m_pkFunc));
		kHolder = it->m_tSecond.m_kHolder;
		m_kLuaCallMap.Clear();
	}
	VeLuaBind::RetParam(kHolder.m_tFirst, this);
	VeLuaBind::Resume(kHolder.m_tFirst, kHolder.m_tSecond, g_pLua->GetLua(), 1);
}
//--------------------------------------------------------------------------
void VeClient::OnConnectFailed(DisconnectType eType)
{
	LuaHolder kHolder;
	{
		VE_ASSERT(m_kLuaCallMap.Size() == 1);
		VeMap<VeUInt32,FuncCall>::iterator it = m_kLuaCallMap.Begin();
		VE_ASSERT(it != m_kLuaCallMap.End() && it->m_tFirst == 0 && (!it->m_tSecond.m_pkFunc));
		kHolder = it->m_tSecond.m_kHolder;
		m_kLuaCallMap.Clear();
	}
	lua_pushnil(kHolder.m_tFirst);
	VeLuaBind::RetParam(kHolder.m_tFirst, eType);
	VeLuaBind::Resume(kHolder.m_tFirst, kHolder.m_tSecond, g_pLua->GetLua(), 2);
}
//--------------------------------------------------------------------------
void VeClient::OnDisconnect(DisconnectType eType)
{
	if(m_kCallback.Length())
	{
		m_kEntityMgr.ClearEntities();
		VeLuaCall<void>(m_kCallback, DisconnectTypeLua(eType));
	}
}
//--------------------------------------------------------------------------
void VeClient::ProcessUserEvent(VeUInt8 u8Event, RakNet::BitStream& kStream)
{
	switch(u8Event)
	{
	case ID_USER_PACKET_ENUM + REQ_CALL_FUNC + 1:
		OnCallFunc(kStream);
		break;
	case ID_USER_PACKET_ENUM + RES_CALL_FUNC + 1:
		OnResCallFunc(kStream);
		break;
	case ID_USER_PACKET_ENUM + NOTI_ENT_LINKED + 1:
		OnEntLinked(kStream);
		break;
	case ID_USER_PACKET_ENUM + NOTI_ENT_UPDATED + 1:
		OnEntUpdated(kStream);
		break;
	default:
		VeDebugOutput("Unknown net event %d", u8Event);
		break;
	}
}
//--------------------------------------------------------------------------
void VeClient::Disconnect()
{
	m_eState = VeClientBase::STATE_DISCONNECTED;
	if(m_kCallback.Length())
	{
		m_kEntityMgr.ClearEntities();
		VeLuaCall<void>(m_kCallback);
	}
}
//--------------------------------------------------------------------------
void VeClient::OnCallFunc(RakNet::BitStream& kStream)
{
	VeUInt16 u16Call;
	if(!kStream.Read(u16Call)) return;
	VeUInt16 u16Ent;
	if(!kStream.Read(u16Ent)) return;
	VeUInt16 u16Func;
	if(!kStream.Read(u16Func)) return;
	VeNetEntityPtr spEntity = m_kEntityMgr.GetEntity(u16Ent);
	if(spEntity && u16Func < spEntity->m_kClientFuncArray.Size())
	{
		VeNetEntity::DataEntity* pkData(NULL);
		if(spEntity->m_eType == VeNetEntity::TYPE_GLOBAL && spEntity->m_kDataArray.Size())
		{
			pkData = spEntity->m_kDataArray.Front();
			CreateLuaData(g_pLua->GetLua(), *pkData);
		}
		if(pkData)
		{
			VeNetEntity::RpcFunc& kFunc = spEntity->m_kClientFuncArray[u16Func];
			lua_State* pkThread = g_pLua->MakeFullCallThread();
			VE_ASSERT(pkThread);
			VeLuaBind::StackHolder kHoldMain(g_pLua->GetLua());
			VeLuaBind::StackHolder kHoldThread(pkThread);
			lua_rawgeti(pkThread, LUA_REGISTRYINDEX, kFunc.m_i32FuncRef);
			lua_pushlightuserdata(pkThread, pkData->m_spLuaSupport);
			lua_pushlightuserdata(pkThread, this);
			lua_pushlightuserdata(pkThread, &kFunc);
			lua_pushunsigned(pkThread, u16Call);
			lua_pushcclosure(pkThread, &OnCallFinished, 4);
			lua_rawgeti(pkThread, LUA_REGISTRYINDEX, pkData->m_i32Ref);
			VeInt32 i32ParamNum = VeNetEntity::RetParam(pkThread, kStream, kFunc.m_kInParams);
			if(VeUInt32(i32ParamNum) == kFunc.m_kInParams.Size())
			{
				VE_ASSERT_EQ(VeLuaBind::CallFuncThread(g_pLua->GetLua(), pkThread, 3 + i32ParamNum), 1);
			}
		}
	}
}
//--------------------------------------------------------------------------
VeInt32 VeClient::OnCallFinished(lua_State* pkState)
{
	VeNetEntity::LuaSupport* pkSupport = (VeNetEntity::LuaSupport*)lua_touserdata(pkState, lua_upvalueindex(1));
	if(pkSupport->m_pkParent && pkSupport->m_pkParent->GetType() == VeNetEntity::Data::TYPE_ENTITY)
	{
		VeClient& kClient = *(VeClient*)lua_touserdata(pkState, lua_upvalueindex(2));
		VeNetEntity::RpcFunc& kFunc = *(VeNetEntity::RpcFunc*)lua_touserdata(pkState, lua_upvalueindex(3));
		VeUInt16 u16Call = lua_tounsigned(pkState, lua_upvalueindex(4));
		if(kFunc.m_kOutParams.Size())
		{
			BitStream kStream;
			kStream.Reset();
			kStream.Write(VeUInt8(ID_USER_PACKET_ENUM + VeClient::RES_CALL_FUNC + 1));
			kStream.Write(u16Call);
			if(VeNetEntity::Write(kStream, pkState, kFunc.m_kOutParams))
			{
				kClient.SendPacket(kStream);
			}
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
void VeClient::OnResCallFunc(BitStream& kStream)
{
	VeUInt16 u16Call;
	VE_ASSERT_EQ(kStream.Read(u16Call), true);
	VeMap<VeUInt32,FuncCall>::iterator it = m_kLuaCallMap.Find(u16Call);
	VE_ASSERT(it != m_kLuaCallMap.End() && it->m_tSecond.m_pkFunc);
	FuncCall kCall(it->m_tSecond);
	m_kLuaCallMap.Erase(it);
	VeInt32 i32ParamNum = VeNetEntity::RetParam(kCall.m_kHolder.m_tFirst,
		kStream, kCall.m_pkFunc->m_kOutParams);
	VE_ASSERT(VeUInt32(i32ParamNum) == kCall.m_pkFunc->m_kOutParams.Size());
	VeLuaBind::Resume(kCall.m_kHolder.m_tFirst, kCall.m_kHolder.m_tSecond,
		g_pLua->GetLua(), i32ParamNum);
}
//--------------------------------------------------------------------------
static VeNetEntity::DataEntityPtr CreateData(BitStream& kStream,
	VeNetEntity& kEntity)
{
	VeNetEntity::DataEntityPtr spDataEnt = VE_NEW VeNetEntity::DataEntity;
	spDataEnt->m_pkObject = &kEntity;
	for(VeUInt32 i(0); i < kEntity.m_kProperties.Size(); ++i)
	{
		if((kEntity.m_kProperties[i])->HasFlag(VeNetEntity::Property::FLAG_CLIENT))
		{
			VeNetEntity::DataPtr spData;
			spData = VeNetEntity::CreateData(kStream, *kEntity.m_kProperties[i]);
			VE_ASSERT(spData);
			spData->m_u32Index = i;
			spData->m_pkHolder = spDataEnt;
			spDataEnt->m_kDataArray.PushBack(spData);
		}
	}
	return spDataEnt;
}
//--------------------------------------------------------------------------
void VeClient::OnEntLinked(BitStream& kStream)
{
	VeUInt16 u16Entity;
	VE_ASSERT_EQ(kStream.Read(u16Entity), true);
	VeNetEntityPtr spEnt = m_kEntityMgr.GetEntity(u16Entity);
	VE_ASSERT(spEnt && spEnt->m_eType != VeNetEntity::TYPE_GLOBAL
		&& spEnt->m_kDataArray.Empty());
	VeNetEntity::DataEntityPtr spData = CreateData(kStream, *spEnt);
	VE_ASSERT(spData);
	spEnt->m_kDataArray.PushBack(spData);
	spEnt->m_kDataArray.Back()->m_u32Index = 0;
	spEnt->m_kDataArray.Back()->m_pkObject = spEnt;
	spEnt->m_kFreeList.AttachBack(spEnt->m_kDataArray.Back()->m_kNode);
}
//--------------------------------------------------------------------------
void VeClient::ReadUpdate(BitStream& kIn, VeNetEntity::DataEntity& kData)
{
	VeNetEntity& kEntity = *(VeNetEntity*)kData.m_pkObject;
	VeUInt16 u16Size;
	VE_ASSERT_EQ(kIn.Read(u16Size), true);
	for(VeUInt32 i(0); i < u16Size; ++i)
	{
		VeUInt16 u16Index;
		VE_ASSERT_EQ(kIn.Read(u16Index), true);
		VE_ASSERT(u16Index < kData.m_kDataArray.Size());
		VeNetEntity::ReadUpdate(kIn, *kData.m_kDataArray[u16Index]);
		{
			lua_State* pkThread = VeLuaBind::MakeFuncThread(g_pLua->GetLua(), kEntity.m_i32UpdateFunc);
			VE_ASSERT(pkThread);
			VeLuaBind::StackHolder kHoldMain(g_pLua->GetLua());
			VeLuaBind::StackHolder kHoldThread(pkThread);
			PushLuaData(pkThread, kData);
			VeNetEntity::Property& kProp = *(VeNetEntity::Property*)kData.m_kDataArray[u16Index]->m_pkObject;
			lua_pushstring(pkThread, kProp.m_kName);
			VeLuaBind::CallFuncThread(g_pLua->GetLua(), pkThread, 2);
		}
	}
}
//--------------------------------------------------------------------------
void VeClient::OnEntUpdated(BitStream& kStream)
{
	VeUInt16 u16Entity;
	VE_ASSERT_EQ(kStream.Read(u16Entity), true);
	VeNetEntityPtr spEnt = m_kEntityMgr.GetEntity(u16Entity);
	VE_ASSERT(spEnt && spEnt->m_eType != VeNetEntity::TYPE_GLOBAL && spEnt->m_kDataArray.Size());
	VeNetEntity::DataEntity& kData = *spEnt->m_kDataArray.Front();
	ReadUpdate(kStream, kData);
}
//--------------------------------------------------------------------------
static VeInt32 PrintBaseFunction(lua_State* pkState)
{
	VeNetEntity::LuaSupport* pkSupport = *(VeNetEntity::LuaSupport**)lua_touserdata(pkState, -1);
	if(pkSupport->m_pkParent && pkSupport->m_pkParent->GetType() == VeNetEntity::Data::TYPE_ENTITY)
	{
		VeChar8 acBuffer[4096];
		VeChar8* pcPointer(acBuffer);
		VeNetEntity& kEnt = *(VeNetEntity*)(pkSupport->m_pkParent->m_pkObject);
		pcPointer += VeSprintf(pcPointer, 1024, "base[%s]:", (const VeChar8*)(kEnt.m_kName));
		for(VeUInt32 i(0); i < kEnt.m_kBaseFuncArray.Size(); ++i)
		{
			if(i) pcPointer += VeSprintf(pcPointer, 1024, ",");
			pcPointer += VeSprintf(pcPointer, 1024, "%s", (const VeChar8*)(kEnt.m_kBaseFuncArray[i].m_kName));
		}
		VeLuaBind::RetParam(pkState, acBuffer);
		return 1;
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeClient::CallBaseFunction(lua_State* pkState)
{
	VeNetEntity::LuaSupport* pkSupport = (VeNetEntity::LuaSupport*)lua_touserdata(pkState, lua_upvalueindex(1));
	if(pkSupport->m_pkParent && pkSupport->m_pkParent->GetType() == VeNetEntity::Data::TYPE_ENTITY)
	{
		VeNetEntity& kEnt = *(VeNetEntity*)(pkSupport->m_pkParent->m_pkObject);
		VeClient& kClient = *(VeClient*)lua_touserdata(pkState, lua_upvalueindex(2));
		VeUInt32 u32Func = lua_tounsigned(pkState, lua_upvalueindex(3));
		VE_ASSERT(u32Func < kEnt.m_kBaseFuncArray.Size());
		VeNetEntity::RpcFunc& kFunc = kEnt.m_kBaseFuncArray[u32Func];
		if(kClient.GetState() == VeClientBase::STATE_CONNECTED)
		{
			VeUInt32 u32CallID(0);
			if(kFunc.m_kOutParams.Size() && kClient.m_kLuaCallMap.Size())
			{
				u32CallID = kClient.m_kLuaCallMap.Last()->m_tFirst + 1;
			}
			VE_ASSERT(u32CallID < VE_UINT16_MAX);
			BitStream kStream;
			kStream.Reset();
			kStream.Write(VeUInt8(ID_USER_PACKET_ENUM + VeClient::REQ_CALL_FUNC + 1));
			kStream.Write(VeUInt16(u32CallID));
			kStream.Write(VeUInt16(kEnt.m_u32Index));
			kStream.Write(VeUInt16(u32Func));
			if(VeNetEntity::Write(kStream, pkState, kFunc.m_kInParams))
			{
				kClient.SendPacket(kStream);
				if(kFunc.m_kOutParams.Size())
				{
					VE_ASSERT(kClient.m_kLuaCallMap.Find(u32CallID) == kClient.m_kLuaCallMap.End());
					VeClient::FuncCall& kCall = kClient.m_kLuaCallMap[u32CallID];
					kCall.m_kHolder.m_tFirst = pkState;
					lua_pushthread(pkState);
					VE_ASSERT(lua_tothread(pkState, -1) == pkState);
					kCall.m_kHolder.m_tSecond = luaL_ref(pkState, LUA_REGISTRYINDEX);
					kCall.m_pkFunc = &kFunc;
					return lua_yield(pkState, 0);
				}
				return 0;
			}
		}
		return VeNetEntity::RetParam(pkState, kFunc.m_kOutParams);
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeClient::RetParamBase(lua_State* pkState,
	VeNetEntity::DataEntity& kData)
{
	if(!kData.m_spLuaSupport)
	{
		kData.m_spLuaSupport = VE_NEW VeNetEntity::LuaSupport(&kData);
	}
	void* pvData = lua_newuserdata(pkState, sizeof(VeNetEntity::LuaSupport*));
	kData.m_spLuaSupport->IncRefCount();
	*(VeNetEntity::LuaSupport**)pvData = kData.m_spLuaSupport;
	lua_newtable(pkState);
	lua_pushstring(pkState, "__newindex");
	lua_pushcfunction(pkState, &VeNetEntity::NoWriteNewIndex);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__gc");
	lua_pushcfunction(pkState, &VeNetEntity::DestructorData);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__tostring");
	lua_pushcfunction(pkState, &PrintBaseFunction);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__index");
	lua_newtable(pkState);
	{
		VeNetEntity& kEnt = *(VeNetEntity*)kData.m_pkObject;
		for(VeUInt32 i(0); i < kEnt.m_kBaseFuncArray.Size(); ++i)
		{
			lua_pushstring(pkState, kEnt.m_kBaseFuncArray[i].m_kName);
			lua_pushlightuserdata(pkState, kData.m_spLuaSupport);
			lua_pushlightuserdata(pkState, this);
			lua_pushunsigned(pkState, i);
			lua_pushcclosure(pkState, &CallBaseFunction, 3);
			lua_rawset(pkState, -3);
		}
	}
	lua_rawset(pkState, -3);
	lua_setmetatable(pkState, -2);
	return 1;
}
//--------------------------------------------------------------------------
static VeInt32 PrintClientFunction(lua_State* pkState)
{
	VeNetEntity::LuaSupport* pkSupport = *(VeNetEntity::LuaSupport**)lua_touserdata(pkState, -1);
	if(pkSupport->m_pkParent && pkSupport->m_pkParent->GetType() == VeNetEntity::Data::TYPE_ENTITY)
	{
		VeChar8 acBuffer[4096];
		VeChar8* pcPointer(acBuffer);
		VeNetEntity& kEnt = *(VeNetEntity*)(pkSupport->m_pkParent->m_pkObject);
		pcPointer += VeSprintf(pcPointer, 1024, "client[%s]:", (const VeChar8*)(kEnt.m_kName));
		for(VeUInt32 i(0); i < kEnt.m_kClientFuncArray.Size(); ++i)
		{
			if(i) pcPointer += VeSprintf(pcPointer, 1024, ",");
			pcPointer += VeSprintf(pcPointer, 1024, "%s", (const VeChar8*)(kEnt.m_kClientFuncArray[i].m_kName));
		}
		VeLuaBind::RetParam(pkState, acBuffer);
		return 1;
	}
	return 0;
}
//--------------------------------------------------------------------------
class LocalFunctionCaller : public VeBackgroundTask
{
public:
	LocalFunctionCaller(lua_State* pkThread, VeInt32 i32Ref, VeUInt32 u32Num)
		: m_pkThread(pkThread), m_i32Ref(i32Ref), m_u32ParamsNum(u32Num) {}

	virtual void DoMainThreadTask(VeBackgroundTaskQueue& kMgr)
	{
		VeLuaBind::CallFuncThread(g_pLua->GetLua(), m_pkThread, m_u32ParamsNum);
		luaL_unref(g_pLua->GetLua(), LUA_REGISTRYINDEX, m_i32Ref);
	}

	lua_State* m_pkThread;
	VeInt32 m_i32Ref;
	VeUInt32 m_u32ParamsNum;

};
//--------------------------------------------------------------------------
VeInt32 VeClient::CallLocalFunction(lua_State* pkState)
{
	VeNetEntity::LuaSupport* pkSupport = (VeNetEntity::LuaSupport*)lua_touserdata(pkState, lua_upvalueindex(1));
	if(pkSupport->m_pkParent && pkSupport->m_pkParent->GetType() == VeNetEntity::Data::TYPE_ENTITY)
	{
		VeNetEntity::DataEntity& kData = *(VeNetEntity::DataEntity*)pkSupport->m_pkParent;
		VeNetEntity& kEnt = *(VeNetEntity*)(kData.m_pkObject);
		VeUInt32 u32Func = lua_tounsigned(pkState, lua_upvalueindex(2));
		VE_ASSERT(u32Func < kEnt.m_kClientFuncArray.Size());
		VeNetEntity::RpcFunc& kFunc = kEnt.m_kClientFuncArray[u32Func];
		VeInt32 i32Top = lua_gettop(pkState);
		if(VeUInt32(i32Top) == kFunc.m_kInParams.Size())
		{
			if(kFunc.m_kOutParams.Size())
			{
				lua_rawgeti(g_pLua->GetLua(), LUA_REGISTRYINDEX, g_pLua->GetFullCall());
				VE_ASSERT(lua_type(g_pLua->GetLua(), -1) == LUA_TFUNCTION);
				lua_State* pkThread = lua_newthread(g_pLua->GetLua());
				VeInt32 i32Ref = luaL_ref(g_pLua->GetLua(), LUA_REGISTRYINDEX);
				lua_xmove(g_pLua->GetLua(), pkThread, 1);
				VE_ASSERT(lua_gettop(pkThread) == 1);
				VeLuaBind::StackHolder kHoldMain(g_pLua->GetLua());
				VeLuaBind::StackHolder kHoldThread(pkThread);
				lua_rawgeti(pkThread, LUA_REGISTRYINDEX, kFunc.m_i32FuncRef);
				lua_pushthread(pkState);
				lua_xmove(pkState, pkThread, 1);
				lua_pushcclosure(pkThread, &OnCallLocalFinished, 1);
				lua_rawgeti(pkThread, LUA_REGISTRYINDEX, kData.m_i32Ref);
				for(VeUInt32 i(0); i < VeUInt32(i32Top); ++i)
				{
					lua_pushvalue(pkState, i + 1);
					lua_xmove(pkState, pkThread, 1);
				}
				g_pResourceManager->AddFGTask(VeResourceManager::BG_QUEUE_PROCESS, VE_NEW LocalFunctionCaller(pkThread, i32Ref, 3 + i32Top));
				return lua_yield(pkState, 0);
			}
			else
			{
				lua_State* pkThread = VeLuaBind::MakeFuncThread(g_pLua->GetLua(), kFunc.m_i32FuncRef);
				VeLuaBind::StackHolder kHoldMain(g_pLua->GetLua());
				VeLuaBind::StackHolder kHoldThread(pkThread);
				lua_rawgeti(pkThread, LUA_REGISTRYINDEX, kData.m_i32Ref);
				for(VeUInt32 i(0); i < VeUInt32(i32Top); ++i)
				{
					lua_pushvalue(pkState, i + 1);
					lua_xmove(pkState, pkThread, 1);
				}
				VeLuaBind::CallFuncThread(g_pLua->GetLua(), pkThread, 1 + i32Top);
				return 0;
			}
		}
		return VeNetEntity::RetParam(pkState, kFunc.m_kOutParams);
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeClient::OnCallLocalFinished(lua_State* pkState)
{
	lua_State* pkThread = lua_tothread(pkState, lua_upvalueindex(1));
	VeInt32 i32Top = lua_gettop(pkState);
	for(VeUInt32 i(0); i < VeUInt32(i32Top); ++i)
	{
		lua_pushvalue(pkState, i + 1);
		lua_xmove(pkState, pkThread, 1);
	}
	lua_resume(pkThread, g_pLua->GetLua(), 0);
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeClient::RetParamClient(lua_State* pkState,
	VeNetEntity::DataEntity& kData)
{
	if(!kData.m_spLuaSupport)
	{
		kData.m_spLuaSupport = VE_NEW VeNetEntity::LuaSupport(&kData);
	}
	void* pvData = lua_newuserdata(pkState, sizeof(VeNetEntity::LuaSupport*));
	kData.m_spLuaSupport->IncRefCount();
	*(VeNetEntity::LuaSupport**)pvData = kData.m_spLuaSupport;
	lua_newtable(pkState);
	lua_pushstring(pkState, "__newindex");
	lua_pushcfunction(pkState, &VeNetEntity::NoWriteNewIndex);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__gc");
	lua_pushcfunction(pkState, &VeNetEntity::DestructorData);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__tostring");
	lua_pushcfunction(pkState, &PrintClientFunction);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__index");
	lua_newtable(pkState);
	{
		VeNetEntity& kEnt = *(VeNetEntity*)kData.m_pkObject;
		for(VeUInt32 i(0); i < kEnt.m_kClientFuncArray.Size(); ++i)
		{
			lua_pushstring(pkState, kEnt.m_kClientFuncArray[i].m_kName);
			lua_pushlightuserdata(pkState, kData.m_spLuaSupport);
			lua_pushunsigned(pkState, i);
			lua_pushcclosure(pkState, &CallLocalFunction, 2);
			lua_rawset(pkState, -3);
		}
	}
	lua_rawset(pkState, -3);
	lua_setmetatable(pkState, -2);
	return 1;
}
//--------------------------------------------------------------------------
VeInt32 VeClient::RetParam(lua_State* pkState,
	VeNetEntity::DataEntity& kData)
{
	lua_newtable(pkState);
	lua_newtable(pkState);
	lua_pushstring(pkState, "__newindex");
	lua_pushcclosure(pkState, VeNetEntity::NoWriteNewIndex, 0);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__index");
	lua_newtable(pkState);

	lua_pushstring(pkState, "base");
	RetParamBase(pkState, kData);
	lua_rawset(pkState, -3);

	lua_pushstring(pkState, "client");
	RetParamClient(pkState, kData);
	lua_rawset(pkState, -3);

	VeNetEntity& kEntity = *(VeNetEntity*)kData.m_pkObject;
	if(kEntity.m_eType != VeNetEntity::TYPE_GLOBAL)
	{
		lua_pushstring(pkState, "prop");
		VeNetEntity::RetParam(pkState, kData, false);
		lua_rawset(pkState, -3);
	}

	lua_rawset(pkState, -3);
	lua_setmetatable(pkState, -2);
	return 1;
}
//--------------------------------------------------------------------------
void VeClient::CreateLuaData(lua_State* pkState,
	VeNetEntity::DataEntity& kEntity)
{
	if(!kEntity.m_i32Ref)
	{
		RetParam(pkState, kEntity);
		kEntity.m_i32Ref = luaL_ref(pkState, LUA_REGISTRYINDEX);
	}
}
//--------------------------------------------------------------------------
void VeClient::PushLuaData(lua_State* pkState,
	VeNetEntity::DataEntity& kEntity)
{
	CreateLuaData(pkState, kEntity);
	lua_rawgeti(pkState, LUA_REGISTRYINDEX, kEntity.m_i32Ref);
}
//--------------------------------------------------------------------------
void VeClient::GetEntity(lua_State* pkState, const VeChar8* pcName)
{
	VeNetEntityPtr spEnt = m_kEntityMgr.GetEntity(pcName);
	if(spEnt)
	{
		if(spEnt->m_eType == VeNetEntity::TYPE_GLOBAL)
		{
			if(spEnt->m_kDataArray.Empty())
			{
				spEnt->m_kDataArray.PushBack(VE_NEW VeNetEntity::DataEntity);
				spEnt->m_kDataArray.Back()->m_u32Index = 0;
				spEnt->m_kDataArray.Back()->m_pkObject = spEnt;
				spEnt->m_kFreeList.AttachBack(spEnt->m_kDataArray.Back()->m_kNode);
			}
		}
		if(spEnt->m_kDataArray.Size())
		{
			PushLuaData(pkState, *spEnt->m_kDataArray.Front());
			VeLuaBind::ManualReturn(1);
		}
	}
}
//--------------------------------------------------------------------------
void Create_S(lua_State* pkState, const VeChar8* pcPath)
{
	VeClientPtr spClient = g_pClientManager->GetClient("VeClient");
	if(!spClient)
	{
		spClient = VE_NEW VeClient();
		g_pClientManager->AddClient(spClient);
		VeDirectory* pkDir = g_pResourceManager->CreateDir(pcPath);
		VE_ASSERT(pkDir);
		g_pResourceManager->AddBGTask(VeResourceManager::BG_QUEUE_FILE,
			VE_NEW VeClient::ConfigLoader(spClient, pkDir,
			VeMakePair(pkState, VeLuaBind::Pause(pkState))));
	}
}
//--------------------------------------------------------------------------
void Connect_S(lua_State* pkState, const VeChar8* pcServerIp,
	VeUInt16 u16Port, const VeChar8* pcPassword, const VeChar8* pcCallback)
{
	VeClientPtr spClient = g_pClientManager->GetClient("VeClient");
	VE_ASSERT(spClient);
	if(spClient->GetState() == VeClient::STATE_DISCONNECTED)
	{
		spClient->m_kCallback = pcCallback;
		VE_ASSERT_EQ(g_pClientManager->ConnectAsync(spClient, pcServerIp, u16Port, pcPassword), true);
		spClient->m_eState = VeClient::STATE_CONNECTING;
		VE_ASSERT(spClient->m_kLuaCallMap.Empty());
		VeClient::FuncCall& kCall = spClient->m_kLuaCallMap[0];
		kCall.m_kHolder.m_tFirst = pkState;
		kCall.m_kHolder.m_tSecond = VeLuaBind::Pause(pkState);
	}
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeClient)
{
	Module() [
		Class<VeClient>().
			Def("GetEntity", &VeClient::GetEntity).
			Def("Disconnect", &VeClient::Disconnect) [
			Def("Create_S", &Create_S),
			Def("Connect_S", &Connect_S)
		]
	];
}
//--------------------------------------------------------------------------
namespace VeLuaBind
{
	VeLuaClassEnumFuncImpl(VeClient, DisconnectType);
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeClient, DisconnectType)
{
	VeLuaClassEnumBase(VeClient, DisconnectType);
	VeLuaClassEnumSlot(VeClient, DisconnectType, DIS_NOTIFICATION, "notification");
	VeLuaClassEnumSlot(VeClient, DisconnectType, DIS_BANNED, "banned");
	VeLuaClassEnumSlot(VeClient, DisconnectType, DIS_INVALID_PWD, "invalid_password");
	VeLuaClassEnumSlot(VeClient, DisconnectType, DIS_SERVER_FULL, "server_full");
	VeLuaClassEnumSlot(VeClient, DisconnectType, DIS_SERVER_LOST, "server_lost");
	VeLuaClassEnumSlot(VeClient, DisconnectType, DIS_ATTEMPT_FAILED, "attempt_failed");
	VeLuaClassEnumSlot(VeClient, DisconnectType, DIS_UNASSIGNED_ADDRESS, "unassigned_address");
}
//--------------------------------------------------------------------------
VeClientManager::VeClientManager()
{
	m_kThread.SetListener(this);
}
//--------------------------------------------------------------------------
VeClientManager::~VeClientManager()
{
	End();
}
//--------------------------------------------------------------------------
bool VeClientManager::AddClient(const VeClientBasePtr& spClient)
{
	if(spClient && !(spClient->m_kNode.IsAttach()))
	{
		if(!m_kClientMap.Find(spClient->GetName()))
		{
			m_kClientMap[spClient->GetName()] = spClient;
			{
				VE_AUTO_LOCK_MUTEX(m_kMutex);
				m_kOffList.AttachBack(spClient->m_kNode);
			}
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------
VeClientBasePtr VeClientManager::GetClient(const VeChar8* pcClient)
{
	if(pcClient)
	{
		VeClientBasePtr* pspIter = m_kClientMap.Find(pcClient);
		if(pspIter)
		{
			return *pspIter;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------------
bool VeClientManager::ConnectSync(const VeChar8* pcClient,
	const VeChar8* pcServerIp, VeUInt16 u16Port, const VeChar8* pcPassword)
{
	return ConnectSync(GetClient(pcClient), pcServerIp, u16Port, pcPassword);
}
//--------------------------------------------------------------------------
bool VeClientManager::ConnectSync(const VeClientBasePtr& spClient,
	const VeChar8* pcServerIp, VeUInt16 u16Port, const VeChar8* pcPassword)
{
	if(spClient && pcServerIp && u16Port)
	{
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		if(spClient->m_kNode.IsAttach(m_kOffList))
		{
			spClient->m_kServerIp = pcServerIp;
			spClient->m_u16Port = u16Port;
			spClient->m_kPassword = pcPassword;
			spClient->_Connect();
			if(spClient->m_pkPeer)
			{
				m_kFGList.AttachBack(spClient->m_kNode);
				return true;
			}
			else
			{
				m_kOffList.AttachBack(spClient->m_kNode);
			}
		}
	}
	return false;
}
//--------------------------------------------------------------------------
bool VeClientManager::ConnectAsync(const VeChar8* pcClient,
	const VeChar8* pcServerIp, VeUInt16 u16Port, const VeChar8* pcPassword)
{
	return ConnectAsync(GetClient(pcClient), pcServerIp, u16Port, pcPassword);
}
//--------------------------------------------------------------------------
bool VeClientManager::ConnectAsync(const VeClientBasePtr& spClient,
	const VeChar8* pcServerIp, VeUInt16 u16Port, const VeChar8* pcPassword)
{
	if(spClient && pcServerIp && u16Port)
	{
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		if(spClient->m_kNode.IsAttach(m_kOffList))
		{
			spClient->m_kServerIp = pcServerIp;
			spClient->m_u16Port = u16Port;
			spClient->m_kPassword = pcPassword;
			m_kTurnList.AttachBack(spClient->m_kNode);
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------
bool VeClientManager::Disconnect(const VeChar8* pcClient)
{
	return Disconnect(GetClient(pcClient));
}
//--------------------------------------------------------------------------
bool VeClientManager::Disconnect(const VeClientBasePtr& spClient)
{
	if(spClient)
	{
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		if(spClient->m_kNode.IsAttach(m_kFGList))
		{
			spClient->_Disconnect();
			m_kOffList.AttachBack(spClient->m_kNode);
			return true;
		}
		else if(spClient->m_kNode.IsAttach(m_kBGList))
		{
			m_kTurnList.AttachBack(spClient->m_kNode);
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------
void VeClientManager::Start()
{
	m_kThread.Start();
}
//--------------------------------------------------------------------------
void VeClientManager::End()
{
	m_kThread.Stop();
	m_kFGList.BeginIterator();
	while(!m_kFGList.IsEnd())
	{
		VeClientBase* pkClient = m_kFGList.GetIterNode()->m_tContent;
		m_kFGList.Next();
		pkClient->_Disconnect();
	}
	m_kBGList.BeginIterator();
	while(!m_kBGList.IsEnd())
	{
		VeClientBase* pkClient = m_kBGList.GetIterNode()->m_tContent;
		m_kBGList.Next();
		pkClient->_Disconnect();
	}
	m_kTurnList.BeginIterator();
	while(!m_kTurnList.IsEnd())
	{
		VeClientBase* pkClient = m_kTurnList.GetIterNode()->m_tContent;
		m_kTurnList.Next();
		pkClient->_Disconnect();
	}
	m_kClientMap.Clear();
	m_kOffList.Clear();
	m_kFGList.Clear();
	m_kBGList.Clear();
	m_kTurnList.Clear();
}
//--------------------------------------------------------------------------
void VeClientManager::Update()
{
	m_kFGList.BeginIterator();
	while(!m_kFGList.IsEnd())
	{
		VeClientBase* pkClient = m_kFGList.GetIterNode()->m_tContent;
		m_kFGList.Next();
		if(pkClient->GetState() == VeClientBase::STATE_DISCONNECTED)
		{
			pkClient->_Disconnect();
			m_kOffList.AttachBack(pkClient->m_kNode);
		}
		else
		{
			pkClient->Update();
		}
	}

	{
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		m_kBGList.BeginIterator();
		while(!m_kBGList.IsEnd())
		{
			VeClientBase* pkClient = m_kBGList.GetIterNode()->m_tContent;
			m_kBGList.Next();
			if(pkClient->GetState() == VeClientBase::STATE_DISCONNECTED)
			{
				pkClient->_Disconnect();
				m_kOffList.AttachBack(pkClient->m_kNode);
			}
			else
			{
				pkClient->UpdateFG();
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeClientManager::Tick()
{
	while(true)
	{
		VeClientBase* pkClient(NULL);
		{
			VE_AUTO_LOCK_MUTEX(m_kMutex);
			if(m_kTurnList.GetHeadNode())
			{
				pkClient = m_kTurnList.GetHeadNode()->m_tContent;
				pkClient->m_kNode.Detach();
			}
			else
			{
				break;
			}
		}
		if(pkClient)
		{
			if(pkClient->m_pkPeer)
			{
				pkClient->_Disconnect();
				VE_AUTO_LOCK_MUTEX(m_kMutex);
				m_kOffList.AttachBack(pkClient->m_kNode);
			}
			else
			{
				pkClient->_Connect();
				VE_AUTO_LOCK_MUTEX(m_kMutex);
				(pkClient->m_pkPeer ? m_kBGList : m_kOffList).AttachBack(pkClient->m_kNode);
			}
		}
	}

	{
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		m_kBGList.BeginIterator();
		while(!m_kBGList.IsEnd())
		{
			VeClientBase* pkClient = m_kBGList.GetIterNode()->m_tContent;
			m_kBGList.Next();
			if(pkClient->GetState() == VeClientBase::STATE_DISCONNECTED)
			{
				pkClient->_Disconnect();
				m_kOffList.AttachBack(pkClient->m_kNode);
			}
			else
			{
				pkClient->UpdateBG();
			}
		}
	}

	VeSleep(5);
}
//--------------------------------------------------------------------------
