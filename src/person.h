#ifndef PERSON_h
#define PERSON_h
#include <iostream>
#include <string>

using namespace std;

//abstract base class for member and person
//contains the name and complete address of the person
class person{
    friend class RecordManager;
    public:
        //base constructor
        person();
        //constructor takes 5 strings throws a string if of an unnacceptable length
        person(const string& name,const string& street,const string& city,const string& state,const string& zip);
        //copy constructor takes a person as an argument;
        person(const person&);     
        virtual ~person();
        //create takes 5 strings and sets class paramaters throws the string if of an unnacceptable length
        bool create(const string& name,const string& street,const string& city,const string& state,const string& zip);
        //copy funciton takes a person as an argument, parses into strings and calls create
        bool copy(const person&);          
        //pure virtual display for abstract base class
        virtual void display() = 0;     

    protected:
        string name;        //string for a persons name, 20 char limit
        string street;      //string for street address, 25 char limit
        string city;        //string for city name, 14 character limit        
        string state;       //string for state abbreviation, 2 char limit
        string zip;         //string for zip code, 5 character limit
};
#endif
//person.h ends definition
