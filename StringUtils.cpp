#include "StringUtils.h"

string ws2s(const wstring& ws)
{
    auto t = ws.c_str();
    char* pchar = (char*)t;
    string result = pchar;
    return result;
}

wstring s2ws(const string& s)
{
    auto t = s.c_str();
    wchar_t* pwchar = (wchar_t*)t;
    wstring result = pwchar;
    return result;
}