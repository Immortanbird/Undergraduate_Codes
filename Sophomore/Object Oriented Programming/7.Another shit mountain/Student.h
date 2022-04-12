#include "Base class.h"

class Student : public Person
{
private:
    long ID;

public:
    void SetID(long n);
    long GetID();
};

void Student::SetID(long n)
{
    ID = n;
    return;
}

long Student::GetID()
{
    return ID;
}