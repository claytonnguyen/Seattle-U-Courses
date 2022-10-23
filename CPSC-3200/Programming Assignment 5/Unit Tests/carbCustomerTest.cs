// Author: Clay Nguyen
// November 4, 2021
// Last Revision - November 5, 2021

using Microsoft.VisualStudio.TestTools.UnitTesting;

// hardcoding is used to control the state of the customer to showcase the test cases
// where it passes or fails. However, the price of each entree is determined randomly
// therefore there are times when the unit test may fail because of the variability in the
// price of the object is unknow till runtime

namespace P5
{
    [TestClass]
    public class carbCustomerTest
    {
        private const string filePath = "/Users/clayton/Downloads/EntreesTabDelimited.txt";
        Vendor vendor2 = new Vendor(filePath);

        [TestMethod]
        public void carbBuysOne_True()
        {
            CarbCustomer carbCustomer = new CarbCustomer(1000, 10034);
            Assert.AreEqual(carbCustomer.buyOne("Welch's Fruit Snacks Mixed Fruit", vendor2), true);
        }

        [TestMethod]
        public void carbBuysOne_False()
        {
            CarbCustomer carbCustomer = new CarbCustomer(1, 10034);
            Assert.AreEqual(carbCustomer.buyOne("Horizon Organic Whole Milk", vendor2), false);
        }

        [TestMethod]
        public void customerCanBuySomethingNotInVendor_False()
        {
            CarbCustomer carbCustomer = new CarbCustomer(100, 10034);
            Assert.AreEqual(carbCustomer.buyOne("Pasta", vendor2), false);
        }

        [TestMethod]
        public void carbBuysMeal_True()
        {
            CarbCustomer carbCustomer = new CarbCustomer(1000, 10034);
            Assert.AreEqual(carbCustomer.buy(vendor2), true);
        }

        [TestMethod]
        public void carbBuysMeal_False()
        {
            CarbCustomer carbCustomer = new CarbCustomer(1, 10034);
            Assert.AreEqual(carbCustomer.buy(vendor2), false);
        }
    }
}
