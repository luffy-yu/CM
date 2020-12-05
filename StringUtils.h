#pragma once
#include <iostream>
using std::string;
using std::wstring;

/// <summary>
/// wstring to string
/// </summary>
/// <param name="ws"></param>
/// <returns></returns>
string ws2s(const wstring& ws);

/// <summary>
/// string to wstring
/// </summary>
/// <param name="ws"></param>
/// <returns></returns>
wstring s2ws(const string& s);