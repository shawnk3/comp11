#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class Card{
private:
  int suit;
  int number;
public:
//   //constructors
  Card();
  Card(int suit, int number);
  
  //destructors
  ~Card();
  //getters
  int getSuit();
  int getNum();
  //setters
  void setSuit(int suit);
  void setNumber(int number);

};

#endif