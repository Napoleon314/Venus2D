////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeServerBase.h
//  Version:     v1.00
//  Created:     15/10/2014 by Napoleon
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
	struct SystemAddress;
	class BitStream;
}

VeSmartPointer(VeServerBase);
VeSmartPointer(VeClientAgent);

class VE_POWER_API VeClientAgent : public VeRefObject
{
public:
	VeClientAgent(VeServerBase* pkParent, const RakNet::SystemAddress& kAddress);

	virtual ~VeClientAgent();

	VeUInt32 GetAddressID();

	const VeChar8* GetAddress();

	void SendPacket(const RakNet::BitStream& kStream);

	virtual void OnConnect() {}

	virtual void OnDisconnect() {}

	virtual void ProcessUserEvent(VeUInt8 u8Event, RakNet::BitStream& kStream) {}

protected:
	friend class VeServerBase;

	VeRefNode<VeClientAgent*> m_kNode;
	VeServerBase* m_pkParent;
	RakNet::SystemAddress* m_pkAddress;

};

class VE_POWER_API VeServerBase : public VeRefObject
{
public:
	enum State
	{
		STATE_NULL,
		STATE_RUNNING,
		STATE_NEEDSTOP,
		STATE_MAX
	};

	enum DisconnectType
	{
		DIS_NOTIFICATION,
		DIS_CONNECTION_LOST,
		DIS_MAX
	};

	struct InitData
	{
		VeString m_kName;
		VeString m_kPath;
		VeUInt16 m_u16Port;
		VeUInt16 m_u16Max;
		VeUInt32 m_u32TimeOut;
		VeString m_kPassword;
	};

	VeServerBase(const InitData& kData);

	virtual ~VeServerBase();

	VE_INLINE State GetState();

	VE_INLINE const VeChar8* GetName();

	VE_INLINE VeUInt16 GetPort();

	VE_INLINE VeUInt16 GetMaxConnections();

	VE_INLINE VeUInt32 GetTimeOut();

	VE_INLINE const VeChar8* GetPassword();

	VeUInt32 GetGuidFromAddress();

	void GetSocketsAddress(VeVector<VeString>& kOut);

	void GetServiceIP(VeVector<VeString>& kOut);

	void AddToBanList(const VeChar8* pcHost);

	void RemoveFromBanList(const VeChar8* pcHost);

	void ClearBanList();

	bool IsBanned(const VeChar8* pcHost);
	
	void Start();

	void End();

	void Connect(const RakNet::SystemAddress& kAddress);

	void Disconnect(DisconnectType eType, const RakNet::SystemAddress& kAddress);

	void Update();

	virtual VeClientAgentPtr CreateClientAgent(const RakNet::SystemAddress& kAddress);

	virtual void OnStart() {}

	virtual void OnEnd() {}

	virtual void OnUpdate() {}

protected:
	friend class VeClientAgent;
	friend class VeServerManager;
	VeRefNode<VeServerBase*> m_kNode;
	State m_eState;
	VeString m_kName;
	VeVector<VeString> m_kPath;
	VeUInt16 m_u16Port;
	VeUInt16 m_u16MaxConnections;
	VeUInt32 m_u32TimeOut;
	VeString m_kPassword;
	RakNet::RakPeerInterface* m_pkPeer;

	VeHashMap<VeUInt32, VeClientAgentPtr> m_kClientAgentMap;
	VeRefList<VeClientAgent*> m_kClientAgentList;

};

class VE_POWER_API VeServerManager : public VeSingleton<VeServerManager>
{
public:
	VeServerManager();

	~VeServerManager();

	VE_INLINE VeUInt32 GetServerNumber();

	bool StartServer(VeServerBase* pkServer);

	void Update();

	void EndServer(const VeChar8* pcServer);

	void EndServers();

	VeServerBase* GetServer(const VeChar8* pcServer);

protected:
	VeStringMap<VeServerBasePtr> m_kServerMap;
	VeRefList<VeServerBase*> m_kServerBase;

};

#define g_pServerManager VeServerManager::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeServerBase.inl"
#endif
