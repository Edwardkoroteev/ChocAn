#ifndef MANAGERLIST
#define MANAGERLIST

#include "manager.h"

class managerList{
    private:
        struct node{
            manager* data;
            node * next;
        };

        node * head;
        node * tail;
        string myFile; //Name of file for read/write

        int adding(const manager & toAdd, node * & head);
        //Recursive dding function. Adds manager object if none exist with an identical username

        void splitString(const string & toSplit, string * & returnArray, const char delim, int & arraySize);
        //Splits a delimited string. Used for file read in

        void nuke(node * & head);
        //Recursive destructor. Deallocates memory of node->data & node

        manager* find(const string & number, node * head);
        //Recursive find function. Returns a matching manager pointer or NULL

        bool remove(const string & username, node * & head);
        //Recursive remove function. Removes a specific manager

    public:
        managerList();
        //Constructor

        managerList(const string & fromFile);
        //Constructor to generate list from a file

        ~managerList();
        //Destrucor

        bool add(const manager & toAdd);
        //Wrapper for adding a manager to the list

        bool remove(const string & username);
        //Wrapper for removing a manager from the list

        bool writeToTxt(const string & filename);
        //Writes the manager list to filename

        bool writeToTxt();
        //Writes the manager list to the file specified by myFile

        manager* find(const string & name);
        //Wrapper for finding a specific manager, returns a pointer or NULL.
};

#endif
