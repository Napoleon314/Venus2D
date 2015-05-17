////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeClientBase.h
//  Version:     v1.00
//  Created:     17/10/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

namespace RakNet
{
	class RakPeerInterface;
	struct Packet;
	class BitStream;
}

class VE_POWER_API VeClientBase : public VeRefObject
{
public:
	enum State
	{
		STATE_DISCONNECTED,
		STATE_CONNECTING,
		STATE_CONNECTED,
		STATE_MAX
	};

	enum DisconnectType
	{
		DIS_NOTIFICATION,
		DIS_BANNED,
		DIS_INVALID_PWD,
		DIS_SERVER_FULL,
		DIS_SERVER_LOST,
		DIS_ATTEMPT_FAILED,
		DIS_UNASSIGNED_ADDRESS,
		DIS_MAX
	};

	VeClientBase(const VeChar8* pcName);

	virtual ~VeClientBase();

	VE_INLINE const VeChar8* GetName();

	VE_INLINE State GetState();

	void Update();

	void UpdateBG();

	void UpdateFG();

	void SendPacket(const RakNet::BitStream& kStream);

	void Process(RakNet::Packet& kPacket);

	virtual void OnConnect() {}

	virtual void OnConnectFailed(DisconnectType eType) {}

	virtual void OnDisconnect(DisconnectType eType) {}

	virtual void ProcessUserEvent(VeUInt8 u8Event, RakNet::BitStream& kStream) {}

protected:
	void _Connect();

	void _Disconnect();

	void DisconnectEvent(DisconnectType eType);

	friend class VeClientManager;
	VeRefNode<VeClientBase*> m_kNode;
	VeString m_kName;
	VeString m_kServerIp;
	VeUInt16 m_u16Port;
	VeUInt16 m_u16Align;
	VeString m_kPassword;
	VeThread::Mutex m_kMutex;
	RakNet::RakPeerInterface* m_pkPeer;
	VeVector<RakNet::Packet*> m_kPacketCache;
	RakNet::SystemAddress* m_pkAddress;
	State m_eState;
	bool m_bFlag;

};

VeSmartPointer(VeClientBase);
VeSmartPointer(VeClient);

class VE_POWER_API VeClient : public VeClientBase
{
	VeDeclareLuaRttiExport(VeClient);
public:
	typedef VePair<lua_State*,VeInt32> LuaHolder;

	VeLuaClassEnumDef(DisconnectType);

	enum Protocol
	{
		REQ_CALL_FUNC,
		RES_CALL_FUNC,
		NOTI_ENT_LINKED,
		NOTI_ENT_UPDATED,
		PRO_MAX
	};

	class ConfigLoader : public VeBackgroundTask
	{
	public:
		ConfigLoader(VeClient* pkParent, VeDirectory* pkDir, LuaHolder kHolder);

		virtual void DoBackgroundTask(VeBackgroundTaskQueue& kMgr);

		virtual void DoMainThreadTask(VeBackgroundTaskQueue& kMgr);

	protected:
		VeClientPtr m_spParent;
		VeDirectory* m_pkDir;
		LuaHolder m_kHolder;

	};

	struct FuncCall
	{
		FuncCall() : m_pkFunc(NULL) {}

		LuaHolder m_kHolder;
		VeNetEntity::RpcFunc* m_pkFunc;
	};

	VeClient();

	virtual ~VeClient();

	virtual void OnConnect();

	virtual void OnConnectFailed(DisconnectType eType);

	virtual void OnDisconnect(DisconnectType eType);

	virtual void ProcessUserEvent(VeUInt8 u8Event, RakNet::BitStream& kStream);

	void Disconnect();

protected:
	friend class LocalFunctionCaller;

	friend void Create_S(lua_State* pkState, const VeChar8* pcPath);

	friend void Connect_S(lua_State* pkState, const VeChar8* pcServerIp,
		VeUInt16 u16Port, const VeChar8* pcPassword, const VeChar8* pcCallback);

	void OnCallFunc(RakNet::BitStream& kStream);

	void OnResCallFunc(RakNet::BitStream& kStream);

	void OnEntLinked(RakNet::BitStream& kStream);

	void ReadUpdate(RakNet::BitStream& kIn, VeNetEntity::DataEntity& kData);

	void OnEntUpdated(RakNet::BitStream& kStream);

	void GetEntity(lua_State* pkState, const VeChar8* pcName);

	VeInt32 RetParamBase(lua_State* pkState, VeNetEntity::DataEntity& kData);

	VeInt32 RetParamClient(lua_State* pkState, VeNetEntity::DataEntity& kData);

	VeInt32 RetParam(lua_State* pkState, VeNetEntity::DataEntity& kData);

	void CreateLuaData(lua_State* pkState, VeNetEntity::DataEntity& kEntity);

	void PushLuaData(lua_State* pkState, VeNetEntity::DataEntity& kEntity);

	static VeInt32 OnCallFinished(lua_State* pkState);

	static VeInt32 CallBaseFunction(lua_State* pkState);

	static VeInt32 CallLocalFunction(lua_State* pkState);

	static VeInt32 OnCallLocalFinished(lua_State* pkState);

	VeString m_kCallback;
	VeEntityManagerClient m_kEntityMgr;
	VeMap<VeUInt32,FuncCall> m_kLuaCallMap;

};

namespace VeLuaBind
{
	VeLuaClassEnumFuncDef(VE_POWER_API, VeClient, DisconnectType);
}

class VE_POWER_API VeClientManager : public VeSingleton<VeClientManager>, public VeTickThread::TickListener
{
public:
	VeClientManager();

	~VeClientManager();

	VE_INLINE VeUInt32 GetClientNumber();

	VE_INLINE VeUInt32 GetAliveClientNumber();

	bool AddClient(const VeClientBasePtr& spClient);

	VeClientBasePtr GetClient(const VeChar8* pcClient);

	bool ConnectSync(const VeChar8* pcClient, const VeChar8* pcServerIp,
		VeUInt16 u16Port, const VeChar8* pcPassword = NULL);

	bool ConnectSync(const VeClientBasePtr& spClient, const VeChar8* pcServerIp,
		VeUInt16 u16Port, const VeChar8* pcPassword = NULL);

	bool ConnectAsync(const VeChar8* pcClient, const VeChar8* pcServerIp,
		VeUInt16 u16Port, const VeChar8* pcPassword = NULL);

	bool ConnectAsync(const VeClientBasePtr& spClient, const VeChar8* pcServerIp,
		VeUInt16 u16Port, const VeChar8* pcPassword = NULL);

	bool Disconnect(const VeChar8* pcClient);

	bool Disconnect(const VeClientBasePtr& spClient);

	void Start();

	void End();

	virtual void Update();

	virtual void Tick();

protected:
	VeTickThread m_kThread;
	VeThread::Mutex m_kMutex;
	VeStringMap<VeClientBasePtr> m_kClientMap;
	VeRefList<VeClientBase*> m_kOffList;
	VeRefList<VeClientBase*> m_kFGList;
	VeRefList<VeClientBase*> m_kBGList;
	VeRefList<VeClientBase*> m_kTurnList;

};

#define g_pClientManager VeClientManager::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeClientBase.inl"
#endif
