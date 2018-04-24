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

providerList::providerList()
{
	/*********************************************************
	* Default providerList constructor
	* Initializes private variables
	*********************************************************/
    head = NULL;
    tail = NULL;
    myFile = "";
}

providerList::providerList(const string & fromFile)
{
    /*************************************************************************
     * Populates the providerList with the contents of <fromFile>
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
            if(splitLine != NULL && arraySize == 7) //Split the line from the DB, create a provider object from that data
                add(provider(splitLine[0], splitLine[1], splitLine[2], splitLine[3], splitLine[4], splitLine[5], splitLine[6]));
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

bool providerList::writeToTxt()
{
    /*****************************************************************
     * Calls writeToTxt(string) with the member string that contains
     * the file the database the program was read from
     ****************************************************************/
    return writeToTxt(myFile);
}

bool providerList::writeToTxt(const string & filename)
{
    /*****************************************************************
     * Writes the provider list to the file <filename>
     * Uses the provider function prepareWrite() to output the strings
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

providerList::~providerList()
{
    /*****************************************
     * Destructor, wrapper that calls nuke
     ****************************************/
    nuke(head);
}

void providerList::nuke(node * & head)
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

bool providerList::add(const provider & toAdd)
{
    /*********************************************************************
     * Wrapper function for adding providers to the list
     * Returns true on successful add. False on unsuccessful add.
     * Add will be unsuccessful if the P-PIN already exists in the list
     * Providers are insorted in alphabetical order based on name.
     ********************************************************************/
    if(adding(toAdd, head) > 0)
        return true;
    else return false;
}

int providerList::adding(const provider & toAdd, node * & head)
{
    /*********************************************************************
     * Recursive function for adding providers to the list
     * Returns true on successful add. False on unsuccessful add.
     * Add will be unsuccessful if the P-PIN already exists in the list
     * Providers are insorted in alphabetical order based on name.
     ********************************************************************/
    int response = 0;
    if(!this->head)
    {
        //List is empty. Creating first node
        head = new node;
        head->next = NULL;
        head->data = new provider(toAdd);
        return 1;
    }
    if(!head)
    {
        //Recursed to end of list and did not find a matching P-PIN
        return 1;
    }
    else if( *(head->data) == toAdd) //Found match. Exit without add.
        return 0;
    response += adding(toAdd, head->next);
    if(response == 1)
    {
        //We've managed to hit the end of the list without a match. Time to check
        //if we can add the provider in sorted order.
        if( *(head->data) < toAdd)
        {
            //toAdd is greater than current node. That means it must be inserted
            node * current = new node;
            current->data = new provider(toAdd);
            current->next = head->next;
            head->next = current;
            return ++response; //Increment response, so we can't add again
        }
        else if(this->head == head && *(head->data) > toAdd)
        {
            //Current node is the head of the list and toAdd comes first alphabetically
            //toAdd must become first node
            node * current = new node;
            current->data = new provider(toAdd);
            current->next = head;
            head = current;
            return ++response; //Increment response, so we can't add again
        }
    }
    return response;
}

void providerList::display()
{
	/*****************************************************
	* Display public wrapper function that will call the
	* display private function
	*****************************************************/
    display(head);
}

void providerList::display(node * head)
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

provider * providerList::find(const string & number)
{
    /***************************************************************
     * Wrapper, will return a pointer to a provider in the list
     * if a provider with a matching P-PIN to <number> is found
     ***************************************************************/
    return find(number, head);
}

provider * providerList::find(const string & number, node * head)
{
    /***************************************************************
     * Recursive function, will return a pointer to a provider in the
     * list if, a provider with a matching P-PIN to <number> is found
     ***************************************************************/
    if(!head)
        return NULL;
    else if(head->data->numberMatch(number))
        return head->data;
    return find(number, head->next);
}

bool providerList::remove(const string & number)
{
    /******************************************************************
     * Wrapper function, will remove a provider with a P-PIN matching
     * <number> and return true if it exists. Returns false otherwise
     ******************************************************************/
    return remove(number, head);
}

bool providerList::remove(const string & number, node * & head)
{
    /******************************************************************
     * Recursive function, will remove a provider with a P-PIN matching
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

int providerList::writeProviderReports(RecordManager & records)
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
    return count;
    /*
    if(count >0)
        return true;
    else
        return false;
        */
}

void providerList::splitString(const string & toSplit, string * & returnArray, const char delim, int & arraySize)
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


