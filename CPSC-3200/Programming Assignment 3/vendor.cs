// Author: Clay Nguyen
// November 4, 2021
// Last Revision - November 5, 2021

// Class Invariant: allows for arbitrary length of entrees in the class since we
// are implementing with a linked list. Ctor sets up the top node to null. All public functions
// use linked list manuevers to go through the linked list, error checking along the way.
// 
//
//
// Interface Invariant: the file path where we derive the entree information is passed in
// as a dependency of the ctor and the ctor error checks the file path. Also as an extra
// counter measure, the entire populating of linked list from the file path by loading the
// entrees into the class is wrapped in a try catch block for maximum security.
// Lastly client needs to inject dependencies correctly for all the methods
// 

using System;
using System.IO;
using static p3.Entree;

namespace p3
{
    public class node
    {
        public float price;
        public Entree data;
        public node next;
    }

    public class Vendor
    {
        private node top;
        private uint entreeCount = 0;
        private readonly string filePath;
        private int lineCount = 0;
        private Random _random = new Random();

        // Pre-Condition: Must inject a valid Vendor object 
        // Post-Condition: Adds a node into the linked list. 
        private void copy(Vendor src)
        {
            node curr = top;
            node prev = null;
            node copyptr = src.top;
            while (copyptr != null)
            {
                node newPtr = new node();
                newPtr.data = new Entree(copyptr.data);
                newPtr.price = copyptr.price;
                newPtr.next = null;
                if (prev == null)
                {
                    top = newPtr;
                    curr = top.next;
                    prev = top;
                    copyptr = copyptr.next;
                }
                else
                {
                    curr = newPtr;
                    prev.next = curr;
                    prev = curr;
                    copyptr = copyptr.next;
                    curr = curr.next;
                }
            }
        }

        // Pre-Condition: Must inject a valid string path for the file
        // Post-Condition: Adds all the entree extracted from the file into
        // the class's linked list
        public Vendor(string _filePath)
        {
            top = null;
            if (_filePath != null) {
                filePath = _filePath;
                lineCount = findLines(filePath);
                // This accounts for the header not being counted
                lineCount--;
                SetUp(filePath, lineCount);
            }
        }

        // Pre-Condition: Must inject a valid Vendor type 
        // Post-Condition: Creates a deep copy of the vendor class passed in 
        public Vendor(Vendor src)
        {
            top = null;
            copy(src);
            entreeCount = src.entreeCount;
            filePath = src.filePath;
            lineCount = src.lineCount;
        }

        // Pre-Condition: Must not inject an incorrect Entree type or price into the function
        // Post-Condition: Adds a node into the linked list. 
        public bool Load(Entree entree, float price)
        {
            if (entree != null)
            {
                entreeCount++;
                node curr = top;
                node newNode = new node();
                newNode.data = entree;
                newNode.price = price;
                newNode.next = null;
                if (top == null)
                {
                    top = newNode;
                    Console.WriteLine("Loaded Entree: " + newNode.data.GetName());
                    return true;
                }
                while (curr.next != null)
                {
                    curr = curr.next;
                }
                Console.WriteLine("Loaded Entree: " + newNode.data.GetName());
                curr.next = newNode;
                return true;
            }
            else { return false; }
        }

        // Pre-Condition: Must inject a valid string into the function
        // Post-Condition: cleans the stock (gets rid of spoiled or expired entrees)
        //  and If the item is within the linked list, gets rid of it as well
        public bool Sell(string name)
        {
            node curr = top;
            node prev = null;
            CleanStock();
            while(curr != null)
            {
                if(curr.data.GetName() == name)
                {
                    if (!curr.data.IsSpoiled())
                    {
                        entreeCount--;
                        if(prev == null)
                        {
                            top = curr.next;
                            curr = top;
                            Console.WriteLine("Sold Entree: " + name);
                        }
                        else
                        {
                            node temp = curr.next;
                            prev.next = temp;
                            curr = prev;
                            Console.WriteLine("Sold Entree: " + name);
                        }
                        return true;
                    }
                }
                prev = curr;
                curr = curr.next;
            }
            return false;
        }

        // Pre-Condition: None
        // Post-Condition: changes all the entrees state to be spoiled since
        // the power went out
        public void PowerOutage()
        {
            node curr = top;
            while(curr != null)
            {
                curr.data.PowerDown();
                curr = curr.next;
            }
        }

        // Pre-Condition: None
        // Post-Condition: checks the entire linked list and gets rid of entree
        // items in the linked list that are spoiled or expired
        public void CleanStock()
        {
            node curr = top;
            node prev = null;
            while(curr != null)
            {
                if(curr.data.IsExpired() == true)
                {
                    if(prev == null)
                    {
                        top = curr.next;
                        curr = top;
                    }
                    else
                    {
                        node temp = curr.next;
                        prev.next = temp;
                        curr = prev;
                    }
                    entreeCount--;
                }
                prev = curr;
                curr = curr.next;
            }
        }

        // Pre-Condition: Injects a valid string
        // Post-Condition: None
        public bool IsStocked(string name)
        {
            node curr = top;
            while(curr != null)
            {
                if(curr.data.GetName() == name)
                {
                    return true;
                }
                curr = curr.next;
            }
            return false;
        }

        // Pre-Condition: Injects a valid string
        // Post-Condition: None
        public bool IsOnRefDisplay(string name)
        {
            node curr = top;
            while(curr != null)
            {
                if(curr.data.GetName() == name)
                {
                    return curr.data.IsRefrigerated();
                }
                curr = curr.next;
            }
            return false;
        }

        // Pre-Condition: Injects a valid string for name and nutrient
        // Post-Condition: None
        public float checkNutrition(string name, string input)
        {
            node curr = top;
            while (curr != null)
            {
                if (curr.data.GetName() == name)
                {
                    return curr.data.checkNutrients(input);
                }
                curr = curr.next;
            }
            return -1;
        }

        // Pre-Condition: Injects a valid string for name and ingredient
        // Post-Condition: None
        public bool containsIngredient(string name, string input)
        {
            node curr = top;
            while (curr != null)
            {
                if (curr.data.GetName() == name)
                {
                    return curr.data.ContainsIngred(input);
                }
                curr = curr.next;
            }
            return false;
        }

        // Pre-Condition: Injects a valid string for name and contains
        // Post-Condition: None
        public bool contains(string name, string input)
        {
            node curr = top;
            while (curr != null)
            {
                if (curr.data.GetName() == name)
                {
                    return curr.data.Contains(input);
                }
                curr = curr.next;
            }
            return false;
        }

        // Pre-Condition: Injects a valid string for name
        // Post-Condition: None
        public float getPrice(string name)
        {
            node curr = top;
            while (curr != null)
            {
                if (curr.data.GetName() == name)
                {
                    return curr.price;
                }
                curr = curr.next;
            }
            return -1;
        }

        // Pre-Condition: Should not call when the linked list is empty, since
        // it will try to create an array of length 0
        // Post-Condition: returns a string array of the names of the entrees in the
        // linked list
        public string[] randomEntree()
        {
            string[] array = new string[entreeCount];
            int count = 0;
            node curr = top;
            while (curr != null)
            {
                array[count] = curr.data.GetName();
                curr = curr.next;
                count++;
            }
            return array;
        }

        // Pre-Condition: Must inject a valid file path for the entree list
        // Post-Condition: returns the number of lines in the file
        public int findLines(string filePath)
        {
            int count = 0;
            try
            {
                StreamReader sr = new StreamReader(filePath);

                string line = sr.ReadLine();

                while (line != null)
                {
                    count++;
                    line = sr.ReadLine();
                }

                sr.Close();

            }
            catch (Exception e)
            {
                Console.WriteLine("Exception: " + e.Message);
            }
            return count;

        }

        // Pre-Condition: Must inject a valid file path for the entree list
        // Post-Condition: Will read from the file and create Entree objects which
        // will then be loadined into this class's linked list. The newly created
        // entrees will never be expired or spoiled. Only when electricity is turned off
        // or expiration date is passed
        private void SetUp(string filePath, int lineCount)
        {
            Random _random = new Random();
            char[] delimiter = new char[] { '\t' };
            char[] ingredientsDelimiter = new char[] { '$' };

            try
            {
                StreamReader sr = new StreamReader(filePath);

                string line = sr.ReadLine();
                string[] lineArr = line.Split(delimiter);

                int count = 0;
                int skipHeader = 0;

                while (line != null)
                {
                    string name = "";

                    const int lengthOfNutrients = 11;

                    float[] nutritionStats = new float[lengthOfNutrients];

                    Entree temp;

                    for (int i = 0; i < lineArr.Length; i++)
                    {
                        if (i == 0)
                        {
                            name = lineArr[i];
                        }
                        else if (i >= 1 && i <= lengthOfNutrients)
                        {
                            string s = lineArr[i];
                            if (skipHeader != 0)
                            {
                                nutritionStats[i - 1] = float.Parse(s);
                            }
                        }
                        else 
                        {
                            if (skipHeader != 0)
                            {
                                lineArr[i] = lineArr[i].Replace("\"", string.Empty);

                                string[] ingredients = lineArr[i].Split(ingredientsDelimiter);
                                string[] ingredientsList = new string[ingredients.Length];
                                ingredientsList = ingredients;

                                string[] contains;
                                contains = lineArr[i + 1].Split(ingredientsDelimiter);
                                string[] containsList = new string[contains.Length];
                                containsList = contains;
                                Entree food = new Entree(name, ingredientsList, true, true, true, DateTime.Now.AddDays(randomExp()), nutritionStats, containsList);
                                temp = food;

                                if (count < lineCount)
                                {
                                    Load(temp, randomPrice());s
                                }

                                break;

                            }

                        }
                    }
                    line = sr.ReadLine();
                    if (line != null)
                    {
                        lineArr = line.Split(delimiter);
                    }
                    if (skipHeader != 0)
                    {
                        count++;
                    }
                    skipHeader++;
                }

                sr.Close();

            }
            catch (Exception e)
            {
                Console.WriteLine("Exception: " + e.Message);
            }
        }

        // Pre-Condition: None
        // Post-Condition: returns a float between 0 and 100
        public float randomPrice()
        {
            float x = _random.Next(0, 100);
            return x;
        }

        // Pre-Condition: None
        // Post-Condition: returns an int between 0 and 10
        public float randomExp()
        {
            int x = _random.Next(0, 10);
            return x;
        }
    }
}

// Implementation Invariant: Designed the vendor class to pass in the file path as a
// dependency to encapsulate all the data into just one class and have the class and
// set up of the class be cohesive and not relying on the client to setup the entrees
// to be loaded into the class's linked list