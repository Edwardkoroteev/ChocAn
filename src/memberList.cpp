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
#include <cstdlib>
#include <cctype>
#include <string>

memberList::memberList()
{
	/*************************************************************
	* Default memberList constructor that will initiazlize
	* private variables
	*************************************************************/
    head = NULL;
    tail = NULL;
    myFile = "";
}

memberList::memberList(const string & fromFile)
{
    /*************************************************************************
     * Populates the memberList with the contents of <fromFile>
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
            if(splitLine != NULL && arraySize == 7) //Split the line from the DB, creating a member object from the data
                add(member(splitLine[0], splitLine[1], splitLine[2], splitLine[3], splitLine[4], splitLine[5], atoi(splitLine[6].c_str())));
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

bool memberList::writeToTxt()
{
    /*****************************************************************
     * Calls writeToTxt(string) with the member string that contains
     * the file the database the program was read from
     ****************************************************************/
    return writeToTxt(myFile);
}

bool memberList::writeToTxt(const string & filename)
{
    /*****************************************************************
     * Writes the member list to the file <filename>
     * Uses the member function prepareWrite() to output the strings
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

memberList::~memberList()
{
    /*****************************************
     * Destructor, wrapper that calls nuke
     ****************************************/
    nuke(head);
}

void memberList::nuke(node * & head)
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

bool memberList::add(const member & toAdd)
{
    /*********************************************************************
     * Wrapper function for adding members to the list
     * Returns true on successful add. False on unsuccessful add.
     * Add will be unsuccessful if the M-PIN already exists in the list
     * members are insorted in alphabetical order based on name.
     ********************************************************************/
    if(adding(toAdd, head) > 0)
        return true;
    else return false;
}

int memberList::adding(const member & toAdd, node * & head)
{
    /*********************************************************************
     * Recursive function for adding members to the list
     * Returns true on successful add. False on unsuccessful add.
     * Add will be unsuccessful if the M-PIN already exists in the list
     * members are insorted in alphabetical order based on name.
     ********************************************************************/
    int response = 0;
    if(!this->head)
    {
        //List is empty. Creating first node
        head = new node;
        head->next = NULL;
        head->data = new member(toAdd);
        return 1;
    }
    if(!head)
    {
        //Recursed to end of list and did not find a matching M-PIN
        return 1;
    }
    else if( *(head->data) == toAdd) //Found match. Exit without add.
        return 0;
    response += adding(toAdd, head->next);
    if(response == 1)
    {
        //We've managed to hit the end of the list without a match. Time to check
        //if we can add the member in sorted order.
        if( *(head->data) < toAdd)
        {
            //toAdd is greater than current node. That means it must be inserted
            node * current = new node;
            current->data = new member(toAdd);
            current->next = head->next;
            head->next = current;
            return ++response; //Increment response, so we can't add again
        }
        else if(this->head == head && *(head->data) > toAdd)
        {
            //Current node is the head of the list and toAdd comes first alphabetically
            //toAdd must become first node
            node * current = new node;
            current->data = new member(toAdd);
            current->next = head;
            head = current;
            return ++response; //Increment response, so we can't add again
        }
    }
    return response;
}

void memberList::display()
{
	/*****************************************************
	* Display public wrapper function that will call the
	* display private function
	*****************************************************/
    display(head);
}

void memberList::display(node * head)
{
	/**********************************************************
	* Display private function that will display the entire
	* list of the service objects
	**********************************************************/
    if(!head)
        return;
    else
    {
        head->data->display();
        display(head->next);
    }
}

member * memberList::find(const string & number)
{
    /***************************************************************
     * Wrapper, will return a pointer to a member in the list
     * if a member with a matching M-PIN to <number> is found
     ***************************************************************/
    return find(number, head);
}

member * memberList::find(const string & number, node * head)
{
    /***************************************************************
     * Recursive function, will return a pointer to a member in the
     * list if, a member with a matching M-PIN to <number> is found
     ***************************************************************/
    if(!head)
        return NULL;
    else if(head->data->numberMatch(number))
        return head->data;
    return find(number, head->next);
}

bool memberList::remove(const string & number)
{
    /******************************************************************
     * Wrapper function, will remove a member with a M-PIN matching
     * <number> and return true if it exists. Returns false otherwise
     ******************************************************************/
    return remove(number, head);
}

bool memberList::remove(const string & number, node * & head)
{
    /******************************************************************
     * Recursive function, will remove a member with a M-PIN matching
     * <number> and return true if it exists. Returns false otherwise
     ******************************************************************/
    if(!head)
        return false;
    else if (head->data->numberMatch(number))
    {
        node * current = head;
        head = head->next;
        current->next = NULL;
        nuke(current);
        return true;
    }
    else
        return remove(number, head->next);
}

int memberList::writeMemberReports(RecordManager & records)
{
    int count = 0;
    string line;
    string * splitLine = NULL;
    int arraySize = 0;

    node * current = head;
    while(current)
    {
        line = current->data->prepareWrite();
        splitString(line, splitLine, '|', arraySize);
        if(splitLine != NULL && arraySize == 7)
        {
            //records.writeProviderReport(splitLine[5]);
            if(records.writeProviderReport(splitLine[5]))
                ++count;
        }
        current = current->next;
    }

    if(splitLine)
    {
        delete [] splitLine;
        splitLine = NULL;
    }
    /*
    if(count > 0)
        return true;
    else
        return false;
        */
    return count;
}

void memberList::splitString(const string & toSplit, string * & returnArray, const char delim, int & arraySize)
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


