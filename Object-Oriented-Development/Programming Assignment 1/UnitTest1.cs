// Author: Clay Nguyen
// September 28, 2021
// Revision History: Last Submitted - September 29, 2021

using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace P1
{
    [TestClass]
    public class UnitTest1
    {
        //Testing to see if an item that is not expired is expired, should return false
        [TestMethod]
        public void IsExpired_False()
        {
            string[] ingreds = { "lettuce", "avocado", "dressing", "egg", "tomatoe", "oil", "salt", "pepper", "croutons", "cheese" };
            string[] nutrients = { "Sugar: 9g", "Carbs: 5g", "protein: 8g", "fats: 19g", "vitamins: a, b, c, d" };
            Entree testObj = new Entree("avocado salad", false, false, true, DateTime.Now.AddDays(2) , ingreds, nutrients);
            Assert.AreEqual(testObj.IsExpired(), false);
        }

        // Testing to see if an expired item is expired, should return true
        [TestMethod]
        public void IsExpired_True()
        {
            string[] ingreds = { "salmon", "greens", "lemons", "oil" };
            string[] nutrients = { "Sugar: 5g", "Carbs: 7g", "Protein: 68g" };
            Entree testObj = new Entree("Salmon Entree Go", false, true, true, DateTime.Now.AddDays(-2), ingreds, nutrients); ;
            Assert.AreEqual(testObj.IsExpired(), true);
        }

        // Testing to see if an item that needs refrigeration is spoiled when the power is off, should return true
        [TestMethod]
        public void PowerDownSpoiled_True()
        {
            string[] ingreds = { "pancake batter", "milk", "dough", "eggs" };
            string[] nutrients = { "Sugar: 9g", "Carbs: 93g", "protein: 1g", "fats: 2g" };
            Entree testObj = new Entree("pancakes", true, true, false, DateTime.Now.AddDays(2), ingreds, nutrients);
            Assert.AreEqual(testObj.IsSpoiled(), true);
        }

        // Testing to see if a fridged item which needs to fridged spoils when the power goes out, should return true
        [TestMethod]
        public void PowerTurnedOffSpoiled_True()
        {
            string[] ingreds = { "patty", "bun", "cheese", "lettuce", "sauce", "pickles", "tomatoes" };
            string[] nutrients = { "Sugar: 32g", "Carbs: 71g", "Protein: 83g", "fats: 90g", "gmo: 99%" };
            Entree testObj = new Entree("hamburger", true, true, true, DateTime.Now.AddDays(2), ingreds, nutrients);
            testObj.PowerDown();
            Assert.AreEqual(testObj.IsSpoiled(), true);
        }

        // Testing to see if a unfridged item which needs to be fridged spoils, should return true
        [TestMethod]
        public void NotFridgedSpoiled_True()
        {
            string[] ingreds = { "apples", "milk", "eggs", "cheese", "yogurt" };
            string[] nutrients = { "Sugar: 9g", "Carbs: 97g", "dairy: 8g" };
            Entree testObj = new Entree("Varied Dairy items and apples", true, false, true, DateTime.Now.AddDays(2), ingreds, nutrients);
            Assert.AreEqual(testObj.IsSpoiled(), true);
        }

        // Testing to see if a fridged and unexpired item is spoiled, should return false
        [TestMethod]
        public void IsSpoiled_False()
        {
            string[] ingreds = { "pasta noodles", "milk", "cheese", "tomatoes" };
            string[] nutrients = { "Sugar: 9g", "Carbs: 97g", "fats: 83g", "proteins: 83g" };
            Entree testObj = new Entree("Pasta", true, true, true, DateTime.Now.AddDays(2), ingreds, nutrients);
            Assert.AreEqual(testObj.IsSpoiled(), false);
        }

        // Testing to see if a unfridged item which doesn't need to be fridged spoils, should return false
        [TestMethod]
        public void DontNeedFridgeUnFridged_False()
        {
            string[] ingreds = { "apples", "bannanas", "pineapple", "orange" };
            string[] nutrients = { "Sugar: 18g", "Carbs: 8g", "fats: 3g", "glucose: 35g" };
            Entree testObj = new Entree("Varied Fruits", false, false, true, DateTime.Now.AddDays(2), ingreds, nutrients);
            Assert.AreEqual(testObj.IsSpoiled(), false);
        }

        // Testing to see if a fridged item which doesn't need to be fridged spoils, should return false
        [TestMethod]
        public void DontNeedFridgeFridged_False()
        {
            string[] ingreds = { "bread", "cheese", "garlic", "salt" };
            string[] nutrients = { "Sugar: 3g", "Carbs: 97g", "gmo: 2%", "fats: 20g" };
            Entree testObj = new Entree("Breadsticks", false, true, true, DateTime.Now.AddDays(2), ingreds, nutrients); ;
            Assert.AreEqual(testObj.IsSpoiled(), false);
        }

        // Testing to see if item contains an ingredient, should return true
        [TestMethod]
        public void ContainsIngred_True()
        {
            string[] ingreds = { "green peas", "milk" };
            string[] nutrients = { "Sugar: 9g", "Carbs: 97g", "Yarn: 8g" };
            Entree testObj = new Entree("Poor man's dinner", false, true, true, DateTime.Now.AddDays(2), ingreds, nutrients); ;
            Assert.AreEqual(testObj.Contains("milk"), true);
        }

        // Testing to see if item contains an ingredient, should return false
        [TestMethod]
        public void DoesntContainIngred_False()
        {
            string[] ingreds = { "beans", "tortilla", "cheese", "chips", "salsa", "beef", "corn" };
            string[] nutrients = { "Sugar: 19g", "Carbs: 90g", "Fats: 8g", "Proteins: 63g", "gmo: 10%" };
            Entree testObj = new Entree("Burrito", false, true, true, DateTime.Now.AddDays(2), ingreds, nutrients); ;
            Assert.AreEqual(testObj.Contains("pizza"), false);
        }
    }
}
