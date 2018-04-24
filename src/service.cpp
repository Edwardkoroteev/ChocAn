#include "service.h"

//default constructor;

service::service(){
    name = "";
    number = "";
    fee = 0;
}

//paramaterized constructor takes arguments and assigns them to appropriate data;
service::service(const string& name,const string& number, float fee){
    create(name,number,fee);
}

//copy constructor makes a deep copy of all data in the argument
service::service(const service& toCopy){
    copy(toCopy);
}

//takes all paramaters for the object and assigns them appropriately
bool service::create(const string& name,const string& number, float fee){
    this->name = name;
    this->number = number;
    this->fee = fee;
    return true;
}

//copy function makes a deep copy of all data in the argument
bool service::copy(const service& toCopy){
    return create(toCopy.name,toCopy.number,toCopy.fee); 
}

//changes an object name, used for editing
void service::setName(const string& name){
    this->name = name;
}

//changes an object fee, used for editing
void service::setFee(float fee){
    this->fee = fee;
}

//getter for the object fee, returns the value
float service::getFee()const{
    return fee;
}

string service::prepareWrite()const{
    string temp = "";
    temp += number;
    temp += "|";
    temp += name;
    temp += "|";
    stringstream stream;
    stream << fixed << setprecision(2) << fee;
    temp += stream.str();
    return temp;
}

istream &operator>>(istream &input, service &toInit){
    string number;
    string name;
    float fee;
    getline(input, number, '|');
    getline(input, name ,'|');
    input >> fee;
    toInit.number = number;
    toInit.name = name;
    toInit.fee = fee;
    return input;
}

//checks that the argument matches the service code number and returns the respective boolean
bool service::numberMatch(const string & toMatch)const{
    if(number.compare(toMatch) == 0)
        return true;
    return false;
}


//displays the object information
void service::display()const{
    cout << number << "   " << name << "   $" << fixed << setprecision(2) << fee << endl;
}

//overloaded > operator compares service name
bool service::operator>(const service& toCompare)const{
    if(name.compare(toCompare.name) > 0)
        return true;
    return false;
}

//overloaded < operator compares service name
bool service::operator<(const service& toCompare)const{
    if(name.compare(toCompare.name) < 0)
        return true;
    return false;
}

//overloaded == operator compares service number
bool service::operator==(const service& toCompare)const{
    if(number.compare(toCompare.number) == 0)
        return true;
    return false;
}
