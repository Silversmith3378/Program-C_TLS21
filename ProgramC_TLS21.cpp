// ProgramC_TLS21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Menu example for tjnapster
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int, int);
void gameMode();
void studyMode();
void options();
void startsteam();

int menu_item = 1, run, x = 1, minmenu = 1, maxmenu = 4, menu = 0;
bool running = true, exitfinish = false, load = false;

int main()
{
	if (load == false) {
		string val;
		ifstream confread("config");
		while (getline(confread, val)) {
			if (val == "0") exitfinish = false;
			else if (val == "1") exitfinish = true;
			confread.close();
		}
		load = true;
	}
	gotoXY(0, 0); cout << "Mode Selector";
	gotoXY(0, 1); cout << "->";

	while (running)
	{
		gotoXY(2, 1);  cout << "Game Mode";
		gotoXY(2, 2);  cout << "Study Mode";
		gotoXY(2, 3);  cout << "Options";
		gotoXY(2, 4); cout << "Quit Program";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && menu_item != maxmenu)
		{
			menu_item++;
			gotoXY(menu*20, menu_item-1); cout << "  ";
			gotoXY(menu*20, menu_item); cout << "->";
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && menu_item != minmenu)
		{
			menu_item--;
			gotoXY(menu*20, menu_item+1); cout << "  ";
			gotoXY(menu*20, menu_item); cout << "->";
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) {
			if (menu == 0) {
				switch (menu_item) {

				case 1: {
					gameMode();
					break;
				}

				case 2: {
					studyMode();
					break;
				}

				case 3: {
					options();
						break;
				}

				case 4: {
					gotoXY(0, 8);
					cout << "Quitting...               ";
					running = false;
					break;
				}
				}
			}else if (menu == 1)
				switch (menu_item) {

				case 1: {
					exitfinish = !exitfinish;

					ofstream config;
					config.open("config");
					config << exitfinish;
					config.close();
					gotoXY(40, 1);
					if (exitfinish) cout << "[V]";else cout << "[ ]";
					break;
				}

				case 2: {
					gotoXY(20, 2); cout << "  ";
					gotoXY(22, 0); cout << "       ";
					gotoXY(22, 1); cout << "                  ";
					gotoXY(40, 1); cout << "   ";
					gotoXY(22, 2); cout << "                 ";

					minmenu = 1; maxmenu = 4;
					menu = 0;
					menu_item = 3;
					break;
				}
				}
		}

	}

	gotoXY(0, 21);
	return 0;
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void gameMode() {
	gotoXY(0, 8); cout << "closing Teams...                   \n";
	system("taskkill /F /IM Teams.exe >nul 2>&1");
	gotoXY(0, 8);  cout << "closing Line...                   \n";
	system("taskkill /F /IM LINEAPP.exe >nul 2>&1");
	gotoXY(0, 8);  cout << "launching Steam...                \n";
	startsteam();
	gotoXY(0, 8); cout << "launching Discord...               \n";
	system("C:\\Users\\Silve\\AppData\\Local\\Discord\\Update.exe --processStart Discord.exe");
	gotoXY(0, 8); cout << "entered Game Mode                  ";
	if (exitfinish) {
		gotoXY(0, 8);
		cout << "Quitting...               ";
		running = false;
	}
}
void studyMode() {
	gotoXY(0, 8); cout << "closing Steam...                  \n";
	system("taskkill /F /IM steam.exe >nul 2>&1");
	gotoXY(0, 8); cout << "closing Discord...                \n";
	system("taskkill /F /IM Discord.exe >nul 2>&1");
	gotoXY(0, 8); cout << "launching Teams...                \n";
	system("C:\\Users\\Silve\\AppData\\Local\\Microsoft\\Teams\\Update.exe --processStart \"Teams.exe\"");
	gotoXY(0, 8); cout << "launching Line...                 \n";
	system("explorer.exe shell:appsFolder\\NAVER.LINEwin8_8ptj331gd3tyt!LINE");
	gotoXY(0, 8); cout << "entered Study Mode                \n                                  \n                                  \n                                  ";
	if (exitfinish) {
		gotoXY(0, 8);
		cout << "Quitting...               ";
		running = false;
	}
}
void options() {
	menu_item = 1; menu = 1;
	minmenu = 1; maxmenu = 2;
	gotoXY(menu * 20, menu_item); cout << "->";
	gotoXY(22, 0); cout << "options";
	gotoXY(22, 1); cout << "exit upon switch  ";
	gotoXY(40, 1);
	if (exitfinish) cout << "[V]"; else cout << "[ ]";
	gotoXY(22, 2);  cout << "back to main menu";
}

void startsteam()
{
	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	CreateProcess(TEXT("C:\\Program Files (x86)\\Steam\\steam.exe"),   // the path
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
