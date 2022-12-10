// Author: Clay Nguyen
// November 4, 2021
// Last Revision - November 5, 2021

// Class Invariant: nutrition array holds strings not an int or double
// expiration is in dateTime format
// when checking a specific nutrient, it will only work for carbs and sugars
// since that is the only nutrient limiting customers that can be created
//
// This class is instantiated when the user creates a new Entree object and supplies the constructor
// with the parameters needed. User should not create an Entree with no parameters. Once power has been turned off
// the entree will be spoiled even when power is restored. If the expiration date is passed in as DateTime.Now, the item
// will be expired when the item is created.
//
//
// Interface Invariant: Cannot pass an int array into Entree as a parameter for ingredients or nutrition
// Cannot pass any arbitrary date format as the expiration date, must be in DateTime format
//
// The Interface will always contain the methods to check if the item is spoiled or expired, check if the entree contains an ingredient,
// and the ability to turn off the power to refrigerate items. Querying the nutrition of the entree will
// print out the nutrients array to account for the variety of nutrients and the order they are in. This is to combat the
// unknown nature of the nutrients array when trying to query for nutrition stats.
//
// The empty entree should not be called only used for the compiler when creating a new entree
// in the vendor class

using System;

namespace p3
{
    public class Entree
    {
        private string _name;
        private string[] _ingredients;
        private float[] _nutritionStats;
        private string[] _contains;
        private readonly DateTime expiration;
        private  bool refrigerationNeeded;
        private  bool refrigerated;
        private  bool electricity;
        private  bool powerIsOff;
        public enum ingreds
        {
            NumberOfServings,
            Calories,
            TotalFat,
            SatFat,
            TransFat,
            Cholest,
            Sodium,
            TotCarb,
            Fiber,
            TotSugars,
            Proteins
        }

        public Entree()
        {

        }


        // Pre-Condition: Must inject all the dependencies in the correct order and must be valid types
        // Post-Condition: Properties of the class are all set here
        public Entree(string name, string[] ingredients, bool _refrigerated, bool _refrigerationNeeded, bool _electricity, DateTime exp, float[] nutritionStats, string[] contains)
        {
            _name = name;
            _ingredients = ingredients;
            _nutritionStats = nutritionStats;
            _contains = contains;
            expiration = exp;
            refrigerated = _refrigerated;
            refrigerationNeeded = _refrigerationNeeded;
            electricity = _electricity;
            powerIsOff = false;
        }

        // Pre-Condition: Must inject a valid Entree class to be constructed
        // Post-Condition: Properties of the class are all set here
        public Entree(Entree src)
        {
            _name = src._name;
            expiration = src.expiration;
            refrigerated = src.refrigerated;
            refrigerationNeeded = src.refrigerationNeeded;
            electricity = src.electricity;
            powerIsOff = src.powerIsOff;
            _ingredients = new string[src._ingredients.Length];
            _contains = new string[src._contains.Length];
            _nutritionStats = new float[src._nutritionStats.Length];
            for (int i = 0; i < src._ingredients.Length; i++)
            {
                _ingredients[i] = src._ingredients[i];
            }
            for (int i = 0; i < src._nutritionStats.Length; i++)
            {
                _nutritionStats[i] = src._nutritionStats[i];
            }
            for (int i = 0; i < src._contains.Length; i++)
            {
                _contains[i] = src._contains[i];
            }
        }

        // Pre-Condition: None
        // Post-Condition: returns true if it is expired else false
        public bool IsExpired()
        {
            return expiration <= DateTime.Now;
        }

        // Pre-Condition: None
        // Post-Condition: returns true if it is spoiled else false
        public bool IsSpoiled()
        {
            if (refrigerationNeeded == true)
            {
                if (refrigerated == true)
                {
                    if (Power() == true)
                    {
                        return false || (expiration <= DateTime.Now);
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
                return false || (expiration <= DateTime.Now);
            }
        }
        
        // Pre-Condition: None
        // Post-Condition: turns electricity false and bool that says that the powerisof true
        public void PowerDown()
        {
            powerIsOff = true;
        }

        // Pre-Condition: None
        // Post-Condition: returns true if electricity is on and has not been turned off before,
        // else returns false
        public bool Power()
        {
            if (electricity == true)
            {
                return !powerIsOff;
            }
            return false;
        }

        // Pre-Condition: None
        // Post-Condition: returns true if refrigerated and false if not
        public bool IsRefrigerated()
        {
            return refrigerated;
        }

        // Pre-Condition: Must inject a valid string for ingredient
        // Post-Condition: returns true if the item is in the ingredient list
        // else returns false
        public bool ContainsIngred(string ingredient)
        {
            for (int i = 0; i < _ingredients.Length; i++)
            {
                if(_ingredients[i] == ingredient)
                {
                    return true;
                }
            }
            return false;
        }

        // Pre-Condition: Must inject a valid string for contains
        // Post-Condition: returns true if the item is in the contains list
        // else returns false
        public bool Contains(string contain)
        {
            for (int i = 0; i < _contains.Length; i++)
            {
                if (_contains[i] == contain)
                {
                    return true;
                }
            }
            return false;
        }

        // Pre-Condition: None
        // Post-Condition: returns the name of the entree
        public string GetName()
        {
            return _name;
        }


        // Pre-Condition: Must inject a valid string for the nutrient name
        // Post-Condition: returns the amount of an ingredient in the entree
        public float checkNutrients(string input)
        {
            if(input == "carbs")
            {
                int num = (int)ingreds.TotCarb;
                return _nutritionStats[num];
            }
            else if (input == "sugar")
            {
                int num = (int)ingreds.TotSugars;
                return _nutritionStats[num];
            }
            else
            {
                return -1;
            }
        }
    }
}

// Implementation Invariant: implemented the nutrients as an array to be able to check certain
// indexes for the carb and/or sugar contents easily
//