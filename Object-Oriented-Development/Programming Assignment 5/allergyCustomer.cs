// Author: Clay Nguyen
// December 3, 2021
// Last Revision - December 3, 2021

// Class Invariant: Class is composed of a buying functions along with the
// public attributes of the base customer class, 
// When buying one entree, a name is needed to be supplied to the
// function.
//
//
// Interface Invariant: Customer calls this class to instantiate an allergic
// customer, does not need to call the base call, this is done automatically
// through inheritence.

using System;
namespace P5
{
    public class AllergyCustomer : Customer
    {
        private bool severeAllergy;
        private string allergy;

        // Pre-Condition: Must inject valid datatypes into the ctor in the correct order
        // Post-Condition: Properties of the class and the base class are set here
        public AllergyCustomer(uint bal, uint accNum, string _allergy, bool severe = false) : base(bal, accNum)
        {
            allergy = _allergy;
            severeAllergy = severe;
        }

        // Pre-Condition: Must inject a valid string name and a Vendor object to buy items
        // Post-Condition: if the item is purchaseable then the item is sold and removed from
        // the vendor's linked list and returns true. If not, nothing happens and returns false
        public override bool buyOne(string name, Vendor vendor)
        {
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
    }
}

// Implementation Invariant: Constantly error checks to see if the entree is
// not expired or spoiled and if the customer has even money in their balance
// to buy the entree