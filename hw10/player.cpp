#include "player.h"

//constructors
/* Player()
 * Arguments: creates Player objects
 */
Player::Player(){
  this -> prestige_total = 0;
  //loop through all array based data
  for(int i = 0; i < 6; i++){
      //initalize all total gems to be zero
      this -> total_gems[i] = 0;
      //since number of discounts is 5, initalize only 5 times
      if(i < 5){
        this -> total_discounts[i] = 0;
      } 
      //since number of discounts is 3, initalize only 3 times
      if(i < 3){
        this -> reserves[i] = nullptr;
      }
  }
}

/* ~Player()
 * Arguments: deletes player objects
 * if player still has reserves, deletes the reserves also
 */
Player::~Player(){
  for(int i = 0; i < 3; i++){
    if(this -> reserves[i] != nullptr){
      delete reserves[i];
    }
  }
}

//setters
/* addPrestige
 * Arguments: integer amount
 * add amount to total prestige for the Player object
 */
void Player:: addPrestige(int amount){
  this -> prestige_total += amount;
} 

/* addReserve
 * Arguments: pointer to Card object
 * add reserevs to array of Card reserve ponter for Player
 */ 
void Player:: addReserve(Card *reserve){
  int count = 0;
  for(int i = 0; i < 3; i++){
    //this is so you only add the reserve once
    if(count == 0){
      //if there is no reserve in position, add reserve
      if(this -> reserves[i] == nullptr){
        this -> reserves[i] = reserve;
        count++;
      }
    }
  }
}
/* add Discount
 * Arguments: string color
 * Given a stirng color, add it to 
 * list of discounts for the Player
 */
void Player:: addDiscount(string color){
  for(int i = 0; i < 5; i++){
    // if color arguemnt matches any of gem colors
    //add discount, which is one gem value
    if(gem_colors[i] == color){
      this -> total_discounts[i]+=1;
    }
  }
}
/* addGem
 * Arguments: string color and int amount
 * Add amount of gems for a specific color to array of gems for Player
 */
void Player:: addGem(string color, int amount){
  for(int i = 0; i < 6; i++){
    // if you find gem color, add number of gems for player
    if(gem_colors[i] == color){
      this -> total_gems[i]+=amount;
    }
  }
}

/* removeReserve
 * Arguments: Card * reserve
 * remove reserve from player's list of reserves
 */
void Player:: removeReserve(Card *reserve){ 
  for(int i = 0; i < 3; i++){
   if(this -> reserves[i] == reserve){
     //if reserve is in last spot, replace it with nulptr
     if(i == 2){
       this -> reserves[i] = nullptr;
     }
     //if reserve is in middle, set current spot to nullptr
     //move last card to middle spot
     if(i == 1){
       this -> reserves[i] = this -> reserves[i + 1];
       this -> reserves[i + 1] = nullptr;
     }
     //if reserve is first spot, move the other cards up one position.
     if(i == 0){
       this -> reserves[i] = this -> reserves[i + 1];
       this -> reserves[i + 1] = this -> reserves[i + 2];
       this -> reserves[i + 2] = nullptr;
       
     }
   }
  }
}



//getters
/* totalPrestige
 * Returns the total prestige for the PLayer
 */
int Player:: totalPrestige(){
  return this -> prestige_total;
}

/* getDiscount
 * Arguments: int index
 * returns the number of discount for the player based on index
 * index and color are analogous to each other
 */
int Player::getDiscount(int index){
  for(int i = 0; i < 5; i++){
    if(i == index){
      return this -> total_discounts[i];
    }
  }
}
/* TotalGems
 * add up the gems in the total gems bank for the PLAYER
 * and return total as integer
 */
int Player:: totalGems(){
  int total = 0;
  for(int i = 0; i < 6; i++){
    total+= total_gems[i];
  }
  return total;
}

/* getGemCount
 * Arguments: int index
 * return the gem count as int  for a specific color, given the index of color
 */
int Player:: getGemCount(int index){
  for(int i = 0; i < 6; i++){
    if(i == index){
      return this -> total_gems[i];
    }
  }
}
/* getReserve
 * Arguments: int index
 * returns pointer to a Player's reserve card given index
 */
Card * Player:: getReserve(int index){
  for(int i = 0 ; i < 3 ; i++){
    if(i == index){
      return this -> reserves[i];
    }
  }
}
/* totalReserves
 * Arguments: int index
 * return the total number of reserves that aren't null ptrs.
 */
int Player::totalReserves(){
  int total = 0;
  for(int i = 0; i < 3; i++){
    if(this -> reserves[i] != nullptr){
    total++;
    }
  }
  return total;
}