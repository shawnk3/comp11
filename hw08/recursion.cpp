/*
 * recursion.cpp
 * Purpose: provides ability to use querey to determine 
 * either call power function, print reverse of word, return reverse of word
 * or dtermine word is subsequence of another word.
 * Submitted by: {Shawn Kuriakose skuria01}
 */
#include <iostream>
#include <string>

using namespace std;

/* Provided functions */
void print_menu(void);
void select_function(int choice);
void call_power(void);
void call_print_reverse(void);
void call_return_reverse(void);
void call_subseq(void);

/* Recursive functions you must write */
int power(int n, int k);
void print_reverse(string s);
string return_reverse(string s, string reverse);
bool subseq(string s, string t);

int main() {
  //Set choice to an initial dummy value
  int choice = -1;
  //Display the menu and get a user's choice
  cout << "Welcome to the recursion program!" << endl;
  print_menu();
  cin >> choice;
  //Perform an execute-and-prompt cycle
  while (choice != 0) {

    //Error checking -- make sure they give me an integer I can handle
    while (choice > 4 || choice < 0) {
      cout << "Please provide an integer between 0 and 4 as an option: ";
      cin >> choice;
    }

    if (choice == 0) {
      //We'll get here if the user gave an invalid number, then a 0
      return 0;
    }

    select_function(choice);

    //Print the menu again and get the user's next choice
    print_menu();
    cin >> choice;
  }
  return 0;
}

/* Select a function to call based on the user's choice. We assume that
 * the provided choice was already error-checked. */
void select_function(int choice) {
  //Run the function the user requested
  if (choice == 1) {
    call_power();
  } 
  else if (choice == 2) {
    call_print_reverse();
  } 
  else if (choice == 3) {
    call_return_reverse();
  } 
  else {
    call_subseq();
  }
}

/* Print out a menu of options for the user */
void print_menu() {
  cout << "Here are the recursive functions you can run:" << endl;
  cout << "1. power" << endl;
  cout << "2. print_reverse" << endl;
  cout << "3. return_reverse" << endl;
  cout << "4. subseq" << endl;
  cout << "Please provide the number of a function in the list to execute";
  cout << " (0 to quit): ";
}

/* Pass two user-provided arguments to the power function. Print the result. */
void call_power() {
  int n, k;
  cout << "Please provide the n to pass to power: ";
  cin >> n; 
  cout << "Please provide the k to pass to power: ";
  cin >> k; 
  cout << power(n, k) << endl;
}

/* Pass a user-provided argument to the print_reverse function. */
void call_print_reverse() {
  string s;
  cout << "Please provide the string to reverse: ";
  cin >> s; 
  print_reverse(s);
  cout << endl;
}

/* Pass a user-provided argument to the set_pins function. 
 * Print the result. */
void call_return_reverse() {
  string s;
  cout << "Please provide the string to reverse: ";
  cin >> s; 
  cout << return_reverse( s , "") << endl;
}


/* Pass two user-provided arguments to the subseq function. Print the result. */
void call_subseq() {
  string s, t;
  cout << "Please provide the s to pass to subseq: ";
  cin >> s;
  cout << "Please provide the t to pass to subseq: ";
  cin >> t;
  if(subseq(s, t)){
    cout << "VALID subsequence" << endl;
  }else{
    cout << "INVALID subsequence" << endl;
  }
}

/* Compute and return the result of n raised to the power of k. 
 * You can assume that k is a non-negative integer. */
int power(int n, int k) {
  // any number raised to zero power is always 1, this is base case
  //if k == 0 , return 1 
  if(k == 0){
    return 1;
  } 
  //Recursive case:
  //else return n multiplied by the power function with k -> k - 1
  //when k-1 = 0, base case is used, and recursive cases 
  //receive values to return.
  return n * power(n , k - 1);
}

/* Print out the string s backwards. */
void print_reverse(string s) {
  //Base case: if a word is a single character, the
  //reverse of a single character is the character, so 
  //you just need to print it out
  if(s.length() == 1){
    cout << s;
  }
  //Recursive case:
  //you print out the last character in word
  //modify the word to not contain the character printed out
  //and call print reverse with parameter as modified word
  else{
  cout << s.substr(s.length() - 1, s.length());
  s = s.substr(0,s.length()-1);
  print_reverse(s);
  }
}

/* Return the string s backwards. */
string return_reverse(string s , string reverse) {
  //Recursive Case: if length of s > 0
  // last character of s should be added to reverse 
  // modify s to not contain char added to reverse 
  // return function call with modifed s and reverse parameters
  if(s.length() > 0){
    reverse += s.substr(s.length()-1, s.length());
    s = s.substr(0,s.length()-1);
    return return_reverse(s,reverse);
  }
  //Base Case:If s.length == 0 , return reverse, which currently == ""
  //But if recursive case happened, will return reverse of s.
  return reverse;
}

/* Return true if string s is a subsequence of string t, false otherwise. */
bool subseq(string s, string t) {
  //Base case: if s = "x" t = "x" , then s is subsequence of t
  if(s == t){
    return true;
  }
  //Base case:
  //is s is blank, regardles of what t is, s is subsequence of t.
  if(s == ""){
    return true;
  }
  //Base case:
  //if t is blank, s can't be  a subseq of nothing, so return false
  if(t == ""){
    return false;
  }
  //Recursive case: 
  //if first char of s == first char of t 
  //modify s and t to not contain the first chars and return subseq(s,t)
  if(s.substr(0,1) == t.substr(0,1)){
    return subseq(s.substr(1,s.length()), t.substr(1,t.length()));
  }
  //Recursive case:
  //if first char of s != first char of t, modify t to not have first char
  //and return subseq(s,t) with modified t string.
  else{
    return subseq(s, t.substr(1,t.length()));
  }
}
