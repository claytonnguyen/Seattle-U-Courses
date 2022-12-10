# Family Tree Assignment in Python

This second Python project has the following goals:

Experience using Python classes
Understand and manipulate an interesting recursively-defined data structure
Understand and extend code written by someone else
The project involves processing genealogy information found in GEDCOM files, a standard interchange format used by genealogists and genealogy software (online GEDCOM specification).  You will be downloading a zip file (Family Tree files.zip) that contains several GEDCOM (.ged) files, among other things relevant to this project.  It also includes a Python program, descendants.py, that will be the starting point for your work.  More details about how to get started are included below.

The program reads in a GEDCOM file and builds a structure of objects that represent some of the information in the file, namely basic info about individuals and families.  It does this using two classes, Person and Family, which have obvious roles corresponding to their names.  More details can be found in the comments within the program.

The functions processPerson() and processFamily() parse the GEDCOM file, leading to creation of Person and Family objects.  Many kinds of GEDCOM records are currently skipped by these functions.  One of your tasks will be to  interpret some of the skipped lines.

The Person class includes a method named printDescendants() that initiates a traversal of the stored objects in a way that prints out a tree of descendants from the referenced instance of Person.  This method uses a corresponding method in Family (called printFamily) to produce its output.  printFamily calls printDescendants on each of the children of the family.  It is important for you to understand this two-step recursive process.  Look at the output it produces for a simple example and identify where how each line gets printed.

Project requirements:

Add a method isDescendant(personID) to Person which takes a person identifier string as an argument and returns True if the identified person is an descendant of self or False if this is not the case.  The answer should be True when the identified person is self.
Add a method printAncestors() to Person that does what its name suggests.  You aren't likely to manage to make this look as good as the output of printDescendants, but each line should include some indication how many generations up the tree the ancestor is.  Just starting the line with a number and appropriate indentation is sufficient.
Extend the processPerson and processFamily functions to handle birth, death and marriage records.  Look at the GEDCOM files to see just what these records look like.  You will find that all of them include specification of a date and a place, but either can be missing.  You will want to define an Event class that can store the date and place information (as strings) and can produce a string that represents all of the information it holds.  Any available event information should appear in the output produced by printDescendants.  See the html file in the project folder for an idea of what the output might look like.
Add a method printCousins(n) to Person that finds and prints out the nth cousins of the person.  You will get partial credit for submitting a method that only works for the special case of first cousins (n=1).  First cousins are other grandchildren of a person's grandparents.  Second cousins are other great grandchildren of a person's great grandparents and I'll assume you can work out the induction from those two examples.   (Sample output will be provided.)
