#include <iostream>
#include "carbCustomer.h"

using namespace std;

CarbCustomer::CarbCustomer(unsigned bal, unsigned accNum) : Customer(bal, accNum) {
    problem = "carbs";
    carbLimit = 30;
    carbIntake = 0;
}

bool CarbCustomer::buyOne(string name, Vendor vendor) {
    vendor.CleanStock();
    float ingred = vendor.checkNutrition(name, problem);
    float price = vendor.getPrice(name);
    if (price == -1) { return false; }
    if (ingred != -1 && ingred <= (carbLimit - carbIntake))
    {
        uint payment = (uint)price;
        bool purchased = vendor.Sell(name); 
        if (purchased)
        {
            carbIntake += ingred;
            return purchase(payment);
        }
    }
    return false;
}

bool CarbCustomer::buy(Vendor vendor) {
    vendor.CleanStock();
    string[] entreeNames = vendor.randomEntree();
    string entree1 = "";
    string entree2 = "";
    string entree3 = "";

    if (entreeNames.Length > 3)
    {
        entree1 = entreeNames[0];
        entree2 = entreeNames[1];
        entree3 = entreeNames[2];
    }
    else
    {
        return false;
    }

    float entree1carbs = vendor.checkNutrition(entree1, problem);
    float entree2carbs = vendor.checkNutrition(entree2, problem);
    float entree3carbs = vendor.checkNutrition(entree3, problem);
    float entree1price = vendor.getPrice(entree1);
    float entree2price = vendor.getPrice(entree2);
    float entree3price = vendor.getPrice(entree3);

    if ((entree1carbs + entree2carbs + entree3carbs) <= (carbLimit - carbIntake) && getBalance() > (entree1price + entree2price + entree3price))
    {
        buyOne(entree1, vendor);
        buyOne(entree2, vendor);
        buyOne(entree3, vendor);
        return true;
    }
    else if((entree1carbs + entree2carbs) <= (carbLimit - carbIntake) && getBalance() > (entree1price + entree2price))
    {
        buyOne(entree1, vendor);
        buyOne(entree2, vendor);
        return true;
    }
    else if ((entree2carbs + entree3carbs) <= (carbLimit - carbIntake) && getBalance() > (entree2price + entree3price))
    {
        buyOne(entree2, vendor);
        buyOne(entree3, vendor);
        return true;
    }
    else if((entree1carbs + entree3carbs) <= (carbLimit - carbIntake) && getBalance() > (entree1price + entree3price))
    {
        buyOne(entree1, vendor);
        buyOne(entree3, vendor);
        return true;
    }
    else
    {
        // cannot buy for whatever reason
        return false;
    }
}

void CarbCustomer::newDay() {
    carbIntake = 0;
}

float carbCheck() {
    return carbIntake;
}