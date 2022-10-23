// Author: Clay Nguyen
// September 28, 2021
// Revision History: Last Submitted - September 29, 2021

// Overview: Program is to simulate the creation of the Entree class and test out its functionality
// Design choices have been made to not allow user manipulation of the data but gives readability.
// The entree class has get methods to query and print data to the console. Ingredients can be queried to
// get if an ingredient is in the array of ingredients. All other get methods except getName () prints out to the
// console. User has the ability to turn off the power to an Entree class to simulate the loss of power.
//
// Assumptions: user instantiates the Entree class correctly  with a (string, bool, bool, bool, DateTime,
// string array, and string array); 

using System;
using System.Linq;
//using static P1.Entree;

namespace P1
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] ingreds = { "tomatoes", "cheese", "dough" };
            string[] nutrients = { "Calories: 90", "sugar: 90g", "fat: 10g", "protein: 12g", "carbs: 170g" };
            Entree constantine = new Entree("Pizza", true, true, true, DateTime.Now.AddDays(7), ingreds, nutrients);

            GetAllInfo(constantine);

        }

        static void GetAllInfo(Entree item)
        {
            Console.WriteLine(item.GetName());
            item.GetIngredients();
            item.GetNutrition();
            Console.WriteLine("Item contains (tomatoes): " + item.Contains("tomatoes").ToString());
            Console.WriteLine("Item is Expired: " + item.IsExpired().ToString());
            Console.WriteLine("Item is Spoiled: " + item.IsSpoiled().ToString());
        }
    }
}
