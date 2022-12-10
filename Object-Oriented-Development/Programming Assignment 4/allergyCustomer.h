#ifndef ALLERGYCUSTOMER_H
#define ALLERGYCUSTOMER_H

#include
using namespace std;

class AllergyCustomer : public Customer {
private:
    bool severeAllergy;
    string allergy;

    public:
    AllergyCustomer(uint bal, uint accNum, string _allergy, bool severe = false) : Customer(bal, accNum);
    bool override buyOne(string name, Vendor vendor);

};

#endif