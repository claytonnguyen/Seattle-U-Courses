// Author: Clay Nguyen
// December 3, 2021
// Last Revision - December 3, 2021

// Class Invariant: customer object is instantiated with an unsigned balance
// and a unsigned account Number. Balance will change by adding money or buying
// items from a vendor
// 
// Interface Invariant: Client must inject dependencies into the constructor
// and the functions correctly. When buying, users only need to call a buy function with
// the correct parameters
//

using System;
namespace P5
{
    interface ICustomer
    {
        void addMoney(uint money);
        bool purchase(uint money);
        bool buyOne(string name, Vendor vendor);
        bool buy(Vendor vendor);
        uint getBalance();
    }

    public class Customer : ICustomer
    {
        private uint balance;
        private uint accountNumber;

        // Pre-Condition: Must inject a valid uint balance and accNum into the ctor
        // Post-Condition: Properties of the class are set here
        public Customer(uint bal, uint accNum)
        {
            balance = bal;
            accountNumber = accNum;
        }

        // Pre-Condition: Must inject a valid uint to be added to the balance
        // Post-Condition: Balance is updated to include the additional money added
        public void addMoney(uint money)
        {
            balance += money;
        }

        // Pre-Condition: Must inject a valid uint to be added to the balance
        // Post-Condition: if the balance is greater than the amount passed in,
        // then the money will be subtracted from the balance.
        public bool purchase(uint money)
        {
            if (money <= balance)
            {
                balance -= money;
                return true;
            }
            return false;
        }

        // Pre-Condition: Must inject a valid string name and Vendor object to buy items
        // Post-Condition: returns true if the item is purchased and the item is sold,
        // and not in the linked list of the vendor anymore
        public virtual bool buyOne(string name, Vendor vendor)
        {
            float price = vendor.getPrice(name);
            if (price == -1) { return false; }
            uint payment = (uint)price;
            bool bought = vendor.Sell(name);
            if (bought == true)
            {
                return purchase(payment);
            }
            return false;
        }


        // Pre-Condition: Must inject a valid vendor into the function
        // Post-Condition: Buys/Deletes items from the vendor of choice if the customer
        // has enough money. 
        public virtual bool buy(Vendor vendor)
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
            float entree1price = vendor.getPrice(entree1);
            float entree2price = vendor.getPrice(entree2);
            float entree3price = vendor.getPrice(entree3);

            if (getBalance() >= (entree1price + entree2price + entree3price))
            {
                buyOne(entree1, vendor);
                buyOne(entree2, vendor);
                buyOne(entree3, vendor);
                return true;
            }
            else if (getBalance() >= (entree1price + entree2price))
            {
                buyOne(entree1, vendor);
                buyOne(entree2, vendor);
                return true;
            }
            else if (getBalance() >= (entree2price + entree3price))
            {
                buyOne(entree2, vendor);
                buyOne(entree3, vendor);
                return true;
            }
            else if (getBalance() >= (entree1price + entree3price))
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
        // Post-Condition: returns the balance of the customer
        public uint getBalance()
        {
            return balance;
        }
    }
}

// Implementation Invariant: implemented balance as an unsigned int to never
// allow balances to be negative. implemented the encapsulation of vendor type
// checking and customer balance checking in the buy functions