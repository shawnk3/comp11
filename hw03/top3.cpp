/*
 * top3.cpp
 * Purpose: Determine top3 numbers in a list.
 * Submitted by: {Shawn Kuriakose skuria01}
 */
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{

  if (argc < 2) {
      cerr << "ERROR: A filename must be specified as the first argument.\n";
      exit(EXIT_FAILURE);
  }
  /* Declare a variable to read in from the file */
  ifstream infile;
  infile.open(argv[1]);
  
    /* Error check */
  if(!infile.is_open()){
    cerr << "ERROR: Error opening file - ";
    cerr << "please check that you specified the correct file name\n";
    exit(EXIT_FAILURE);
  }
  //declare integer to write to
  int next_num;

  //declare variables for storing top 3 integers.
  int large1,large2,large3;
  //initialize integers to zero.
  large1=large2=large3=0;

/*Read the file and store top3 integers */  
 while ( infile >> next_num ) {
   //if number is greater than the greatest number
   //then set large1 to the number LAST
   //order of top3 should descend
   //so if large1 is replace, original large1, large2, and large3 should
   //all move down in order
   if( next_num > large1){
     large3 = large2; //replace the third value with intial second value
     large2 = large1; // replace second value with initial first value
     large1 = next_num; // set number as greatest value
   }
   //if number is greater than large2 
   //then it's same logic for large1
   //large1 is ignored
   else if( next_num > large2){
     large3 = large2; // large3 is set to large2 initial
     large2 = next_num; // set large2 to next num
   } 
   //if number is greater than large3, then replace large3
   else if ( next_num > large3 ) {
      large3 = next_num;
   }
 }

//print the numbers from greatest to least.
cout<<large1<<endl;
cout<<large2<<endl;
cout<<large3<<endl;

}