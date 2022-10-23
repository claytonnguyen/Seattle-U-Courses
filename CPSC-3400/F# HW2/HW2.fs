/// Name: Clayton Nguyen
/// Program Name: Homework5.fs
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

/// function returns a number if the search keyword is in the list of tuple keys, 0 if not found
/// Type Annotion of int list was used for a parameter since the VS compiler gave errors says list was generic
/// and that I needed to use type annotations
let rec findMatches (search:string) (list) =
    match list with
    | [] -> 0
    | hd :: tl -> 
          let hd :: tl = list
          let sttr, num = hd
          if sttr = search
              then
                  num
              else
                  findMatches search tl

// arithmetic function that returns the new stack once an arithmetic function
// is applied to the first two elements and pushed the result to a new stack
let calculate (stack: int list) func = 
    let hd :: mid :: tl = stack
    let num = func hd mid
    num :: tl

// function that switches the place of the first and second elements in the stack
// and returns the new stack
let swap (stack: int list) = 
    let hd :: mid :: tl = stack
    mid :: hd :: tl

// function that binds the first letter from the expression string to the first
// number in the stack and returns the new vars list
let bind vars (stack: int list) (expr:string) =
    let letter = (expr.[1].ToString())
    let hd :: tl = stack
    (letter, hd) :: vars

// function that returns the stack without the first element
let popStack (stack: int list) =
    let hd :: tl = stack
    tl

// function that returns a number based on a postfix expression in a specific
// form that will return a number based on variable bindings and the arithmetic
// in the expession
let eval vars (expr:string) = 
    let rec innerEval vars (stack: int list) (expr:string) =
        let lengthOfString = expr.Length
        if lengthOfString = 0 then stack.[0] else 
        match expr.[0] with
        | '+' -> innerEval vars (calculate stack (fun x y -> x + y)) (expr.[1..].ToString()) // shortens the stack by 1, shortens the expr by 1
        | '-' -> innerEval vars (calculate stack (fun x y -> y - x)) (expr.[1..].ToString()) // shortens the stack by 1, shortens the expr by 1
        | '*' -> innerEval vars (calculate stack (fun x y -> x * y)) (expr.[1..].ToString()) // shortens the stack by 1, shortens the expr by 1
        // if division by 0 occurs, then x / y == x / 1, basically returning x
        | '/' -> innerEval vars (calculate stack (fun x y -> if x = 0 then y / 1 else y / x)) (expr.[1..].ToString()) // shortens the stack by 1, shortens the expr by 1
        | '$' -> innerEval vars (swap stack) (expr.[1..].ToString()) // changes values in the stack, shortens the expr by 1
        | '@' -> innerEval (bind vars stack expr) (popStack stack) (expr.[2..].ToString())// adds a tuple to the vars, shortens the stack by 1, shortens the expr by 2
        | ' ' -> innerEval vars stack (expr.[1..].ToString()) // shortens the expr string by 1, skips spaces
        | _ -> innerEval vars ((findMatches (expr.[0].ToString()) vars) :: stack) (expr.[1..].ToString()) // pushes a new number to the stack and 
        // shortens the expression string by 1

    innerEval vars [] expr