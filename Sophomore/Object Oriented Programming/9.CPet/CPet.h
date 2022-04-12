#include <iostream>
#include <vector>

using namespace std;

class CPet
{
private:
    string name;

public:
    CPet(string s) { name = s; }      //初始化宠物名字
    string GetName() { return name; } //获取宠物名字
    virtual void PetCall() = 0;       //输出宠物叫声
};

class Sparrow : public CPet
{
public:
    Sparrow(string s) : CPet(s) {}
    void PetCall() { cout << "Coo Coo" << endl; }
};

class Dog : public CPet
{
public:
    Dog(string s) : CPet(s) {}
    void PetCall() { cout << "Woof Woof" << endl; }
};

class Cat : public CPet
{
public:
    Cat(string s) : CPet(s) {}
    void PetCall() { cout << "Meow Meow" << endl; }
};

class PetManagement
{
private:
    vector<CPet *> Pets;

public:
    int AddPet(CPet *pet);
    void GetPetCall(int n);
    void GetPetName(int n);
};

int PetManagement::AddPet(CPet *pet)
{
    if (Pets.size() == 10)
        return 0;
    else
    {
        Pets.push_back(pet);
        return 1;
    }
}

void PetManagement::GetPetCall(int n)
{
    if (Pets.size() < n)
        cout << "(They don't have enough pets.)" << endl;
    else
        Pets[n]->PetCall();

    return;
}

void PetManagement::GetPetName(int n)
{
    if (Pets.size() < n)
        cout << "(They don't have enough pets.)" << endl;
    else
        cout << Pets[n]->GetName() << endl;

    return;
}