# Word Ladder Programming Assignment in Python

A Word Ladder program is similar to a "6 degrees of separation" or Oracle of (Kevin) Bacon game, but using words rather than people or actors. Simply, from a given starting word, find the shortest "ladder" of single letter changes which leads to some final word, where each intermediate state is also a word.

For example:

clash, flash, flask, flack, flock, clock, crock, crook, croon, crown, clown.

As you might infer from the example above, there is no simple algorithm that generates a word ladder.   Rather, you have to search for a ladder by generating all of the possibilities. Doing so will give you an opportunity to use Python data structures like lists, sets and dictionaries.

Your program should first read in the file words.txt giving it a large collection of words to work with.  All of the examples in the tests that your program will be given will be of lengths no greater than 7, so you can discard all words that are longer than 7 characters.  However, if you choose the right data structures, keeping all of the words won't have any significant impact on how your program executes.

After processing the file of words, your program should process a sequence of pairs of words from a second file named pairs.txt.  Each pair of words in this file will be found on a single line of text.  There is no association between the lines of this file, so there is no reason to read and store the contents of this file.  Just process the lines one at a time, printing out the ladder for each pair or an indication that no ladder exists.  You should check that the input words are of the same length and produce an appropriate error message if they are of different lengths.  You can assume that every line in the text file will contain two words; you only need to check for potential length problems, as described above. 

Design your program using functions that encapsulate key design decisions.  For example, how you find adjacent words and how you implement the breadth-first search are completely independent.  Don't put the code for finding the adjacent words in the middle of your search loop.  Create a function that returns a list of the adjacent words given a single word as an argument.  Use that list to drive the loop that creates new queue entries,
