#ifndef MEMBERLIST
#define MEMBERLIST

#include "member.h"
#include "RecordManager.h"

using namespace std;

class memberList{
    private:
        struct node{
            member * data;
            node * next;
        };

        node * head;
        node * tail;
        string myFile; //Name of file for read/write

        int adding(const member & memberObj, node * & head);
        //Recursive adding function. Adds member object if none exist with an identical M-PIN

        void splitString(const string & toSplit, string * & returnArray, const char delim, int & arraySize);
        //splits a delimited string. used for file read in

        void display(node * head);
        //recursive display function

        void nuke(node * & head);
        //Recursive destructor. Deallocates memory of node->data & node

        member* find(const string & number, node * head);
        //Recursive find function. Returns a matching member pointer or NULL

        bool remove(const string & number, node * & head);
        //Recursive remove function. Removes a specific member

    public:
        memberList();
        //constructor
        
        memberList(const string & fromFile);
        //Constructor to generate list from file

        ~memberList();
        //Destructor

        bool add(const member & memberObj);
        //Wrapper for adding a member to the list

        bool remove(const string & number); 
        //Wrapper for removing a member from the list

        bool writeToTxt(const string & filename);
        //Writes the member list to filename

        bool writeToTxt();
        //Writes the member list to the file specified by myFile

        member* find(const string & number);
        //Wrapper for finding a specific member, returns a pointer or NULL

        int writeMemberReports(RecordManager & records);
        //Writes a member report for all members in <this>

        void display();
        //display wrapper
};

#endif
