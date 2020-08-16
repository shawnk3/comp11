#include "card.h"

// //default constructor always needed.
Card::Card(){
  cout << "Enter the suit: ";
  cin >> suit;
  cout << "Enter the number for card: ";
  cin >> number;
}

//argument based constructor
Card::Card(int suit, int number ){
  this -> suit = suit;
  this -> number = number;
}
//destructor
Card::~Card(){
  cout << "I'm here!" << endl;
}
void Card::setSuit(int suit){
  this -> suit = suit;
}

void Card::setNumber(int number){
  this -> number = number;
}

int Card::getSuit(){
  return suit;
}

int Card::getNum(){
  return number;
}


