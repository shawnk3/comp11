/*
 * card.h
 * COMP11 Splendor
 */
 
 #ifndef CARD_H
 #define CARD_H
 #include <iostream>
 #include <fstream>
 #include <string>
 using namespace std;
 
 const string gem_colors[6] = {"white",	"red"	,"pink", "blue",
  "green","yellow"};
 
class Card{
  private:
  int prestige;
  int gems_cost[5]; // number of gems, and which gems are required to pay
  string gem_color; // represents discount
  public:
  //constructors
  Card(int prestige, string gem_color,int white,int red,
    int pink,int blue,int green);
  
  //destructor
  ~Card();
  //setters
  void setPrice(int price, int index);
  //getters
  string getGemColor();
  int getPrestige(); 
  int getPrice(int index);
  
  
   
};
#endif