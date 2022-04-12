#include <iostream>
#include <string>

using namespace std;

class Person //用于派生学生和老师的基类
{
private:
    string name;
    string gender;
    double birth;

public:
    void SetName(string s);
    void SetGender(string s);
    void SetBirth(double m);
    string GetName();
    string Getgender();
    double Getbirth();
};

void Person::SetName(string s)
{
    name = s;
    return;
}

void Person::SetGender(string s)
{
    gender = s;
    return;
}

void Person::SetBirth(double m)
{
    birth = m;
    return;
}

string Person::GetName()
{
    return name;
}

string Person::Getgender()
{
    return gender;
}

double Person::Getbirth()
{
    return birth;
}