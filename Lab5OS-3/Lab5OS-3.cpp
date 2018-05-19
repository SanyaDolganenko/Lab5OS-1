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
					_tprintf(_T("FOUND FILE: '%s' WITH SIZE: %d\n"), findData.cFileName, findData.nFileSizeLow);
				}
			} 
			FindClose(h);
		}

	}
}

