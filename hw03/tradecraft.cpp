/*
 * tradecraft.cpp
 * Purpose: Determine shift amount of encrypted text.
 * Submitted by: {Shawn Kuriakose skuria01}
 */
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

/* 
   declare global arrays for tracking frequency of 
   uppercase and lowercase letters in text
*/
int lower_counters[26];
int upper_counters[26];

/* count_letters
  Arguements: string filename
  
  Description: Reads a file and counts the frequency of lowercase
  and uppercase characters in the text file. The frequencies are 
  stored in global lower and uppercase letter frequency arrays.
  
  Return Value: no value
*/
void count_letters(string filename);
/* common_letter
  Arguements: no Arguements
  
  Description: Goes through global arrays for uppercase and lowercase 
  frequencies and determines the highest frequency between both uppercase 
  and lowercase letters. The letter with highest frequency is returned
  as char.
  
  Return Value: char 
*/
char common_letter();
/* shift_amount
  Arguements: char character
  
  Description: function calculates the shift amount by finding difference
  between the character parameter and the letter 'e'. 
  
  Return Value: integer
*/
int shift_amount(char character);

/* The main file takes the input file to determine shift amount for.
*/
int main(int argc, char *argv[])
{

  if (argc < 2) {
      cerr << "ERROR: A filename must be specified as the first argument.\n";
      exit(EXIT_FAILURE);
  }
  
  /*count the frequency of every letter in text */
  count_letters(argv[1]);
  /* determine letter of highest frequency*/
  char result = common_letter();
  //cout<<"result:"<<result<<endl;
  
  /*determine the shift amount*/
  int answer = shift_amount(result);
  
  //print shift amount
  cout<<"The shift amount is: "<<answer<<endl;
  
}



void count_letters(string filename){
  /* Declare a variable to read in from the file */
  ifstream infile;
  infile.open(filename);

  /* Error check */
  if(!infile.is_open()){
    cerr << "ERROR: Error opening file - ";
    cerr << "please check that you specified the correct file name\n";
    exit(EXIT_FAILURE);
  }

  char next_char;
  //int count=0;
  
  /*Read the file and count frequency of specific character */
  while( infile >> next_char ){
      //(next_char >= 'a' && next_char <= 'z' ) 
      // || (next_char >= 'A' && next_char <= 'Z'
      
      /* check if character is in alphabet */
        if( isalpha(next_char) ){
          /* check if character is uppercase letter*/
            if( isupper(next_char) ){
            // next_char - 'A' gives an index value between 0 and 25
             int index = next_char -'A';
             //the letter frequency is incremented given the right index
             upper_counters[index]++;
            // cout<<"upper index:"<<index<<endl;
            }
            else{ 
            // next_char - 'a' gives an index value between 0 and 25
             int index = (next_char -'a');
            //the letter frequency is incremented given the right index
             lower_counters[index]++;
            // cout<<"lower index:"<<index<<endl;
           }
            // cout<<"::"<<counters[index]<<endl;
             //cout<<":"<<next_char<<endl;   
        }
  }
  
/*  
  for (int i = 0; i<26; i++)      // Print the results
  	{
  		cout << "  " << char(i + 'a') << " occurs at "
  			<< lower_counters[i] << " times" << endl;
  	}
    for (int i = 0; i<26; i++)      // Print the results
      {
        cout << "  " << char(i + 'A') << " occurs at "
          << upper_counters[i] << " times" << endl;
      }
  */
}

char common_letter(){
  /* declare swap variable */
  int temp;
  
  /* declare index tracker for uppercase and lowercase */
  int index1,index2;
  
  /*initialize copies of uppercase and lowercase counter arrays */
  int arr1[26];
  int arr2[26];
  
  /* initialize copy of lower_counters to arr1 */
  for( int i = 0 ; i < 26; i++){
    arr1[i] = lower_counters[i];
    //cout<<"lower_counters:"<<arr1[i]<<endl;
  }
  
  /* sorts lower_counters from least to greatest */
  for( int i = 0; i < 26 ; i++){
    for( int j = i + 1; j < 26 ; j++){
    //cout<<"case1:"<<lower_counters[i]<<endl;
    //cout<<"case2:"<<lower_counters[i+1]<<endl;
    
    /* if current value is greater than next value, swap */
      if(lower_counters[i] > lower_counters[i + 1]){
        temp = lower_counters[i];
        lower_counters[i] = lower_counters[i + 1];
        lower_counters[i + 1] = temp;
      }
      //cout<<"temp:"<<temp<<endl;
      
    }
  }
  //cout<<"last element"<<lower_counters[25]<<endl;
  /*
    binary search to find when original array matches with last element
    of lower counters. In other words, determine index of letter 
    which has the greatest frequency.
 */  
  for( int i = 0; i < 26;i++){
    if(arr1[i] == lower_counters[25]){
      index1 = i;
    }
    
  }
  
   /* initialize copy of upper_counters to arr2 */
  for( int i = 0; i < 26 ;i++){
    arr2[i] = upper_counters[i];
    //cout<<"lower_counters:"<<arr1[i]<<endl;
  }
  
  /* sorts upper_counters from least to greatest */
  for( int i = 0; i < 26; i++){
    for( int j = i + 1 ; j < 26 ; j++){
    //cout<<"case1:"<<upper_counters[i]<<endl;
    //cout<<"case2:"<<upper_counters[i+1]<<endl;
    
      /* if current value is greater than next value, swap */
      if(upper_counters[i] > upper_counters[i + 1]){
        temp = upper_counters[i];
        upper_counters[i] = upper_counters[i + 1];
        upper_counters[i + 1] = temp;
      }
      //cout<<"temp:"<<temp<<endl;
      
    }
  }
  //cout<<"last element"<<upper_counters[25]<<endl;
  
 /*
    binary search to find when original array matches with last element
    of upper counters. In other words, determine index of letter 
    which has the greatest frequency.
 */  
  for( int i = 0; i < 26;i++){
    if(arr2[i] == upper_counters[25]){
      index2 = i;
    }
    
  }
 //cout<<index1<<endl;
//cout<<index2<<endl;

/* 
  assuming last element of upper and lower counters is the highest
  frequency amount, if upper > lower, then return an uppercase char
  using the index2 value, since that is value matched for 
  uppercase values 
*/
if(upper_counters[25] > lower_counters[25]){
   return char(index2 + 'A');
 }
 
 //else use index1 value which was found in binary search for lowercase
  return char(index1 + 'a');
}


int shift_amount(char character){
  int result = 0;
  // if character is uppercase , calculate shift amount 
  // with respect to capital 'E'  
    if(isupper(character)){
      result = character - 'E';
   }
  //lowercase, shift amount is letter minus 'e' 
  result = character - 'e';
  
  /*
   if result for either uppercase or lowercase is less than zero
   that indicates the most common letter isn't e.
   so then by adding 26 to the negative shift shift_amount
   the correct shift amount for the text is still determined.
  */
  if(result < 0){
    result += 26;
  }
  
  //return shift amount as integer.
  return result;
}