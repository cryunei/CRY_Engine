#pragma once


#include <windows.h>
#include <string>


//=====================================================================================================================
// @brief	ToWstring
//=====================================================================================================================
inline std::wstring ToWstring( const std::string& Str )
{

    int wide_size = MultiByteToWideChar( CP_UTF8, 0, Str.c_str(), -1, nullptr, 0 );

    std::wstring wStr( wide_size, 0 );

    MultiByteToWideChar( CP_UTF8, 0, Str.c_str(), -1, &wStr[ 0 ], wide_size );

    return wStr;
}
