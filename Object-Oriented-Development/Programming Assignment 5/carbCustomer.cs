// Author: Clay Nguyen
// December 3, 2021
// Last Revision - December 3, 2021

// Class Invariant: Class is composed of two buying functions along with the
// public attributes of the base customer class, a function to reset daily
// sugar intake and a function to view the running total of the carb intake for the day.
// When buying one entree, a name is needed to be supplied to the
// function while the buy function will automatically try to buy between two to
// three entrees.
//
//
// Interface Invariant: Customer calls this class to instantiate a low carb
// customer, does not need to call the base call, this is done automatically
// through inheritence. Customer will have to reset their daily carb intake
// to be able to keep buying and therefore not going over their daily limit

using System;
namespace P5
{
    public class CarbCustomer : Customer
    {
        private readonly string problem;
        private readonly float carbLimit;
        private float carbIntake = 0;

        // Pre-Condition: Must inject valid datatypes into the ctor in the correct order
        // Post-Condition: Properties of the class and the base class are set here
        public CarbCustomer(uint bal, uint accNum) : base(bal, accNum)
        {
            problem = "carbs";
            carbLimit = 30;
        }

        // Pre-Condition: Must inject a valid string name and a Vendor object to buy items
        // Post-Condition: if the item is purchaseable then the item is sold and removed from
        // the vendor's linked list and returns true. If not, nothing happens and returns false
        public override bool buyOne(string name, Vendor vendor)
        {
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
            else if ((entree1carbs + entree2carbs) <= (carbLimit - carbIntake) && getBalance() > (entree1price + entree2price))
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
            else if ((entree1carbs + entree3carbs) <= (carbLimit - carbIntake) && getBalance() > (entree1price + entree3price))
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
        // Post-Condition: Sets the carbIntake of a customer to 0 to
        // signal a new day so the daily carb limit would be reset
        public void newDay()
        {
            carbIntake = 0;
        }

        // Pre-Condition: None
        // Post-Condition: returns the intake of carb for that day
        public float carbCheck()
        {
            return carbIntake;
        }

    }
}

// Implementation Invariant: Implemented a function to reset the daily carb intake
// so that a new low carb customer did not need to be created every day, they can
// just reset their intake