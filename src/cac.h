// Filename:	cac.h
// Author:	Lance Booth, Christian Clevinger, Austin Parrish
// Description:	Class decleration for the CAC class

#ifndef CAC_H_INCLUDED
#define CAC_H_INCLUDED

#include <iostream>
#include <list>
#include <string>
#include <locale>
#include "RecordManager.h"
#include "managerList.h"
#include "memberList.h"
#include "providerList.h"
#include "serviceList.h"
#include "provider.h"
#include "member.h"

class CAC {
private:
	managerList *ManagerList = new managerList(DATADIR "/ManagerDB.txt");
	memberList *MemberList = new memberList(DATADIR "/MemberDB.txt");
	providerList *ProviderList = new providerList(DATADIR "/ProviderDB.txt");
	serviceList *SeriveList = new serviceList(DATADIR "/ServiceDB.txt");
	RecordManager *recordManager = new RecordManager(DATADIR "/RecordsDB.txt");
	std::string loggedProviderID;

public:
	CAC();
	void loginMenu();

	//Displays admin interface
	int runAdmin();

	//Display admin options after running a function.
	void displayOptionsAdminMenu();

	//add - create new object
	//mod - modify existing object
	//rem - remove existing class
	//All data is capatalized.
	// Return 1 - If function occurs
	// Return -1 - If user exits before function occurs.
	// Return 0 - If function error occurs.	
	int addMember();
	int modMember();
	int remMember();
	
	int addProvider();
	int modProvider();
	int remProvider();

	//Should only allow you to create piramiters that fit the criterea.
	string validMemberNumber();
	string validProviderNumber();
	string validName();
	string validAddress();
	string validCity();
	string validState();
	string validZip();

	void providerMenu();
	bool validateMember(std::string & number);
	bool validateProvider(std::string & number);
	bool validateService(std::string & number);
	void logService();
	void displayServices();
	//	void administrator_menu();
	void reportMenu();

	void generateMemberReport(std::string memberNumber);
	void generateProviderReport(std::string providerNumber);
	void generateEFTReport(std::string providerNumber);
	void generateSummaryReport();
	void generateWeekly();

	void clearScreen();
};

#endif // CAC_H_INCLUDED
