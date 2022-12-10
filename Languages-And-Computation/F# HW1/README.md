# F# exercises

### Part 1
Write a function maxCubeVolume that takes a list of floating-point tuples that represent dimensions of a cube (length, width, and height) and returns the volume of the cube that has the largest volume.  Each tuple consists of three floating point values that are all greater than zero.  The volume of the cube is computed using (length*width*height). If the list is empty, return 0.0

### Part 2
Write an function findMatches that takes a string and a list of tuples as arguments. Each element of the list will be a tuple consisting of a string and an int. Find all of the tuples for which the string matches the first argument and collect all of the corresponding integers. Your final result should be the collected integers sorted in ascending order. For example, if the string argument is "A" and the list is [("A",5); ("BB",6); ("AA",9); ("A",0)], your function should return the list [0;5].  You may use the List.sort function to produce your final result.

### Part 3
Write the following binary search tree functions for a binary search tree of integers. (This will essentially be a tree set, i.e., a set data structure implemented using a tree.)
1. insert value tree
  * Inserts the value into the tree and returns the resulting tree. The resulting tree does NOT need to be balanced.  If the value already exists in the tree, return the tree without inserting the value.
2. Contains value tree
  * Returns true if the value is in the tree or false if it is not.
3. Count func tree
  * The parameter func is a Boolean function that takes a single parameter and returns true or false. The function tests the value of each node with func and returns the number of nodes that evaluate to true.
4. EvenCount tree
  * Returns the number of nodes that contain even integers.
  * REQUIREMENT: This function may not call any other function by name, except for the count function. However, you may use lambda functions (which do not have a name).
