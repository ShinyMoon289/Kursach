#include"Users.h"
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<conio.h>
#include<vector>
#include<algorithm>
using namespace std;
extern HANDLE hSTDOUT = GetStdHandle(STD_OUTPUT_HANDLE);
extern const unsigned int UP = 72, DOWN = 80, ESC = 27,ENTER=13;	//defining constant keys

vector<patient> listOfPatients;
vector<doctor> listOfDoctors;
vector<admin> listOfAdmins;
vector<appointment> listOfAppointments;

//global functions for misc use


void fillVectors()
{
	ifstream reader;
	reader.open("listOfPatients.txt", ifstream::in);
	if (!reader.is_open()) cout << "Unable to open file";
	patient basepatient;
	basepatient.setLogin("patientlogin");
	basepatient.setPassword("patientpassword");
	basepatient.setName("patientName");
	basepatient.setLastName("patientLastName");
	basepatient.setDiagnosis("patientDiagnoses");
	date basebirtdate;
	basebirtdate.day = 1;
	basebirtdate.month = 1;
	basebirtdate.year = 2001;
	basepatient.setBirthdate(basebirtdate);
	address baseAddress;
	baseAddress.city = "Minsk";
	baseAddress.street = "Kolotushkina";
	baseAddress.houseNum = 54;
	basepatient.setHomeAddress(baseAddress);
	listOfPatients.push_back(basepatient);
	while (reader)
	{
		patient newpatient;
		string newName, newLastName, newLogin, newPassword, newDiagnosis;
		address newAddress;
		date newBirthdate;
		getline(reader, newLogin);
		getline(reader, newPassword);
		reader >> newName >> newLastName;
		reader.ignore('\n');
		getline(reader, newDiagnosis);
		reader >> newAddress.city >> newAddress.street >> newAddress.houseNum;
		reader.ignore('\n');
		reader >> newBirthdate.day >> newBirthdate.month >> newBirthdate.year;
		newpatient.setLogin(newLogin);
		listOfPatients.push_back(newpatient);
		reader.ignore('\n');
		reader.ignore('\n');
	}
	reader.close();

	doctor baseDoctor;
	baseDoctor.setLogin("doctorlogin");
	baseDoctor.setPassword("doctorpassword");
	baseDoctor.setName("Bob");
	baseDoctor.setLastName("Odenkirk");
	listOfDoctors.push_back(baseDoctor);
	reader.open("listOfDoctors.txt", ifstream::in);
	if (!reader.is_open()) cout << "Unable to open file";
	while (reader)
	{
		doctor newDoctor;
		string newName, newLastName, newLogin, newPassword;
		getline(reader, newLogin);
		getline(reader, newPassword);
		reader >> newName >> newLastName;
		newDoctor.setLogin(newLogin);
		listOfDoctors.push_back(newDoctor);
		reader.ignore('\n');
		reader.ignore('\n');
	}
	reader.close();

	admin baseAdmin;
	baseAdmin.setLogin("admin");
	baseAdmin.setPassword("password");
	listOfAdmins.push_back(baseAdmin);
	reader.open("listOfAdmins.txt", ifstream::in);
	if (!reader.is_open()) cout << "Unable to open file";
	while (reader)
	{
		admin newAdmin;
		string newLogin, newPassword;
		getline(reader, newLogin);
		getline(reader, newPassword);
		newAdmin.setLogin(newLogin);
		listOfAdmins.push_back(newAdmin);
		reader.ignore('\n');
		reader.ignore('\n');
	}
	reader.close();
	appointment baseapp;
	baseapp.doctorName = "doctor1";
	baseapp.patientName = "patient1";
	baseapp.doctorLastName = "lulz";
	baseapp.patientLastName = "lulztoo";
	baseapp.Date.day = 1;
	baseapp.Date.month = 4;
	baseapp.Date.day = 2001;
	listOfAppointments.push_back(baseapp);
	reader.open("listOfAppointments.txt", ifstream::in);
	if (!reader.is_open()) cout << "Unable to open file";
	while (reader)
	{
		appointment newAppointment;
		reader >> newAppointment.patientName >> newAppointment.patientLastName;
		reader >> newAppointment.doctorName >> newAppointment.doctorLastName;
		reader.ignore('\n');
		reader >> newAppointment.Date.day >> newAppointment.Date.month >> newAppointment.Date.year;
		listOfAppointments.push_back(newAppointment);
		reader.ignore('\n');
		reader.ignore('\n');
	}
}



bool alreadyRegistered(vector<patient>&list,std::string login,string password)
{
	string buffer;
	for (unsigned int i=0;i<list.size();i++)
	{
		if (list[i].getLogin() == login && list[i].getPassword()==password) return true;
	}
	return false;
}
bool alreadyRegistered(vector<doctor>& list, std::string login, string password)
{
	string buffer;
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i].getLogin() == login && list[i].getPassword() == password) return true;
	}
	return false;
}
bool alreadyRegistered(vector<admin>& list, std::string login, string password)
{
	string buffer;
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i].getLogin() == login && list[i].getPassword() == password) return true;
	}
	return false;
}

bool alreadyRegistered(vector<patient>& list, std::string login)
{
	string buffer;
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i].getLogin() == login) return true;
	}
	return false;
}
bool alreadyRegistered(vector<doctor>& list, string login)
{
	string buffer;
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i].getLogin() == login) return true;
	}
	return false;
}

bool alreadyRegistered(vector<admin>& list, string login)
{
	string buffer;
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i].getLogin() == login) return true;
	}
	return false;
}

bool HasSpecialCharsAndDigits(std::string input)
{
	if (input.length() == 0) return true;
	for (int i = 0; i < input.length(); i++)
	{
		int uppercaseChar = toupper(input[i]); 
		if (uppercaseChar < 'A' || uppercaseChar > 'Z')
		{
			return true;
		}
	}
	return false;
}

bool HasSpecialChars(std::string input)
{
	if (input.length() == 0) return true;
	for (int i = 0; i < input.length(); i++)
	{
		int uppercaseChar = toupper(input[i]);
		if ((uppercaseChar < 'A' || uppercaseChar > 'Z')&& (input[i] < '0' || input[i]>'9'))
		{ 
				return true;
		}
	}
	return false;
}

void setCursAt(short int x, short int y)
{
	SetConsoleCursorPosition(hSTDOUT, { x, y });
}


//members for patient
int patient::showMenu(std::string *MenuList,unsigned int MenuSize)
{
	system("CLS");
	
	int activeMenu=0;
	for (;;)
	{
		int x = 50, y = 12;
		setCursAt(x, y);
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hSTDOUT, &cursorInfo);
		system("CLS");
		for (int i = 0; i < MenuSize; i++)
		{
			if (i == activeMenu) SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			else SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE);
			setCursAt(x, y++);
			std::cout << MenuList[i] << std::endl;
		}
		char ch;
		ch = _getch();
		if (ch == -32) ch = _getch(); 
		switch (ch)
		{
		case UP:
		{
			activeMenu--;
			if (activeMenu < 0) activeMenu = MenuSize-1;
			break;
		}
		case DOWN:
		{
			activeMenu++;
			if (activeMenu > MenuSize-1)activeMenu = 0;
			break;
		}
		case ENTER:
		{
			return activeMenu;
		}
		}
	}
}

void patient::setUpAppointment()
{
	appointment newApp;
	system("CLS");
	int chosenDoctor = 0;
	int activeMenu = 0;
	for (;;)
	{
		int x = 50, y = 12;
		setCursAt(x, y);
		cout << "Please choose your doctor:" << endl;
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hSTDOUT, &cursorInfo);
		system("CLS");
		for (int i = 0; i < listOfDoctors.size(); i++)
		{
			if (i == activeMenu) SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			else SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE);
			setCursAt(x, y++);
			std::cout << listOfDoctors[i].getName() << " " << listOfDoctors[i].getLastName() << std::endl;
		}
		char ch;
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
		{
			activeMenu--;
			if (activeMenu < 1) activeMenu = listOfDoctors.size() - 1;
			break;
		}
		case DOWN:
		{
			activeMenu++;
			if (activeMenu > listOfDoctors.size() - 1) activeMenu = 0;
			break;
		}
		case ENTER:
		{
			chosenDoctor = activeMenu;
			break;
		}
		}
	}

	while (true)
	{
		int x = 50, y = 12;
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter the date of appointment: ";
		cin >> newApp.Date.day >> newApp.Date.month >> newApp.Date.year;
		if (birthdate.day > 1 && birthdate.month > 1 && birthdate.month < 13 && birthdate.year > 1900) break;
		system("CLS");
		setCursAt(x, y);
		cout << "Incorrect input!";
		Sleep(2000);
	}
	newApp.doctorName = listOfDoctors[chosenDoctor].getName();
	newApp.doctorLastName = listOfDoctors[chosenDoctor].getLastName();
	newApp.patientName = this->getName();
	newApp.patientLastName = this->getLastName();
	listOfAppointments.push_back(newApp);
}

void patient::showAppointments()
{
	int actualsize = 0;
	int x = 10, y = 10;
	for (int itr = 0; itr < listOfAppointments.size(); ++itr)
	{
		if (name == listOfAppointments[itr].patientName && lastName == listOfAppointments[itr].patientLastName) actualsize++;
	}
	if (actualsize > 0)
	{
		for (int itr = 0; itr < listOfAppointments.size(); ++itr)
		{
			if (name == listOfAppointments[itr].patientName && lastName == listOfAppointments[itr].patientName)
			{
				setCursAt(x, y++);
				cout << setw(40) << setfill('&') << endl;

				setCursAt(x, y++);
				cout << itr + 1 <<" " << listOfAppointments[itr].Date.day << " " << listOfAppointments[itr].Date.month << " " << listOfAppointments[itr].Date.year << " -- "
					<< listOfAppointments[itr].doctorName << " " << listOfAppointments[itr].doctorLastName;
			}
		}
		setCursAt(x, y++);
		cout << setw(40) << setfill('&') << endl;
		cout << "Press any key to continue...";
		_getch();
	}
	else
	{
		setCursAt(x, y);
		cout << "You have no appointments!";
	}
	
}

void patient::deleteAppointment()
{
	system("CLS");
	int chosenApp = 0;
	int activeMenu = 0;
	int actualsize = 0,g=0;
	int x = 50, y = 12;
	bool checker = true;
	for (int i = 0; i < listOfAppointments.size(); i++)
	{
		if (listOfAppointments[i].patientName == this->name && listOfAppointments[i].patientLastName == this->lastName) actualsize++;
	}
	if (actualsize == 0)
	{
		setCursAt(x, y);
		cout << "You have 0 appointments!" << endl;
		Sleep(2000);
		checker = false;
	}
	while (checker==true)
	{
		
		setCursAt(x, y);
		
		cout << "Choose the appointment you wont to delete:" << endl;
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hSTDOUT, &cursorInfo);
		system("CLS");
		for (int i = 0; i < listOfAppointments.size(); i++)
		{
			if (listOfAppointments[i].patientName == this->name && listOfAppointments[i].patientLastName == this->lastName)
			{
				g = i;
				if (g == activeMenu) SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				else SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE);
				setCursAt(x, y++);
				std::cout << listOfDoctors[i].getName() << " " << listOfDoctors[i].getLastName() << std::endl;
			}
			
		}
		char ch;
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
		{
			activeMenu--;
			if (activeMenu < 1) activeMenu = actualsize - 1;
			break;
		}
		case DOWN:
		{
			activeMenu++;
			if (activeMenu > actualsize - 1) activeMenu = 0;
			break;
		}
		case ENTER:
		{
			chosenApp = activeMenu;
			break;
		}
		}
	}
	listOfAppointments.erase(listOfAppointments.begin() + chosenApp);
}

bool patient::logIn()
{
	string newlogin, newpassword;
	int x = 50, y = 12;
	char ch;
	while (true)
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your login: ";
		std::getline(std::cin, newlogin);
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your password: ";
		while ((ch = _getch()) != ENTER)
		{
			newpassword += ch;
			std::cout << '*';
		}
		if (!alreadyRegistered(listOfPatients, newlogin, newpassword))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Incorrect login or password! Abort? y or n";
			newpassword.clear();
			char chooser;
			cin >> chooser;
			if (chooser == 'y')
			{
				cin.ignore(MAXCHAR, '\n');
				return false;
			}
			else cin.ignore(MAXCHAR,'\n');
		}
		else
		{
			break;
		}
	}

	return true;
}



void patient::signUp()		//signing up a patient
{
	patient newpatient;
	string newlogin, newname, newpassword, newlastname;
	date newbirthdate;
	unsigned int newtel;
	address newhomeaddress;
	system("CLS");
	int x = 40, y = 15;

	do		//checking for forbidden characters
	{

		setCursAt(x, y);
		std::cout << "Enter your login: ";
		std::getline(std::cin, newlogin );
		if (HasSpecialChars(newlogin))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Your login MUST NOT contain spaces or special characters!";
			Sleep(2000);
		}
		if (alreadyRegistered(listOfPatients, newlogin))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "This user is already registered!";
			Sleep(2000);
		}
		system("CLS");
	} while (HasSpecialChars(newlogin));
	
	do
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your name: ";
		std::getline(std::cin, newname);
		if (HasSpecialCharsAndDigits(newname))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Your name MUST NOT contain spaces or digits!";
			Sleep(2000);
		}
	} while (HasSpecialCharsAndDigits(newname));


	do
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your last name: ";
		std::getline(std::cin, newlastname);
		if (HasSpecialCharsAndDigits(newlastname))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Your last name MUST NOT contain spaces or special characters!";
			Sleep(2000);
		}
	} while (HasSpecialCharsAndDigits(newlastname));

	char ch;
	do
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your password: ";
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
			newpassword.clear();
			Sleep(2000);
		}
	} while (HasSpecialChars(newpassword));

	while (true)
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your date of birth: ";
		cin >> newbirthdate.day >> newbirthdate.month >> newbirthdate.year;
		if (newbirthdate.day > 1 && newbirthdate.month > 1 && newbirthdate.month < 13 && newbirthdate.year > 1900) break;
		system("CLS");
		setCursAt(x, y);
		cout << "Incorrect input!";
		Sleep(2000);
	}
	cin.ignore();
	do
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your city: ";
		std::getline(std::cin, newhomeaddress.city);
		if (HasSpecialCharsAndDigits(newhomeaddress.city))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Your name MUST NOT contain digits or special characters!";
			Sleep(2000);
		}
	} while (HasSpecialCharsAndDigits(newhomeaddress.city));

	do
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your street: ";
		std::getline(std::cin, newhomeaddress.street);
		if (HasSpecialCharsAndDigits(newhomeaddress.street))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout << "Your name MUST NOT contain spaces or special characters!";
			Sleep(2000);
		}
	} while (HasSpecialCharsAndDigits(newhomeaddress.street));

	while (true)
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your house number: ";
		cin >> newhomeaddress.houseNum;
		if (newhomeaddress.houseNum > 1) break;
		system("CLS");
		setCursAt(x, y);
		cout << "Incorrect input!";
		Sleep(2000);
	}

	while (true)
	{
		system("CLS");
		setCursAt(x, y);
		std::cout << "Enter your telephone number: ";
		cin >> newtel;
		if (newtel > 1000000&&newtel<9999999) break;
		system("CLS");
		setCursAt(x, y);
		cout << "Incorrect input!";
		Sleep(2000);
	}
	ofstream WritingPatients;
	WritingPatients.open("listOfPatients.txt", ofstream::out);
	WritingPatients << newlogin << endl;
	WritingPatients << newpassword << endl;
	WritingPatients << newname << newlastname<<endl;
	WritingPatients << newbirthdate.day<< newbirthdate.month << newbirthdate.year << endl;
	WritingPatients << newhomeaddress.city<< newhomeaddress.street<< newhomeaddress.houseNum << endl;
	WritingPatients << newtel << endl << endl;
	WritingPatients.close();

	newpatient.setName(newname);
	newpatient.setLastName(newlastname);
	newpatient.setLogin(newlogin);
	newpatient.setPassword(newpassword);
	newpatient.setBirthdate(newbirthdate);
	newpatient.setHomeAddress(newhomeaddress);
	newpatient.setTelephone(newtel);
	listOfPatients.push_back(newpatient);
	system("CLS");
	setCursAt(x, y);
	std::cout << "Patient successfully registered!";
	Sleep(2000);
}


void patient::setName(std::string newName)
{
	this->name = newName;
}
std::string patient::getName()
{
	return this->name;
}

void patient::setLastName(std::string newLastName)
{
	this->name = newLastName;
}

std::string patient::getLastName()
{
	return this->lastName;
}

void patient::setPassword(std::string newPassword)
{
	this->password = newPassword;
}
std::string patient::getPassword()
{
	return this->password;
}

void patient::setLogin(std::string newLogin)
{
	this->login = newLogin;
}
std::string patient::getLogin()
{
	return this->login;
}

void patient::setDiagnosis(std::string newDiagnosis)
{
	this->diagnosis = newDiagnosis;
}
std::string patient::getDiagnosis()
{
	return this->diagnosis;
}

void patient::setBirthdate(date newBirthdate)
{
	this->birthdate.day = newBirthdate.day;
	this->birthdate.month = newBirthdate.month;
	this->birthdate.year = newBirthdate.year;
}
date patient::getBirthdate()
{
	return this->birthdate;
}

address patient::getHomeAddress()
{
	return this->homeAddress;
}
void patient::setHomeAddress(address newAddress)
{
	this->homeAddress.city = newAddress.city;
	this->homeAddress.street = newAddress.street;
	this->homeAddress.houseNum = newAddress.houseNum;
}

void patient::setTelephone(unsigned int tel)
{
	this->tel = tel;
}
unsigned int patient::getTelephone()
{
	return this->tel;
}



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
	string newlogin, newpassword,newName,newLastName;
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
	WritingDoctors.open("listOfDoctors.txt", ofstream::out|ofstream::ate);
	WritingDoctors << newlogin << endl;
	WritingDoctors << newpassword << endl; 
	WritingDoctors << newName << newLastName<< endl;
	
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
	while (check==true)
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
		cout << "press Esc to cancel"<<endl;
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
			listOfAdmins.erase(listOfAdmins.begin()+activeMenu);
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
		cout<<listOfAppointments[i].doctorName << " " << listOfAppointments[i].doctorLastName;
		setCursAt(x, y++);
		cout<<listOfAppointments[i].patientName << " " << listOfAppointments[i].patientLastName;
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
	listOfDoctors.erase(listOfDoctors.begin()+ chosenDoc);
}

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

void admin::sortPatients()
{
	int i, j;
	for (i = 0; i < listOfPatients.size() - 1; i++)
	{
		for (j = 0; j < listOfPatients.size() - i - 1; j++)
		{
			if (listOfPatients[j].getName()[0] > listOfPatients[j+1].getName()[0])
				swap(listOfPatients[j], listOfPatients[j + 1]);
		}
	}
}

void admin::showAppointments()
{
	system("CLS");
	int x = 10, y = 10;
	if (listOfAppointments.size() > 0)
	{
		for (int itr = 0; itr < listOfAppointments.size(); ++itr)
		{
			setCursAt(x, y++);
			for (int i = 0; i < 41; i++)cout << '_';
			setCursAt(x, y++);
			cout << itr + 1 << " " << listOfAppointments[itr].Date.day << " " << listOfAppointments[itr].Date.month << " " << listOfAppointments[itr].Date.year << " -- "
				<< listOfAppointments[itr].doctorName << " " << listOfAppointments[itr].doctorLastName;
		}
		setCursAt(x, y++);
		for (int i = 0; i < 41; i++)cout << '_';
		setCursAt(x, y++);
		cout << "Press any key to continue...";
		_getch();
	}
	else
	{
		setCursAt(x, y);
		cout << "You have no appointments!";
		Sleep(2000);
	}

}