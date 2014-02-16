#include "Scorpion.h"

namespace Scorpion
{
	bool EnableDebugPrivilege(bool bEnable)
	{
		HANDLE hToken = nullptr;
		LUID luid;

		// Can we TOKEN_ADJUST_PRIVILEGES on the current process?
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken) || 
			!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) return false;

		// Create a new TOKEN_PRIVILEGES object with SeDebugPrivilege enabled (SE_PRIVILEGE)
		TOKEN_PRIVILEGES tP;
		tP.PrivilegeCount = 1;
		tP.Privileges[0].Luid = luid;
		tP.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0; // Ternary operator for passed in bool

		// Return false if we can't adjust our privileges
		if (!AdjustTokenPrivileges(hToken, false, &tP, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) return false;

		return true; 
	}

	bool InjCRT(DWORD PID, String^ dllPath, bool PAA)
	{
		// Let's open a handle to our process
		HANDLE pHandle;
		(PAA) ? pHandle = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_CREATE_THREAD, FALSE, PID) : pHandle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD, FALSE, PID);
		
		if (pHandle == INVALID_HANDLE_VALUE) return false; 

		// Time to change that String into a char*
		char* dllP = (char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(dllPath).ToPointer();

		// Now that we know that our handle is valid, let's grab some memory space
		LPVOID ProcAlloc = LPVOID(VirtualAllocEx(pHandle, nullptr, strlen(dllP), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
		
		// Write the name of the DLL in ProcAlloc
		WriteProcessMemory(pHandle, ProcAlloc, dllP, strlen(dllP), nullptr);

		LPVOID LoadLib = LPVOID(GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA"));

		// Time to make the remote thread:
		HANDLE ret = CreateRemoteThread(pHandle, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLib), ProcAlloc, NULL, NULL);

		// Free memory
		VirtualFreeEx(pHandle, ProcAlloc, 0, MEM_RELEASE);

		// Close handle(s) and tidy up
		CloseHandle(pHandle);
		if (ret == NULL) return false;
		else
		{
			CloseHandle(ret);
			return true;
		}
	}

	bool InjHWEx(DWORD PID, System::String^ dllPath, System::String^ idHook)
	{
		// I hate whomever decided that an inline constructor wasn't a good idea...
		Collections::Generic::Dictionary<System::String^, Tuple<int, System::String^>^> idFunc;

		idFunc.Add("WH_CALLWNDPROC",     gcnew Tuple<int, System::String^>(WH_CALLWNDPROC,     "CallWndProc"));
		idFunc.Add("WH_CALLWNDPROCRET",  gcnew Tuple<int, System::String^>(WH_CALLWNDPROCRET,  "CallWndProcRet"));
		idFunc.Add("WH_CBT",             gcnew Tuple<int, System::String^>(WH_CBT,             "CBTProc"));
		idFunc.Add("WH_DEBUG",           gcnew Tuple<int, System::String^>(WH_DEBUG,           "DebugProc"));
		idFunc.Add("WH_FOREGROUNDIDLE",  gcnew Tuple<int, System::String^>(WH_FOREGROUNDIDLE,  "ForegroundIdleProc"));
		idFunc.Add("WH_GETMESSAGE",      gcnew Tuple<int, System::String^>(WH_GETMESSAGE,      "GetMsgProc"));
		idFunc.Add("WH_JOURNALPLAYBACK", gcnew Tuple<int, System::String^>(WH_JOURNALPLAYBACK, "JournalPlaybackProc"));
		idFunc.Add("WH_JOURNALRECORD",   gcnew Tuple<int, System::String^>(WH_JOURNALRECORD,   "JournalRecordProc"));
		idFunc.Add("WH_KEYBOARD",        gcnew Tuple<int, System::String^>(WH_KEYBOARD,        "KeyboardProc"));
		idFunc.Add("WH_KEYBOARD_LL",     gcnew Tuple<int, System::String^>(WH_KEYBOARD_LL,     "LowLevelKeyboardProc"));
		idFunc.Add("WH_MOUSE",           gcnew Tuple<int, System::String^>(WH_MOUSE,           "MouseProc"));
		idFunc.Add("WH_MOUSE_LL",        gcnew Tuple<int, System::String^>(WH_MOUSE_LL,        "LowLevelMouseProc"));
		idFunc.Add("WH_MSGFILTER",       gcnew Tuple<int, System::String^>(WH_MSGFILTER,       "MessageProc"));
		idFunc.Add("WH_SHELL",           gcnew Tuple<int, System::String^>(WH_SHELL,           "ShellProc"));
		idFunc.Add("WH_SYSMSGFILTER",    gcnew Tuple<int, System::String^>(WH_SYSMSGFILTER,    "SysMsgProc"));


		// Let's make our HMODULE and the hookProcess by resolving from the dictionary.
		HMODULE dll = LoadLibrary((char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(dllPath).ToPointer());
		HOOKPROC hookProc = (HOOKPROC)GetProcAddress(dll, (char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(idFunc[idHook]->Item2).ToPointer());

		// We inject here, we use GetThreadId for the main TID for our PID, and use that to get in.
		HHOOK ret = SetWindowsHookEx(idFunc[idHook]->Item1, hookProc, dll, GetThreadId(OpenProcess(THREAD_QUERY_INFORMATION, FALSE, PID)));

		// HHOOK is just a HANDLE to HOOK
		if (ret == NULL) return false;
		CloseHandle(ret);
		return true;
	}
	
	bool injASM(DWORD PID, System::String^ dllPath, bool PAA)
	{

		void* dll;
		void* stubby;

		// As we do with CreateRemoteThread, we have to open a HANDLE to the process
		HANDLE pHandle;
		(PAA) ? pHandle = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_CREATE_THREAD, FALSE, PID) : pHandle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD, FALSE, PID);
		if (pHandle == INVALID_HANDLE_VALUE) return false;

		// We allocate memory for the DLL name
		VirtualAllocEx(pHandle, NULL, strlen((char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(dllPath)) + 1,

	}
	__declspec(naked) loadDll(void)
	{
		_asm
		{
			push 0xDEADBEEF
				pushfd
				pushad
				push 0xDEADBEEF
				mov eax, 0xDEADBEEF
				call eax
				popad
				popfd
				ret
		}
	}

}

[System::STAThread]
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	// First, we have to check our privilege
	Scorpion::EnableDebugPrivilege(true);
	Scorpion::Application::EnableVisualStyles();
	Scorpion::Application::Run(gcnew Scorpion::Window());
	return 0;
}