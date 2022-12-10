// Author: Clay Nguyen
// November 4, 2021
// Last Revision - November 5, 2021

using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

// hardcoding is used to control the state of the vendor to showcase the test cases
// where it passes or fails.

namespace p3
{
    [TestClass]
    public class vendorTest
    {
        const string filePath = "/Users/clayton/Downloads/EntreesTabDelimited.txt";
        Vendor vendor5 = new Vendor(filePath);

        [TestMethod]
        public void Load_true()
        {
            string[] ingreds = { "salmon", "greens", "lemons", "oil" };
            float[] nutrients = { 5, 10, 23, 3, 52, 95, 50, 2, 0, 0, 3 };
            string[] contains = { "eggs" };
            Entree testObj = new Entree("Salmon Entree Go", ingreds, false, true, true, DateTime.Now.AddDays(-2), nutrients, contains);
            Assert.AreEqual(vendor5.Load(testObj, 25), true);
        }

        [TestMethod]
        public void Load_false()
        {
            Entree entree = new Entree();
            entree = null;
            Assert.AreEqual(vendor5.Load(entree, 10), false);
        }

        [TestMethod]
        public void Sell_true()
        {
            Assert.AreEqual(vendor5.Sell("Horizon Organic Whole Milk"), true);
        }

        [TestMethod]
        public void Sell_false()
        {
            Assert.AreEqual(vendor5.Sell("Popsicle"), false);
        }

        [TestMethod]
        public void IsStocked_true()
        {
            Assert.AreEqual(vendor5.IsStocked("Horizon Organic Whole Milk"), true);
        }

        [TestMethod]
        public void IsStocked_false()
        {
            vendor5.Sell("Horizon Organic Whole Milk");
            Assert.AreEqual(vendor5.IsStocked("Horizon Organic Whole Milk"), false);
        }

        [TestMethod]
        public void OnRefDisplay_true()
        {
            Assert.AreEqual(vendor5.IsOnRefDisplay("Cheez It"), true);
        }

        [TestMethod]
        public void OnRefDisplay_false()
        {
            Assert.AreEqual(vendor5.IsOnRefDisplay("Pizza"), false);
        }

        [TestMethod]
        public void ContainsIngred_true()
        {
            Assert.AreEqual(vendor5.containsIngredient("Rhythm Superfoods Carrot Sticks", "Organic carrots"), true);
        }

        [TestMethod]
        public void ContainsIngred_false()
        {
            Assert.AreEqual(vendor5.containsIngredient("Rhythm Superfoods Carrot Sticks", "Pumpkin"), false);
        }

        [TestMethod]
        public void Contains_true()
        {
            Assert.AreEqual(vendor5.contains("Planters Nuts on the Go Salted Peanuts", "peanuts"), true);
        }

        [TestMethod]
        public void Contains_false()
        {
            Assert.AreEqual(vendor5.contains("Planters Nuts on the Go Salted Peanuts", "pickle"), false);
        }

    }
}
