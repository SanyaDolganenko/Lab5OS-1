// Lab5OS-3.cpp: определяет точку входа для консольного приложения.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <iostream>
#include <string.h>
#include "windows.h"
#include <vector>
#include <fstream>

using namespace std;

void printLines(LPWSTR fileName)
{
	TCHAR fName[255];
	_tcscpy(fName, L"C:\\Users\\Саша\\Desktop\\");
	_tcscat(fName, fileName);

	ifstream in(fName);

	if (!in) {
		std::cout << "Cannot open input file.\n";
	}

	char str[255];
	vector<string> lines;


	while (in) {
		in.getline(str, 255);  
		lines.push_back(str);
	}

	in.close();

		printf("Encoding: ASCII\n");
		printf("Lines Count: %d\n", lines.size());

		for (size_t i = 0; i < lines.size(); i++)
		{
			cout << "Line #" << i + 1 << ": "<< "; Size: " << lines[i].length() << " bytes" << endl;
		}

	printf("\n");

}


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
					_tprintf(_T("FOUND FILE: '%s' WITH SIZE: %d\n"),
						findData.cFileName, findData.nFileSizeLow);
					printLines(findData.cFileName);
				}
			} 
			FindClose(h);
		}

	}
}

