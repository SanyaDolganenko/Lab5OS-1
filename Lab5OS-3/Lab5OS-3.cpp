// Lab5OS-3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
void  _tmain(int argc, TCHAR *argv[])
{
	for (int i = 0; i < argc; i++) {
		cout << "ARGUMENT: " << argv[i] << endl;
	}
}

