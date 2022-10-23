# Postfix Expression Evaluation

Your second F# assignment will be to write an expression evaluation function that take as arguments a list of variable bindings and a string that is composed of letters and operators from the set [+ - * /$@].  It will scan the string from left to right, interpreting the string as an expression in postfix Polish notation (except for the $ and @ special characters). 

* When it encounters a letter, it should retrieve the value associated with that letter and push it on an operand stack. 
* When it encounters an arithmetic operator, it should pop two operands off of the stack, do the computation indicated by the operation, and then push the result onto the stack. 
* When it encounters a $, it should should be interpreted as a swap operation, which pops two operands off of the stack, and pushes them back on in reverse order. 
* When the function encounters @, it should read the next character, which will be a letter,  then pop the top value from the stack and set that value as the new binding for the letter.
* Any spaces in the string should be skipped.
* When the input string is exhausted, the function should return the top value on the stack.
* You may assume that all input strings are syntactically legal according to this list of rules.

For example, given a set of variables described by [("a",5);("b",2);("c",9)], here is how several possible input strings would be interpreted:

"ab+" should return 7 (push 5, push 2, add)

"cab+-" should return 2 (push 9, push 5, push 2, add, subtract)

"cab+$-" should return -2 (push 9, push 5, push 2, add, swap the top two values (9 and 7), subtract)

"ab+cb-*" should return 49 (push 5, push 2, add, push 9, push2, subtract, multiply)

"ab+cb-* @d bd+" should return 51

(push 5, push 2, add, push 9, push2, subtract, multiply, bind 49 to d, push 2, push 49, add)

See the bottom of this assignment for some additional test strings.

Your function should be able to handle arbitrarily complex expressions, which implies that the stack should be represented by a list.  In order to handle what seems to be a requirement to remember a "state", you can use the accumulator technique we have seen for writing tail-recursive functions.  That means your evaluation function that looks like this

`let eval vars expr = ...`

should contain an inner recursive function with this signature:

`let rec innerEval vars stack expr = ...`

A new value for 'stack' will be used in a recursive call whenever the stack is pushed or popped.  Similarly, an @ operation will require a new value of 'vars' to be created to hold the new binding and the 'expr' string will get shorter by 1 or 2 characters for each recursive call.

You will need a helper function that takes a string and the list of tuples representing variable bindings as arguments. Each element of the list will be a tuple consisting of a string and an int. Find the first tuple for which the string matches the first argument and return the corresponding integer.  Note that this approach will allow you to add a new binding by creating a new list with that binding on the front.  Using the first binding found will then guarantee that the value from the most recent one is returned.
