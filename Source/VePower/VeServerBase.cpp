////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeServerBase.cpp
//  Version:     v1.00
//  Created:     15/10/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeServerBase.inl"
#endif

#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>

using namespace RakNet;

//--------------------------------------------------------------------------
VeClientAgent::VeClientAgent(VeServerBase* pkParent,
	const RakNet::SystemAddress& kAddress) : m_pkParent(pkParent)
{
	m_kNode.m_tContent = this;
	m_pkAddress = new (VeMalloc(sizeof(SystemAddress))) SystemAddress(kAddress);
}
//--------------------------------------------------------------------------
VeClientAgent::~VeClientAgent()
{
	VeFree(m_pkAddress);
}
//--------------------------------------------------------------------------
VeUInt32 VeClientAgent::GetAddressID()
{
	return (VeUInt32)SystemAddress::ToInteger(*m_pkAddress);
}
//--------------------------------------------------------------------------
const VeChar8* VeClientAgent::GetAddress()
{
	return m_pkAddress->ToString(true);
}
//--------------------------------------------------------------------------
void VeClientAgent::SendPacket(const RakNet::BitStream& kStream)
{
	VE_ASSERT(m_pkParent->m_pkPeer);
	m_pkParent->m_pkPeer->Send(&kStream, MEDIUM_PRIORITY, RELIABLE_SEQUENCED, 0, *m_pkAddress, false);
}
//--------------------------------------------------------------------------
VeServerBase::VeServerBase(const InitData& kData) : m_eState(STATE_NULL)
	, m_kName(kData.m_kName), m_u16Port(kData.m_u16Port)
	, m_u16MaxConnections(kData.m_u16Max), m_u32TimeOut(kData.m_u32TimeOut)
	, m_kPassword(kData.m_kPassword), m_pkPeer(NULL)
{
	VeChar8 acBuffer[1024];
	VeStrcpy(acBuffer, kData.m_kPath);
	VeChar8* pcContent;
	const VeChar8* pcTemp = VeStrtok(acBuffer, ";", &pcContent);
	while(pcTemp)
	{
		m_kPath.PushBack(pcTemp);
		pcTemp = VeStrtok(NULL, ";", &pcContent);
	}
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
VeServerBase::~VeServerBase()
{

}
//--------------------------------------------------------------------------
VeUInt32 VeServerBase::GetGuidFromAddress()
{
	return m_pkPeer ? (VeUInt32)RakNetGUID::ToUint32(
		m_pkPeer->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS)) : 0;
}
//--------------------------------------------------------------------------
void VeServerBase::GetSocketsAddress(VeVector<VeString>& kOut)
{
	kOut.Clear();
	if(m_pkPeer)
	{
		DataStructures::List<RakNetSocket2*> kSockets;
		m_pkPeer->GetSockets(kSockets);
		for(VeUInt32 i(0); i < kSockets.Size(); ++i)
		{
			kOut.PushBack(kSockets[i]->GetBoundAddress().ToString(true));
		}
	}
}
//--------------------------------------------------------------------------
void VeServerBase::GetServiceIP(VeVector<VeString>& kOut)
{
	kOut.Clear();
	if(m_pkPeer)
	{
		for(VeUInt32 i(0); i < m_pkPeer->GetNumberOfAddresses(); ++i)
		{
			kOut.PushBack(m_pkPeer->GetLocalIP(i));
		}
	}
}
//--------------------------------------------------------------------------
void VeServerBase::AddToBanList(const VeChar8* pcHost)
{
	if(m_pkPeer)
	{
		m_pkPeer->AddToBanList(pcHost);
	}
}
//--------------------------------------------------------------------------
void VeServerBase::RemoveFromBanList(const VeChar8* pcHost)
{
	if(m_pkPeer)
	{
		m_pkPeer->RemoveFromBanList(pcHost);
	}
}
//--------------------------------------------------------------------------
void VeServerBase::ClearBanList()
{
	if(m_pkPeer)
	{
		m_pkPeer->ClearBanList();
	}
}
//--------------------------------------------------------------------------
bool VeServerBase::IsBanned(const VeChar8* pcHost)
{
	if(m_pkPeer)
	{
		return m_pkPeer->IsBanned(pcHost);
	}
	return false;
}
//--------------------------------------------------------------------------
void VeServerBase::Start()
{
	m_pkPeer = RakPeerInterface::GetInstance();
	if(m_kPassword != "null")
	{
		m_pkPeer->SetIncomingPassword(m_kPassword, (VeInt32)(m_kPassword.Length()));
	}
	else
	{
		m_pkPeer->SetIncomingPassword(NULL, 0);
	}
	m_pkPeer->SetTimeoutTime(m_u32TimeOut, UNASSIGNED_SYSTEM_ADDRESS);
    SocketDescriptor sd(m_u16Port, AF_UNSPEC);
	if(m_pkPeer->Startup(m_u16MaxConnections, &sd, 1) == RAKNET_STARTED)
	{
		((RakPeerInterface*)m_pkPeer)->SetMaximumIncomingConnections(m_u16MaxConnections);
		((RakPeerInterface*)m_pkPeer)->SetOccasionalPing(true);
		((RakPeerInterface*)m_pkPeer)->SetUnreliableTimeout(1000);
		m_eState = STATE_RUNNING;
		OnStart();
	}
	else
	{
		RakPeerInterface::DestroyInstance(m_pkPeer);
		m_pkPeer = NULL;
		m_eState = STATE_NULL;
	}
}
//--------------------------------------------------------------------------
void VeServerBase::End()
{
	OnEnd();
	RakPeerInterface::DestroyInstance(m_pkPeer);
	m_pkPeer = NULL;
	m_eState = STATE_NULL;
}
//--------------------------------------------------------------------------
void VeServerBase::Connect(const RakNet::SystemAddress& kAddress)
{
	VeUInt32 u32ClientID = (VeUInt32)SystemAddress::ToInteger(kAddress);
	if(!m_kClientAgentMap.Find(u32ClientID))
	{
		VeClientAgentPtr spAgent = CreateClientAgent(kAddress);
		if(spAgent)
		{
			m_kClientAgentMap[u32ClientID] = spAgent;
			m_kClientAgentList.AttachBack(spAgent->m_kNode);
			spAgent->OnConnect();
		}
	}
}
//--------------------------------------------------------------------------
void VeServerBase::Disconnect(DisconnectType eType,
	const RakNet::SystemAddress& kAddress)
{
	VeUInt32 u32ClientID = (VeUInt32)SystemAddress::ToInteger(kAddress);
	VeClientAgentPtr* pspkIter = m_kClientAgentMap.Find(u32ClientID);
	if(pspkIter)
	{
		(*pspkIter)->OnDisconnect();
		m_kClientAgentMap.Remove(u32ClientID);
	}
}
//--------------------------------------------------------------------------
void VeServerBase::Update()
{
	for(Packet* pkPacket = m_pkPeer->Receive(); pkPacket;
		m_pkPeer->DeallocatePacket(pkPacket), pkPacket = m_pkPeer->Receive())
	{
		BitStream kStream((unsigned char*)pkPacket->data, pkPacket->length, false);
		VeUInt8 u8Event;
		kStream >> u8Event;
		switch(u8Event)
		{
		case ID_DISCONNECTION_NOTIFICATION:
			Disconnect(DIS_NOTIFICATION, pkPacket->systemAddress);
			break;
		case ID_NEW_INCOMING_CONNECTION:
			Connect(pkPacket->systemAddress);
			break;
		case ID_CONNECTION_LOST:
			Disconnect(DIS_CONNECTION_LOST, pkPacket->systemAddress);
			break;
		default:
			{
				VeUInt32 u32ClientID = (VeUInt32)SystemAddress::ToInteger(pkPacket->systemAddress);
				VeClientAgentPtr* pspkIter = m_kClientAgentMap.Find(u32ClientID);
				if(pspkIter)
				{
					(*pspkIter)->ProcessUserEvent(u8Event, kStream);
				}
			}
			break;
		}
	}

	OnUpdate();
}
//--------------------------------------------------------------------------
VeClientAgentPtr VeServerBase::CreateClientAgent(
	const RakNet::SystemAddress& kAddress)
{
	return VE_NEW VeClientAgent(this, kAddress);
}
//--------------------------------------------------------------------------
VeServerManager::VeServerManager()
{

}
//--------------------------------------------------------------------------
VeServerManager::~VeServerManager()
{
	EndServers();
}
//--------------------------------------------------------------------------
bool VeServerManager::StartServer(VeServerBase* pkServer)
{
	if(pkServer && !(pkServer->m_kNode.IsAttach()))
	{
		if(!m_kServerMap.Find(pkServer->GetName()))
		{
			VeServerBasePtr spServer = pkServer;
			spServer->Start();
			if(spServer->GetState() == VeServerBase::STATE_RUNNING)
			{
				m_kServerMap[spServer->GetName()] = spServer;
				m_kServerBase.AttachBack(spServer->m_kNode);
				return true;
			}
		}
	}
	return false;
}
//--------------------------------------------------------------------------
void VeServerManager::Update()
{
	m_kServerBase.BeginIterator();
	while(!m_kServerBase.IsEnd())
	{
		VeServerBase* pkServer = m_kServerBase.GetIterNode()->m_tContent;
		m_kServerBase.Next();
		pkServer->Update();
		if(pkServer->GetState() != VeServerBase::STATE_RUNNING)
		{
			pkServer->m_kNode.Detach();
			m_kServerMap.Remove(pkServer->GetName());
		}
	}
}
//--------------------------------------------------------------------------
void VeServerManager::EndServer(const VeChar8* pcServer)
{
	VeServerBasePtr* pspServer = m_kServerMap.Find(pcServer);
	if(pspServer)
	{
		(*pspServer)->End();
		(*pspServer)->m_kNode.Detach();
		m_kServerMap.Remove(pcServer);
	}
}
//--------------------------------------------------------------------------
void VeServerManager::EndServers()
{
	m_kServerBase.BeginIterator();
	while(!m_kServerBase.IsEnd())
	{
		VeServerBase* pkServer = m_kServerBase.GetIterNode()->m_tContent;
		m_kServerBase.Next();
		pkServer->End();
	}
	m_kServerBase.Clear();
	m_kServerMap.Clear();
}
//--------------------------------------------------------------------------
VeServerBase* VeServerManager::GetServer(const VeChar8* pcServer)
{
	VeServerBasePtr* pspServer = m_kServerMap.Find(pcServer);
	if(pspServer)
	{
		return *pspServer;
	}
	else
	{
		return NULL;
	}
}
//--------------------------------------------------------------------------
