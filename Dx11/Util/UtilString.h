#pragma once


#include <codecvt>
#include <locale>
#include <string>


inline std::wstring ToWstring( const std::string& Str )
{
    std::wstring_convert< std::codecvt_utf8_utf16< wchar_t > > converter;

    return converter.from_bytes( Str );
}
