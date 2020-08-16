/*
 * cstrings.cpp
 * Purpose: Determine if word is substring of another word.
 * Submitted by: {Shawn Kuriakose skuria01}
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cctype> //Lets us use the isalpha function

using namespace std;

const int SIZE = 50;
int read_line(ifstream &infile, char words[SIZE][SIZE]);
bool is_equal(char *word1, char *word2);
bool is_prefix(char *word1, char *word2);
char *find_substring(char *haystack, char *needle);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "ERROR: A filename must be specified as the first argument.\n";
    exit(EXIT_FAILURE);
  }

  /* Open the file */
  ifstream infile;
  infile.open(argv[1]); 

  /* Error check */
  if (infile.fail()) {
    cerr << "ERROR: Error opening file - ";
    cerr << "please check that you specified the correct file name\n";
    exit(EXIT_FAILURE);
  }

  int total_words = 0;
  char words[SIZE][SIZE];
  total_words = read_line(infile, words); //Read the first line from the file
  while (!infile.eof()) {




    /* DO NOT MODIFY THE CODE IN main() ABOVE OR BELOW THIS COMMENT BLOCK */
    /* YOUR CODE GOES HERE */
    
  //initialize pointers to direct you to word in every line  
  char * a;
  char * b;
  
  //initialize iterators for loop
  int i,j;

  /* loop through the words array and compare every word with
  the rest of the words in the list*/ 
  for(i = 0; i < total_words; i++){
      // initialize a to point to word to compare to other words
      a = words[i];

    for(j = 0; j < total_words; j++){ 
      //initialize b to point to every word in line,
      //this way you can compare one word to every other word.
        b = words[j]; 
        //cout<<"word[i]:"<<words[i]<<endl;
        //cout<<"word[j]:"<<words[j]<<endl;
        //if(is_equal(a,b)){}
          //cout<< words[i] << " and "<< words[j] << " are equal."<<endl;  
        //if(is_prefix(a,b)){}
          //cout<< words[j] << " is prefix of "<< words[i] <<endl;
        
      
          //if find_substring doesn't return a nullptr
          //print word[j] is substring of word[i]
        if(find_substring(a,b) != nullptr){
          cout<< words[j] << " is a substring of "<< words[i] <<endl;
        }
    }

  }
    /* DO NOT MODIFY THE CODE IN main() ABOVE OR BELOW THIS COMMENT BLOCK */

  

    
    total_words = read_line(infile, words); //Read the next line from the file
  }
  
  /* Close the file */
  infile.close();
}

/* is_equal
 * Arguments: two pointers to C-style strings
 * Description: determines if two C-style strings are equivalent
 * Return value: true if strings are equivalent, false otherwise
 */
bool is_equal(char *word1, char *word2) {
  /* YOUR CODE GOES HERE. DELETE THE RETURN STATEMENT BELOW WHEN YOU'RE WORKING
   * ON THIS FUNCTION. */
   //initialize iterator
   int i = 0;   
   //cout<<"------------------------------"<<endl;
   /* Perform the loop compare the characters of 
     to see if they match. */
     //*(word + i)  == word[i]
     //loop should break if word1[i] or word2[i] points to \0 
   while(*(word1 + i) != '\0' || *(word2 + i) != '\0'){
     // if character never match, return false right away
     //since characters should match. 
     if(*(word1 + i) != *(word2 + i)){
       return false;
     }
     i++; 
     //else keep looking for a chance that words don't match
   }
    //if loop completes, that means words match, meaning they are true.
    return true;
 }

/* is_prefix
 * Arguments: two pointers to C-style strings
 * Description: determines if string word2 is a prefix of string word1
 * Return value: true if word2 is a prefix of word1, false otherwise
 */
bool is_prefix(char *word1, char *word2) {
  /* YOUR CODE GOES HERE. DELETE THE RETURN STATEMENT BELOW WHEN YOU'RE WORKING
   * ON THIS FUNCTION. */
   //initialize iterator
   int i = 0;
  //bool q = false;
    /*so long as smaller word(word2) charcter isn't \0, 
    we can just check if all of  word2 appears 
    in word1. */
  while(*(word2 + i) != '\0'){
      //if at the beginning,  word2's characters
      //doesn't appear in word1, then it 
      //isn't a prefix at all. so return false.
      if(*(word2 + i) != *(word1 + i)){  
          return false;  
      }
      //else keep looping
      i++;
  }
  //cout<<"j:"<<i<<endl;
  //assuming that the loop finished,that mean 
  //that word2 is prefix of word1
  return true;
}

/* find_substring
 * Arguments: two pointers to C-style strings
 * Description: determines whether string 'needle' is a proper substring of
 *              string 'haystack'. 
 * Return value: if 'needle' isn't a proper substring of 'haystack', return
 *               nullptr. Otherwise, return a pointer to the beginning of the
 *               first occurrence of 'needle' within 'haystack'.
 */
char *find_substring(char *haystack, char *needle) {
  /* YOUR CODE GOES HERE. DELETE THE RETURN STATEMENT BELOW WHEN YOU'RE WORKING
   * ON THIS FUNCTION. */
   //variable to store result of is_prefix 
   bool prefix = is_prefix(haystack,needle);
   // variable to store result of is_equal
   bool equal = is_equal(haystack,needle);
   //initialize iterator
   int i = 0;
   //if Is_prefix returns true and is_equal returns false 
   //then it is a substring.
   if(prefix && !(equal)){
     return needle;
   }
   // if is_equal returns true, then it is not a substring 
   if(equal){
     return nullptr;
   }
   /*loop and use the is_prefix func to find if needle occurs inside 
   haystack but it doesn't start at first character of haystack */
   while( *(haystack + i) != '\0' ){
     //if needle character ever equals haystack character
      if( *(needle) == *(haystack + i)){
        //cout<<"needle:"<<*needle<<endl;
        //cout<<"haystack:"<<*(haystack+i)<<endl;
        //call is prefix so that you can see if all
        //of the characters in needle match,
        //the rest of haystack
        //if is_prefix returns true, return needle right away
        if(is_prefix((haystack + i), needle)){
          return needle;
        }
      }
      //else keep looping
      i++;
   }
     //if(){
       //return needle;
     //}
   //cout<<"i:"<<i<<endl;

    
   //*(word2 + i)
   //*(word1 + i)
   //assuming you couldn't find needle in haystack
   //return the null ptr.
  return nullptr;
}

/* Retrieve a line of input from a file, parse it into individual words, and
 * store those words in the "words_in_sentence" 2D-array. Each "row" of
 * words_in_sentence is another word. Return the total number of words read in.
 *
 * NOTE: We have to write "ifstream &infile" as a parameter to pass an input
 * file stream correctly to a function. If you need to write a function that
 * takes a file stream as an argument, always put the '&' in front of the name
 * of your file stream.
 */
int read_line(ifstream &infile, char words_in_sentence[SIZE][SIZE]) {
  int spot = 0;
  int word_index = 0;
  char *next_word;
  char next_char;

  infile.get(next_char);
  while (!infile.eof() && next_char != '\n') {
    next_word = words_in_sentence[word_index];
    while (!infile.eof() && isalpha(next_char)) {
      next_word[spot] = next_char;
      ++spot;
      infile.get(next_char);  
    }
    if (spot > 0) {
      next_word[spot] = '\0';
      ++word_index;
      spot = 0;
    } else {
      infile.get(next_char);
    }
  
  }
  return word_index;
}
