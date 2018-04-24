#ifndef MANAGER_h
#define MANAGER_h
#include <iostream>
#include <string>

using namespace std;

//manager class object deals with username and passwords for admins
class manager{
    public:
        //default constructor
        manager();
        //paramaterized constructor
        manager(const string& username,const string& password);
        //copy constructor
        manager(const manager&);
        //create funciton initializes to arguments
        void create(const string& username, const string& password);
        //copy function makes a deep copy of arg data
        void copy(const manager&);
        //concatenates data into a string delimited by '|'
        string prepareWrite()const;
        //changes current password to the argument
        bool changePassword(const string& password);
        //changes current username to the argument
        bool changeUsername(const string& username);
        //returns a boolean if argument matches name
        bool isUsername(const string& username)const;
        //returns true if argument matches password
        bool isPassword(const string& password)const;
        //overloaded > operator compares name
        bool operator>(const manager&)const;
        //overloaded < operator compares name
        bool operator<(const manager&)const;
        //overloaded == operator compares name;
        bool operator==(const manager&)const;

    private:
        string username;        //string for name should be >0 and < 21 characters
        string password;    //string for password should be >8 and <21 characters
};
#endif
