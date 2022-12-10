// Author: Clay Nguyen
// September 28, 2021
// Revision History: Last Submitted - Sept. 29, 2021

// Class Invariant: nutrition array holds strings not an int or double
// expiration is in dateTime format
// cannot check to see a specific nutrient, will only print out the nutrients array.
//
// This class is instantiated when the user creates a new Entree object and supplies the constructor
// with the parameters needed or supplies nothing, which will create a generic Entree object. Once power has been turned off
// the entree will be spoiled even when power is restored. If the expiration date is passed in as DateTime.Now, the item
// will be expired when the item is created.
//
//
//
//
// Interface Invariant: Cannot pass an int array into Entree as a parameter for ingredients or nutrition
// Cannot pass any arbitrary date format as the expiration date, must be in DateTime format
//
// The Interface will always contain the methods to fetch the name of the entree, its ingredients,
// its nutrients, the ability to check if the item is spoiled or expired, check if the entree contains an ingredient,
// and the ability to turn off the power to refrigerate items. Querying the nutrition of the entree will
// print out the nutrients array to account for the variety of nutrients and the order they are in. This is to combat the
// unknown nature of the nutrients array when trying to query for nutrition stats.
// 

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace P1
{
    public class Entree
    {
        private string _name;
        private string[] _ingredients;
        private string[] _nutritionStats;
        private readonly DateTime _expiration;
        private readonly bool _refrigeration;
        private readonly bool _refrigerated;
        private readonly bool _power;
        private bool _powerOff;

        // Pre-Condition: This is in the case someone instantiates an Entree item but passes nothing in
        // Post-Condition: Creates a generic Entree type with generic state data.
        public Entree()
        {
            _name = "Food";
            _refrigeration = true;
            _refrigerated = true;
            _power = true;
            _powerOff = false;
            _expiration = DateTime.Now.AddDays(7);
            _ingredients = new string[] { "sugar", "salt", "pepper"};
            _nutritionStats = new string[] { "Sugars: 9g", "Carbs: 83g", "gmo: 100%" };
        }

        // Pre-Condition: User needs to pass in the correct data types in the right order to initialize state right
        // Post-Condition: Creates an Entree object instantiated with all the parameters, all state is initialzed here
        public Entree(string name, bool refrigeration, bool refrigerated, bool power, DateTime expiration, string[] ingredients, string[] nutritionStats)
        {
            _name = name;
            _refrigeration = refrigeration;
            _refrigerated = refrigerated;
            _power = power;
            _powerOff = false;
            _expiration = expiration;
            _ingredients = ingredients;
            _nutritionStats = nutritionStats;
        }

        // Pre-Condition: _expiration must be a valid DateTime
        // Post-Condition: State has not been changed since nothing was altered only returned a bool
        public bool IsExpired()
        {
            return _expiration <= DateTime.Now;
        }

        // Pre-Condition: None
        // Post-Condition: State has not been changed since nothing was altered only returned a bool
        public bool IsSpoiled()
        {
            if (_refrigeration == true)
            {
                if(_refrigerated == true)
                {
                    if(Power() == true)
                    {
                        return false || IsExpired();
                    }
                    return true;
                }
                else
                {
                    return true;
                }
            }
            else
            {
                return false || IsExpired();
            }
        }

        // Pre-Condition: None
        // Post-Condition: turns _powerOff to true, cannot be turned back to false
        public void PowerDown()
        {
            _powerOff = true;
        }

        // Pre-Condition: None
        // Post-Condition: State has not been changed since nothing was altered only returned a bool
        public bool Power()
        {
            if (_power == true)
            {
                return _power && !_powerOff;
            }
            return false;
        }

        // Pre-Condition: User needs to pass in a valid string
        // Post-Condition: State has not been changed since nothing was altered only returned a bool
        public bool Contains(string ingredient)
        {
            for (int i = 0; i < _ingredients.Length; i++)
            {
                if (_ingredients[i] == ingredient)
                {
                    return true;
                }
            }
            return false;
        }

        // Pre-Condition: None
        // Post-Condition: State has not been changed since nothing was altered or returned
        public string GetName()
        {
            return _name;
        }

        // Pre-Condition: None
        // Post-Condition: State has not been changed since nothing was altered or returned
        public void GetNutrition()
        {
            for (int i = 0; i < _nutritionStats.Length; i++)
            {
                Console.WriteLine(_nutritionStats[i]);
            }
        }

        // Pre-Condition: None
        // Post-Condition: State has not been changed since nothing was altered or returned
        public void GetIngredients()
        {
            for (int k = 0; k < _ingredients.Length; k++)
            {
                Console.WriteLine(_ingredients[k]);
            }
        }
    }
}


// Implementation Invariant: will not get back a string when getting nutrients (will print nutrients on the console)
// 
//
// To limit the access and control to the client, the name, ingredients, and nutrition will
// only be printed to the console if they want to see the data. The nutrients array supplied will also need to be in the form
// of a string array with ex. ["nutrient name: nutrient info"]. The user will also be needed to supply the entree name,
// whether it needs to be refridgerated, if it is refrigerated, if there is power to refrigerate, the DateTime equivalent of the
// expiration date, the string array of ingredients, and the string array of nutrients (in that order) when creating an Entree object.