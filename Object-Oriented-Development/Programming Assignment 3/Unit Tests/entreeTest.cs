// Author: Clay Nguyen
// November 4, 2021
// Last Revision - November 5, 2021

using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

// hardcoding is used to control the state of the entree to showcase the test cases
// where it passes or fails.

namespace p3
{
    [TestClass]
    public class entreeTest
    {
        //Testing to see if an item that is not expired is expired, should return false
        [TestMethod]
        public void IsExpired_False()
        {
            string[] ingreds = { "lettuce", "avocado", "dressing", "egg", "tomatoe", "oil", "salt", "pepper", "croutons", "cheese" };
            float[] nutrients = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
            string[] contains = { "peanuts" };
            Entree testObj = new Entree("avocado salad", ingreds, false, false, true, DateTime.Now.AddDays(2), nutrients, contains);
            Assert.AreEqual(testObj.IsExpired(), false);
        }
        // Testing to see if an expired item is expired, should return true
        [TestMethod]
        public void IsExpired_True()
        {
            string[] ingreds = { "salmon", "greens", "lemons", "oil" };
            float[] nutrients = { 5, 10, 23, 3, 52, 95, 50, 2, 0, 0, 3 };
            string[] contains = { "eggs" };
            Entree testObj = new Entree("Salmon Entree Go", ingreds, false, true, true, DateTime.Now.AddDays(-2), nutrients, contains);
            Assert.AreEqual(testObj.IsExpired(), true);
        }
        // Testing to see if an item that needs refrigeration is spoiled when the power is off, should return true
        [TestMethod]
        public void PowerDownSpoiled_True()
        {
            string[] ingreds = { "pancake batter", "milk", "dough", "eggs" };
            float[] nutrients = { 34, 3, 5, 0, 0, 0, 0, 2, 3, 4, 1 };
            string[] contains = { "yogurt" };
            Entree testObj = new Entree("pancakes", ingreds, true, true, false, DateTime.Now.AddDays(2), nutrients, contains);
            Assert.AreEqual(testObj.IsSpoiled(), true);
        }
        // Testing to see if a fridged item which needs to fridged spoils when the power goes out, should return true
        [TestMethod]
        public void PowerTurnedOffSpoiled_True()
        {
            string[] ingreds = { "patty", "bun", "cheese", "lettuce", "sauce", "pickles", "tomatoes" };
            float[] nutrients = { 3, 0, 0, 0, 0, 1, 4, 5, 24, 10, 3 };
            string[] contains = { "carb" };
            Entree testObj = new Entree("hamburger", ingreds, true, true, true, DateTime.Now.AddDays(2), nutrients, contains);
            testObj.PowerDown();
            Assert.AreEqual(testObj.IsSpoiled(), true);
        }
        // Testing to see if a unfridged item which needs to be fridged spoils, should return true
        [TestMethod]
        public void IsSpoiled_DoesntNeedToBeFridged_False()
        {
            string[] ingreds = { "apples", "milk", "eggs", "cheese", "yogurt" };
            float[] nutrients = { 34, 3, 5, 0, 0, 0, 0, 2, 3, 4, 1 };
            string[] contains = { "peanuts" };
            Entree testObj = new Entree("Varied Dairy items and apples", ingreds, true, false, true, DateTime.Now.AddDays(2), nutrients, contains);
            Assert.AreEqual(testObj.IsSpoiled(), false);
        }
        // Testing to see if a fridged and unexpired item is spoiled, should return false
        [TestMethod]
        public void IsSpoiled_False()
        {
            string[] ingreds = { "pasta noodles", "milk", "cheese", "tomatoes" };
            float[] nutrients = { 3, 0, 0, 0, 0, 1, 4, 5, 24, 10, 3 };
            string[] contains = { "fish" };
            Entree testObj = new Entree("Pasta", ingreds, true, true, true, DateTime.Now.AddDays(2), nutrients, contains);
            Assert.AreEqual(testObj.IsSpoiled(), false);
        }
        // Testing to see if a unfridged item which doesn't need to be fridged spoils, should return false
        [TestMethod]
        public void IsSpoiled_NotRefrigerated_False()
        {
            string[] ingreds = { "apples", "bannanas", "pineapple", "orange" };
            float[] nutrients = { 5, 10, 23, 3, 52, 95, 50, 2, 0, 0, 3 };
            string[] contains = { "apples" };
            Entree testObj = new Entree("Varied Fruits", ingreds, false, false, true, DateTime.Now.AddDays(2), nutrients, contains);
            Assert.AreEqual(testObj.IsSpoiled(), false);
        }
        // Testing to see if a fridged item which doesn't need to be fridged spoils, should return false
        [TestMethod]
        public void IsSpoiled_NeedsFridgeFridged_True()
        {
            string[] ingreds = { "bread", "cheese", "garlic", "salt" };
            float[] nutrients = { 3, 0, 0, 0, 0, 1, 4, 5, 24, 10, 3 };
            string[] contains = { "pumpkin" };
            Entree testObj = new Entree("Breadsticks", ingreds, false, true, true, DateTime.Now.AddDays(2), nutrients, contains); ;
            Assert.AreEqual(testObj.IsSpoiled(), true);
        }
        // Testing to see if item contains an ingredient, should return true
        [TestMethod]
        public void ContainsIngred_True()
        {
            string[] ingreds = { "green peas", "milk" };
            float[] nutrients = { 5, 10, 23, 3, 52, 95, 50, 2, 0, 0, 3 };
            string[] contains = { "carb" };
            Entree testObj = new Entree("Poor man's dinner", ingreds, false, true, true, DateTime.Now.AddDays(2), nutrients, contains); ;
            Assert.AreEqual(testObj.ContainsIngred("milk"), true);
        }
        // Testing to see if item contains an ingredient, should return false
        [TestMethod]
        public void DoesntContainIngred_False()
        {
            string[] ingreds = { "beans", "tortilla", "cheese", "chips", "salsa", "beef", "corn" };
            float[] nutrients = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
            string[] contains = { "tomatoes" };
            Entree testObj = new Entree("Burrito", ingreds, false, true, true, DateTime.Now.AddDays(2), nutrients, contains); ;
            Assert.AreEqual(testObj.ContainsIngred("pizza"), false);
        }
    }
}
