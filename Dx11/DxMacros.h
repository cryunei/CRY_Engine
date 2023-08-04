#pragma once


//=====================================================================================================================
// @brief	SAFE_RELEASE
//=====================================================================================================================
#define SAFE_RELEASE( x ) if( x ) { x->Release(); x = nullptr; }

//=====================================================================================================================
// @brief	SAFE_RELEASE_COMPTR
//=====================================================================================================================
#define SAFE_RELEASE_COMPTR( x ) if( x.Get() ) { x->Release(); x = nullptr; }

//=====================================================================================================================
// @brief	CLASS_DEFAULT_BODY
//=====================================================================================================================
#define CLASS_DEFAULT_BODY( ClassName ) \
public: \
    ClassName( const ClassName& Other ) = default; \
    ClassName( ClassName&& Other ) noexcept = default; \
    ClassName& operator=( const ClassName& Other ) = default; \
    ClassName& operator=( ClassName&& Other ) noexcept = default;