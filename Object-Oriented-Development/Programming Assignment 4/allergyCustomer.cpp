#include <iostream>
#include "allergyCustomer.h"
#include "customer.h"

using namespace std;

AllergyCustomer::AllergyCustomer(unsigned int bal, unsigned int accNum, string _allergy, bool severe = false) : Customer(bal, accNum) {
    allergy = _allergy;
    severeAllergy = severe;
}

bool AllergyCustomer::buyOne(string name, Vendor vendor){
    vendor.CleanStock();
    bool contains = vendor.contains(name, allergy);
    float price = vendor.getPrice(name);
    if (price == -1) { return false; }
    if (severeAllergy == false && contains == false)
    {
        uint payment = (uint)price;
        if (vendor.Sell(name) == true)
        {
            return purchase(payment);
        }
    }
    else
    {
        bool ingred = vendor.containsIngredient(name, allergy);
        if (severeAllergy == true && ingred == false && contains == false)
        {
            uint payment = (uint)price;
            if (vendor.Sell(name) == true)
            {
                return purchase(payment);
            }
        }
    }
    return false;
}
