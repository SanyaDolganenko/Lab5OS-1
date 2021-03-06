#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <TlHelp32.h>
#define CreateProcessNow( path, startupInfo, processInfo) CreateProcess( path,NULL,NULL,NULL,FALSE,0,NULL,NULL, &si, &pi)
#define CreateProcessNowCmd( args, startupInfo, processInfo) CreateProcess(NULL, args,NULL,NULL,FALSE,0,NULL,NULL, &si, &pi)
using namespace std;

void PrintModuleList(HANDLE outputHandle, DWORD dwProcessId) {
	MODULEENTRY32 libraryInfo;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);

	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return;
	}

	libraryInfo.dwSize = sizeof(MODULEENTRY32);
	BOOL b = Module32First(hSnapshot, &libraryInfo);

	do {
		wprintf(L"%s, ", libraryInfo.szModule);
	} while (Module32Next(hSnapshot, &libraryInfo));

	wprintf(L"\n");

	CloseHandle(hSnapshot);
}

void printProcessInfo(int id) {

	HANDLE processHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,id);
	if (processHandle == INVALID_HANDLE_VALUE) {
		cout << "ERROR retrieving toolhelp snapshot(" << GetLastError() << ")" << endl;
	}
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(processHandle, &entry)) {
		cout << "DWSIZE: " << entry.dwSize << " cntThreads: " << entry.cntThreads << endl;
	}
	else {
		cout << "Failed process 32 first." << endl;
	}
	PrintModuleList(processHandle, id);
}

void _tmain(int argc, TCHAR *argv[])
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	//TODO save current time.
	SYSTEMTIME systemTime; GetSystemTime(&systemTime);
	FILETIME fileTime; SystemTimeToFileTime(&systemTime, &fileTime);

	if (!CreateProcessNow(_TEXT("C:\\Users\\Саша\\source\\repos\\Lab5OS\\x64\\Debug\\Lab5OS-2.exe"),si,pi))
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
	else {
		cout << "Notepad launcher process started, id: " << pi.dwProcessId << endl;
		printProcessInfo(pi.dwProcessId);
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	cout<<"Closing notepad launcher process"<<endl;
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	//TODO save current time.

	//TODO start new process with passing 2 arguments - time bounds in which the files have been created.


	TCHAR value[MAX_PATH];
	
	_stprintf(value, _T("C:\\Users\\Саша\\source\\repos\\Lab5OS\\x64\\Debug\\Lab5OS-3.exe %d %d"),
		fileTime.dwLowDateTime, fileTime.dwHighDateTime);
	if (!CreateProcessNowCmd(value,si,pi))
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

