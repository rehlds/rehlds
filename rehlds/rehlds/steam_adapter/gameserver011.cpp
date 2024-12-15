//=============================================================================
//
// Versioned interface adapter ISteamGameServer for rehlds api
//
//=============================================================================

#include "precompiled.h"

#include "steam/steam_api.h"
#include "steam/steam_gameserver.h"

class CAdapterSteamGameServer011: public ISteamGameServer011
{
public:
	virtual bool InitGameServer(uint32 unIP, uint16 usGamePort, uint16 usQueryPort, uint32 unFlags, AppId_t nGameAppId, const char *pchVersionString);
	virtual void SetProduct(const char *pszProduct);
	virtual void SetGameDescription(const char *pszGameDescription);
	virtual void SetModDir(const char *pszModDir);
	virtual void SetDedicatedServer(bool bDedicated);
	virtual void LogOn(const char *pszAccountName, const char *pszPassword);
	virtual void LogOnAnonymous();
	virtual void LogOff();
	virtual bool BLoggedOn();
	virtual bool BSecure();
	virtual CSteamID GetSteamID();
	virtual bool WasRestartRequested();
	virtual void SetMaxPlayerCount(int cPlayersMax);
	virtual void SetBotPlayerCount(int cBotplayers);
	virtual void SetServerName(const char *pszServerName);
	virtual void SetMapName(const char *pszMapName);
	virtual void SetPasswordProtected(bool bPasswordProtected);
	virtual void SetSpectatorPort(uint16 unSpectatorPort);
	virtual void SetSpectatorServerName(const char *pszSpectatorServerName);
	virtual void ClearAllKeyValues();
	virtual void SetKeyValue(const char *pKey, const char *pValue);
	virtual void SetGameTags(const char *pchGameTags);
	virtual void SetGameData(const char *pchGameData);
	virtual void SetRegion(const char *pszRegion);
	virtual bool SendUserConnectAndAuthenticate(uint32 unIPClient, const void *pvAuthBlob, uint32 cubAuthBlobSize, CSteamID *pSteamIDUser);
	virtual CSteamID CreateUnauthenticatedUserConnection();
	virtual void SendUserDisconnect(CSteamID steamIDUser);
	virtual bool BUpdateUserData(CSteamID steamIDUser, const char *pchPlayerName, uint32 uScore);
	virtual HAuthTicket GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket);
	virtual EBeginAuthSessionResult BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID);
	virtual void EndAuthSession(CSteamID steamID);
	virtual void CancelAuthTicket(HAuthTicket hAuthTicket);
	virtual EUserHasLicenseForAppResult UserHasLicenseForApp(CSteamID steamID, AppId_t appID);
	virtual bool RequestUserGroupStatus(CSteamID steamIDUser, CSteamID steamIDGroup);
	virtual void GetGameplayStats();
	virtual SteamAPICall_t GetServerReputation();
	virtual uint32 GetPublicIP();
	virtual bool HandleIncomingPacket(const void *pData, int cbData, uint32 srcIP, uint16 srcPort);
	virtual int GetNextOutgoingPacket(void *pOut, int cbMaxOut, uint32 *pNetAdr, uint16 *pPort);
	virtual void EnableHeartbeats(bool bActive);
	virtual void SetHeartbeatInterval(int iHeartbeatInterval);
	virtual void ForceHeartbeat();
	virtual SteamAPICall_t AssociateWithClan(CSteamID steamIDClan);
	virtual SteamAPICall_t ComputeNewPlayerCompatibility(CSteamID steamIDNewPlayer);
};

ISteamGameServer011 *SteamGameServer_v011()
{
	static CAdapterSteamGameServer011 gSteamGameServer011Singleton{};
	return &gSteamGameServer011Singleton;
}

bool CAdapterSteamGameServer011::InitGameServer(uint32_t unIP, uint16_t usGamePort, uint16_t usQueryPort, uint32_t unFlags, AppId_t nGameAppId, const char *pchVersionString)
{
	return SteamGameServer()->InitGameServer(unIP, usGamePort, usQueryPort, unFlags, nGameAppId, pchVersionString);
}

void CAdapterSteamGameServer011::SetProduct(const char *pszProduct)
{
	SteamGameServer()->SetProduct(pszProduct);
}

void CAdapterSteamGameServer011::SetGameDescription(const char *pszGameDescription)
{
	SteamGameServer()->SetGameDescription(pszGameDescription);
}

void CAdapterSteamGameServer011::SetModDir(const char *pszModDir)
{
	SteamGameServer()->SetModDir(pszModDir);
}

void CAdapterSteamGameServer011::SetDedicatedServer(bool bDedicated)
{
	SteamGameServer()->SetDedicatedServer(bDedicated);
}

void CAdapterSteamGameServer011::LogOn(const char *pszAccountName, const char *pszPassword)
{
	const char *pszToken = pszAccountName;
	SteamGameServer()->LogOn(pszToken);
}

void CAdapterSteamGameServer011::LogOnAnonymous()
{
	SteamGameServer()->LogOnAnonymous();
}

void CAdapterSteamGameServer011::LogOff()
{
	SteamGameServer()->LogOff();
}

bool CAdapterSteamGameServer011::BLoggedOn()
{
	return SteamGameServer()->BLoggedOn();
}

bool CAdapterSteamGameServer011::BSecure()
{
	return SteamGameServer()->BSecure();
}

CSteamID CAdapterSteamGameServer011::GetSteamID()
{
	return SteamGameServer()->GetSteamID();
}

bool CAdapterSteamGameServer011::WasRestartRequested()
{
	return SteamGameServer()->WasRestartRequested();
}

void CAdapterSteamGameServer011::SetMaxPlayerCount(int cPlayersMax)
{
	SteamGameServer()->SetMaxPlayerCount(cPlayersMax);
}

void CAdapterSteamGameServer011::SetBotPlayerCount(int cBotplayers)
{
	SteamGameServer()->SetBotPlayerCount(cBotplayers);
}

void CAdapterSteamGameServer011::SetServerName(const char *pszServerName)
{
	SteamGameServer()->SetServerName(pszServerName);
}

void CAdapterSteamGameServer011::SetMapName(const char *pszMapName)
{
	SteamGameServer()->SetMapName(pszMapName);
}

void CAdapterSteamGameServer011::SetPasswordProtected(bool bPasswordProtected)
{
	SteamGameServer()->SetPasswordProtected(bPasswordProtected);
}

void CAdapterSteamGameServer011::SetSpectatorPort(uint16_t unSpectatorPort)
{
	SteamGameServer()->SetSpectatorPort(unSpectatorPort);
}

void CAdapterSteamGameServer011::SetSpectatorServerName(const char *pszSpectatorServerName)
{
	SteamGameServer()->SetSpectatorServerName(pszSpectatorServerName);
}

void CAdapterSteamGameServer011::ClearAllKeyValues()
{
	SteamGameServer()->ClearAllKeyValues();
}

void CAdapterSteamGameServer011::SetKeyValue(const char *pKey, const char *pValue)
{
	SteamGameServer()->SetKeyValue(pKey, pValue);
}

void CAdapterSteamGameServer011::SetGameTags(const char *pchGameTags)
{
	SteamGameServer()->SetGameTags(pchGameTags);
}

void CAdapterSteamGameServer011::SetGameData(const char *pchGameData)
{
	SteamGameServer()->SetGameData(pchGameData);
}

void CAdapterSteamGameServer011::SetRegion(const char *pszRegion)
{
	SteamGameServer()->SetRegion(pszRegion);
}

bool CAdapterSteamGameServer011::SendUserConnectAndAuthenticate(uint32_t unIPClient, const void *pvAuthBlob, uint32_t cubAuthBlobSize, CSteamID *pSteamIDUser)
{
	return SteamGameServer()->SendUserConnectAndAuthenticate(unIPClient, pvAuthBlob, cubAuthBlobSize, pSteamIDUser);
}

CSteamID CAdapterSteamGameServer011::CreateUnauthenticatedUserConnection()
{
	return SteamGameServer()->CreateUnauthenticatedUserConnection();
}

void CAdapterSteamGameServer011::SendUserDisconnect(CSteamID steamIDUser)
{
	SteamGameServer()->SendUserDisconnect(steamIDUser);
}

bool CAdapterSteamGameServer011::BUpdateUserData(CSteamID steamIDUser, const char *pchPlayerName, uint32_t uScore)
{
	return SteamGameServer()->BUpdateUserData(steamIDUser, pchPlayerName, uScore);
}

HAuthTicket CAdapterSteamGameServer011::GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32_t *pcbTicket)
{
	SteamNetworkingIdentity snidl{};
	snidl.SetSteamID64(GetSteamID().ConvertToUint64());
	return SteamGameServer()->GetAuthSessionTicket(pTicket, cbMaxTicket, pcbTicket, &snidl);
}

EBeginAuthSessionResult CAdapterSteamGameServer011::BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
{
	return SteamGameServer()->BeginAuthSession(pAuthTicket, cbAuthTicket, steamID);
}

void CAdapterSteamGameServer011::EndAuthSession(CSteamID steamID)
{
	SteamGameServer()->EndAuthSession(steamID);
}

void CAdapterSteamGameServer011::CancelAuthTicket(HAuthTicket hAuthTicket)
{
	SteamGameServer()->CancelAuthTicket(hAuthTicket);
}

EUserHasLicenseForAppResult CAdapterSteamGameServer011::UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
{
	return SteamGameServer()->UserHasLicenseForApp(steamID, appID);
}

bool CAdapterSteamGameServer011::RequestUserGroupStatus(CSteamID steamIDUser, CSteamID steamIDGroup)
{
	return SteamGameServer()->RequestUserGroupStatus(steamIDUser, steamIDGroup);
}

void CAdapterSteamGameServer011::GetGameplayStats()
{
	SteamGameServer()->GetGameplayStats();
}

SteamAPICall_t CAdapterSteamGameServer011::GetServerReputation()
{
	return SteamGameServer()->GetServerReputation();
}

uint32_t CAdapterSteamGameServer011::GetPublicIP()
{
	SteamIPAddress_t publicIP = SteamGameServer()->GetPublicIP();
	return publicIP.m_unIPv4;
}

bool CAdapterSteamGameServer011::HandleIncomingPacket(const void *pData, int cbData, uint32_t srcIP, uint16_t srcPort)
{
	return SteamGameServer()->HandleIncomingPacket(pData, cbData, srcIP, srcPort);
}

int CAdapterSteamGameServer011::GetNextOutgoingPacket(void *pOut, int cbMaxOut, uint32_t *pNetAdr, uint16_t *pPort)
{
	return SteamGameServer()->GetNextOutgoingPacket(pOut, cbMaxOut, pNetAdr, pPort);
}

void CAdapterSteamGameServer011::EnableHeartbeats(bool bActive)
{
	SteamGameServer()->SetAdvertiseServerActive(bActive);
}

void CAdapterSteamGameServer011::SetHeartbeatInterval(int iHeartbeatInterval)
{
	SteamGameServer()->SetMasterServerHeartbeatInterval(iHeartbeatInterval);
}

void CAdapterSteamGameServer011::ForceHeartbeat()
{
	SteamGameServer()->ForceMasterServerHeartbeat();
}

SteamAPICall_t CAdapterSteamGameServer011::AssociateWithClan(CSteamID steamIDClan)
{
	return SteamGameServer()->AssociateWithClan(steamIDClan);
}

SteamAPICall_t CAdapterSteamGameServer011::ComputeNewPlayerCompatibility(CSteamID steamIDNewPlayer)
{
	return SteamGameServer()->ComputeNewPlayerCompatibility(steamIDNewPlayer);
}
