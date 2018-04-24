#ifndef SERVICELIST
#define SERVICELIST

#include "service.h"

class serviceList{
private:
	struct node{
		service * data;
		node * next;
	};
	node * head;
	node * tail;
	string myFile;
	int add(const service & serviceObj, node * & head); //actual adding function
	void splitString (const string & toSplit, string * & returnArray, const char delim, int & arraySize);
	void display(node * current);
	void nuke(node * & head);
	service* find(const string & serviceNumber, node * & current);
	bool remove(const string & serviceNumber, node * & current);

public:
	serviceList();
    serviceList(const string & fromFile); //Constructor to read from file.
	~serviceList(); //Not sure if destructor is needed
	bool add(const service & serviceObj); //adding wrapper
	bool remove(const string & serviceNumber); 
	bool writeToTxt(const string & filename);
	bool writeToTxt();
	service* find(const string & serviceNumber);
	void display(); //display wrapper
};

#endif

