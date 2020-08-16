#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }

    bool valid_braces = true;
    
    
    /* DO NOT MODIFY THE CODE ABOVE OR BELOW THIS COMMENT BLOCK */
    /*                  YOUR CODE GOES HERE                     */
    
    ifstream infile;
    infile.open(argv[1]);
        
  
    if(!infile.is_open()){
      cerr << "ERROR: Error opening file - ";
      cerr << "please check that you specified the correct file name\n";
      exit(EXIT_FAILURE);
    }
    
    string next_char;
    string braces;
  
    while (infile>>next_char) {  
   
      if((next_char  == "{")||(next_char == "}")){
          braces.append(next_char);
    }
   }
   
  int i;
  int opencount=0;
  int closecount=0;

   for(i=0; i < braces.length();i++){
     if(braces[i] == '{'){
       opencount++;
     }
     
     if(braces[i] == '}'){
       closecount++;
        

   }
   if(closecount>opencount){
     valid_braces =false;
   }
  
 }
   
   infile.close();
   
   if(opencount>closecount){
     valid_braces = false;
   }
    /* DO NOT MODIFY THE CODE ABOVE OR BELOW THIS COMMENT BLOCK */
    if (valid_braces) {
        cout << "Baby G approves!" << endl;
    } else {
        cout << "Baby G does NOT approve!" << endl;
    }
}


