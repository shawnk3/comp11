/*
 * phone_tree.cpp
 * Purpose: Read a phone tree and determine if you can kmake a phone call
 * Submitted by: {Shawn Kuriakose skuria01}
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Mom{
  string name;
  int time;
  bool called;
  string next_mom;
  Mom * callmom; 
};

Mom *read_file(string filename, int *size); 
void point(Mom *moms , int num_moms);
void reset(Mom *moms , int num_moms);
bool callMoms(Mom *moms, int num_moms);
bool checkMoms(Mom * moms , int num_moms);

int main(int argc, char* argv[]){
  
  if (argc < 2) {
      cerr << "ERROR: Expecting a file name as a command-line argument."; 
      cerr <<endl;
      exit(EXIT_FAILURE);
  }
  //declare num_moms
  int num_moms;
  //call read file and input the filename and address for num_moms
  //so that we can array of structs for other functions
  Mom * moms = read_file(argv[1] , &num_moms);
  //call point to initalze pointers for every struct
  point(moms, num_moms);
  //call callMoms to check if the result was false
  if(!callMoms(moms, num_moms)){
      cout << "Another bungled phone tree, Sharon."<<endl;
  }
  //delete the Mom array of structs
  delete [] moms;
  
  return 0;
}
 //Read file into an array of Mom structs
Mom *read_file(string filename, int *size) {
 
    /* Open the file */
    ifstream infile(filename.c_str());
    /* Error check */
    if(infile.fail()){
      cerr<< "ERROR: error opening file, please  check filename."<<endl;
      exit(EXIT_FAILURE);
    }
    infile >> *size; // read size of array from first line
    //create moms array of structs of length *size
    Mom *moms = new Mom[*size]; 
    //loop in and initialize every parameter 
    //of the struct and add it to array
    for (int i = 0; i < *size ; i++){
      //every line after the first gives the name, time and next_mom
      infile >> moms[i].name >> moms[i].time >> moms[i].next_mom;
      //initialze the callmom pointer for every struct to null
      moms[i].callmom = nullptr;
      //called attribute should be initialized to be false
      moms[i].called = false;
    }

//close file
infile.close();

//return array of structs
return moms;
}
// initializes mom struct to the struct it should point to
void point(Mom *moms , int num_moms){
//loop through array of structs
  for (int i = 0; i < num_moms; i++) {
      for (int j = 0; j < num_moms; j++) {
          //check if the next mom attribute for the current 
          // mom struct matches the name attribute for another struct
          if (moms[j].name == moms[i].next_mom ) {
             // then initialze the current mom struct to point 
             //to the address of the other struct, and break
              moms[i].callmom = &moms[j];
              break;
          }
      }
  }
}
// resets the called attribute for every struct to false.
void reset (Mom *moms , int num_moms){
  for (int i = 0; i < num_moms ; i++){
      moms[i].called = false;
  }
}
//checks if any of the mom structs called is false
bool checkMoms (Mom * moms , int num_moms){
  for (int i = 0; i < num_moms ; i++){
    //return false if called attribute is false
      if(!moms[i].called){
        return false;
      }
  }
  //return true means all of the mom structs were called
  return true;
}
//determines if you can call the moms
bool callMoms(Mom *moms, int num_moms){
  //declare time and iterator i
  int time,i;
  time = 0;
  Mom * curr; //declare Mom*  
  string answer; // declare string answer
  for( i = 0 ; i < num_moms ; i++){
    // initializes curr to point to address of start of phone thread
    curr = &moms[i]; 
    //initialze answer to be the name attribute for the curr struct
    answer = curr -> name; 

    //call reset function for every struct in struct array
    reset(moms, num_moms);
    //count should start as one every time you start a new thread

    //initialize time to be zero for every time you start a call read through
    time = 0;
    //cout << curr -> name << endl;
    // add time since the first call should always be able to be completeres
    time += curr -> time;

    //run loop to determine if you can all the moms.
    //loop will break when you have already called a mom.
    while (!(curr -> called)){
      //cout<< "Curr:"<<curr -> name << endl;
  
      //marks the current mom as having made the call
      curr -> called = true;
      //change curr to point to the mom it called
      curr = curr -> callmom;
      // if you haven't call a mom more than once 
      if (!curr -> callmom -> called) {
       // add to the time
        time += curr -> time;
      }
      //calls checkMoms to see if all structs have been called.
      //returns true to main
      if(checkMoms(moms, num_moms)){
        cout << "Starting with "<< answer << " the phone tree will succeed in "
           << time <<" seconds!"<<endl;
          return true;
      }  
    }    

  }

  //indicates that you weren't able to complete a call
  // for the given the list of moms.
  return false;
}