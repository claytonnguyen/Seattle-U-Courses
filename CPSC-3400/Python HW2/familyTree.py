"""
GEDCOM parser design

Create empty dictionaries of individuals and families
Ask user for a file name and open the gedcom file
Read a line
Skip lines until a FAM or INDI tag is found
    Call functions to process those two types

Processing an Individual
Get pointer string
Make dictionary entry for pointer with ref to Person object
Find name tag and identify parts (surname, given names, suffix)
Find FAMS and FAMC tags; store FAM references for later linkage
Skip other lines

Processing a family
Get pointer string
Make dictionary entry for pointer with ref to Family object
Find HUSB WIFE and CHIL tags
    Add included pointers to Family object
Skip other lines

Testing to show the data structures:
    Print info from the collections of Person and Family objects
    Print descendant chart after all lines are processed

"""

# Clayton Nguyen
# familyTree.py
# All of the code you turn in must have been written by you without immediate 
# reference to another solution to the problem you are solving.  That means that you can look at 
# other programs to see how someone solved a similar problem, but you shouldn't have any code 
# written by someone else visible when you write yours (and you shouldn't have looked at a 
# solution just a few seconds before you type!).  You should compose the code you write based on 
# your understanding of how the features of the language you are using can be used to implement 
# the algorithm you have chosen to solve the problem you are addressing.  Doing it this way is 
# "real programming" - in contrast to just trying to get something to work by cutting and pasting 
# stuff you don't actually understand.  It is the only way to achieve the learning objectives of the 
# course.

from collections import namedtuple
import os


class Event():

    def __init__(self,ref, type):
        # Initializes a new Event object
        self._id = ref
        self._place = None
        self._date = None
        if type == 'place':
            self._place = ref
        if type == 'date':
            self._date = ref

    def addDate(self, ref):
        # initialize date for event
        self._date = ref

    def addPlace(self, ref):
        # initialize place for event
        self._place = ref

    def date(self):
        # return date for the str function
        if self._date:
            return str(self._date)
        else:
            return ""

    def place(self):
        # return place for the str function
        if self._place:
            return str(self._place)
        else:
            return ""

    def __str__(self):
        if self._place and self._place == None:
            return None
        return self.date() \
                + " " + self.place()

#-----------------------------------------------------------------------

ordinal = dict({1:'first', 2:'second', 3:'third', 4:'fourth', 5:'fifth'})


class Person():
    # Stores info about a single person
    # Created when an Individual (INDI) GEDCOM record is processed.
    #-------------------------------------------------------------------

    def __init__(self,ref):
        # Initializes a new Person object, storing the string (ref) by
        # which it can be referenced.
        self._id = ref
        self._asSpouse = []  # use a list to handle multiple families
        self._asChild = None
        self._birth = None
        self._death = None
                
    def addName(self, names):
        # Extracts name parts from a list of names and stores them
        self._given = names[0]
        self._surname = names[1]
        self._suffix = names[2]

    def addIsSpouse(self, famRef):
        # Adds the string (famRef) indicating family in which this person
        # is a spouse, to list of any other such families
        self._asSpouse.append(famRef)
        
    def cousinHelper(self, level, currLevel, cousins):
        # is the helper function for printCousins
        # recurses up the family structure to get common parent
        if families.get(self._asChild):
            families[self._asChild].getParents(level, currLevel, cousins, self._id)


    def getCousins(self, currLevel, cousins):
        # checks if the level is the level to start going down the tree
        if currLevel == 0:
            cousins.append(self._id)
        else:
            for spouse in self._asSpouse:
                families[spouse].goDown(currLevel, cousins)

    def printCousins(self, level=1):
        # prints the cousins out
        cousins = []
        currLevel = 0
        self.cousinHelper(level, currLevel, cousins)
        print( ordinal.get(level) + ' cousins for ' + self.name())
        if len(cousins) == 0:
            print('No cousins')
        else:
            for cousin in cousins:
                print(persons[cousin].name() + ' ' + persons[cousin].eventInfo())




    def addIsChild(self, famRef):
        # Stores the string (famRef) indicating family in which this person
        # is a child
        self._asChild = famRef

    def printDescendants(self, prefix=''):
        # print info for this person and then call method in Family
        print(prefix + self.name() + " " + self.eventInfo())
        # recursion stops when self is not a spouse
        for fam in self._asSpouse:
            families[fam].printFamily(self._id,prefix)

    def isDescendant(self, personRef):
        # checks if the personRef is equal to the person
        if self._id == personRef:
            return True
        for fam in self._asSpouse:
            found = families[fam].findDescendant(personRef)
            if found == True:
                return True


    def printAncestors(self, prefix="", level=0):
        # prints out the ancestors
        if families.get(self._asChild):
            families[self._asChild].printParent1(prefix, level + 1)
        print(prefix + str(level) + " " + self.name() + self.eventInfo())
        if families.get(self._asChild):
            families[self._asChild].printParent2(prefix, level + 1)

    def addBirthDate(self, ref):
        
        if self._birth == None:
            self._birth = Event(ref, 'date')
        else:
            self._birth.addDate(ref)

    def addBirthPlace(self, ref):
        if self._birth == None:
            self._birth = Event(ref, 'place')
        else:
            self._birth.addPlace(ref)

    def addDeathDate(self, ref):
        if self._death == None:
            self._death = Event(ref, 'date')
        else:
            self._death.addDate(ref)

    def addDeathPlace(self, ref):
        if self._death == None:
            self._death = Event(ref, 'place')
        else:
            self._death.addPlace(ref)

    def name (self):
        # returns a simple name string 
        return self._given + ' ' + self._surname.upper()\
               + ' ' + self._suffix
    
    def treeInfo (self):
        # returns a string representing the structure references included in self
        if self._asChild: # make sure value is not None
            childString = ' | asChild: ' + self._asChild
        else: childString = ''
        if self._asSpouse != []: # make sure _asSpouse list is not empty
            # Use join() to put commas between identifiers for multiple families
            # No comma appears if there is only one family on the list
            spouseString = ' | asSpouse: ' + ','.join(self._asSpouse)
        else: spouseString = ''
        return childString + spouseString
    
    def eventInfo(self):
        ## add code here to show information from events once they are recognized
        if self._birth == None and self._death == None:
            return ''
        elif self._birth and self._death:
            return " | n: " + str(self._birth) + " | d: " + str(self._death)
        elif self._birth:
            return " | n: " + str(self._birth)
        elif self._death:
            return " | d: " + str(self._death)
        return ''

    def __str__(self):
        # Returns a string representing all info in a Person instance
        # When treeInfo is no longer needed for debugging it can 
        return self.name() \
                + self.eventInfo()  \
                + self.treeInfo()  ## Comment out when not needed for debugging


# end of class Person
 
#-----------------------------------------------------------------------

# Declare a named tuple type used by Family to create a list of spouses
Spouse = namedtuple('Spouse',['personRef','tag'])

class Family():
    # Stores info about a family
    # An instance is created when an Family (FAM) GEDCOM record is processed.
    #-------------------------------------------------------------------

    def printParent1(self, prefix, level):
        # goes up to parent 1
        prefix = prefix + "   "
        spouse1 = persons.get(self._spouse1.personRef)
        if spouse1:
            spouse1.printAncestors(prefix, level)

    def printParent2(self, prefix, level):
        # goes up to parent 2
        prefix = prefix + "   "
        spouse2 = persons.get(self._spouse2.personRef)
        if spouse2:
            spouse2.printAncestors(prefix, level)
        

    def goDown(self, currLevel, cousins):
        # helper function to recurse down tree to get to the right level to add cousin
        for child in self._children:
            persons[child].getCousins(currLevel - 1, cousins)

    def getParents(self, level, currLevel, cousins, familyId):
        # goes up the tree to find the family we want to recurse down with
        if level == currLevel:
            for child in self._children:
                if child not in familyId:
                    persons[child].getCousins(currLevel, cousins)


        if self._spouse1:
            if persons.get(self._spouse1.personRef):
                persons[self._spouse1.personRef].cousinHelper(level, currLevel + 1, cousins)

        if self._spouse2:
            if persons.get(self._spouse2.personRef):
                persons[self._spouse2.personRef].cousinHelper(level, currLevel + 1, cousins)


    def findDescendant(self, personRef):
        for child in self._children:
            found = persons[child].isDescendant(personRef)
            if found == True:
                return True

    def __init__(self, ref):
        # Initializes a new Family object, storing the string (ref) by
        # which it can be referenced.
        self._id = ref
        self._spouse1 = None
        self._spouse2 = None
        self._children = []
        self._marriage = None

    def addSpouse(self, personRef, tag):
        # Stores the string (personRef) indicating a spouse in this family
        newSpouse = Spouse(personRef, tag)
        if self._spouse1 == None:
            self._spouse1 = newSpouse
        else: self._spouse2 = newSpouse

    def addChild(self, personRef):
        # Adds the string (personRef) indicating a new child to the list
        self._children.append(personRef)

    def addMarrDate(self, ref):
        if self._marriage == None:
            self._marriage = Event(ref, 'date')
        else:
            self._marriage.addDate(ref)

    def addMarrPlace(self, ref):
        if self._marriage == None:
            self._marriage = Event(ref, 'place')
        else:
            self._marriage.addPlace(ref)
        
    def printFamily(self, firstSpouse, prefix):
        # Used by printDecendants in Person to print other spouse
        # and recursively invoke printDescendants on children

        # Manipulate prefix to prepare for adding a spouse and children
        if prefix != '': prefix = prefix[:-2]+'  '
        marriageInfo = ''
        if self._marriage != None:
            marriageInfo = ' m: ' + str(self._marriage)
        
        # Print out a '+' and the name of the second spouse, if present
        if self._spouse2:  # check for the presence of a second spouse
            # If a second spouse is included, figure out which is the
            # "other" spouse relative to the descendant firstSpouse
            if self._spouse1.personRef == firstSpouse:
                secondSpouse = self._spouse2.personRef
            else: secondSpouse = self._spouse1.personRef
            print(prefix+ '+' + persons[secondSpouse].name()+marriageInfo)

        # Make a recursive call for each child in this family
        for child in self._children:
            persons[child].printDescendants(prefix+'|--')

    def isChild(self, personId):
        for child in self._children:
            if persons[child] == personId:
                return True
            persons[child].isDescendant(persons[child])
        return False
        
    def __str__(self):
        ## Constructs a single string including all info about this Family instance
        spousePart = ''
        marriageDetails = ''
        for spouse in (self._spouse1, self._spouse2):  # spouse will be a Spouse namedtuple (spouseRef,tag)
            if spouse:  # check that spouse is not None
                if spouse.tag == 'HUSB':
                    spousePart += ' Husband: ' + spouse.personRef
                else: spousePart += ' Wife: ' + spouse.personRef
        childrenPart = '' if self._children == [] \
            else' Children: ' + ','.join(self._children)
        if self._marriage != None:
            marriageDetails = ' m: ' + str(self._marriage) + ' '
        return spousePart + childrenPart + marriageDetails

# end of class Family





#-----------------------------------------------------------------------
# Global dictionaries used by Person and Family to map INDI and FAM identifier
# strings to corresponding object instances

persons = dict()  # saves references to all of the Person objects
families = dict() # saves references to all of the Family objects


## Access functions to map identifier strings to Person and Family objects
## Meant to be used in a module that tests this one

def getPerson (personID):
    return persons[personID]

def getFamily (familyID):
    return families[familyID]

## Print functions that print the info in all Person and Family objects 
## Meant to be used in a module that tests this one
def printAllPersonInfo():
    # Print out all information stored about individuals
    for ref in sorted(persons.keys()):
        print(ref + ':' + str(persons[ref]))
    print()

def printAllFamilyInfo():
    # Print out all information stored about families
    for ref in sorted(families.keys()):
        print(ref + ':' + str(families[ref]))
    print()

#-----------------------------------------------------------------------
 
def processGEDCOM(file):

    def getPointer(line):
        # A helper function used in multiple places in the next two functions
        # Depends on the syntax of pointers in certain GEDCOM elements
        # Returns the string of the pointer without surrounding '@'s or trailing
        return line[8:].split('@')[0]
            
    def processPerson(newPerson):
        nonlocal line
        line = f.readline()
        tryBirth = False
        tryDeath = False

        while line[0] != '0': # process all lines until next 0-level
            # eventLine = line
            tag = line[2:6]  # substring where tags are found in 0-level elements
            numb = line[0]
            if tryBirth == True:
                if numb != '2':
                    tryBirth = False
            if tryDeath == True:
                if numb != '2':
                    tryDeath = False
            if tag == 'NAME':
                names = line[6:].split('/')  #surname is surrounded by slashes
                names[0] = names[0].strip()
                names[2] = names[2].strip()
                newPerson.addName(names)
            elif tag == 'FAMS':
                newPerson.addIsSpouse(getPointer(line))
            elif tag == 'FAMC':
                newPerson.addIsChild(getPointer(line))
            ## add code here to look for other fields
            
            elif tag == 'BIRT':
                tryBirth = True

            elif tag == 'DEAT':
                tryDeath = True

            elif numb == '2' and tag == 'DATE' and tryBirth == True:
                newPerson.addBirthDate(getPointer(" " + line.split('\n')[0]))
            elif numb == '2' and tag == 'PLAC' and tryBirth == True:
                newPerson.addBirthPlace(getPointer(" " + line.split('\n')[0]))

            elif numb == '2' and tag == 'DATE' and tryDeath == True:
                newPerson.addDeathDate(getPointer(" " + line.split('\n')[0]))
            elif numb == '2' and tag == 'PLAC' and tryDeath == True:
                newPerson.addDeathPlace(getPointer(" " + line.split('\n')[0]))

            # # read to go to next line
            line = f.readline()

    def processFamily(newFamily):
        nonlocal line
        line = f.readline()
        tryMarriage = False
        while line[0] != '0':  # process all lines until next 0-level
            tag = line[2:6]
            numb = line[0]
            if tryMarriage == True:
                if numb != '2':
                    tryMarriage = False
            if tag == 'HUSB':
                newFamily.addSpouse(getPointer(line),'HUSB')
            elif tag == 'WIFE':
                newFamily.addSpouse(getPointer(line),'WIFE')
            elif tag == 'CHIL':
                newFamily.addChild(getPointer(line))
            ## add code here to look for other fields 
            elif tag == 'MARR':
                tryMarriage = True

            elif numb == '2' and tag == 'DATE' and tryMarriage == True:
                newFamily.addMarrDate(getPointer(" " + line.split('\n')[0]))
            elif numb == '2' and tag == 'PLAC' and tryMarriage == True:
                newFamily.addMarrPlace(getPointer(" " + line.split('\n')[0]))

            # read to go to next line
            line = f.readline()


    ## f is the file handle for the GEDCOM file, visible to helper functions
    ## line is the "current line" which may be changed by helper functions

    f = open(file)
    line = f.readline()
    while line != '':  # end loop when file is empty
        fields = line.strip().split(' ')
        # print(fields)
        if line[0] == '0' and len(fields) > 2:
            # print(fields)
            if (fields[2] == "INDI"): 
                ref = fields[1].strip('@')
                ## create a new Person and save it in mapping dictionary
                persons[ref] = Person(ref)
                ## process remainder of the INDI record
                processPerson(persons[ref])
                
            elif (fields[2] == "FAM"):
                ref = fields[1].strip('@')
                ## create a new Family and save it in mapping dictionary
                families[ref] = Family(ref) 
                ## process remainder of the FAM record
                processFamily(families[ref])
                
            else:    # 0-level line, but not of interest -- skip it
                line = f.readline()
        else:    # skip lines until next candidate 0-level line
            line = f.readline()

    ## End of ProcessGEDCOM

#-----------------------------------------------------------------------    
## Test code starts here
            
def _main():
    filename = "Kennedy.ged"  # Set a default name for the file to be processed
##    Uncomment the next line to make the program interactive
##    filename = input("Type the name of the GEDCOM file:")

    processGEDCOM(filename)

    printAllPersonInfo()

    printAllFamilyInfo()
    
    person = "I46"  # Default selection to work with Kennedy.ged file
##    Uncomment the next line to make the program interactive
##    person = input("Enter person ID for descendants chart:")

    getPerson(person).printDescendants()

    
if __name__ == '__main__':
    _main()

