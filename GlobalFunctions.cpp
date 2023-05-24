#include"Users.h"
#include"GlobalFunctions.h"
#include<Windows.h>
#include<fstream>
#include<string>
using namespace std;

extern HANDLE hSTDOUT;

bool alreadyRegistered(vector<admin>& list, string login)
{
	string buffer;
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i].getLogin() == login) return true;
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
		unsigned int newtel = 0;
		getline(reader, newLogin);
		getline(reader, newPassword);
		reader >> newName >> newLastName;
		reader >> newBirthdate.day >> newBirthdate.month >> newBirthdate.year;
		reader >> newAddress.city >> newAddress.street >> newAddress.houseNum;
		newpatient.setLogin(newLogin);
		newpatient.setName(newName);
		newpatient.setLastName(newLastName);
		newpatient.setHomeAddress(newAddress);
		newpatient.setBirthdate(newBirthdate);
		newpatient.setTelephone(newtel);
		newpatient.setPassword(newPassword);
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



bool alreadyRegistered(vector<patient>& list, std::string login, string password)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i].getLogin() == login && list[i].getPassword() == password) return true;
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
		if ((uppercaseChar < 'A' || uppercaseChar > 'Z') && (input[i] < '0' || input[i]>'9'))
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
