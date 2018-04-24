#include "person.h"

//base class constructor initializes to empty strings
person::person(){
    name = "";
    street = "";
    city = "";
    state = "";
    zip = "";
}

//class constructor takes the necessary self documented arguments
//ensure that passed arguments are of the appropriate length before invoking
//calls the create function to set argument values
person::person(const string & name,const string & street,const string & city,const string & state,const string & zip){
    create(name,street,city,state,zip);
}

//copy constructor take a person object as an argument
//parses out the variables from the object and passes them to the create function;
person::person(const person & toCopy){
    create(toCopy.name,toCopy.street,toCopy.city,toCopy.state,toCopy.zip);
}

//create takes the self documented arguments and assigns their value to their corresponding class paramater
//returns true when all objects have been copied;
bool person::create(const string & name,const string & street,const string & city,const string & state,const string & zip){
    this->name = name;
    this->street = street;
    this->city = city;
    this->state = state;
    this->zip = zip;
    return true;
}

//takes a personobject as an argument
//parses out the variables from the object and passes them to the create function;
//returns the return of create;
bool person::copy(const person & toCopy){
    return create(toCopy.name,toCopy.street,toCopy.city,toCopy.state,toCopy.zip);
}

//Destructor that does nothing. Squelches compiler error when deleting a pointer
//to an object derived from the person class.
person::~person() {}

