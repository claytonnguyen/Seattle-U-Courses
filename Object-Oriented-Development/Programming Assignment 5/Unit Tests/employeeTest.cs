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
    public class employeeTest
    {
        private const string filePath = "/Users/clayton/Downloads/EntreesTabDelimited.txt";
        Vendor vendor3 = new Vendor(filePath);

        [TestMethod]
        public void customerCanBuyCheezIt_true()
        {
            Employee employee = new Employee(ref vendor3, 1);
            Assert.AreEqual(employee.payDay(), true);
        }

        [TestMethod]
        public void customerCanBuyCheezIt_false()
        {
            Employee employee = new Employee(ref vendor3, 9);
            Assert.AreEqual(employee.payDay(), false);
        }
    }
}
