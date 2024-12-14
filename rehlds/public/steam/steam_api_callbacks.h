//====== Copyright Valve Corporation, All rights reserved. ====================
//
// Steamworks SDK minimal include
//
// Defines the minimal set of things we need to use register for any callback.
//
//=============================================================================

#ifndef STEAM_API_CALLBACKS_H
#define STEAM_API_CALLBACKS_H

//
// Internal stuff used for the standard, higher-level callback mechanism
//

// Internal functions used by the utility CCallback objects to receive callbacks
S_API void S_CALLTYPE SteamAPI_RegisterCallback( class CCallbackBase *pCallback, int iCallback );
S_API void S_CALLTYPE SteamAPI_UnregisterCallback( class CCallbackBase *pCallback );
// Internal functions used by the utility CCallResult objects to receive async call results
S_API void S_CALLTYPE SteamAPI_RegisterCallResult( class CCallbackBase *pCallback, SteamAPICall_t hAPICall );
S_API void S_CALLTYPE SteamAPI_UnregisterCallResult( class CCallbackBase *pCallback, SteamAPICall_t hAPICall );

#define _STEAM_CALLBACK_OFFSETOF( type, member ) ( (size_t)( (char *)&( (type *)0 )->member ) )
#define _STEAM_CALLBACK_AUTO_HOOK( thisclass, func, param )
#define _STEAM_CALLBACK_HELPER( _1, _2, SELECTED, ... )		_STEAM_CALLBACK_##SELECTED
#define _STEAM_CALLBACK_SELECT( X, Y )						_STEAM_CALLBACK_HELPER X Y
#define _STEAM_CALLBACK_3( extra_code, thisclass, func, param ) \
	struct CCallbackInternal_ ## func : private CCallbackImpl< sizeof( param ) > { \
		CCallbackInternal_ ## func () { extra_code SteamAPI_RegisterCallback( this, param::k_iCallback ); } \
		CCallbackInternal_ ## func ( const CCallbackInternal_ ## func & ) { extra_code SteamAPI_RegisterCallback( this, param::k_iCallback ); } \
		CCallbackInternal_ ## func & operator=( const CCallbackInternal_ ## func & ) { return *this; } \
		private: virtual void Run( void *pvParam ) S_OVERRIDE { _STEAM_CALLBACK_AUTO_HOOK( thisclass, func, param ) \
			thisclass *pOuter = reinterpret_cast<thisclass*>( reinterpret_cast<char*>(this) - _STEAM_CALLBACK_OFFSETOF( thisclass, m_steamcallback_ ## func ) ); \
			pOuter->func( reinterpret_cast<param*>( pvParam ) ); \
		} \
	} m_steamcallback_ ## func ; void func( param *pParam )
#define _STEAM_CALLBACK_4( _, thisclass, func, param, var ) \
	CCallback< thisclass, param > var; void func( param *pParam )
#define _STEAM_CALLBACK_GS( _, thisclass, func, param, var ) \
	CCallback< thisclass, param, true > var; void func( param *pParam )

#ifndef API_GEN

template< class T, class P >
inline CCallResult<T, P>::CCallResult()
{
	m_hAPICall = k_uAPICallInvalid;
	m_pObj = nullptr;
	m_Func = nullptr;
	m_iCallback = P::k_iCallback;
}

template< class T, class P >
inline void CCallResult<T, P>::Set( SteamAPICall_t hAPICall, T *p, func_t func )
{
	if ( m_hAPICall )
		SteamAPI_UnregisterCallResult( this, m_hAPICall );

	m_hAPICall = hAPICall;
	m_pObj = p;
	m_Func = func;

	if ( hAPICall )
		SteamAPI_RegisterCallResult( this, hAPICall );
}

template< class T, class P >
inline bool CCallResult<T, P>::IsActive() const
{
	return (m_hAPICall != k_uAPICallInvalid);
}

template< class T, class P >
inline void CCallResult<T, P>::Cancel()
{
	if ( m_hAPICall != k_uAPICallInvalid )
	{
		SteamAPI_UnregisterCallResult( this, m_hAPICall );
		m_hAPICall = k_uAPICallInvalid;
	}
}

template< class T, class P >
inline CCallResult<T, P>::~CCallResult()
{
	Cancel();
}

template< class T, class P >
inline void CCallResult<T, P>::Run( void *pvParam )
{
	m_hAPICall = k_uAPICallInvalid; // caller unregisters for us
	(m_pObj->*m_Func)((P *)pvParam, false);
}

template< class T, class P >
inline void CCallResult<T, P>::Run( void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall )
{
	if ( hSteamAPICall == m_hAPICall )
	{
		m_hAPICall = k_uAPICallInvalid; // caller unregisters for us
		(m_pObj->*m_Func)((P *)pvParam, bIOFailure);
	}
}

template< class T, class P, bool bGameserver >
inline CCallback< T, P, bGameserver >::CCallback( T *pObj, func_t func )
	: m_pObj( nullptr ), m_Func( nullptr )
{
	if ( bGameserver )
	{
		this->SetGameserverFlag();
	}
	Register( pObj, func );
}

template< class T, class P, bool bGameserver >
inline void CCallback< T, P, bGameserver >::Register( T *pObj, func_t func )
{
	if ( !pObj || !func )
		return;

	if ( this->m_nCallbackFlags & CCallbackBase::k_ECallbackFlagsRegistered )
		Unregister();

	m_pObj = pObj;
	m_Func = func;
	// SteamAPI_RegisterCallback sets k_ECallbackFlagsRegistered

#ifdef REHLDS_SELF
	CRehldsPlatformHolder::get()->SteamAPI_RegisterCallback(this, P::k_iCallback);
#else
	SteamAPI_RegisterCallback(this, P::k_iCallback);
#endif // REHLDS_SELF
}

template< class T, class P, bool bGameserver >
inline void CCallback< T, P, bGameserver >::Unregister()
{
	// SteamAPI_UnregisterCallback removes k_ECallbackFlagsRegistered
	SteamAPI_UnregisterCallback( this );
}

template< class T, class P, bool bGameserver >
inline void CCallback< T, P, bGameserver >::Run( void *pvParam )
{
	(m_pObj->*m_Func)((P *)pvParam);
}

#endif // #ifndef API_GEN

#endif // STEAM_API_CALLBACKS_H
