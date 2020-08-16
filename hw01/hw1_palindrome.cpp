
// hw1.palindrome.cpp
// Purpose: This program takes any word and checks
//      if the word is a palindrome, and almost palindrome
//      or not a palindrome    .
// Written by: Shawn Kuriakose skuria01
#include <iostream>
#include <string>

using namespace std;

int main(){
  
    
    cout<< "Greetings! I am the palindrome decider!"<<endl;
    
    //intialize variables
    string word;  
    int i,j,count;
    bool palindrome = true;
    
    do{
      
      i=0; 
      count=0; 
      
      //call for user input
      cout<< "Please enter a word:";
      cin>>word;
      j = word.length() - 1 ;
     //two separate variables i and j are initialized to compare
     //word in reverse and the normal word
         
    // boolean variable initialize to track state of words
    //if it's a palindrome or not     
    //nested while loop is used to compare the beginning and end of word 
    //if the letters match
        while(i<j){
          //if at any case the characters aren't matchning,
          // the state of word is that it's not a perfect palindrome
          if(word[i] != word[j]){
            palindrome = false;
          }
        
          else{
            // else it's a perfect palindrome
            palindrome = true;
            //counter is initialized to track the number of letters that match
            count++;
            //this helps in the case that palindrome is false
            //but the front and end letters match
          }
      
        i++;
        j--;
    
      }
  // when palindrome is true, then word is perfect palindrome
    if(palindrome){ cout<< " Your word is a palindrome! Fantastic!"<<endl;}    

    //in case palindrome is false
    //counter kept track if the number of matching letters at front and end 
    // is greater than or equal to three
    if(count >= 3){
      cout<<" Not quite a palindrome, but close enough."<<endl;
      //setting palidrome boolean to true, so that 
      //even if the the word isn't perfect, you will be able to enter a new word
      palindrome = true;
    }
    
    
  }while(palindrome);
  // do while loop breaks when palidrome is false after
  //the nested while loop finishes
  
  // so then since palindrome isn't true, then isn't a palindrome
  cout<<" Your word is NOT a palindrome. Thanks anyway!"<<endl;

  return 0;
  
}
