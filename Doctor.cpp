#include"Users.h"
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<conio.h>
#include<algorithm>
#include"GlobalFunctions.h"
using namespace std;

extern HANDLE hSTDOUT;
vector<doctor> listOfDoctors;

void doctor::addDiagnosis()
{
	system("CLS");
	int chosenPat = 0;
	int activeMenu = 0;
	int x = 50, y = 12;
	bool checker = true;
	if (listOfPatients.size() == 0)
	{
		setCursAt(x, y);
		cout << "You have no patients!" << endl;
		Sleep(2000);
		checker = false;
	}
	while (checker == true)
	{

		setCursAt(x, y);

		cout << "Choose the patient you want to add diagnosis:" << endl;
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hSTDOUT, &cursorInfo);
		system("CLS");
		for (int i = 0; i < listOfPatients.size(); i++)
		{
			if (i == activeMenu) SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE);
			setCursAt(x, y++);
			cout << listOfPatients[i].getName() << " " << listOfPatients[i].getLastName() << ": " << listOfPatients[i].getDiagnosis();
		}
		char ch;
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
		{
			activeMenu--;
			if (activeMenu < 1) activeMenu = listOfPatients.size() - 1;
			break;
		}
		case DOWN:
		{
			activeMenu++;
			if (activeMenu > listOfPatients.size() - 1) activeMenu = 0;
			break;
		}
		case ENTER:
		{
			chosenPat = activeMenu;
			checker = false;
			break;
		}
		}
	}
	string newdiagnosis;
	do
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter the diagnosis: ";
		std::getline(std::cin, newdiagnosis);
		if (HasSpecialCharsAndDigits(newdiagnosis))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "The diagnosis MUST NOT contain spaces or special characters!";
			Sleep(2000);
		}
	} while (HasSpecialCharsAndDigits(newdiagnosis));
	listOfPatients[chosenPat].setDiagnosis(newdiagnosis);
	system("CLS");
	setCursAt(x, y);
	std::cout << "Diagnosis is set!";
	Sleep(2000);
}

bool doctor::logIn()
{
	int x = 50, y = 12;
	char ch;
	while (true)
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your login: ";
		cin >> login;
		system("CLS");
		setCursAt(x, y);
		password.clear();
		std::cout << "Enter your password: ";
		while ((ch = _getch()) != ENTER)
		{
			password += ch;
			std::cout << '*';
		}
		if (!alreadyRegistered(listOfDoctors, login, password))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Incorrect login or password! Abort? y or n";
			password.clear();
			char chooser;
			cin >> chooser;
			if (chooser == 'y')
			{
				cin.ignore(MAXCHAR, '\n');
				return false;
			}
			else cin.ignore(MAXCHAR, '\n');
		}
		else return true;
	}
}
