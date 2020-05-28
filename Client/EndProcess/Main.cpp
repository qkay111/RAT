// Main.cpp

#include <conio.h>
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	//char signalName[] = "EndScreenShareRAT";
	//HANDLE signal = CreateEvent(NULL, TRUE, FALSE, signalName);
	//char acceptSignalName[] = "EndScreenShareAccept";
	//HANDLE acceptSignal = CreateEvent(NULL, TRUE, FALSE, acceptSignalName);

	//ResetEvent(signal);
	//ResetEvent(acceptSignal);

	cout << "Нажмите на любую кнопку для завершения трансляции...";
	_getch();

	//SetEvent(signal);
	//WaitForSingleObject(acceptSignal, INFINITE);

	//CloseHandle(signal);
	//CloseHandle(acceptSignal);

	return 0;
}