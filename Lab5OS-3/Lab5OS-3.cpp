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
	printf("HELLO FROM FILEREADER. NUMBER OF ARGUMENTS = %d\n",argc);
	for (int i = 1; i < argc; i++) {

		ULONGLONG largeInteger;
		swscanf(argv[i], L"%llu", &largeInteger);
	_tprintf(_T("ARGUMENT: %llu\n"), largeInteger);
		//cout << "ARGUMENT: " << argv[i] << "\n";
	}
}

