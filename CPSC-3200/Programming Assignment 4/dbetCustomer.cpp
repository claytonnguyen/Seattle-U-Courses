#include <iostream>
#include "dbetCustomer.h"

using namespace std;

DBetCustomer::DBetCustomer(unsigned bal, unsigned accNum) : Customer(bal, accNum) {
    problem = "sugar";
    dailySugarLimit = 50;
    mealSugarLimit = 25;
    itemSugarLimit = 10;
    sugarIntake = 0;
}

bool DBetCustomer::buyOne(string name, Vendor vendor) {
    vendor.CleanStock();
    float ingred = vendor.checkNutrition(name, problem);
    float price = vendor.getPrice(name);
    if(price == -1) { return false; }
    if(ingred != -1 && ingred <= itemSugarLimit)
    {
        uint payment = (uint)price;
        bool purchased = vendor.Sell(name); 
        if (purchased)
        {
            sugarIntake += ingred;
            return purchase(payment);
        }
    }
    return false;
}

bool DBetCustomer::buy(Vendor vendor) {
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
    float entree1sugar = vendor.checkNutrition(entree1, problem);
    float entree2sugar = vendor.checkNutrition(entree2, problem);
    float entree3sugar = vendor.checkNutrition(entree3, problem);
    float entree1price = vendor.getPrice(entree1);
    float entree2price = vendor.getPrice(entree2);
    float entree3price = vendor.getPrice(entree3);

    if ((entree1sugar + entree2sugar + entree3sugar) <= mealSugarLimit && getBalance() >= (entree1price + entree2price + entree3price)
        && (entree1sugar + entree2sugar + entree3sugar + sugarIntake) <= dailySugarLimit)
    {
        buyOne(entree1, vendor);
        buyOne(entree2, vendor);
        buyOne(entree3, vendor);
        return true;
    }
    else if ((entree1sugar + entree2sugar) <= mealSugarLimit && getBalance() >= (entree1price + entree2price)
        && (entree1sugar + entree2sugar + sugarIntake) <= dailySugarLimit)
    {
        buyOne(entree1, vendor);
        buyOne(entree2, vendor);
        return true;
    }
    else if ((entree2sugar + entree3sugar) <= mealSugarLimit && getBalance() >= (entree2price + entree3price)
        && (entree2sugar + entree3sugar + sugarIntake) <= dailySugarLimit)
    {
        buyOne(entree2, vendor);
        buyOne(entree3, vendor);
        return true;
    }
    else if ((entree1sugar + entree3sugar) <= mealSugarLimit && getBalance() >= (entree1price + entree3price)
        && (entree1sugar + entree3sugar + sugarIntake) <= dailySugarLimit)
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

void newDay() {
    sugarIntake = 0;
}