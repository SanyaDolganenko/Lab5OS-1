// Lab5OS.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>

using namespace std;
void _tmain(int argc, TCHAR *argv[])
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	// Start the child process. 
	if (!CreateProcess(_TEXT("C:\\Users\\Саша\\source\\repos\\Lab5OS-2\\x64\\Debug\\Lab5OS-2"),
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
		cout << "Process started, id: " << pi.dwProcessId << endl;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	cout<<"Closing process"<<endl;
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

