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

std::vector<admin> listOfAdmins;

extern bool HasSpecialCharsAndDigits(std::string input);
extern bool HasSpecialChars(std::string input);
extern void setCursAt(short int x, short int y);


extern bool alreadyRegistered(vector<doctor>& list, string login);

HANDLE hSTDOUT = GetStdHandle(STD_OUTPUT_HANDLE);





// admin members

bool admin::logIn()
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

		std::cout << "Enter your password: ";
		while ((ch = _getch()) != ENTER)
		{
			password += ch;
			std::cout << '*';
		}
		if (!alreadyRegistered(listOfAdmins, login, password))
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
			cin.ignore(MAXCHAR, '\n');
		}
		else
		{
			cin.ignore(MAXCHAR, '\n');
			return true;
		}
	}
}

void admin::addAdmin()
{
	admin newAdmin;
	string newlogin, newpassword;
	system("CLS");
	int x = 40, y = 15;
	do		//checking for forbidden characters
	{
		setCursAt(x, y);
		std::cout << "Enter login: ";
		std::getline(std::cin, newlogin);
		if (HasSpecialChars(newlogin))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Your login MUST NOT contain spaces or special characters!";
			Sleep(2000);
		}
		if (alreadyRegistered(listOfAdmins, newlogin))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "This user is already registered!";
			Sleep(2000);
		}
		system("CLS");
	} while (HasSpecialChars(newlogin));
	char ch;
	do
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter password: ";
		while ((ch = _getch()) != ENTER)
		{
			newpassword += ch;
			std::cout << '*';
		}

		if (HasSpecialChars(newpassword))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Your password MUST NOT contain spaces or special characters!";
			Sleep(2000);
		}
	} while (HasSpecialChars(newpassword));
	ofstream WritingAdmins;
	WritingAdmins.open("listOfAdmins.txt", ofstream::out);
	WritingAdmins << newlogin << endl;
	WritingAdmins << newpassword << endl;
	WritingAdmins.close();
	newAdmin.setPassword(newpassword);
	newAdmin.setLogin(newlogin);
	listOfAdmins.push_back(newAdmin);
	system("CLS");
	setCursAt(x, y);
	cout << "New admin added!";
	Sleep(2000);
}


void admin::deletePatient()
{
	system("CLS");
	int activeMenu = 0;
	bool check = true;
	while (check == true)
	{
		int x = 50, y = 12;
		if (listOfPatients.size() == 0)
		{
			setCursAt(x, y);
			cout << "You have no patients!" << endl;
			Sleep(2000);
			break;
		}
		setCursAt(x, y);
		cout << "Choose the patient you wont to delete:" << endl;
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hSTDOUT, &cursorInfo);
		system("CLS");
		for (int i = 0; i < listOfPatients.size(); i++)
		{
			if (i == activeMenu) SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE);
			setCursAt(x, y++);
			std::cout << listOfPatients[i].getLogin() << std::endl;
		}
		setCursAt(x, y++);
		cout << "press Esc to cancel" << endl;
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
			listOfPatients.erase(listOfPatients.begin() + activeMenu);
			check = false;
			break;
		}
		case ESC:
		{
			check = false;
			break;
		}
		}
	}
}


void admin::addDoctor()
{
	doctor newDoctor;
	string newlogin, newpassword, newName, newLastName;
	system("CLS");
	int x = 40, y = 15;

	do		//checking for forbidden characters
	{

		setCursAt(x, y);
		std::cout << "Enter login: ";
		std::getline(std::cin, newlogin);
		if (HasSpecialChars(newlogin))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Your login MUST NOT contain spaces or special characters!";
			Sleep(2000);
		}
		if (alreadyRegistered(listOfDoctors, newlogin))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "This user is already registered!";
			Sleep(2000);
		}
		system("CLS");
	} while (HasSpecialChars(newlogin));
	char ch;
	do
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter password: ";
		while ((ch = _getch()) != ENTER)
		{
			newpassword += ch;
			std::cout << '*';
		}

		if (HasSpecialChars(newpassword))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Your password MUST NOT contain spaces or special characters!";
			Sleep(2000);
		}
	} while (HasSpecialChars(newpassword));

	do
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your name: ";
		std::getline(std::cin, newName);
		if (HasSpecialCharsAndDigits(newName))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Your name MUST NOT contain spaces or digits!";
			Sleep(2000);
		}
	} while (HasSpecialCharsAndDigits(newName));


	do
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your last name: ";
		std::getline(std::cin, newLastName);
		if (HasSpecialCharsAndDigits(newLastName))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Your name MUST NOT contain spaces or special characters!";
			Sleep(2000);
		}
	} while (HasSpecialCharsAndDigits(newLastName));
	ofstream WritingDoctors;
	WritingDoctors.open("listOfDoctors.txt", ofstream::out | ofstream::ate);
	WritingDoctors << newlogin << endl;
	WritingDoctors << newpassword << endl;
	WritingDoctors << newName << newLastName << endl;

	newDoctor.setPassword(newpassword);
	newDoctor.setLogin(newlogin);
	newDoctor.setName(newName);
	newDoctor.setLastName(newLastName);
	listOfDoctors.push_back(newDoctor);
	system("CLS");
	setCursAt(x, y);
	cout << "New doctor added!";
	Sleep(2000);
}

void admin::deleteAdmin()
{
	system("CLS");
	int activeMenu = 0;
	bool check = true;
	while (check == true)
	{
		int x = 50, y = 12;
		if (listOfAdmins.size() == 0)
		{
			setCursAt(x, y);
			cout << "You have no admins!" << endl;
			Sleep(2000);
			break;
		}
		setCursAt(x, y);
		cout << "Choose the admin you wont to delete:" << endl;
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hSTDOUT, &cursorInfo);
		system("CLS");
		for (int i = 0; i < listOfAdmins.size(); i++)
		{
			if (i == activeMenu) SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE);
			setCursAt(x, y++);
			std::cout << listOfAdmins[i].getLogin() << std::endl;
		}
		setCursAt(x, y++);
		cout << "press Esc to cancel" << endl;
		char ch;
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
		{
			activeMenu--;
			if (activeMenu < 1) activeMenu = listOfAdmins.size() - 1;
			break;
		}
		case DOWN:
		{
			activeMenu++;
			if (activeMenu > listOfAdmins.size() - 1) activeMenu = 0;
			break;
		}
		case ENTER:
		{
			listOfAdmins.erase(listOfAdmins.begin() + activeMenu);
			check = false;
			break;
		}
		case ESC:
		{
			check = false;
			break;
		}
		}
	}
}

void admin::deleteAppointment()
{
	system("CLS");
	int chosenApp = 0;
	int activeMenu = 0;

	bool checker = true;
	if (listOfAppointments.size() == 0)
	{
		setCursAt(50, 12);
		cout << "You have 0 appointments!" << endl;
		Sleep(2000);
		checker = false;
	}
	while (checker == true)
	{
		int x = 50, y = 12;
		setCursAt(x, y);

		cout << "Choose the appointment you wont to delete:" << endl;
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hSTDOUT, &cursorInfo);
		system("CLS");
		for (int i = 0; i < listOfAppointments.size(); i++)
		{
			if (i == activeMenu) SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE);
			setCursAt(x, y++);
			cout << i + 1 << ": " << listOfAppointments[i].Date.day << " " << listOfAppointments[i].Date.month << " " << listOfAppointments[i].Date.year;
			setCursAt(x, y++);
			cout << listOfAppointments[i].doctorName << " " << listOfAppointments[i].doctorLastName;
			setCursAt(x, y++);
			cout << listOfAppointments[i].patientName << " " << listOfAppointments[i].patientLastName;
		}
		char ch;
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
		{
			activeMenu--;
			if (activeMenu < 1) activeMenu = listOfAppointments.size() - 1;
			break;
		}
		case DOWN:
		{
			activeMenu++;
			if (activeMenu > listOfAppointments.size() - 1) activeMenu = 0;
			break;
		}
		case ENTER:
		{
			chosenApp = activeMenu;
			checker = false;
			break;
		}
		}

	}
}

void admin::removeDoctor()
{
	system("CLS");
	int chosenDoc = 0;
	int activeMenu = 0;
	int x = 50, y = 12;
	bool checker = true;
	if (listOfAppointments.size() == 0)
	{
		setCursAt(x, y);
		cout << "You have no doctors!" << endl;
		Sleep(2000);
		checker = false;
	}
	while (checker == true)
	{

		setCursAt(x, y);

		cout << "Choose the doctor you want to remove:" << endl;
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hSTDOUT, &cursorInfo);
		system("CLS");
		for (int i = 0; i < listOfAppointments.size(); i++)
		{
			if (i == activeMenu) SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE);
			setCursAt(x, y++);
			cout << listOfAppointments[i].doctorName << " " << listOfAppointments[i].doctorLastName;

		}
		char ch;
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
		{
			activeMenu--;
			if (activeMenu < 1) activeMenu = listOfAppointments.size() - 1;
			break;
		}
		case DOWN:
		{
			activeMenu++;
			if (activeMenu > listOfAppointments.size() - 1) activeMenu = 0;
			break;
		}
		case ENTER:
		{
			chosenDoc = activeMenu;
			checker = false;
			break;
		}
		}
	}
	listOfDoctors.erase(listOfDoctors.begin() + chosenDoc);

}

void admin::showPatient()
{
	system("CLS");
	for (int itr = 0; itr < listOfPatients.size(); ++itr)
	{
		for (int i = 0; i < 41; i++)cout << '_';
		cout << endl;
		cout << itr+1 << "\t" << listOfPatients[itr].getName() << " " << listOfPatients[itr].getLastName() << endl;
		cout << "\t" << listOfPatients[itr].getLogin() << endl;
		cout << "\t" << listOfPatients[itr].getBirthdate().day << "." << listOfPatients[itr].getBirthdate().month << "." << listOfPatients[itr].getBirthdate().year << endl;
		cout << "\t" << "Diagnosis: " << listOfPatients[itr].getDiagnosis() << endl;
		cout << "\t" << listOfPatients[itr].getHomeAddress().city << ", " << listOfPatients[itr].getHomeAddress().street << " " << listOfPatients[itr].getHomeAddress().houseNum << endl << endl;
	}
	for (int i = 0; i < 41; i++)cout << '_';
	cout << endl;
	cout << "Press any key to continue...";
	_getch();
	
}

