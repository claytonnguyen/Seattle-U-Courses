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
    public class employeeCustomerTest
    {
        private const string filePath = "/Users/clayton/Downloads/EntreesTabDelimited.txt";
        Vendor vendor3 = new Vendor(filePath);
        Vendor vendor2 = new Vendor(filePath);

        [TestMethod]
        public void customerCanBuyCheezIt_true()
        {
            EmployeeCustomer customer = new EmployeeCustomer(vendor3, 1, 100, 987340);
            Assert.AreEqual(customer.buyOne("Cheez It", vendor3), true);
        }

        [TestMethod]
        public void customerCanBuyFruitSnacks_false()
        {
            EmployeeCustomer customer = new EmployeeCustomer(vendor3, 1, 100, 987340);
            Assert.AreEqual(customer.buyOne("Welch's Fruit Snacks Mixed Fruit", vendor3), true);
        }

        [TestMethod]
        public void customerCanBuySomethingNotInVendor_False()
        {
            EmployeeCustomer customer = new EmployeeCustomer(vendor3, 1, 100, 987340);
            Assert.AreEqual(customer.buyOne("Pizza", vendor3), false);
        }

        [TestMethod]
        public void customerCanBuyAMeal_True()
        {
            EmployeeCustomer customer = new EmployeeCustomer(vendor3, 1, 100, 987340);
            Assert.AreEqual(customer.buy(vendor3), true);
        }

        [TestMethod]
        public void customerCanBuyAMeal_False()
        {
            EmployeeCustomer customer = new EmployeeCustomer(vendor2, 1, 1, 98732);
            Assert.AreEqual(customer.buy(vendor2), true);
        }
        [TestMethod]
        public void customerIsReplaced_True()
        {
            EmployeeCustomer customer = new EmployeeCustomer(vendor2, 1, 1, 98732);
            Customer cust = new CarbCustomer(12, 2894);
            Assert.AreEqual(customer.replaceCustomer(cust), true);
        }
        [TestMethod]
        public void customerIsReplaced_False()
        {
            EmployeeCustomer customer = new EmployeeCustomer(vendor2, 1, 1, 98732);
            Assert.AreEqual(customer.replaceCustomer(null), false);
        }
    }
}