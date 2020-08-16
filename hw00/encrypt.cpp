// encrypt.cpp
// Purpose: This program encrypts a user-provided word
//          using any-shift Caesar cipher.
// Written by: Shawn Kuriakose (skuria01)

#include <iostream>
#include <string>

using namespace std;

int main() {

  //Create two variables to hold the shift amount and the word to encrypt
  int shift_amount;
  string word_to_encrypt;

  //Print a message explaining the purpose of this program
  cout << "This program will encrypt a word provided by the user.";
  cout << endl;

  //prompt user to enter the shift_amount for cipher
  cout<< "Enter a shift amount:";
  cin>>shift_amount;
  cout<<endl;

  //Prompt the user for a word to encrypt
  cout << "Word to encrypt (in lowercase letters): ";
  //Retrive the word from the user and store it in our variable
  cin >> word_to_encrypt;

  //These variables store the length of the word and the position in that word
  //of the next letter to encrypt.
  int length_of_word = word_to_encrypt.length();
  int next_letter_pos = 0;

  cout << "Encrypted word:";

  // Loop through each character of the word, generating the 
  // encrypted output as we go
  while ( next_letter_pos < length_of_word ) {
    char new_letter;

    //Perform the shift; use a different equation to shift based on whether we
    //have to wrap-around to the start of the alphabet
    
    //case where shift_amount is positive
    if(shift_amount>0){
    // for every case, shifting is based on letters after z-shiftamount
    // so if any letter exceeds the last letter minus shiftamount
    // the wrap around equation is used.
      
      //accounts for every shift amount that is over 26 
      if (shift_amount>25){ shift_amount%=26;}
      
      if ( word_to_encrypt[next_letter_pos] < ('z'-(shift_amount-1))  ) {
      
      new_letter = word_to_encrypt[next_letter_pos] + (shift_amount);
      }
       
      else {
        new_letter = word_to_encrypt[next_letter_pos] - 26 + (shift_amount);
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
    
    if ( word_to_encrypt[next_letter_pos] < ('a' - (shift_amount))  ) {
    new_letter = word_to_encrypt[next_letter_pos]+ 26 +shift_amount;
    } 
    else {
      new_letter = word_to_encrypt[next_letter_pos] + shift_amount;
    }  
  }
    
    //Print out the encrypted letter
    cout << new_letter;

    // Move to the next character
    next_letter_pos = next_letter_pos + 1;
  }

  //Finish off by printing a newline
  cout << endl;

  return 0;
} 
