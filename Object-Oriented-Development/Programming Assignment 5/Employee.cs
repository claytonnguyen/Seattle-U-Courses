// Author: Clay Nguyen
// December 3, 2021
// Last Revision - December 3, 2021

// Class Invariant: Class that instantiates an Employee object, balance of the employee cannot
// go negative, each customer has a pay level and a vendor which they work at/belong to.
// Need a vendor object passed in when constructing to complete the class definition and instantiate.
// Employee also gets paid according to their pay level.
//
// Interface Invariant: Method to pay the employee returns true if they are paid based on their
// pay level and false otherwise
// 

using System;
namespace P5
{
    
    public class Employee
    {
        public uint[] pay = {300, 500, 800};
        protected uint balance = 0;
        protected uint position = 1;
        protected Vendor worksAt;

        // PRECONDITIONS: Customer must pass in the correct dependencies into ctor
        // POSTCONDITIONS: Creates an Employee object
        public Employee(ref Vendor vendor, uint payLevel = 0) 
        {
            worksAt = vendor;
            position = payLevel;
        }

        // PRECONDITIONS: None
        // POSTCONDITIONS: Returns true if they are paid (balance updated) and false if not.
        // Depends on their position if they get paid or not.
        public virtual bool payDay()
        {
            if(position > 0 && position < pay.Length)
            {
                balance += pay[position - 1];
                return true;
            }
            return false;
        }
    }
}

// Implementation Invariant: balance is uint to avoid balance from going negative and the
// pay level is just an int to get their pay from a pay array. Default value for this is 0
// for the first pay level in the array. 