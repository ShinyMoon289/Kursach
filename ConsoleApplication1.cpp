
#include"Users.h"
#include"Project1/GlobalFunctions.h"
#include<Windows.h>
#include <iostream>
#include<fstream>
#include<conio.h>
using namespace std;
std::string startMenu[] = {
	"Sign up a new patient",
	"Log in as an admin",
	"Log in as a patient",
	"Log in as a doctor",
	"Quit program" 
};

std::string AdminMenu[] = {
	"Add a new doctor",
	"Add a new admin",
	"Delete an appointment",
	"Delete an admin",
	"Log out",
	"Show all appointments",
	"Sort all patients",
	"Delete a patient",
	"Delete a doctor",
	"Show all patients"
};

std::string PatientMenu[] = {
	"Show appointments",
	"Set up a new appointment",
	"Delete an appointment",
	"Log out"
};
std::string DoctorMenu[] = {
	"Show appointments",
	"Add diagnosis",
	"Log out"
};

int main()
{
	admin Admin;
	patient Patient;
	doctor Doctor;
	fillVectors();
	while (true)
	{
		int chooser1 = Admin.showMenu(startMenu, size(startMenu));
		switch (chooser1)
		{
		case 0:
		{
			Patient.signUp();
			break;
		}
		case 1:
		{
			bool checkadmin = Admin.logIn();
			
			if (checkadmin==true)
			{
				bool checker = true;
				while (checker==true)
				{
					int chooser2 = Admin.showMenu(AdminMenu, size(AdminMenu));
					switch (chooser2)
					{
					case 0:
					{
						Admin.addDoctor();
						break;
					}
					case 1:
					{
						Admin.addAdmin();
						break;
					}
					case 2:
					{
						Admin.deleteAppointment();
						break;
					}
					case 3:
					{
						Admin.deleteAdmin();
						break;
					}
					case 4:
					{
						checker = false;
						break;
					}
					case 5:
					{
						Admin.showAppointments();
						break;
					}
					case 6:
					{
						Admin.sortPatients();
						break;
					}
					case 7:
					{
						Admin.deletePatient();
						break;
					}
					case 8:
					{
						Admin.removeDoctor();
						break;
					}
					case 9:
					{
						Admin.showPatient();
						break;
					}
					}
				}
				
			}
			else break;
			break;
		}
		case 2:
		{
			bool checkPatient = Patient.logIn();
			if (checkPatient==true)
			{
				bool sw = true;
				while (sw == true)
				{
					int chooser3 = Patient.showMenu(PatientMenu, size(PatientMenu));
					switch (chooser3)
					{
					case 0:
					{
						Patient.showAppointments();
						break;
					}
					case 1:
					{
						Patient.setUpAppointment();
						break;
					}
					case 2:
					{
						Patient.deleteAppointment();
						break;
					}
					case 3:
					{
						sw = false;
						break;
					}
					}
				}
			}
			break;
		}
		case 3:
		{
			bool checkDoctor = Doctor.logIn();
			if (checkDoctor == true)
			{
				bool sw = true;
				while (sw == true)
				{
					int chooser3 = Doctor.showMenu(DoctorMenu, size(DoctorMenu));
					switch (chooser3)
					{
					case 0:
					{
						Doctor.showAppointments();
						break;
					}
					case 1:
					{
						Doctor.addDiagnosis();
						break;
					}
					case 2:
					{
						sw = false;
						break;
					}
					}
				}
			}
			else break;
			break;
		}
		case 4:
		{
			return 0;
		} 
		}
	}
	
}

