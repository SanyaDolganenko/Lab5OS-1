// Lab5OS-2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>
#define CreateProcessNow( path, startupInfo, processInfo) CreateProcess(path, NULL,NULL,NULL,FALSE,0,NULL,NULL, &si, &pi)
using namespace std;
void _tmain(int argc, TCHAR *argv[])
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	// Start the child process. 

	if (!CreateProcessNow(_TEXT("C:\\Windows\\notepad.exe"), si, pi))
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
	cout << "Closing notepad process" << endl;
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}