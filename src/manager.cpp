#include "manager.h"

//default constructor
manager::manager(){
    username = "";
    password = "";
}

//paramaterized constructor
manager::manager(const string& username,const string& password){
    create(username,password);
}

//copy constructor makes a deep copy of arg data
manager::manager(const manager& toCopy){
    copy(toCopy);
}

//initializes object with argument data
void manager::create(const string& username,const string& password){
    this->username = username;
    this->password = password;
}

//makes a deep copy of the arg data
void manager::copy(const manager& toCopy){
    create(toCopy.username,toCopy.password);
}

//concatenates data into a single string delimited by "|", returns the string
string manager::prepareWrite()const{
    string temp = username;
    temp += "|";
    temp += password;
    return temp;
}

//changes current password to the argument
bool manager::changePassword(const string& password){
    this->password = password;
    return true;
}

//returns a boolean if argument matches name
bool manager::isUsername(const string& username)const{
    if(this->username.compare(username) == 0)
        return true;
    return false;
}

//returns true if argument matches password
bool manager::isPassword(const string& password)const{
    if(this->password.compare(password) == 0)
        return true;
    return false;
}

//overloaded > operator compares name
bool manager::operator>(const manager& toCompare)const{
    if(username.compare(toCompare.username) > 0)
        return true;
    return false;
}

//overloaded < operator compares name
bool manager::operator<(const manager& toCompare)const{
    if(username.compare(toCompare.username) > 0)
        return false;
    return true;
}

//overloaded == operator compares name;
bool manager::operator==(const manager& toCompare)const{
    if(username.compare(toCompare.username) == 0)
        return true;
    return false;
}

