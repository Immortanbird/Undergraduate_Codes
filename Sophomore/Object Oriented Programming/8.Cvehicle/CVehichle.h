#include <iostream>

using namespace std;

class CVehicle
{
protected:
    double m_dParaDistance, m_dParaWeight;

public:
    CVehicle(double paraDistance, double paraWeight) { SetParameters(paraDistance, paraWeight); }
    virtual ~CVehicle() { cout << "~CVehicle" << endl; }
    void SetParameters(double paraDistance, double paraWeight)
    {
        m_dParaDistance = paraDistance;
        m_dParaWeight = paraWeight;

        return;
    }
    virtual double Freight(double distance, double weight) = 0;
};

class CTruck : public CVehicle
{
public:
    CTruck(double paraDistance, double paraWeight) : CVehicle(paraDistance, paraWeight) {}
    double Freight(double distance, double weight) { return distance * m_dParaDistance + weight * m_dParaWeight + 30; }
};

class CShip : public CVehicle
{
public:
    CShip(double paraDistance, double paraWeight) : CVehicle(paraDistance, paraWeight) {}
    double Freight(double distance, double weight) { return distance * m_dParaDistance + weight * m_dParaWeight + 10; }
};

class CPlane : public CVehicle
{
public:
    CPlane(double paraDistance, double paraWeight) : CVehicle(paraDistance, paraWeight) {}
    double Freight(double distance, double weight) { return distance * m_dParaDistance + weight * m_dParaWeight + 60; }
};

class CFreight
{
private:
    CVehicle *vehicle;

public:
    void SetVehicle(CVehicle *veh)
    {
        vehicle = veh;
        return;
    }
    double GetPrice(double distance, double weight) { return vehicle->Freight(distance, weight); }
};