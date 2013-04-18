#pragma once 
#include "UItype.h"
#include <string>
std::wstring UI_API AnsiToWstring(const char* src , int len);
std::wstring UI_API AnsiToWstring(const std::string& str);