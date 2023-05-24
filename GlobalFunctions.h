#include<iostream>
#include<vector>
#include<string>
#pragma once

extern std::vector<admin> listOfAdmins;
extern std::vector<patient> listOfPatients;
extern std::vector<doctor> listOfDoctors;
extern std::vector<appointment> listOfAppointments;

extern void fillVectors();
extern bool HasSpecialCharsAndDigits(std::string input);
extern bool HasSpecialChars(std::string input);
extern void setCursAt(short int x, short int y);
extern bool alreadyRegistered(std::vector<admin>& list, std::string login);
extern bool alreadyRegistered(std::vector<doctor>& list, std::string login);
extern bool alreadyRegistered(std::vector<patient>& list, std::string login);
extern bool alreadyRegistered(std::vector<admin>& list, std::string password, std::string login);
extern bool alreadyRegistered(std::vector<doctor>& list, std::string password, std::string login);
extern bool alreadyRegistered(std::vector<patient>& list, std::string password, std::string login);