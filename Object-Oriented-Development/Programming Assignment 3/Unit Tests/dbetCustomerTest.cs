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
    public class dbetCustomerTest
    {
        private const string filePath = "/Users/clayton/Downloads/EntreesTabDelimited.txt";
        Vendor vendor1 = new Vendor(filePath);

        [TestMethod]
        public void diabeticBuysOne_True()
        {
            DBetCustomer dbetCustomer = new DBetCustomer(1000, 10034);
            Assert.AreEqual(dbetCustomer.buyOne("Welch's Fruit Snacks Mixed Fruit", vendor1), true);
        }

        [TestMethod]
        public void diabeticBuysOne_False()
        {
            DBetCustomer dbetCustomer = new DBetCustomer(1, 10034);
            Assert.AreEqual(dbetCustomer.buyOne("Horizon Organic Whole Milk", vendor1), false);
        }

        [TestMethod]
        public void customerCanBuySomethingNotInVendor_False()
        {
            DBetCustomer dbetCustomer = new DBetCustomer(100, 10034);
            Assert.AreEqual(dbetCustomer.buyOne("Tomatoe", vendor1), false);
        }

        [TestMethod]
        public void diabeticBuysMeal_True()
        {
            DBetCustomer dbetCustomer = new DBetCustomer(1000, 10034);
            Assert.AreEqual(dbetCustomer.buy(vendor1), true);
        }

        [TestMethod]
        public void diabeticBuysMeal_False()
        {
            DBetCustomer dbetCustomer = new DBetCustomer(1, 10034);
            Assert.AreEqual(dbetCustomer.buy(vendor1), false);
        }
    }
}
