#include "Base class.h"

class Teacher : public Person
{
private:
    string ID;
public:
    void SetID(string s);
    string GetID();
};

void Teacher::SetID(string s)
{
    ID = s;
    return;
}

string Teacher::GetID()
{
    return ID;
}