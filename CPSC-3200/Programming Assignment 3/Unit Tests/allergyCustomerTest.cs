// Author: Clay Nguyen
// November 4, 2021
// Last Revision - November 5, 2021

using Microsoft.VisualStudio.TestTools.UnitTesting;

// hardcoding is used to control the state of the customer to showcase the test cases
// where it passes or fails. However, the price of each entree is determined randomly
// therefore there are times when the unit test may fail because of the variability in the
// price of the object is unknow till runtime

namespace p3
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
            Assert.AreEqual(allergyCustomer.buyOne("Horizon Organic Whole Milk", vendorPerson), false);
        }
    }
}
