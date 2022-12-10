using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace P5
{
    [TestClass]
    public class allergyCustomerTest
    {
        private const string filePath = "/Users/clayton/Downloads/EntreesTabDelimited.txt";
        Vendor vendorPerson = new Vendor(filePath);

        [TestMethod]
        public void allergicBuysOne_True()
        {
            AllergyCustomer allergyCustomer = new AllergyCustomer(1000, 10034, "peanuts", false);
            Assert.AreEqual(allergyCustomer.buyOne("Cheez It", vendorPerson), true);
        }

        [TestMethod]
        public void allergicBuysOne_False()
        {
            AllergyCustomer allergyCustomer = new AllergyCustomer(1000, 10034, "peanuts", false);
            Assert.AreEqual(allergyCustomer.buyOne("Planters Nuts on the Go Salted Peanuts", vendorPerson), false);
        }

        [TestMethod]
        public void allergicCustomerDoesNotHaveEnoughMoneyToBuy_True()
        {
            AllergyCustomer allergyCustomer = new AllergyCustomer(1, 10034, "Cashew", false);
            Assert.AreEqual(!allergyCustomer.buyOne("Horizon Organic Whole Milk", vendorPerson), true);
        }
    }
}
