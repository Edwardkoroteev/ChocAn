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


managerList::managerList()
{
	/*************************************************************
	* Default managerList constructor.
	* Initializes private variables
	*************************************************************/

    head = NULL;
    tail = NULL;
    myFile = "";
}

managerList::managerList(const string & fromFile)
{
    /*************************************************************************
     * Populates the managerList with the contents of <fromFile>
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
            if(splitLine != NULL && arraySize == 2)
                add(manager(splitLine[0], splitLine[1]));
            else
                cout << "ERROR IN EXPECTED LINE FORMAT" << endl;

            getline(file, line);
        }
    }

    if(splitLine)
    {
        delete [] splitLine;
        splitLine = NULL;
    }
}

bool managerList::add(const manager & toAdd)
{
    /*********************************************************************
     * Wrapper function for adding managers to the list
     * Returns true on successful add. False on unsuccessful add.
     * Add will be unsuccessful if the username already exists in the list
     * managers are insorted in alphabetical order based on name.
     ********************************************************************/
    if(adding(toAdd, head) > 0)
        return true;
    else
        return false;
}

int managerList::adding(const manager & toAdd, node * & head)
{
    /*********************************************************************
     * Recursive function for adding managers to the list
     * Returns true on successful add. False on unsuccessful add.
     * Add will be unsuccessful if the username already exists in the list
     * managers are insorted in alphabetical order based on name.
     ********************************************************************/
    int response = 0;

    if(!this->head)
    {
        //List is empty. Creating first node.
        head = new node;
        head->next = NULL;
        head->data = new manager(toAdd);
        return 1;
    }
    if(!head)
    {
        //Recursed to the end of the list and did not find matching username
        return 1;
    }
    else if( *(head->data) == toAdd) //Found match. Exit without add.
        return 0;
    response += adding(toAdd, head->next);
    if(response == 1)
    {
        //We've managed to hit the end of the list without a match. Time to check
        //if we can add the manager in sorted order.
        if( *(head->data) < toAdd)
        {
            //toAdd is greater than current node. That means it must be inserted
            node * current = new node;
            current->data  = new manager(toAdd);
            current->next = head->next;
            head->next = current;
            return ++response; //Increment response, so we can't add again
        }
        else if(this->head == head && *(head->data) > toAdd)
        {
            //Current node is the head of the list and toAdd comes first alphabetically
            //toAdd must become first node
            node * current = new node;
            current->data = new manager(toAdd);
            current->next = head;
            head = current;
            return ++response; //Increment response, so we can't add again
        }
    }
    return response;
}

void managerList::splitString(const string & toSplit, string * & returnArray, const char delim, int & arraySize)
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

managerList::~managerList()
{
    /*****************************************
     * Destructor, wrapper that calls nuke
     ****************************************/
    nuke(head);
}

void managerList::nuke(node * & head)
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

manager* managerList::find(const string & username)
{
    /***************************************************************
     * Wrapper, will return a pointer to a manager in the list
     * if a manager with a matching username is found
     ***************************************************************/
    return find(username, head);
}

manager* managerList::find(const string & username , node * head)
{
    /***************************************************************
     * Recursive function, will return a pointer to a manager in the
     * list if, a manager with a matching username is found
     ***************************************************************/
    if(!head)
        return NULL;
    else if(head->data->isUsername(username))
        return head->data;
    return find(username, head->next);
}

bool managerList::remove(const string & username, node * & head)
{
    /******************************************************************
     * Recursive function, will remove a manager with a matching
     * username and return true if it exists. Returns false otherwise
     ******************************************************************/
    if(!head)
        return false;

    else if(head->data->isUsername(username))
    {
        node * current = head;
        head = head->next;
        current->next = NULL;
        nuke(current);
        return true;
    }
    else
        return remove(username, head->next);
}

bool managerList::remove(const string & username)
{
    /******************************************************************
     * Wrapper function, will remove a manager with a matching
     * username and return true if it exists. Returns false otherwise
     ******************************************************************/
    return remove(username, head);
}

bool managerList::writeToTxt(const string & filename)
{
    /*****************************************************************
     * Writes the manager list to the file <filename>
     * Uses the manager function prepareWrite() to output the strings
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

//Testing functions
bool managerList::writeToTxt()
{
    /*****************************************************************
     * Calls writeToTxt(string) with the member string that contains
     * the file the database the program was read from
     ****************************************************************/
    return writeToTxt(myFile);
}

