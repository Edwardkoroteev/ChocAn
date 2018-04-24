/*********************************************
// Filename:	cac.cpp
// Author:	Austin Parrish, Christian Clevinger
// Description:	Functions for the CAC class
 *********************************************/

#include "cac.h"

using namespace std;

CAC::CAC() {
	//MemberList->display();
}

void CAC::loginMenu()
{
	clearScreen();
	//Pompt user for input.
	std::cout << "Welcome to ChocAnon.\n";
	std::cout << "This system is for the exclusive use of those associated with ChocAnon. \nUnauthorized access to this system is prohibited.\n";
	std::cout << "ALL ACTIVITY MAY BE RECORDED!\n";

	std::string userInput;
	std::string userPassword;
	bool exit = false;

	while (exit == false) {
		std::cout << "Please enter your username or Provider ID number, or type exit to quit: ";
		std::cin >> userInput;

		clearScreen();
		if (ProviderList->find(userInput) != NULL) {
			std::cout << "Enter your password: ";
			std::cin >> userPassword;

			if (ProviderList->find(userInput)->isPassword(userPassword) == true) {
				clearScreen();
				loggedProviderID = userInput;
				providerMenu();
			}
			else {
				std::cout << "The username or password is incorect, try again.\n";
			}
		}
		else if (ManagerList->find(userInput) != NULL) {
			std::cout << "Enter your password: ";
			std::cin >> userPassword;
			if (ManagerList->find(userInput)->isPassword(userPassword) == true) {
				clearScreen();
				runAdmin();
			}
			else {
				clearScreen();
				std::cout << "The username or password is incorect, try again.\n";
			}
		}
		else if (userInput == "exit") {
			std::cout << "Bye.\n";
			exit = true;
		}
		else {
			std::cout << "Not a valid ID, try again.\n";
		}
	}
}

int CAC::runAdmin()
{
	string adminInput;

	cout << "Please select an option, or type exit to quit." << endl;

	cout << "1) Add Memmber" << endl;
	cout << "2) Modify Member" << endl;
	cout << "3) Remove Member" << endl;
	cout << "4) Add Provider" << endl;
	cout << "5) Modify Provider" << endl;
	cout << "6) Remove Provider" << endl;
	cout << "7) Report Menu" << endl;

	while(adminInput != "exit")
	{
		getline(cin, adminInput);


		if (adminInput == "1")
		{
			addMember();
			displayOptionsAdminMenu();
		}

		else if (adminInput == "2")
		{
			modMember();
			displayOptionsAdminMenu();

		}
		else if (adminInput == "3")
		{
			remMember();
			displayOptionsAdminMenu();

		}
		else if (adminInput == "4")
		{
			addProvider();
			displayOptionsAdminMenu();

		}
		else if (adminInput == "5")
		{
			modProvider();
			displayOptionsAdminMenu();

		}
		else if (adminInput == "6")
		{
			remProvider();
			displayOptionsAdminMenu();
		}
		else if (adminInput == "7")
		{
			reportMenu();
			displayOptionsAdminMenu();
		}
		else if (adminInput != "exit")
			cout << "Invalid input." << endl;
	}

	if(adminInput == "exit")
		return -1;
	else
		return 1;
}

void CAC::displayOptionsAdminMenu()
{

	cout << "Please select an option, or type exit to quit." << endl;

	cout << "1) Add Memmber" << endl;
	cout << "2) Modify Member" << endl;
	cout << "3) Remove Member" << endl;
	cout << "4) Add Provider" << endl;
	cout << "5) Modify Provider" << endl;
	cout << "6) Remove Provider" << endl;
	cout << "7) Report Menu" << endl;

}

string CAC::validMemberNumber()
{
	string numberToTest;
	bool validNumber = false;
	cout << "Please enter a nine digit number to be the member number." << endl;
	while(validNumber == false)
	{
		getline(cin, numberToTest);
		validNumber = true;

		if(numberToTest == "exit")
			return numberToTest;
		if(numberToTest.length() != 9)
			validNumber = false;
		for(int i = 0; i < numberToTest.length(); i++)
			if(numberToTest[i] < '0' || numberToTest[i] > '9')
				validNumber = false;
		if(MemberList->find(numberToTest) != NULL)
			validNumber = false;

		if(validNumber == false)
		{
			cout << "Invalid member number." << endl;
			cout << "Please enter a valid member number." << endl;
			numberToTest = "";
		}
	}
}


string CAC::validProviderNumber()
{
	string numberToTest;
	bool validNumber = false;
	cout << "Please enter a nine digit number to be the member number." << endl;
	while(validNumber == false)
	{
		getline(cin, numberToTest);
		validNumber = true;

		if(numberToTest == "exit")
			return numberToTest;
		if(numberToTest.length() != 9)
			validNumber = false;
		for(int i = 0; i < numberToTest.length(); i++)
			if(numberToTest[i] < '0' || numberToTest[i] > '9')
				validNumber = false;
		if(ProviderList->find(numberToTest) != NULL)
			validNumber = false;
		if(numberToTest[0] != '9')
			validNumber = false;

		if(validNumber == false)
		{
			cout << "Invalid member number." << endl;
			cout << "Please enter a valid member number." << endl;
			numberToTest = "";
		}
	}
}

string CAC::validName()
{
	string nameToTest;
	bool validName = false;

	cout << "Please enter a valid name." << endl;
	while(validName == false)
	{
		getline(cin, nameToTest);
		validName = true;

		if(nameToTest == "exit")
			return nameToTest;
		if(nameToTest.length() > 25)
			validName = false;
		for(int i = 0; i < nameToTest.length(); i++)
		{
			if(nameToTest[i] < 'a' || nameToTest[i] > 'z')
				if(nameToTest[i] < 'A' || nameToTest[i] > 'Z')
					if(nameToTest[i] != ' ')
						validName = false;
		}
		if(nameToTest.length() == 0 || nameToTest[0] == ' ')
			validName = false;
		if(validName == false)
		{
			cout << "Invalid name." << endl;
			cout << "Please enter a correct name." << endl;
			nameToTest = "";
		}
	}

	for(int i = 0; i < nameToTest.length(); i++)
		nameToTest[i] = toupper(nameToTest[i]);
	return nameToTest;

}

string CAC::validAddress()
{
	string addressToTest;
	bool validAddress = false;
	cout << "Please enter a valid address." << endl;
	while(validAddress == false)
	{
		validAddress = true;
		getline(cin, addressToTest);

		if(addressToTest == "exit")
			return addressToTest;
		if(addressToTest.length() > 25)
		{
			validAddress = false;
			cout << "Invalid address." << endl;
			cout << "Please enter a valid address." << endl;
			addressToTest = "";
		}
	}

	for(int i = 0; i < addressToTest.length(); i++)
	{
		if(addressToTest[i] >= 'a' && addressToTest[i] <= 'z')
			addressToTest[i] = toupper(addressToTest[i]);
	}
	return addressToTest;
}

string CAC::validCity()
{
	string cityToTest;
	bool validCity = false;
	cout << "please enter a valid city." << endl;
	while(validCity == false)
	{
		validCity = true;
		getline(cin, cityToTest);

		if(cityToTest == "exit")
			return cityToTest;
		if(cityToTest.length() > 14)
			validCity = false;
		for(int i = 0; i < cityToTest.length(); i++)
			if(cityToTest[i] < 'a' || cityToTest[i] > 'z')
				if(cityToTest[i] < 'A' || cityToTest[i] > 'z')
					validCity = false;
		if(validCity == false)
		{
			cout << "Invalid city." << endl;
			cout << "Please enter a valid city." << endl;
			cityToTest = "";
		}
	}

	for(int i = 0; i < cityToTest.length(); i++)
		if(cityToTest[i] >= 'a' && cityToTest[i] <= 'z')
			cityToTest[i] = toupper(cityToTest[i]);

	return cityToTest;
}

string CAC::validState()
{
	string stateToTest;
	bool validState = false;
	cout << "Please enter a valid state." << endl;
	cout << "Enter the states two letter representation." << endl;
	while(validState == false)
	{
		validState = true;
		getline(cin, stateToTest);

		if(stateToTest == "exit")
			return stateToTest;
		if(stateToTest.length() != 2)
			validState = false;
		for(int i = 0; i < stateToTest.length(); i++)
			if(stateToTest[i] < 'a' || stateToTest[i] > 'z')
				if(stateToTest[i] < 'A' || stateToTest[i] > 'Z')
					validState = false;

		if(validState == false)
		{
			cout << "Invalid state." << endl;
			cout << "Please enter a valid state." << endl;
			stateToTest = "";
		}
	}

	for(int i = 0; i < stateToTest.length(); i++)
		if(stateToTest[i] >= 'a' && stateToTest[i] <= 'z')
			stateToTest[i] = toupper(stateToTest[i]);
	return stateToTest;
}

string CAC::validZip()
{
	string zipToTest;
	bool validZip = false;
	cout << "Please enter a valid zip." << endl;
	while(validZip == false)
	{
		validZip = true;
		getline(cin, zipToTest);

		if(zipToTest == "exit")
			return zipToTest;
		if(zipToTest.length() != 5)
			validZip = false;
		for(int i = 0; i < zipToTest.length(); i++)
			if(zipToTest[i] < '1' || zipToTest[i] > '9')
				validZip = false;

		if(validZip == false)
		{
			cout << "Invalid zip." << endl;
			cout << "Please enter a valid zip." << endl;
			zipToTest = "";
		}
	}
	return zipToTest;
}

int CAC::addMember()
{
	clearScreen();
	cout << "Member Creation" << endl;
	cout << "Type exit to quit." << endl;	
	string memberNumber = validMemberNumber();
	if(memberNumber == "exit")
		return -1;

	string memberName = validName();
	if(memberName == "exit")
		return -1;

	string memberAddress = validAddress();
	if(memberAddress == "exit")
		return -1;

	string memberCity = validCity();
	if(memberCity == "exit")
		return -1;

	string memberState = validState();
	if(memberState == "exit")
		return -1;

	string memberZip = validZip();
	if(memberZip == "exit")
		return -1;

	member tempMember(memberName, memberAddress, memberCity, memberState, memberZip, memberNumber, true);

	tempMember.display();	

	cout << "Member will be created." << endl;

	if (MemberList->add(tempMember) == false) 
	{
		std::cout << "Falied to add member to MemberList\n";
		return 0;
	}
	if (MemberList->writeToTxt() == false) {
		std::cout << "Falied to add member to MemberList text file\n";
		return 0;
	}
	else
	{
		cout << "Press any key to return to menu." << endl;
		getline(cin, memberZip); //Changes to the string wont matter because you are exiting function.
		clearScreen();
		return 1;	
	}
}

int CAC::modMember()
{

	clearScreen();
	cout << "Please enter a valid member number." << endl;
	string memberNumber;
	bool validNumber = false;

	while(validNumber == false)
	{
		getline(cin, memberNumber);
		validNumber = true;
		if(memberNumber == "exit")
			return -1;
		if(MemberList->find(memberNumber) == NULL)
			validNumber = false;
		if(validNumber == false)
		{
			cout << "Member number doesn't exist." << endl;
			cout << "Please enter existing member number." << endl;
		}
	}


	clearScreen();

	member *memberToEdit = MemberList->find(memberNumber);
	memberToEdit->display();

	cout << "What would you like to change?" << endl;
	cout << "1) Change status" << endl;
	cout << "2) Change Name" << endl;
	cout << "3) Change address" << endl;
	cout << "4) Change city" << endl;
	cout << "5) Change state" << endl;
	cout << "6) Change Zip" << endl;

	string adminInput;
	while(adminInput.length() != 1 && adminInput[0] < '1' || adminInput[0] > '6')
	{
		getline(cin, adminInput);
		if(adminInput == "exit")
			return -1;
	}

	if (adminInput == "1") {
		if(adminInput == "exit")
			return -1;
		MemberList->find(memberNumber)->changeStatus();
		cout << "Status changed. Please hit enter to return to main menu." << endl;
		getline(cin, adminInput);
	}
	else if (adminInput == "2") {
		adminInput = validName();
		if(adminInput == "exit")
			return -1;
		MemberList->find(memberNumber)->setName(adminInput);
		cout << "Name changed. Please hit enter to return to main menu." << endl;
		getline(cin, adminInput);
	}
	else if (adminInput == "3") {
		adminInput = validAddress();
		if(adminInput == "exit")
			return -1;
		MemberList->find(memberNumber)->setStreet(adminInput);
		cout << "Address changed. Please hit enter to return to main menu." << endl;
		getline(cin, adminInput);
	}
	else if (adminInput == "4") {
		adminInput = validCity();
		if(adminInput == "exit")
			return -1;
		MemberList->find(memberNumber)->setCity(adminInput);
		cout << "City changed. Please hit enter to return to main menu." << endl;
		getline(cin, adminInput);
	}
	else if (adminInput == "5") {
		adminInput = validState();

		if(adminInput == "exit")
			return -1;
		MemberList->find(memberNumber)->setState(adminInput);
		cout << "State changed. Please hit enter to return to main menu." << endl;
		getline(cin, adminInput);
	}
	else if (adminInput == "6") {
		adminInput = validZip();
		if(adminInput == "exit")
			return -1;
		MemberList->find(memberNumber)->setZip(adminInput);
		cout << "Zip changed. Please hit enter to return to main menu." << endl;
		getline(cin, adminInput);
	}
	MemberList->writeToTxt();
	clearScreen();
	return 1;

}

int CAC::remMember(){
	clearScreen();
	std::string adminInput;
	std::string option;
	bool validNumber = false;
	bool exit = false;

	while (validNumber == false){
		validNumber = validateMember(adminInput);
	}
	clearScreen();
	MemberList->find(adminInput)->display();

	while (exit == false) {
		std::cout << "Are you sure you wish to delete the following user? ";
		cin >> option;

		if (option == "yes") {
			MemberList->remove(adminInput);
			MemberList->writeToTxt();
			exit = true;
		}
		else if (option == "no") {
			exit = true;
		}
	}
}

int CAC::addProvider(){

	clearScreen();

	string providerNumber = validProviderNumber();
	if(providerNumber == "exit")
		return -1;

	string providerName = validName();
	if(providerName == "exit")
		return -1;

	string providerAddress = validAddress();
	if(providerAddress == "exit")
		return -1;

	string providerCity = validCity();
	if(providerCity == "exit")
		return -1;

	string providerState = validState();
	if(providerState == "exit")
		return -1;

	string providerZip = validZip();
	if(providerZip == "exit")
		return -1;

	string providerPassword;
	cout << "Please enter a valid password." << endl;
	while(providerPassword.length() > 20 || providerPassword.length() ==0)
	{
		getline(cin, providerPassword);
		if(providerPassword == "exit")
			return -1;
		if(providerPassword.length() > 20)
		{
			cout << "Invalid password. Please enter a new one." << endl;
			providerPassword = "";
		}
	}




	provider tempProvider(providerName, providerAddress, providerCity, providerState, providerZip, providerNumber,providerPassword);
	tempProvider.display();

	if (ProviderList->add(tempProvider) == false) {
		std::cout << "Falied to add member to MemberList\n";
		return 0;
	}
	if (ProviderList->writeToTxt() == false) {
		std::cout << "Falied to add member to MemberList text file\n";
		return 0;
	}
	return 1;
}

int CAC::modProvider(){
	clearScreen();
	string providerNumber;
	bool existingNumber = false;

	while(existingNumber == false)
	{
		existingNumber = true;
		cout << "Please enter an existing provider number." << endl;
		getline(cin, providerNumber);

		if(providerNumber == "exit")
			return -1;
		if(ProviderList->find(providerNumber) == NULL)
			existingNumber = false;

		if(existingNumber == false)
		{
			cout << "Invalid provider number." << endl;
			cout << "Please enter an existing provider number." << endl;
			providerNumber = "";
		}
	}
		clearScreen();
		provider *providerToEdit = ProviderList->find(providerNumber);
		providerToEdit->display();

		std::cout << "\nWhat would you like to change?\n" << endl;
		cout << "1) Change password" << endl;
		cout << "2) Change Name" << endl;
		cout << "3) Change address" << endl;
		cout << "4) Change city" << endl;
		cout << "5) Change state" << endl;
		cout << "6) Change Zip" << endl;
		cout << "7) Return to main menu" << endl;


		string adminInput;
		while(adminInput.length() != 1 && adminInput[0] < '1' || adminInput[0] > '7')
		{
			getline(cin, adminInput);
			if(adminInput == "exit" || adminInput == "7")
				return -1;
		}


		if (adminInput == "1") {
			cout << "Please enter a new password." << endl;
			adminInput = "";
			while(adminInput.length() > 20 || adminInput.length() == 0)
			{
				getline(cin, adminInput);
			}
			cout << "Password set." << endl;
			ProviderList->find(providerNumber)->setPassword(adminInput);
			cout << "Please hit enter to return to the main menu." << endl;
			getline(cin, adminInput);
		}
		else if (adminInput == "2") {
			adminInput = validName();
			ProviderList->find(providerNumber)->setName(adminInput);
			cout << "Name changed." << endl;
			cout << "Please hit enter to return to the main menu." << endl;
			getline(cin, adminInput);
		}
		else if (adminInput == "3") {
			adminInput = validAddress();
			ProviderList->find(providerNumber)->setStreet(adminInput);
			cout << "Address changed." << endl;
			cout << "Please hit enter to return to the main menu." << endl;
			getline(cin, adminInput);
		}
		else if (adminInput == "4") {
			adminInput = validCity();
			ProviderList->find(providerNumber)->setCity(adminInput);
			cout << "City changed." << endl;
			cout << "Please hit enter to return to the main menu." << endl;
			getline(cin, adminInput);
		}
		else if (adminInput == "5") {
			adminInput = validState();
			ProviderList->find(providerNumber)->setState(adminInput);
			cout << "State changed." << endl;
			cout << "Please hit enter to return to the main menu." << endl;
			getline(cin, adminInput);
		}
		else if (adminInput == "6") {
			adminInput = validZip();
			ProviderList->find(providerNumber)->setState(adminInput);
			cout << "Zip changed." << endl;
			cout << "Please hit enter to return to the main menu." << endl;
			getline(cin, adminInput);
		}
		
	
	ProviderList->writeToTxt();
	clearScreen();
	return 1;
}

int CAC::remProvider(){
	clearScreen();
	std::string adminInput;
	std::string option;
	bool validNumber = false;
	bool exit = false;

	while (validNumber == false) {
		validNumber = validateProvider(adminInput);
	}
	clearScreen();
	ProviderList->find(adminInput)->display();

	while (exit == false) {
		std::cout << "Are you sure you wish to delete the following provider? ";
		cin >> option;

		if (option == "yes") {
			ProviderList->remove(adminInput);
			ProviderList->writeToTxt();
			exit = true;
		}
		else if (option == "no") {
			exit = true;
		}
	}
}

void CAC::providerMenu(){
	string adminInput;
	bool exit = false;

	while (exit == false) {
		//clearScreen();
		cout << "Please select an option" << endl;

		cout << "1) Validate Member" << endl;
		cout << "2) Log a service" << endl;
		cout << "3) Display Service Directory" << endl;

		std::cin >> adminInput;

		if (adminInput == "1") {
			validateMember(adminInput);
		}
		else if (adminInput == "2") {
			logService();
		}
		else if (adminInput == "3") {
			displayServices();
		}
		else if (adminInput == "exit") {
			loggedProviderID = "";
			exit = true;
		}
	}
	clearScreen();
}

bool CAC::validateMember(std::string & number) {
	bool validNumber = false;
	bool displayMember = false;

	if (number == "1") {
		displayMember = true;
	}

	while (validNumber == false)
	{
		cout << "Please enter a valid member number, or type exit to return to main menu." << endl;
		cin >> number;
		validNumber = true;

		if (number.length() != 9)
		{
			validNumber = false;
			std::cout << "ID must be 9 digits long!\n" << endl;
		}

		for (int i = 0; i < number.length(); i++) {
			if (isdigit(number.at(i)) == false) {
				validNumber = false;
				std::cout << "ID must only contain digits!\n" << endl;
			}
		}
	}

	//	Tests to see if the number is already in use.
	if (MemberList->find(number) != NULL) {
		if (displayMember == true) {
			clearScreen();
			MemberList->find(number)->display();
			cout << "Press anykey to exit.";
			cin.ignore();
			cin.get();
		}
		return true;
	}
	else {
		return false;
	}
}

bool CAC::validateService(std::string & number) {
	bool validNumber = false;

	while (validNumber == false)
	{
		cout << "Please enter a valid service number, or type exit to return to the main menu." << endl;
		cin >> number;
		validNumber = true;

		if (number.length() != 6)
		{
			validNumber = false;
			std::cout << "ID must be 9 digits long!\n" << endl;
		}

		for (int i = 0; i < number.length(); i++) {
			if (isdigit(number.at(i)) == false) {
				validNumber = false;
				std::cout << "ID must only contain digits!\n" << endl;
			}
		}
	}

	//	Tests to see if the number is already in use.
	if (SeriveList->find(number) != NULL) {
		return true;
	}
	else {
		return false;
	}
}

bool CAC::validateProvider(std::string & number){
	bool validNumber = false;

	while (validNumber == false)
	{
		cout << "Please enter a valid provider number, or type exit to return to the main menu." << endl;
		cin >> number;
		validNumber = true;

		if (number.length() != 9)
		{
			validNumber = false;
			std::cout << "ID must be 9 digits long!\n" << endl;
		}

		for (int i = 0; i < number.length(); i++) {
			if (isdigit(number.at(i)) == false) {
				validNumber = false;
				std::cout << "ID must only contain digits!\n" << endl;
			}
		}
	}

	//	Tests to see if the number is already in use.
	if (ProviderList->find(number) != NULL) {
		return true;
	}
	else {
		return false;
	}
}

/*bool CAC::validate_service(std::string & number){
  bool validNumber = false;
  while (validNumber == false){
  cout << "Please enter a valid service number, or type exit to return to the main menu." << endl;
  cin >> number;
  validNumber = true;

  if (number.length() != 6){
  validNumber = false;
  std::cout << "ID must be 6 digits long!\n" << endl;
  }

  for (int i = 0; i < number.length(); i++) {
  if (isdigit(number.at(i)) == false) {
  validNumber = false;
  std::cout << "ID must only contain digits!\n" << endl;
  }
  }
  }
  if (ServiceList->find(number) != NULL) {
  return true;
  }else{
  return false;
  }
  }*/

void CAC::logService() {
	//ask for member pin
	std::string memberID;
	std::string providerID;
	bool validNumber = false;

	while (validNumber == false) {
		validNumber = validateMember(memberID);
	}

	validNumber = false;

	//ask for service code
	std::string serviceID;
	while (validNumber == false) {
		validNumber = validateService(serviceID);
	}

	//ask user for date of services
	std::string date;
	std::cout << "Enter the date of service: ";
	std::cin >> date;

	//ask user for comment
	std::string comment;
	std::cout << "Please enter your comment:\n";
	std::cin.ignore (); 
		
	std::getline(std::cin, comment);
	recordManager->addRecord(*MemberList->find(memberID), *ProviderList->find(loggedProviderID), *SeriveList->find(serviceID),date, comment);

}

void CAC::displayServices() {
	SeriveList->display();
	cout << "Press anykey to exit.";
	cin.ignore();
	cin.get();
}

void CAC::reportMenu(){
	string adminInput;
	bool exit = false;

	while (exit == false) {
		clearScreen();
		cout << "Please select an option, or type exit to quit." << endl;

		cout << "1) Generate Member Reports" << endl;
		cout << "2) Generate Provider Reports" << endl;
		cout << "3) Generate EFT Reports" << endl;
		cout << "4) Generate Summary Reports" << endl;
		cout << "5) Generate Weekly Reports" << endl;

		std::cin >> adminInput;

		if (adminInput == "1") {
			adminInput = "";
			if (validateMember(adminInput) == true) {
				generateMemberReport(adminInput);
			}
		}
		else if (adminInput == "2") {
			generateProviderReport(loggedProviderID);
		}
		else if (adminInput == "3") {
			if (validateProvider(adminInput) == true) {
				generateEFTReport(loggedProviderID);
			}
		}
		else if (adminInput == "4") {
			generateSummaryReport();
		}
		else if (adminInput == "5") {
			generateWeekly();
		}
		else if (adminInput == "exit") {
			exit = true;
		}
	}
	clearScreen();
}

void CAC::generateMemberReport(std::string memberNumber){
	recordManager->writeMemberReport(memberNumber);
}

void CAC::generateProviderReport(std::string providerNumber){
	recordManager->writeProviderReport(providerNumber);
}

void CAC::generateEFTReport(std::string providerNumber){
	recordManager->writeEFT(providerNumber);
}

void CAC::generateSummaryReport(){
	recordManager->writeSummaryReport();
}

void CAC::generateWeekly(){
	recordManager->writeSummaryReport();
}

void CAC::clearScreen(){
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	system("CLS");
#else
	system("clear");
#endif
}
