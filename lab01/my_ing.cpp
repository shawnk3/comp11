// my_ing.cpp
// Purpose: This program decides whether a user-provided
//          word ends in the suffix "ing"
// Written by: {your name and CS login}

#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "Greetings! I am the \"ing\" decider!" << endl;
    cout<< "Please enter a word:";
    string word;
    cin>> word;
    
    if(word.substr(word.length()-3 ,word.length()) == "ing"){
    cout<<  " Your word ends in \"ing\"! Fantastic!"<<endl;
    }
    else{
      cout<< " Oh no! I think you meant " + word + "-ing!"<<endl;
    }
    

  return 0;
}
