// Author: Clay Nguyen
// November 4, 2021
// Last Revision - November 5, 2021

// Overview: Program is made to simulate the creation of the entree, vendor,
// customer, and derived classes of customer.
// Designed to allow user to interface with the objects but if wrong data or
// incorrect types are given, they cannot corrupt the data, the functions called
// wrong will just exit.
// In the driver, instantiate a variety of objects and trigger a variety of mode changes

using System;
using System.IO;

namespace p3
{
    class Program
    {
        static void Main(string[] args)
        {
            Random random = new Random();
            const int customerArrSize = 6;
            const string filePath = "/Users/clayton/Downloads/EntreesTabDelimited.txt";
            Vendor vending = new Vendor(filePath);

            Vendor vending2 = new Vendor(vending);

            string[] entreeNames = vending.randomEntree();
            string[] entreeNames2 = vending2.randomEntree();

            Customer[] customerArray = new Customer[customerArrSize];
            for (int i = 0; i < customerArrSize; i++)
            {
                customerArray[i] = GetObj(random, i);
            }

            // Don't want to use buy() function a lot in the driver testing since there are not a lot of
            // entrees in the test file to buy. Tested the buy() function in the unit tests.
            // customers may not be able to buy since the prices are random and balances are
            // random as well.

            for (int i = 0; i < customerArrSize; i++)
            {
                if(entreeNames[i] != null && entreeNames[i] != "")
                {
                    if (i % 3 == 0)
                    {
                        customerArray[i].buyOne(entreeNames[i], vending);
                    }
                    else if (i % 3 == 1)
                    {
                        customerArray[i].buy(vending2);
                    }
                    else
                    {
                        customerArray[i].buyOne(entreeNames[i], vending2);
                    }
                }
            }

        }


        // Pre-Condition: Injects a valid Random type and integer into the function
        // Post-Condition: creates a new Customer type or derived Customer and returns it
        // by value;
        static public Customer GetObj(Random _random, int i)
        {
            if (i % 4 == 0) { return new CarbCustomer(randomBal(_random), randomAccNum(_random)); }
            else if (i % 4 == 1) { return new DBetCustomer(randomBal(_random), randomAccNum(_random)); }
            else if (i % 4 == 2) { return new AllergyCustomer(randomBal(_random), randomAccNum(_random), "peanuts", randomBool(_random)); }
            else { return new Customer(randomBal(_random), randomAccNum(_random)); }
        }

        // Pre-Condition: Injects a valid Random type into the function
        // Post-Condition: returns a random uint from 0 to 500
        static public uint randomBal(Random _random)
        {
            return (uint)_random.Next(0, 500);
        }

        // Pre-Condition: Injects a valid Random type into the function
        // Post-Condition: returns a random uint from 1000 to 10000
        static public uint randomAccNum(Random _random)
        {
            return (uint)_random.Next(1000, 10000);

        }

        // Pre-Condition: Injects a valid Random type into the function
        // Post-Condition: returns a random bool (true or false)
        static public bool randomBool(Random _random)
        {
            int rand = _random.Next(1, 10);
            if (rand % 2 == 0) { return true; }
            else { return false; }
        }

    }
}
