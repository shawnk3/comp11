#include "card.h"


//constructor
//constructors
/* Card()
 * Arguments: int prestige, string gem_color,
   int white,int red,int pink,int blue,int green)
 * initalize all of the private variables for the card
 *  it's prestige, discount, and prices to buy with gems
 */
Card::Card(int prestige, string gem_color,
  int white,int red,int pink,int blue,int green){
  this -> prestige = prestige;
  this -> gem_color = gem_color;
  setPrice(white,0);
  setPrice(red,1);
  setPrice(pink,2);
  setPrice(blue,3);
  setPrice(green,4);
}

//destructor
Card::~Card(){}

//setters
/* setPrice
 * Arguments: int price, int index
 * given arguements, initalize the price for a card depending on color
 */
void Card::setPrice(int price, int index){
  for(int i = 0; i < 5; i++){
    if (i == index){
        this -> gems_cost[i] = price;
    }
  }
}
//getters
/* getGemColor
 * return the discount for the card
 */
string Card::getGemColor(){
  return this -> gem_color;
}
/* getPrestige
 * return the prestige for the card
 */
int Card::getPrestige(){
  return this -> prestige;
} 
/* get Price
 * Arguments: int index
 * given index, return the number of gems for a specific color
 * needed to pay for the card
 */
int Card::getPrice(int index){
  for(int i = 0; i < 5; i++){
    if (i == index){
        return this -> gems_cost[i];
    }
  }
}
