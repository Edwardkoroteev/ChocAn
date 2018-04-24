#include "providerList.h"
#include "memberList.h"
#include "serviceList.h"
#include "managerList.h"
#include "provider.h"
#include "member.h"
#include "service.h"
#include "manager.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <string>
#include <cstdlib>

serviceList::serviceList()
{
	/************************************************************************
	* Default serviceList constructor
	* Initializes the private variables
	************************************************************************/

    head = NULL;
    tail = NULL;
    myFile = "";
}

serviceList::serviceList(const string & fromFile)
{
    /*************************************************************************
     * Populates the service with the contents of <fromFile>
     * If the file is empty, nothing is added and head/tail are set to NULL
     *************************************************************************/

    head = NULL;
    tail = NULL;
    myFile = fromFile;

    ifstream file;
    file.open(fromFile.c_str());

    string line;
    string * splitLine = NULL;
    int arraySize = 0;

    if(file)
    {
        getline(file, line); //Prime the pump

        while(file && !file.eof())
        {
            splitString(line, splitLine, '|', arraySize);
            if(splitLine != NULL && arraySize == 3) //Split the line from the DB, create a service object from the data
            {
                add(service(splitLine[1], splitLine[0], strtof(splitLine[2].c_str(), NULL)));
            }
            else
                cout << "ERROR IN EXPECTED LINE FORMAT" << endl;
            getline(file, line);
        }
        file.close();
        file.clear();
    }

    if(splitLine)
    {
        delete [] splitLine;
        splitLine = NULL;
    }
}

serviceList::~serviceList()
{
	/********************************************************************
	* Default destructor
	********************************************************************/
    nuke(head);
}

int serviceList::add(const service & serviceObj, node * & head)
{
    /*********************************************************************
     * Recursive function for adding services to the list
     * Returns 2 on successful add. 0 on unsuccessful add.
     * Add will be unsuccessful if the service code already exists in the list
     * Services are insorted in alphabetical order based on description.
     ********************************************************************/
    int response = 0;
    if(!this->head)
    {
        head = new node;
        //List is empty. Creating first node
        head->next = NULL;
        head->data = new service(serviceObj);
        return 1;
    }
    if(!head)
    {
        //Recursed to end of list and did not find a matching service code
        return 1;
    }
    else if( *(head->data) == serviceObj) //Found match. Exit without add.
        return 0;
    response += add(serviceObj, head->next);
    if(response == 1)
    {
        //We've managed to hit the end of the list without a match. Time to check
        //if we can add the service in sorted order.
        if( *(head->data) < serviceObj)
        {
            //serviceObj is greater than current node. That means it must be inserted
            node * current = new node;
            current->data = new service(serviceObj);
            current->next = head->next;
            head->next = current;
            return ++response; //Increment response, so we can't add again
        }
        else if(this->head ==  head && *(head->data) > serviceObj)
        {
            //Current node is the head of the list and serviceObj comes first alphabetically
            //serviceObj must become first node
            node * current = new node;
            current->data = new service(serviceObj);
            current->next = head;
            head = current;
            return ++response; //Increment response, so we can't add again
        }
    }
    return response;
}

bool serviceList::add(const service & serviceObj)
{
    /*********************************************************************
     * Wrapper function for adding services to the list
     * Returns true on successful add. False on unsuccessful add.
     * Add will be unsuccessful if the service code already exists in the list
     * Services are insorted in alphabetical order based on description.
     ********************************************************************/
    if(add(serviceObj, head) > 0)
        return true;
    else
        return false;
}

void serviceList::splitString(const string & toSplit, string * & returnArray, const char delim, int & arraySize)
{
    /***********************************************************************
     * Splits the string <toSplit> into an array of strings, <returnArray>,
     * of size <arraySize>, based off of the delimiter <delim>.
     * expects <returnArray> to be NULL, if not NULL, deletes <returnArray>
     ***********************************************************************/
    if(returnArray != NULL)
    {
        delete [] returnArray;
        returnArray = NULL;
    }

    arraySize = 1;

    for(unsigned int i = 0; i < toSplit.size(); ++i)
    {
        if(toSplit[i] == delim)
            arraySize++;
    }

    returnArray = new string[arraySize];

    for(unsigned int i = 0, j = 0; i < toSplit.size(); ++i)
    {
        if(toSplit[i] != delim)
            returnArray[j] += toSplit[i];
        else
            j++;
    }
    return;
}

void serviceList::display(node * current)
{
	/**********************************************************
	* Display private function that will display the entire
	* list of the service objects
	**********************************************************/

    if(!current)
        return;
    else
    {
        current->data->display();
        display(current->next);
    }
}

void serviceList::display()
{
	/*****************************************************
	* Display public wrapper function that will call the
	* display private function
	*****************************************************/
    display(head);
}

void serviceList::nuke(node * & head)
{
    /*****************************************************
     * Destructor actual, deallocates memory of list
     *****************************************************/
    if(!head)
        return;
    nuke(head->next);
    if(head->data)
    {
        delete head->data;
        head->data = NULL;
    }
    delete head;
    head = NULL;
}

service * serviceList::find(const string & number)
{
    /***************************************************************
     * Wrapper, will return a pointer to a service in the list
     * if a service with a matching code to <number> is found
     ***************************************************************/
    return find(number, head);
}

service * serviceList::find(const string & number, node * & current)
{
    /***************************************************************
     * Recursive function, will return a pointer to a service in the
     * if a service with a matching code to <number> is found
     ***************************************************************/
    if(!current)
        return NULL;
    else if(current->data->numberMatch(number))
        return current->data;
    return find(number, current->next);
}

bool serviceList::writeToTxt()
{
    /*****************************************************************
     * Calls writeToTxt(string) with the member string that contains
     * the file the database the program was read from
     ****************************************************************/
    return writeToTxt(myFile);
}

bool serviceList::writeToTxt(const string & filename)
{
    /*****************************************************************
     * Writes the service list to the file <filename>
     * Uses the service function prepareWrite() to output the strings
     *****************************************************************/
    ofstream file;
    file.open(filename.c_str());

    if(file)
    {
        node * current = head;
        while(current)
        {
            file << current->data->prepareWrite() << endl;
            current = current->next;
        }
        file.close();
        file.clear();
        return true;
    }
    return false;
}

bool serviceList::remove(const string & number)
{
    /******************************************************************
     * Wrapper function, will remove a service with a code matching
     * <number> and return true if it exists. Returns false otherwise
     ******************************************************************/
    return remove(number, head);
}

bool serviceList::remove(const string & number, node * & current)
{
    /******************************************************************
     * Recursive function, will remove a service with a code matching
     * <number> and return true if it exists. Returns false otherwise
     ******************************************************************/
    if(!current)
        return false;
    else if(current->data->numberMatch(number))
    {
        node * newNode = current;
        current = current->next;
        newNode->next = NULL;
        nuke(newNode);
        return true;
    }
    else
        return remove(number, current->next);
}
