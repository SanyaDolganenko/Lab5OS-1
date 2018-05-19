#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "windows.h"
#include <iostream>

using namespace std;
void _tmain(int argc, TCHAR *argv[])
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	//TODO save current time.
	SYSTEMTIME st; GetSystemTime(&st);
	FILETIME ft; SystemTimeToFileTime(&st, &ft);

	if (!CreateProcess(_TEXT("C:\\Users\\Саша\\source\\repos\\Lab5OS-2\\x64\\Debug\\Lab5OS-2.exe"),
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
	else {
		cout << "Notepad launcher process started, id: " << pi.dwProcessId << endl;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	cout<<"Closing notepad launcher process"<<endl;
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	//TODO save current time.
	SYSTEMTIME st2; GetSystemTime(&st2);
	FILETIME ft2; SystemTimeToFileTime(&st2, &ft2);

	//TODO start new process with passing 2 arguments - time bounds in which the files have been created.


	TCHAR value[MAX_PATH];
	ULARGE_INTEGER integerLrgae = { ft.dwLowDateTime,ft.dwHighDateTime };
	ULARGE_INTEGER integerLrgae2 = { ft2.dwLowDateTime,ft2.dwHighDateTime };
	_stprintf(value, _T("C:\\Users\\Саша\\source\\repos\\Lab5OS\\x64\\Debug\\Lab5OS-3.exe %lu %lu"),
		integerLrgae.QuadPart, integerLrgae2);
	if (!CreateProcess(NULL,
		value,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
	else {
		cout << "File viewer process started, id: " << pi.dwProcessId << endl;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	cout << "Closing file viewer process" << endl;
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

