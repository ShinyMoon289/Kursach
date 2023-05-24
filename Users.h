#include<iostream>
#include<vector>
#include<Windows.h>
#pragma once

const unsigned int UP = 72, DOWN = 80, ESC = 27, ENTER = 13;	//defining constant keys
extern HANDLE hSTDOUT;

struct date
{
	unsigned int day=0, month=0, year=0;
};

struct address
{
	std::string city, street;
	unsigned int houseNum = 0;
};

struct appointment
{
	std::string patientName,patientLastName, doctorName,doctorLastName;
	date Date;
};

class patient
{
private: 
	std::string diagnosis;
	date birthdate;
	address homeAddress;
	unsigned int tel=0;
	std::string login, password, name, lastName;
public:
	void setName(std::string newName);
	std::string getName();

	void setLastName(std::string newLastName);
	std::string getLastName();

	void setPassword(std::string newPassword);
	std::string getPassword();

	void setLogin(std::string newLogin);
	std::string getLogin();

	void setDiagnosis(std::string newDiagnosis);
	std::string getDiagnosis();

	void setBirthdate(date newBirthdate);
	date getBirthdate();

	void setTelephone(unsigned int tel);
	unsigned int getTelephone();

	address getHomeAddress();
	void setHomeAddress(address newAddress);

	int showMenu(std::string *MenuList,unsigned int menuSize);
	void showAppointments();
	bool logIn();
	void setUpAppointment();
	void deleteAppointment();
	void signUp();


};

class admin :public patient
{
private:
	std::string login, password;
public:
	void showAppointments();
	void deleteAdmin();
	bool logIn();
	void addDoctor();
	void removeDoctor();
	void addAdmin();
	void deleteAppointment();
	void sortPatients();
	void deletePatient();
	void showPatient();
};

class doctor: public patient
{
private:
	std::string login, password, name, lastName;
public:
	bool logIn();
	void addDiagnosis();
};

extern std::vector<admin> listOfAdmins;
extern std::vector<patient> listOfPatients;
extern std::vector<doctor> listOfDoctors;
extern std::vector<appointment> listOfAppointments;






