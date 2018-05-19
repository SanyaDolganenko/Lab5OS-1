// Lab5OS-3.cpp: определяет точку входа для консольного приложения.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <iostream>
#include <string.h>
#include "windows.h"

using namespace std;
void  _tmain(int argc, wchar_t *argv[])
{
	if (argc == 3) {
		ULONGLONG ull;
		FILETIME fileTIme;
		_stscanf(argv[1], _T("%d"), &fileTIme.dwLowDateTime);
		_stscanf(argv[2], _T("%d"), &fileTIme.dwHighDateTime);
		WIN32_FIND_DATA findData;
		TCHAR tcTemplate[] = _T("C:\\Users\\Саша\\Desktop\\*.txt");
		HANDLE h = FindFirstFile(tcTemplate, &findData);
		if (h != INVALID_HANDLE_VALUE) {
			while (FindNextFile(h, &findData)) {
				if (CompareFileTime(&fileTIme, &findData.ftLastWriteTime) < 0) {
					char* message = (char*)malloc(findData.nFileSizeLow + sizeof(char));

					TCHAR buffer[100];
					_stprintf(buffer,_T("C:\\Users\\Саша\\Desktop\\%s.txt"), findData.cFileName);
					HANDLE handle = CreateFile(buffer, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					SetFilePointer(handle, 0, 0, FILE_BEGIN);
					ReadFile(h, message, sizeof(findData.nFileSizeLow), NULL, NULL);
					
					_tprintf(_T("FOUND FILE: '%s' WITH SIZE: %d LINES: %s\n"),
						findData.cFileName, findData.nFileSizeLow, message);
				}
			} 
			FindClose(h);
		}

	}
}

