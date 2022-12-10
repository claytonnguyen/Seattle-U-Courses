// Author: Clay Nguyen
// November 4, 2021
// Last Revision - November 5, 2021

// Class Invariant: Class is composed of two buying functions along with the
// public attributes of the base customer class and a function to reset daily
// sugar intake. When buying one entree, a name is needed to be supplied to the
// function while the buy function will automatically try to buy between two to
// three entrees.
//
//
// Interface Invariant: Customer calls this class to instantiate a diabetic
// customer, does not need to call the base call, this is done automatically
// through inheritence. Customer will have to reset their daily sugar intake
// to be able to keep buying and therefore not going over their daily limit
// 

using System;

namespace p3
{
    public class DBetCustomer : Customer
    {
        private readonly string problem;
        private readonly float dailySugarLimit;
        private readonly float mealSugarLimit;
        private readonly float itemSugarLimit;
        private float sugarIntake = 0;

        // Pre-Condition: Must inject valid datatypes into the ctor in the correct order
        // Post-Condition: Properties of the class and the base class are set here
        public DBetCustomer(uint bal, uint accNum) : base(bal, accNum)
        {
            problem = "sugar";
            dailySugarLimit = 50;
            mealSugarLimit = 25;
            itemSugarLimit = 10;
        }

        // Pre-Condition: Must inject a valid string name and a Vendor object to buy items
        // Post-Condition: if the item is purchaseable then the item is sold and removed from
        // the vendor's linked list and returns true. If not, nothing happens and returns false
        public override bool buyOne(string name, Vendor vendor)
        {
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

        // Pre-Condition: Must inject a valid vendor object
        // Post-Condition: If the first three entrees in the vendor's registry
        // is purchaseable even with the restrictions of the customer, then the
        // items are sold but if not all three entrees are purchaseable, then
        // it will try to buy a combo of two entrees out of the three, if it cannot
        // buy a combo, then it will not purchase any entrees
        public override bool buy(Vendor vendor)
        {
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

        // Pre-Condition: None
        // Post-Condition: Sets the sugarIntake of a customer to 0 to
        // signal a new day so the daily sugar limit would be reset
        public void newDay()
        {
            sugarIntake = 0;
        }
    }
}

// Implementation Invariant: Implemented a function to reset the daily sugar intake
// so that a new diabetic customer did not need to be created every day, can just
// reset their intake