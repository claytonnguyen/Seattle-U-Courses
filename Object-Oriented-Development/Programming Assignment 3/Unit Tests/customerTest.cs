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
    public class customerTest
    {
        private const string filePath = "/Users/clayton/Downloads/EntreesTabDelimited.txt";
        Vendor vendor3 = new Vendor(filePath);

        [TestMethod]
        public void customerCanBuyCheezIt_true()
        {
            Customer customer = new Customer(100, 987340);
            Assert.AreEqual(customer.buyOne("Cheez It", vendor3), true);
        }

        [TestMethod]
        public void customerCanBuyFruitSnacks_false()
        {
            Customer customer = new Customer(1, 987340);
            Assert.AreEqual(customer.buyOne("Welch's Fruit Snacks Mixed Fruit", vendor3), true);
        }

        [TestMethod]
        public void customerCanBuySomethingNotInVendor_False()
        {
            Customer customer = new Customer(100, 987340);
            Assert.AreEqual(customer.buyOne("Pizza", vendor3), false);
        }

        [TestMethod]
        public void customerCanBuyAMeal_True()
        {
            Customer customer = new Customer(100, 987340);
            Assert.AreEqual(customer.buy(vendor3), true);
        }

        [TestMethod]
        public void customerCanBuyAMeal_False()
        {
            Customer customer = new Customer(10, 987340);
            Assert.AreEqual(customer.buy(vendor3), false);
        }
    }
}
