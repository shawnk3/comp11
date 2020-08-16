// hw1.decrypt.cpp
// Purpose: This program decrypts a user-provided word
//          using any-shift Caesar cipher.
// Written by: Shawn Kuriakose (skuria01)
#include <iostream>
#include <string>

using namespace std;

int main(){
  
  int shift_amount;
  string word_to_decrypt;
  
  //Print a message explaining the purpose of this program
  cout << "Enter the word that you would like to decrypt (in lowercase characters)";
  cout << endl;
  
  //Prompt the user for a word to decrypt
  cout << "Word to decrypt: ";
  //Retrive the word from the user and store it in our variable
  cin >> word_to_decrypt;
  
  cout<< "Enter the shift amount:";
  cin>> shift_amount;
  

  
  //These variables store the length of the word and the position in that word
  //of the next letter to decrypt.
  int length_of_word = word_to_decrypt.length();
  int next_letter_pos = 0;
  
  cout << " Decrypted word: ";
  while ( next_letter_pos < length_of_word ) {
    char new_letter;

    //Perform the shift; use a different equation to shift based on whether we
    //have to wrap-around to the start of the alphabet
    
    //case where shift_amount is positive
    if(shift_amount>0){
    // for every case, shifting is based on letters after a+shiftamount
   // the opposite of z - shift amount , since we are going in reverse
   // for decrypting.   
      
      //accounts for every shift amount that is over 26 
      if (shift_amount>25){ shift_amount%=26;}
      
      if ( word_to_decrypt[next_letter_pos] < ('a' + (shift_amount))  ) {
      
     // since it's opposite of encrypt, we add 26- shift amount to letters
    // for words that exceed boundary of a+shift amount
      new_letter = word_to_decrypt[next_letter_pos] + 26 - (shift_amount);
     
      }
       
      else {
        // or else you just go reverse normally, opposite of encrypting
        // when it was addding
        new_letter = word_to_decrypt[next_letter_pos] - (shift_amount);
        
      }
    }
  
    //case where shift_amount is negative
  else {
    //for every case, shifting is based on going n amount of times backwards 
    //in alphabet base on shift shift_amount
    // if a letter is less than the first letter minus the shift_amount
    // then you add the shift amount + the number of letters in alphaebet
    // to get the correct cipher letter
      
      
      if (shift_amount<-25){ shift_amount%=26;}
    // for decrypting, the boolean conditionals are the same as encrypting
    //for positive shift amounts
    if ( word_to_decrypt[next_letter_pos] < ('z'+ (shift_amount-1))  ) {
    // note we are substracting because it's decrypting,
    // and since shift amount is negative, this cause is
    //shifting letter by positive value
    new_letter = word_to_decrypt[next_letter_pos]-shift_amount;
    } 
    else {
      // in the case you exceed the boundary, you have to return to alphabet,
      // so we go backwards if we exceed boundary, which is why
      // we shift back by the sum of the max letters in alphabet 
      //and shift amount
      new_letter = word_to_decrypt[next_letter_pos] - (26+shift_amount);
    }  
  }
    
    //Print out the decrypted letter
    cout << new_letter;

    // Move to the next character
    next_letter_pos = next_letter_pos + 1;
  }

  //Finish off by printing a newline
  cout << endl;

  
  return 0;
  
}