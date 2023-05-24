#include"Users.h"
#include<fstream>
#include<iomanip>
#include<string>
#include<conio.h>
#include<algorithm>
#include"Project1/GlobalFunctions.h"
using namespace std;
extern HANDLE hSTDOUT;

vector<patient> listOfPatients;
vector<appointment> listOfAppointments;


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
	bool checker = TRUE;
	while(checker==true)
	{
		int x = 50, y = 12;
		setCursAt(x, y);
		SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE);
		cout << "Please choose your doctor:" << endl;
		setCursAt(x, y++);
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hSTDOUT, &cursorInfo);
		for (int i = 0; i < listOfDoctors.size(); i++)
		{
			if (i == activeMenu) SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hSTDOUT, FOREGROUND_BLUE);
			setCursAt(x, y++);
			cout << listOfDoctors[i].getName() << " " << listOfDoctors[i].getLastName();
		}
		char ch;
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
		{
			activeMenu--;
			if (activeMenu < 0) activeMenu = listOfDoctors.size()-1 ;
			break;
		}
		case DOWN:
		{
			activeMenu++;
			if (activeMenu > listOfDoctors.size()-1) activeMenu = 0;
			break;
		}
		case ENTER:
		{
			chosenDoctor = activeMenu;
			checker = false;
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
		if (newApp.Date.day > 1 && newApp.Date.month > 1 && newApp.Date.month < 13 && newApp.Date.year > 1900) break;
		
		system("CLS");
		setCursAt(x, y);
		cout << "Incorrect input! Skip? y or n";
		char ch;
		cin >> ch;
		if (ch == 'y')
		{
			cin.ignore(MAXINT, '\n');
			break;
		}
		
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
		system("CLS");
		for (int itr = 0; itr < listOfAppointments.size(); ++itr)
		{
			if (name == listOfAppointments[itr].patientName && lastName == listOfAppointments[itr].patientName)
			{
				for (int i = 0; i < 41; i++)cout << "_";
				cout << endl;
				cout << itr + 1 << ": " << listOfAppointments[itr].Date.day << "." << listOfAppointments[itr].Date.month << "." << listOfAppointments[itr].Date.year<<endl;
				cout<<"Your doctor: "<< listOfAppointments[itr].doctorName << " " << listOfAppointments[itr].doctorLastName;
				cout << endl;
			}
		}
		for (int i = 0; i < 41; i++)cout << "_";
		setCursAt(50,12);
		cout << "Press any key to continue...";
		_getch();
	}
	else
	{
		system("CLS");
		setCursAt(50, 12);
		cout << "You have no appointments!";
		Sleep(2000);
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
		if (!alreadyRegistered(listOfPatients, login, password))
		{
			system("CLS");
			setCursAt(x, y);
			std::cout <<listOfPatients[1].getLogin()<<" "<<listOfPatients[1].getLogin()<<" " << "Incorrect login or password! Abort? y or n";
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
	} while (HasSpecialChars(newlogin)||alreadyRegistered(listOfPatients, newlogin));
	
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
	WritingPatients.open("listOfPatients.txt", ofstream::out|ofstream::ate);
	WritingPatients << newlogin << endl;
	WritingPatients << newpassword << endl;
	WritingPatients << newname <<" "<< newlastname << endl;
	WritingPatients << newbirthdate.day<< " " << newbirthdate.month <<" " << newbirthdate.year << endl;
	WritingPatients << newhomeaddress.city<< " " <<newhomeaddress.street<<" " << newhomeaddress.houseNum << endl;
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



void patient::setLastName(std::string newLastName)
{
	this->name = newLastName;
}

std::string patient::getLastName()
{
	return this->lastName;
}

void patient::setName(std::string newname)
{
	this->name = newname;
}

std::string patient::getName()
{
	return name;
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