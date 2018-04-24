#ifndef PROVIDERLIST
#define PROVIDERLIST

#include "provider.h"
#include "RecordManager.h"

using namespace std;

class providerList{
    private:
        struct node{
            provider* data;
            node * next;
        };

        node * head;
        node * tail;
        string myFile; //Name of file for read/write

        int adding(const provider & theProvider, node * & current);
        //Recursive adding function. Adds provider object if none exist with an identical P-PIN

        void splitString(const string & toSplit, string * & returnArray, const char delim, int & arraySize);
        //Splits a delimited string. Used for file read in

        void display(node * head);
        //Recursive display funtion. Displays all Providers in list

        void nuke(node * & head);
        //Recursive destructor. Deallocates memory of node->data & node
        
        provider* find(const string & number, node * head);
        //Recursive find function. Returns a matching provider pointer or NULL

        bool remove(const string & number, node * & head);
        //Recursive remove function. Removes a specific provider

    public:
        providerList();
        //constructor;

        providerList(const string & fromFile);
        //Constructor to generate list from a file

        ~providerList();
        //Destructor

        bool add(const provider & providerObj);
        //Wrapper for adding a provider to the list

        bool remove(const string & number); 
        //Wrapper for removing a provider from the list

        bool writeToTxt(const string & filename);
        //Writes the provider list to filename

        bool writeToTxt();
        //Writes the provider list to the file specified by myFile

        provider* find(const string & number);
        //Wrapper for finding a specific provider, returns pointer or NULL

        int writeProviderReports(RecordManager & records);
        //Writes a Provider report from <records> for all providers in <this>

        void display();
        //display wrapper
};

#endif
