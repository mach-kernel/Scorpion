// WinAPI stuff

#pragma once

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <vcclr.h>
#include <msclr/marshal.h>

#include "targetver.h"
#include "psapi.h"
#include "Window.h"


#include <cstdio>
#include <vector>

namespace Scorpion
{
	bool EnableDebugPrivilege(bool bEnable);
	bool InjCRT(DWORD PID, System::String^ dllPath, bool PAA);
	bool InjHWEx(DWORD PID, System::String^ dllPath, System::String^ idHook);
	//__declspec(naked) loadDll(void);
}