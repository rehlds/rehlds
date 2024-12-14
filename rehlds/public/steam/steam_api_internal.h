//====== Copyright Valve Corporation, All rights reserved. ====================
//
// Internal implementation details of the steamworks SDK.
//
// You should be able to figure out how to use the SDK by reading
// steam_api_common.h, and should not need to understand anything in here.
//
//-----------------------------------------------------------------------------

#ifdef STEAM_CALLBACK_BEGIN
#error "This file should only be included from steam_api_common.h"
#endif

#include <string.h>

// Internal functions used to locate/create interfaces
S_API HSteamPipe S_CALLTYPE SteamAPI_GetHSteamPipe();
S_API HSteamUser S_CALLTYPE SteamAPI_GetHSteamUser();
S_API HSteamPipe S_CALLTYPE SteamGameServer_GetHSteamPipe();
S_API HSteamUser S_CALLTYPE SteamGameServer_GetHSteamUser();
S_API void *S_CALLTYPE SteamInternal_ContextInit( void *pContextInitData );
S_API void *S_CALLTYPE SteamInternal_CreateInterface( const char *ver );
S_API void *S_CALLTYPE SteamInternal_FindOrCreateUserInterface( HSteamUser hSteamUser, const char *pszVersion );
S_API void *S_CALLTYPE SteamInternal_FindOrCreateGameServerInterface( HSteamUser hSteamUser, const char *pszVersion );

// Macro used to define a type-safe accessor that will always return the version
// of the interface of the *header file* you are compiling with!  We also bounce
// through a safety function that checks for interfaces being created or destroyed.
//
// SteamInternal_ContextInit takes a base pointer for the equivalent of
// struct { void (*pFn)(void* pCtx); uintptr_t counter; void *ptr; }
// Do not change layout or add non-pointer aligned data!
#define STEAM_DEFINE_INTERFACE_ACCESSOR( type, name, expr, kind, version ) \
	inline void S_CALLTYPE SteamInternal_Init_ ## name( type *p ) { *p = (type)( expr ); } \
	STEAM_CLANG_ATTR( "interface_accessor_kind:" kind ";interface_accessor_version:" version ";" ) \
	inline type name() { \
		static void* s_CallbackCounterAndContext[ 3 ] = { (void*)&SteamInternal_Init_ ## name, 0, 0 }; \
		return *(type*)SteamInternal_ContextInit( s_CallbackCounterAndContext ); \
	}

#define STEAM_DEFINE_USER_INTERFACE_ACCESSOR( type, name, version ) \
	STEAM_DEFINE_INTERFACE_ACCESSOR( type, name, SteamInternal_FindOrCreateUserInterface( SteamAPI_GetHSteamUser(), version ), "user", version )
#define STEAM_DEFINE_GAMESERVER_INTERFACE_ACCESSOR( type, name, version ) \
	STEAM_DEFINE_INTERFACE_ACCESSOR( type, name, SteamInternal_FindOrCreateGameServerInterface( SteamGameServer_GetHSteamUser(), version ), "gameserver", version )

// structure that contains client callback data
// see callbacks documentation for more details
#if defined( VALVE_CALLBACK_PACK_SMALL )
#pragma pack( push, 4 )
#elif defined( VALVE_CALLBACK_PACK_LARGE )
#pragma pack( push, 8 )
#else
#error steam_api_common.h should define VALVE_CALLBACK_PACK_xxx
#endif

/// Internal structure used in manual callback dispatch
struct CallbackMsg_t
{
	HSteamUser m_hSteamUser; // Specific user to whom this callback applies.
	int m_iCallback; // Callback identifier.  (Corresponds to the k_iCallback enum in the callback structure.)
	uint8 *m_pubParam; // Points to the callback structure
	int m_cubParam; // Size of the data pointed to by m_pubParam
};
#pragma pack( pop )

// Macros to define steam callback structures.  Used internally for debugging
#ifdef STEAM_CALLBACK_INSPECTION_ENABLED
	#include "../../clientdll/steam_api_callback_inspection.h"
#else
	#define STEAM_CALLBACK_BEGIN( callbackname, callbackid )	struct callbackname { enum { k_iCallback = callbackid };
	#define STEAM_CALLBACK_MEMBER( varidx, vartype, varname )	vartype varname ;
	#define STEAM_CALLBACK_MEMBER_ARRAY( varidx, vartype, varname, varcount ) vartype varname [ varcount ];
	#define STEAM_CALLBACK_END(nArgs) };
#endif

// Forward declare all of the Steam interfaces.  (Do we really need to do this?)
class ISteamClient;
class ISteamUser;
class ISteamGameServer;
class ISteamFriends;
class ISteamUtils;
class ISteamMatchmaking;
class ISteamContentServer;
class ISteamMatchmakingServers;
class ISteamUserStats;
class ISteamApps;
class ISteamNetworking;
class ISteamRemoteStorage;
class ISteamScreenshots;
class ISteamMusic;
class ISteamMusicRemote;
class ISteamGameServerStats;
class ISteamPS3OverlayRender;
class ISteamHTTP;
class ISteamController;
class ISteamUGC;
class ISteamHTMLSurface;
class ISteamInventory;
class ISteamVideo;
class ISteamParentalSettings;
class ISteamGameSearch;
class ISteamInput;
class ISteamParties;
class ISteamRemotePlay;

// Forward declare types
struct SteamNetworkingIdentity;

//-----------------------------------------------------------------------------
// Purpose: Base values for callback identifiers, each callback must
//			have a unique ID.
//-----------------------------------------------------------------------------
enum { k_iSteamUserCallbacks = 100 };
enum { k_iSteamGameServerCallbacks = 200 };
enum { k_iSteamFriendsCallbacks = 300 };
enum { k_iSteamBillingCallbacks = 400 };
enum { k_iSteamMatchmakingCallbacks = 500 };
enum { k_iSteamContentServerCallbacks = 600 };
enum { k_iSteamUtilsCallbacks = 700 };
enum { k_iSteamAppsCallbacks = 1000 };
enum { k_iSteamUserStatsCallbacks = 1100 };
enum { k_iSteamNetworkingCallbacks = 1200 };
enum { k_iSteamNetworkingSocketsCallbacks = 1220 };
enum { k_iSteamNetworkingMessagesCallbacks = 1250 };
enum { k_iSteamNetworkingUtilsCallbacks = 1280 };
enum { k_iSteamRemoteStorageCallbacks = 1300 };
enum { k_iSteamGameServerItemsCallbacks = 1500 };
enum { k_iSteamGameCoordinatorCallbacks = 1700 };
enum { k_iSteamGameServerStatsCallbacks = 1800 };
enum { k_iSteam2AsyncCallbacks = 1900 };
enum { k_iSteamGameStatsCallbacks = 2000 };
enum { k_iSteamHTTPCallbacks = 2100 };
enum { k_iSteamScreenshotsCallbacks = 2300 };
// NOTE: 2500-2599 are reserved
enum { k_iSteamStreamLauncherCallbacks = 2600 };
enum { k_iSteamControllerCallbacks = 2800 };
enum { k_iSteamUGCCallbacks = 3400 };
enum { k_iSteamStreamClientCallbacks = 3500 };
enum { k_iSteamMusicCallbacks = 4000 };
enum { k_iSteamMusicRemoteCallbacks = 4100 };
enum { k_iSteamGameNotificationCallbacks = 4400 };
enum { k_iSteamHTMLSurfaceCallbacks = 4500 };
enum { k_iSteamVideoCallbacks = 4600 };
enum { k_iSteamInventoryCallbacks = 4700 };
enum { k_ISteamParentalSettingsCallbacks = 5000 };
enum { k_iSteamGameSearchCallbacks = 5200 };
enum { k_iSteamPartiesCallbacks = 5300 };
enum { k_iSteamSTARCallbacks = 5500 };
enum { k_iSteamRemotePlayCallbacks = 5700 };
enum { k_iSteamChatCallbacks = 5900 };
enum { k_iSteamTimelineCallbacks = 6000 };
// NOTE: Internal "IClientXxx" callback IDs go in clientenums.h

// Macros used to annotate various Steamworks interfaces to generate the
// flat API
#ifdef API_GEN
# define STEAM_CLANG_ATTR(ATTR) __attribute__((annotate( ATTR )))
#else
# define STEAM_CLANG_ATTR(ATTR)
#endif

#define STEAM_OUT_STRUCT() STEAM_CLANG_ATTR( "out_struct: ;" )
#define STEAM_OUT_STRING() STEAM_CLANG_ATTR( "out_string: ;" )
#define STEAM_OUT_ARRAY_CALL(COUNTER,FUNCTION,PARAMS) STEAM_CLANG_ATTR( "out_array_call:" #COUNTER "," #FUNCTION "," #PARAMS ";" )
#define STEAM_OUT_ARRAY_COUNT(COUNTER, DESC) STEAM_CLANG_ATTR( "out_array_count:" #COUNTER  ";desc:" #DESC )
#define STEAM_ARRAY_COUNT(COUNTER) STEAM_CLANG_ATTR( "array_count:" #COUNTER ";" )
#define STEAM_ARRAY_COUNT_D(COUNTER, DESC) STEAM_CLANG_ATTR( "array_count:" #COUNTER ";desc:" #DESC )
#define STEAM_BUFFER_COUNT(COUNTER) STEAM_CLANG_ATTR( "buffer_count:" #COUNTER ";" )
#define STEAM_OUT_BUFFER_COUNT(COUNTER) STEAM_CLANG_ATTR( "out_buffer_count:" #COUNTER ";" )
#define STEAM_OUT_STRING_COUNT(COUNTER) STEAM_CLANG_ATTR( "out_string_count:" #COUNTER ";" )
#define STEAM_DESC(DESC) STEAM_CLANG_ATTR("desc:" #DESC ";")
#define STEAM_CALL_RESULT(RESULT_TYPE) STEAM_CLANG_ATTR("callresult:" #RESULT_TYPE ";")
#define STEAM_CALL_BACK(RESULT_TYPE) STEAM_CLANG_ATTR("callback:" #RESULT_TYPE ";")
#define STEAM_FLAT_NAME(NAME) STEAM_CLANG_ATTR("flat_name:" #NAME ";")

class CSteamGameServerAPIContext
{
public:
	CSteamGameServerAPIContext() { Clear(); }
	inline void Clear() { memset( this, 0, sizeof(*this) ); }
	inline bool Init(); // NOTE: This is defined in steam_gameserver.h, to avoid this file having to include everything

	ISteamClient *SteamClient() const					{ return m_pSteamClient; }
	ISteamGameServer *SteamGameServer() const			{ return m_pSteamGameServer; }
	ISteamUtils *SteamGameServerUtils() const			{ return m_pSteamGameServerUtils; }
	ISteamNetworking *SteamGameServerNetworking() const	{ return m_pSteamGameServerNetworking; }
	ISteamGameServerStats *SteamGameServerStats() const	{ return m_pSteamGameServerStats; }
	ISteamHTTP *SteamHTTP() const						{ return m_pSteamHTTP; }
	ISteamInventory *SteamInventory() const				{ return m_pSteamInventory; }
	ISteamUGC *SteamUGC() const							{ return m_pSteamUGC; }

private:
	ISteamClient				*m_pSteamClient;
	ISteamGameServer			*m_pSteamGameServer;
	ISteamUtils					*m_pSteamGameServerUtils;
	ISteamNetworking			*m_pSteamGameServerNetworking;
	ISteamGameServerStats		*m_pSteamGameServerStats;
	ISteamHTTP					*m_pSteamHTTP;
	ISteamInventory				*m_pSteamInventory;
	ISteamUGC					*m_pSteamUGC;
};


