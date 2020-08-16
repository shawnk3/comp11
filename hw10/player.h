/*
 * player.h
 * COMP11 Splendor
 */
 
 #ifndef PLAYER_H
 #define PLAYER_H
 #include <iostream>
 #include <fstream>
 #include <string>
 #include "card.h"
 using namespace std;
 
 // {"white",	"red"	,"pink", "blue", "green"};
 
 class Player{
  private:
  Card * reserves[3];
  int prestige_total;
  int total_gems[6];
  int total_discounts[5];
  
  public:
  //constructors
  Player();  
  //destructor
  ~Player();
  //setters
  void addPrestige(int amount);
  void addReserve(Card *reserve);
  void addDiscount(string color);
  void addGem(string color, int amount);
  void removeReserve(Card *reserve);

   
  //getters
  int totalPrestige();
  int getDiscount(int index);
  int getGemCount(int index);
  int totalGems();
  int totalReserves();
  Card * getReserve(int index);
   
 };
 #endif
 
 
 
 
 