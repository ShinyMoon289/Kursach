#include<iostream>
#include<vector>
#pragma once
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
	unsigned int tel;
	std::string login, password, name, lastName;
protected:
	
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

class doctor: public patient
{
private:
	std::string login, password, name, lastName;
public:
	bool logIn();
	void addDiagnosis();
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
};

extern void fillVectors();
extern std::vector<patient> listOfPatients;
extern std::vector<doctor> listOfDoctors;
extern std::vector<admin> listOfAdmins;
extern std::vector<appointment> listOfAppointments;

