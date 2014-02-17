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
	
#pragma unmanaged
	__declspec(naked) bool injASM(DWORD PID, System::String^ dllPath, bool PAA)
	{
		void* dll;
		char* dllName = (char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(dllPath).ToPointer();
		void* stubby;

		// As we do with CreateRemoteThread, we have to open a HANDLE to the process
		HANDLE pHandle;
		(PAA) ? pHandle = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_CREATE_THREAD, FALSE, PID) : pHandle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD, FALSE, PID);
		if (pHandle == INVALID_HANDLE_VALUE) return false;

		// We allocate memory for the DLL name + 1 for NULL terminator, MEM_COMMIT allocates memory (physically paged only on access), and we make sure the memory is executable and writable. 
		dll = VirtualAllocEx(pHandle, NULL, strlen(dllName) + 1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		stubby = VirtualAllocEx(pHandle, NULL, 512, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

		// We write our stub in
		WriteProcessMemory(pHandle, dll, dllName, strlen(dllName), NULL);

		// Open a HANDLE to Snapshot, 
		HANDLE threadShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, PID); 
		DWORD TID;

		// This shouldn't happen, but it can, so we must. 
		if (threadShot == INVALID_HANDLE_VALUE) return false;
		else
		{
			// Instead of walking processes, we're gonna walk some threads until we find one which is a child of PID
			THREADENTRY32 te32;
			te32.dwSize = sizeof(te32);
			if (Thread32First(threadShot, &te32))
				while (Thread32Next(threadShot, &te32))
				{
					if (te32.th32OwnerProcessID == PID) TID = te32.th32ThreadID;
					break;
				}
		}

		// Time to open a HANDLE to our thread.
		HANDLE tHandle;

		// The thread accessors are similar to the process accessors, I'm going to use the same bool to reduce overhead. 
		(PAA) ? tHandle = OpenProcess(THREAD_ALL_ACCESS, false, TID) : OpenProcess(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_TERMINATE | THREAD_SUSPEND_RESUME, false, TID);
		if (tHandle == INVALID_HANDLE_VALUE) return false;

		// We suspend our thread
		SuspendThread(tHandle);

		// CONTEXT is a Win32 struct that has internal processor data. MSDN is your friend. I'm still flaky with this. 
		CONTEXT ctx;
		ctx.ContextFlags = CONTEXT_CONTROL;

		// Save our old EIP, we need to RET to this
		DWORD oldEIP = ctx.Eip;

		__asm
		{
			push oldEIP // Our old EIP
				// PUSH EFLAGS register to stack
				pushfd
				// PUSH EXX registers to stack (EAX, EBX, etc.)
				pushad

				push dllStr
				mov eax, loadlib
				call eax

				// Restore registers
				popad
				popfd
				// Return control to thread
				ret
		}

	}

}
#pragma managed(push, on)

[System::STAThread]
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	// First, we have to check our privilege
	Scorpion::EnableDebugPrivilege(true);
	Scorpion::Application::EnableVisualStyles();
	Scorpion::Application::Run(gcnew Scorpion::Window());
	return 0;
}