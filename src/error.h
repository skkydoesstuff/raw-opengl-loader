#pragma once

#include <windows.h>

#define LOG(x) do { MessageBoxA(NULL, (x), "Log", MB_OK); } while(0)