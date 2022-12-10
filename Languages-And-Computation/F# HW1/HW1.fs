/// Name: Clayton Nguyen
/// Program Name: pa4.fs
/// Originality of Code: All of the code you turn in must have been written by you without immediate 
/// reference to another solution to the problem you are solving.  That means that you can look at 
/// other programs to see how someone solved a similar problem, but you shouldn't have any code 
/// written by someone else visible when you write yours (and you shouldn't have looked at a 
/// solution just a few seconds before you type!).  You should compose the code you write based on 
/// your understanding of how the features of the language you are using can be used to implement 
/// the algorithm you have chosen to solve the problem you are addressing.  Doing it this way is 
/// "real programming" - in contrast to just trying to get something to work by cutting and pasting 
/// stuff you don't actually understand.  It is the only way to achieve the learning objectives of the 
/// course. 


/// function returns the highest volume (a float) given a three float tuple list
let rec maxCubeVolume list =
  if list = [] 
    then 0.0
    else 
      let hd :: tl = list
      let (width, height, length) = hd
      let volume = (width * height * length)
      let nextres = maxCubeVolume tl
      if nextres > volume
        then
            nextres
        else
            volume

/// function returns a list of sorted tuple entries if the search keyword is in the list of tuple keys
/// Type Annotion of int list was used for a parameter since the VS compiler gave errors says list was generic
/// and that I needed to use type annotations
let rec findMatches search list:int list =
    match list with
    | [] -> []
    | hd :: tl -> 
          let hd :: tl = list
          let sttr, num = hd
          if sttr = search
              then
                  List.sort (num :: findMatches search tl)
              else
                  List.sort (findMatches search tl)


/// Tree definition for problem 3
type BST =
    | Empty
    | TreeNode of int * BST * BST

/// inserts a value at the empty leaf of a BST data type, returns the entire tree up to the root once inserted
/// works like a BST, inserting values into leafs based on the value at the root, traversing to the right or left node to insert
let rec insert value tree =
    match tree with
    | Empty -> TreeNode(value, Empty, Empty)
    | TreeNode (leaf, tree1, tree2) -> if leaf > value then TreeNode(leaf, (insert value tree1), tree2) else TreeNode(leaf, tree1, (insert value tree2))
        

/// recurses through the entire BST data type to find if the tree has the value in any of the nodes as its children
let rec contains value tree =
    match tree with
    | Empty -> false
    | TreeNode(leaf, tree1, tree2) -> if (leaf = value) then true else (contains value tree1 || contains value tree2)

/// takes in a function as a parameter that returns a bool that is used to return the count of the number of nodes which
/// satisfy the function passed in
let rec count func = function
    | Empty -> 0
    | TreeNode(leaf, tree1, tree2) -> if (func leaf) then (1 + (count func tree1) + (count func tree2)) else (count func tree1) + (count func tree2)

/// takes in a tree and returns the count of how many of the node values are even, uses the count function with a lambda
/// function that returns true when the value is divisible by two (even)
let rec evenCount tree =
    count (fun x -> x % 2 = 0) tree


