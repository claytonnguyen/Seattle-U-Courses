// Author: Clay Nguyen
// December 3, 2021
// Last Revision - December 3, 2021

// Class Invariant: Class that instantiates an EmployeeCustomer object which inherits from
// an employee and composes a Customer object with the help of an interface to echo the calls
// to the Customer handle. Instead of deducting from pay each week, empcust will get an advanced
// pay for the week to buy groceries, only gets an advnaced pay once for each payday. Cannot get
// two advanced pays since advanced pays only work if the empcust has not received one for the payweek.
//
// Interface Invariant: that interface of ICustomer is supported and through this the calls of
// the Customer heirarchy delegate is echoed through the interface functions. Payday is overriden
// from Employee to add specialization and through replaceCustomer method, user can replace the
// customer delegate with any member in the Customer heirarchy.

using System;
namespace P5
{
    public class EmployeeCustomer : Employee, ICustomer
    {
        private Customer customer = null;
        public bool advancedPay = false;

        // PRECONDITIONS: Must inject correct dependencies in the correct order
        // POSTCONDITIONS: Creates a new EmployeeCustomer object
        public EmployeeCustomer(Vendor vendor, uint payLevel, uint balance, uint accNum) : base(ref vendor, payLevel)
        {
            if (customer == null)
            {
                customer = new Customer(balance, accNum);
            }
        }

        // PRECONDITIONS: None
        // POSTCONDITIONS: balance updated if custemp got an advanced pay already
        // returns true in that case and false in every other case.
        public override bool payDay()
        {
            if (!advancedPay)
            {
                return base.payDay();
            }
            else
            {
                advancedPay = false;
                return false;
            }
        }

        // PRECONDITIONS: Must inject a valid Customer heirarchy object into the method
        // POSTCONDITIONS: replaces customer handle with new customer if not null
        public bool replaceCustomer(Customer cust)
        {
            if (cust != null)
            {
                customer = cust;
                return true;
            }
            return false;
        }

        // PRECONDITIONS: Must inject a valid uint to be added to the balance
        // POSTCONDITIONS: Balance is updated to include the additional money added
        public void addMoney(uint balance)
        {
            customer.addMoney(balance);
        }

        // PRECONDITIONS: Must inject a valid uint
        // POSTCONDITIONS: None
        public bool purchase(uint money)
        {
            return true;
        }

        // PRECONDITIONS: Must inject a valid vendor into the function
        // POSTCONDITIONS: Buys/Deletes items from the vendor of choice if the customer
        // has enough money. 
        public bool buy(Vendor vendor)
        {
            if (!advancedPay)
            {
                customer.addMoney(pay[position - 1]);
                advancedPay = true;
                return customer.buy(worksAt);
            }
            Console.WriteLine("buying in the emp cust");
            return customer.buy(worksAt);
        }

        // PRECONDITIONS: Must inject a valid string name and Vendor object to buy items
        // POSTCONDITIONS: returns true if the item is purchased and the item is sold,
        // and not in the linked list of the vendor anymore
        public bool buyOne(string name, Vendor vendor)
        {
            if (!advancedPay)
            {
                customer.addMoney(pay[position - 1]);
                advancedPay = true;
                return customer.buyOne(name, worksAt);
            }
            Console.WriteLine("buying one in the emp cust");
            return customer.buyOne(name, worksAt);
        }

        // PRECONDITIONS: None
        // POSTCONDITIONS: returns the balance of the customer
        public uint getBalance()
        {
            return customer.getBalance() + balance;
        }
    }
}


// Implementation Invariant: Implemented the class to simulate multiple inheritance by inheriting
// from employee and an interface for customer and composing with customer. The interface forces
// echoes of the customer methods for the customer delegate. Cannot do true multiple inheritance in
// C#. Also implemented the deduction of paycheck when buying groceries differently. Instead of deducting
// food prices from paycheck, if the empcust has not received an advanced pay for their paycheck and wants
// to buy food, they will get an advanced pay of their check and can buy all the food they want.
// If they have already gotten an advanced pay of their paycheck before they get paid, they will not get
// another advanced pay since they can only receive one for one paycheck and needs to get "paid" for the
// bool tracking advanced pay to reset.