/*
 * game.cpp
 * COMP11 Splendor
 */

#include "game.h"

const string QUIT = "q";
const string P2 = "p2";
const string P3 = "p3";
const string RESERVE = "r";
const string BUY = "b";
const string BUYRESERVE = "br";

//constructor
Game::Game(string filename, string play_nobles){
    //create player objects
    player_1 = Player();
    player_2 = Player();
   //include nobles or not
   if(play_nobles == "true"){
        this->play_nobles = true;
   }else{
        this->play_nobles = false;
   }
   //populate bank with gems
   populateBank();
   //initialize the board
   for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
   }     
  
    /*-----------------------------------------------*/
    /*          FINISH SETTING UP THE GAME           */
    //read in data from file
    read_file(filename);
    //create grid
    printCards();
    /*-----------------------------------------------*/ 
}

//main game loop
void Game::playGame(){
    bool game_over = false;
    bool player1_turn = true;

    while(!game_over){
        //reset the screen
        setup(); // call setup to initalize the board
        
      
        /*-----------------------------------------------*/
        /*             PLAY A TURN OF THE GAME           */
        GameQuery(player1_turn,&game_over); // run game query
          // check if current player has more than 10 gems
        while(!gemMaximized(player1_turn)){} 
        // check at any point if either player has won the game
        GameWon(&game_over,player1_turn);
        /*-----------------------------------------------*/

        //change turns
        player1_turn = !player1_turn;
    } 

}

//draw all of the elements onto the game board
void Game::drawBoard(){
    int vpos = 0;
    int hpos = 1;

    //draw the card decks
    if(!vendors.empty()){
        drawDeck(vpos, hpos, "Vendors");
    }
    vpos += CARD_HEIGHT + 1;
    if(!transport.empty()){
        drawDeck(vpos, hpos, "Transport");
    }
    vpos += CARD_HEIGHT + 1;
    if(!mines.empty()){
        drawDeck(vpos, hpos, "Mines");
    }

    //draw the in play cards
    vpos = 0;
    hpos = CARD_WIDTH + 2;
    for(int i = 0; i < CARD_ROWS; i++){
        for(int j = 0; j < CARD_COLS; j++){
            if(grid[i][j] != nullptr){
                drawCard(vpos, hpos, grid[i][j]);
            }
            hpos += CARD_WIDTH + 1;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = CARD_WIDTH + 2;
    }

    //draw the gems
    int gemOffset = ((CARD_WIDTH + 1) * 5) + 3;
    vpos = 1;
    hpos = gemOffset;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            int index = (i * 2) + j;

            if(gem_bank[index] > 0){
                board[vpos][hpos + 5] = gem_bank[index] + 48;
                board_color[vpos][hpos + 5] = indexToColor(index);
                drawGem(vpos + 1, hpos, indexToColor(index));
            }
            hpos += CARD_WIDTH;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = gemOffset;
    }
    
    //draw players
    drawPlayer(vpos + 1, 1, &player_1);
    drawPlayer(vpos + 1, ((CARD_WIDTH + 1) * 4), &player_2);

    //draw nobles
    if(play_nobles){
        hpos = ((CARD_WIDTH + 1) * 7) + 2;
        vpos = 2;
        for(int i = 0; i < NUM_NOBLES; i++){
            if(nobles.at(i) != nullptr){
                drawNoble(vpos, hpos, nobles.at(i));
            }
            vpos += CARD_HEIGHT + 1;
        }
    }

    //print out the finished board
    for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            if(board_color[i][j] != "white"){
                screen_fg(board_color[i][j]);
            }
            cout << board[i][j];
            screen_fg("white");
        }
        cout << endl;
   } 
   cout << endl; 
}

//draws a noble at the specified position of the board
void Game::drawNoble(int vpos, int hpos, Card *c){
    string top    = "|\\  /*\\  /|";
    string second = "| \\/   \\/ |";
    string blank  = "N         N";
    string bottom = "~~~~~~~~~~~";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];

        for(int j = 2; j < 5; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + 5][hpos + i] = bottom[i];
    }

    //draw the prices
    vpos += 2;
    for(int i = 0; i < GEMS-1; i++){
        int price = c->getPrice(i);
        if(price > 0){
            board_color[vpos][hpos + 4] = indexToColor(i);
            board_color[vpos][hpos + 5] = indexToColor(i);
            board_color[vpos][hpos + 6] = indexToColor(i);
            board[vpos][hpos + 4] = '|';
            board[vpos][hpos + 5] = price + 48;
            board[vpos][hpos + 6] = '|';
            vpos++;
        }
    }
}

//draws a player at the specified position of the board
void Game::drawPlayer(int vpos, int hpos, Player *p){
    //player string
    string prestige = to_string(p->totalPrestige());
    string player_s;
    if(hpos < 10){
        player_s = " PLAYER 1: " + prestige + " prestige point(s)";
    }else{
        player_s = " PLAYER 2: " + prestige + " prestige point(s)";
    }
    int length = player_s.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = player_s[i];
    }

    //bonus string
    vpos++;
    string bonus_s = "Discounts: ";
    length = bonus_s.length();
    for(int i = 0; i < GEMS-1; i++){
        int bonus = p->getDiscount(i);
        bonus_s += "|" + to_string(bonus) + "| ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
        if(bonus >= 10){
            length += 1;
        }
    }
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = bonus_s[i];
    }

    //gem string
    vpos++;
    string gems_s = "     Gems: ";
    length = gems_s.length();
    for(int i = 0; i < GEMS; i++){
        int gems = p->getGemCount(i);
        gems_s += "(" + to_string(gems) + ") ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
    }
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = gems_s[i];
    }

    //reserve string
    vpos++;
    string reserve_s = " Reserved:";
    length = reserve_s.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = reserve_s[i];
    }

    hpos += reserve_s.length();
    for(int i = 0; i < 3; i++){
        Card *c = p->getReserve(i);
        if(c == nullptr){
            drawDeck(vpos, hpos, "");
        }else{
            drawCard(vpos, hpos, c);
        }
        hpos += CARD_WIDTH + 1;
    }
}

//draws a card deck at the specified position of the board
void Game::drawDeck(int vpos, int hpos, string type){
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];
        for(int j = 2; j < CARD_HEIGHT; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    int start_pos = hpos + (blank.length() / 2) - (type.length() / 2);
    length = type.length();
    for(int i = 0; i < length; i++){
        board[vpos + (CARD_HEIGHT/2)][start_pos + i] = type[i];
    }
}

//draws a gem at the specified position of the board
void Game::drawGem(int vpos, int hpos, string color){
    string gem_image[6];
    gem_image[0] = "  _______  ";
    gem_image[1] = ".'_/_|_\\_'.";
    gem_image[2] = "\\`\\  |  /`/";
    gem_image[3] = " `\\  | //' ";
    gem_image[4] = "   `\\|/`   ";
    gem_image[5] = "     `     ";

    for(int i = 0; i < GEMS; i++){
        int length = gem_image[i].length();
        for(int j = 0; j < length; j++){
            board[vpos + i][hpos + j] = gem_image[i][j];
            board_color[vpos + i][hpos + j] = color;
        }
    }
}

//draws a card at the specified position of the board
void Game::drawCard(int vpos, int hpos, Card *c){
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];

        if(i == 8 || i == 9){
            board_color[vpos + 1][hpos + i] = c->getGemColor();
        }
        board[vpos + 1][hpos + i] = second[i];

        for(int j = 2; j < CARD_HEIGHT; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    //draw the prestige number and gem
    board[vpos + 2][hpos + 3] = c->getPrestige() + 48;
    board_color[vpos + 2][hpos + 8] = c->getGemColor();
    board_color[vpos + 2][hpos + 9] = c->getGemColor();
    board[vpos + 2][hpos + 8] = '\\';
    board[vpos + 2][hpos + 9] = '/';
    board_color[vpos + 1][hpos + 8] = c->getGemColor();
    board_color[vpos + 1][hpos + 9] = c->getGemColor();
    board[vpos + 1][hpos + 8] = '_';
    board[vpos + 1][hpos + 9] = '_';

    //draw the prices
    vpos += 4;
    for(int i = 0; i < GEMS-1; i++){
        int price = c->getPrice(i);
        if(price > 0){
            board_color[vpos][hpos + 2] = indexToColor(i);
            board_color[vpos][hpos + 3] = indexToColor(i);
            board_color[vpos][hpos + 4] = indexToColor(i);
            board[vpos][hpos + 2] = '(';
            board[vpos][hpos + 3] = price + 48;
            board[vpos][hpos + 4] = ')';
            vpos++;
        }
    }

}

//clear the board display
void Game::clearBoard(){
    for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
   }  
}

/* GameWon
 * Arguments: bool game_over, bool turn
 * determines if at any point if player 1 or player 2 has won the game
 */
void Game:: GameWon(bool *game_over , bool turn){
  if(turn){ //f it's player 1 turn and player 1 has more than 15 points
    if(player_1.totalPrestige() >= 15){
      //give player 2 a second chance to try and beat player 1
      setup(); 
      GameQuery(!turn,game_over);
      //player 2 beat player 1
      if(player_2.totalPrestige() > player_1.totalPrestige()){
        cout << "Congratulations Player 2: YOU WIN!!!!" << endl;
        *game_over = true;
      }
      //both players tied
      else if(player_2.totalPrestige() == player_1.totalPrestige()){
        cout << "You losers tied - BORING!!!!" << endl; 
        *game_over = true;
      }
      //player 1 won the game
      else{
        cout << "Congratulations Player 1: YOU WIN!!!!" << endl;
        *game_over = true;
      }
    }
  }
  else{ //if player 2 has more points on it's turn, and >=15, player 2 wins
    if(player_2.totalPrestige() >= 15){
      if(player_2.totalPrestige() > player_1.totalPrestige()){
        cout << "Congratulations Player 2: YOU WIN!!!!" << endl;
        *game_over = true;
      }
    }
  }
  
}


/* indexToColor
 * Arguments: int index
 * return the string color for given index, as gem_colors is accessible to all
 */
string Game:: indexToColor(int index){
  for(int i = 0; i < 6; i++){
    if(i == index){
      return gem_colors[i];
    }
  }
}
/* read_file
 * Arguments: string filename
 *  reads in data and calls initializeVect to initialize Vectors
 */
void Game:: read_file(string filename){
  //create infile object
  ifstream infile(filename.c_str());
  if(infile.fail()){
    cerr << "ERROR OPENING FILE: Exiting Program" << endl;
    exit(EXIT_FAILURE);
  }
  string str, row, discount;
  int prestige,white,red,pink,blue,green;
  //skip first line of file
  getline(infile,str);
  //keep reading in data until you reach end of file
  while(getline(infile,str)){
    infile >> row >> prestige >> discount >> white >> red >> pink 
    >> blue >> green;
    // call initializeVect to initalize vectors for Game
    initializeVect(row,prestige,discount,white,red,pink,blue,green);
  }
  //close file
  infile.close();
  
}
/* initializeVect
 * Arguments: string row, int prestige, string discount, int white,
   int red,int pink,int blue,int green
 * given argument inputs, create a card, and based on argument row,
 * add card to it's respective vector
 */
void Game::initializeVect(string row, int prestige, string discount, int white,
  int red,int pink,int blue,int green){
  //create card object
  Card * card = new Card(prestige,discount,white,red,pink,blue,green);
  //if row equals m t v or n , add it to it's respective vector
  //and using pushback to add it to end
  if(row == "m"){
    mines.push_back(card);
    //mines.print();
  }
  else if(row == "t"){
    transport.push_back(card);
    //transport.print();
  }
  else if(row == "v"){
    vendors.push_back(card);
    //vendors.print();
  }
  else if(row == "n"){
    nobles.push_back(card);
    //nobles.print();
  }
}
/* printCards
 * initalizes cards in play( the grid), by taking the last 4
 * cards in the deck, and pop_back every vector 4 times
 */
void Game::printCards(){
  for(int i = 0; i < CARD_ROWS; i++){
    for(int j = 0; j < CARD_COLS; j++){
      //print out cardfro respective row, starting with last card 
      //and initalize three more cards
      // print out the grid cards from mines deck
      if(i == 2){ 
        grid[i][j] = mines.at(mines.size()-1-j);}
      //print out grid cards from trasnport deck
      if(i == 1){
        grid[i][j] = transport.at(transport.size()-1-j);}
      //print out grid cards from vendors deck
      if(i == 0){
        grid[i][j] = vendors.at(vendors.size()-1-j);}
    }
  }
  //for initalize 4 cards from every deck in the grid,pop back 4 times
  for(int k = 0; k < 4; k++){
  mines.pop_back();  transport.pop_back();  vendors.pop_back();
  }
}

/* populateBank
 * populates the gems in the bank with their correct max gems.
 */
void Game::populateBank(){
  for(int i = 0; i < GEMS-1;i++){
    // all gems should be 4
    gem_bank[i] = 4;
  }
  //5 yellow gems
  gem_bank[GEMS-1] = 5;
}

/* isColor
  * Arguements: string color
 * returns true if given color is a valid color for game
 */
bool Game::isColor(string color){
  for(int i = 0 ; i < GEMS; i++){
    if(gem_colors[i] == color){
      return true;
    }
  }
  return false;
}
/* colorToindex
  * Arguements: string color 
 * return index for specific color
 */
int Game:: colorToindex(string color){
  for(int i = 0; i < GEMS; i++){
    //if color is a gem color, return index
    if(gem_colors[i] == color ){
      return i;
    }
  }
  return -1;
}
/* gemsInBank
  * Arguements: string color 
 * returns number of gems in bank for specific color
 */
int Game:: gemsInBank(string color){
  for(int i = 0; i < GEMS; i++){
    // if the index is found, return the gem bank amount
    if(i == colorToindex(color)){
      return gem_bank[i];
    }
  }
}
/* removeGems
  * Arguements: string color 
 * returns number of gems in bank for specific color
 */
void Game:: removeBankGems(string color,int amount){
  for(int i = 0; i < GEMS; i++){
    // if the index is found, return the gem bank amount
    if(i == colorToindex(color)){
      gem_bank[i] -= amount;
    }
  }
}
/* setup
  * calls functions necessary to set up board for playing game
 */
void Game:: setup(){
  clearBoard();
  screen_clear();
  screen_home();
  //draw the board
  drawBoard();
}

/* getMaximized
  * Arguements: bool turn
 * check if player has more than 10 gems, if they do
 * player must remove one gem of their choice.
 */
bool Game:: gemMaximized(bool turn){
  string color; int index;
  //if turn is true indicates player1
  if(turn){
    //if player total gems exceeds 10 or is 10, remove a gem
    if(player_1.totalGems() > 10){return p1GemMaximized();}
    return true;
  }
  else{
    //check if total gems exceeds 10
    if(player_2.totalGems() > 10){return p2GemMaximized();}
    return true;
  }
}
/* p1GemMaximized
  * Arguements:
 * prompts user to remove color designted gem so that gem count 
 * doesn't exceed 10. Returns true if you have <=10, else return false
 */
bool Game:: p1GemMaximized(){
  string color;
  setup();
  cout << "PLAYER 1, you have more than 10 gems!Name " 
  << "one gem you would like to return: ";
  cin >> color;
  //make sure user enters correct gem color
  while(!isColor(color)){
    cout << "Invalid color. Name one gem you would like to return: ";
    cin >> color;
  }
  int index = colorToindex(color);
  //can't take anything away from zero
  if(player_1.getGemCount(index) > 0){
    //return gems to bank
    player_1.addGem(color,-1);
    removeBankGems(color,-1);
  }
  //if player still has more than 10 gems, return false, else return true;
  if(player_1.totalGems() <= 10){ return true;} 
  else{
    return false;
  }
}
/* p2GemMaximized
  * Arguements:
 * prompts user to remove color designted gem so that gem count 
 * doesn't exceed 10. Returns true if you have <=10, else return false
 */
bool Game::p2GemMaximized(){
  string color;
  setup();
  cout << "PLAYER 2, you have more than 10 gems!Name " 
  << "one gem you would like to return: ";
  cin >> color;
  //check if it's a color
  while(!isColor(color)){
    cout << "Invalid color. Name one gem you would like to return: ";
    cin >> color;
  }
  int index = colorToindex(color);
  if(player_2.getGemCount(index) > 0){
    //return gems to bank
    player_2.addGem(color,-1);
    removeBankGems(color,-1);
  }
    //if player still has more than 10 gems, return false, else return true;
  if(player_2.totalGems() <= 10){ return true;} 
  else{
    return false;
  }
}
/* gridRowIndex
  * Arguements: string row
 * given string row, returns correct row index for deck 
 */
int Game:: gridRowIndex(string row){
  if(row == "v"){return 0;}
  if(row == "t"){return 1;}
  if(row == "m"){return 2;}
}
/* getGridCard
  * Arguements: string row, int col
 * given string row, and int col, returns 
 * the specific card in grid with the given parameters
 * else a null ptr is returned.
 */
Card * Game :: getGridCard(string row, int col){
  int rowindex = gridRowIndex(row); //retrieve row index of card 
  for(int i = 0; i < CARD_ROWS; i++){
    for(int j = 0; j < CARD_COLS; j++){
      // if row and col is found , return the card
      if(i == rowindex && j == col){
        return grid[i][j];
      }
    }
  }
  return nullptr;
}
/* replaceGridCard
  * Arguements: string row, int col
 * given string row, and int col, replaces the missing card
 * in the grid with the correct card from it's respective deck.
 */
void Game::replaceGridCard(string row, int col){
  int rowindex = gridRowIndex(row); //retrieve row index
  for(int i = 0; i < CARD_ROWS; i++){
    for(int j = 0; j < CARD_COLS; j++){
      //if the correct row and col is found, place a new card onto gridRowIndex
      //based on teh row index value
      if(i == rowindex){ 
       if(j == col){
        if(i == 2){grid[i][j] = mines.at(mines.size()-1);}
        if(i == 1){grid[i][j] = transport.at(transport.size()-1);}
        if(i == 0){grid[i][j] = vendors.at(vendors.size()-1);}
       }
      }
    }
  }
  //for every card taken away, pop back the respective vector
  if(rowindex == 2){mines.pop_back();}
  if(rowindex == 1){transport.pop_back();}
  if(rowindex == 0){vendors.pop_back();}
}
/* ReservesFree
  * Arguements: bool turn
 * depending on player turn, if the player has all 3 reserve spots
 * filled, they can't add any more cards, else, they can add cards
 */
bool Game:: ReservesFree(bool turn){
  //if total reserves is 3, means that reserve list is full.
    if(turn){
      if(player_1.totalReserves() == 3){
        return false;
      }
    }
    else{
      if(player_2.totalReserves() == 3){
        return false;
      }
    }
    //else the player can add a reserve
    return true;
}
/* CanBuyCard
  * Arguements: Card * card, bool turn
 * Checks to see if the player based on turn 
 *can buy the card passed into the function.
 * if you can pass the function return true, else return false
 */
bool Game:: CanBuyCard(Card * card, bool turn){
//if price match is true, then player can buy card
if(turn){
  if(PriceMatch(card,turn)){
       return true;
  }
}
else{
  if(PriceMatch(card,turn)){
      return true;
  }
}
//else it's impossible with current amount of gems
  return false;
}
/* PriceMatch
  * Arguements: Card * card, bool turn
 * Checks to see if the player based on turn 
 * returns false if either player can't pay for cards
 *else either player can buy the card.
 */
bool Game :: PriceMatch(Card * card, bool turn){
  int amount;
  if(turn){
   for(int i = 0; i < GEMS - 1; i++){
      if(!p1Match(card,i)){return false;} // player doesn not have enough gems
   }
  }
  else{
    for(int i = 0; i < GEMS - 1; i++){
     if(!p2Match(card,i)){return false;}// player doesn not have enough gems
    }
  }
  //regardless of player, price match should return true if
  // you can pay with current gems
  return true;
}
/* p1Match
  * Arguements: Card * card, int i 
 * checks if a certain color gem in player 1's bank can be used
 * to buy the card. also checks if you need to use any available yellow gems
 * to buy the card. If none of these options work, then you can't buy the card
 */
bool Game:: p1Match(Card * card,int i){
  int discount =  player_1.getDiscount(i); 
  int gem_count = player_1.getGemCount(i);
  //if the gem count is less than the current price
  if(gem_count < card -> getPrice(i)){
    //determines if you can buy the card with Discounts
    if(gem_count + discount >= card -> getPrice(i)){
      //if you can, return gem amount to bank, return true
      player_1.addGem(indexToColor(i), - gem_count); 
      removeBankGems(indexToColor(i), - gem_count);
      return true;
    }
    else{ // checks and determines whether yellow gems need to be used
      return p1UseYellow(card,i);
    }
  }
  //if the gem count and discount exceed , or maybe gem count exceeds
  //the price, you can buy the card. return gems to bank, and return true;
  if(gem_count + discount >= card -> getPrice(i)){
    player_1.addGem(indexToColor(i), -(card -> getPrice(i)));
    removeBankGems(indexToColor(i),-(card -> getPrice(i)));
    return true;
  }
  //can't buy the card using the current color gem
  return false;
}
/* p1UseYellow
  * Arguements: Card * card, int i 
 * determines if player 1's yellow gems can be used in any way to
 * replace the payment for the specific color gem given by the int i parameter
 */
bool Game:: p1UseYellow(Card * card, int i){
  //declare variables
  int k = 1;
  int amount = player_1.getGemCount(GEMS - 1);
  int discount =  player_1.getDiscount(i);
  int gem_count = player_1.getGemCount(i);
  //if there are yellow gems
  if(amount > 0){
    //determine how many yellow gems are needed to complete payment
    while(k <= amount){
      //if there are gems for specific color
      if(gem_count > 0){ 
        //use yellow gems to increase amount of gems for specific color
        if(gem_count + k + discount >= card -> getPrice(i)){
          //remove gems from bank, both the current color and yellow gems
          player_1.addGem(indexToColor(i), - gem_count);
          removeBankGems(indexToColor(i), -gem_count);
          player_1.addGem(indexToColor(GEMS - 1), -k);
          removeBankGems(indexToColor(GEMS - 1),-k);
          return true;
        }
      }
      //use yellow gems in place of the gem color 
      else{
        if(k + discount >= card -> getPrice(i)){
          //remove yellow gems from bank 
          player_1.addGem(indexToColor(GEMS - 1), -k);
          removeBankGems(indexToColor(GEMS - 1),-k);
          return true;
        }
      }
      k++; //increase number of yellow gems being used
    }
  
  }
  //can't use the yellow gems
  return false;
}

/* p1Match
  * Arguements: Card * card, int i 
 * checks if a certain color gem in player 2's bank can be used
 * to buy the card. also checks if you need to use any available yellow gems
 * to buy the card. If none of these options work, then you can't buy the card
 */
bool Game:: p2Match(Card * card,int i){
  int discount =  player_2.getDiscount(i);
  int gem_count = player_2.getGemCount(i);
  //if the gem count is less than the current price
  if(gem_count < card -> getPrice(i)){
      //determines if you can buy the card with Discounts
    if(gem_count + discount >= card -> getPrice(i)){
      //if you can, return gem amount to bank, return true
      player_2.addGem(indexToColor(i), - gem_count);
      removeBankGems(indexToColor(i), - gem_count);
      return true;
    }
    else{  // checks and determines whether yellow gems need to be used
      return p2UseYellow(card,i);
    }
  }
  //if the gem count and discount exceed , or maybe gem count exceeds
  //the price, you can buy the card. return gems to bank, and return true;
  if(gem_count + discount >= card -> getPrice(i)){
    player_2.addGem(indexToColor(i), -(card -> getPrice(i)));
    removeBankGems(indexToColor(i),-(card -> getPrice(i)));
    return true;
  }
  //can't buy the card using the current color gem
  return false;
}
/* p1UseYellow
  * Arguements: Card * card, int i 
 * determines if player 2's yellow gems can be used in any way to
 * replace the payment for the specific color gem given by the int i parameter
 */
bool Game:: p2UseYellow(Card * card, int i){
  //declare variables
  int k = 1;
  int amount = player_2.getGemCount(GEMS - 1);
  int discount =  player_2.getDiscount(i);
  int gem_count = player_2.getGemCount(i);
  //if there are yellow gems
  if(amount > 0){
      //determine how many yellow gems are needed to complete payment
    while(k <= amount){
        //if there are gems for specific color
      if(gem_count > 0){ 
        //use yellow gems to increase amount of gems for specific color
        if(gem_count + k + discount >= card -> getPrice(i)){
        //remove gems from bank, both the current color and yellow gems
          player_2.addGem(indexToColor(i), - gem_count);
          removeBankGems(indexToColor(i), -gem_count);
          player_2.addGem(indexToColor(GEMS - 1), -k);
          removeBankGems(indexToColor(GEMS - 1),-k);
          return true;
        }
      }
        //use yellow gems in place of the gem color 
      else{
        if(k + discount >= card -> getPrice(i)){
          //remove gems from bank 
          player_2.addGem(indexToColor(GEMS - 1), -k);
          removeBankGems(indexToColor(GEMS - 1),-k);
          return true;
        }
      }
      k++;//increase number of yellow gems being used
    }
  }
    //can't use the yellow gems
  return false;
}
/* p1CanBuyReserve
  * Arguements: Card * card, bool turn
 * checks if player 1 can buy the reserve by calling CanBuyCard
 * if it can, all available discounts and yellow gems are applied.
  */
bool Game:: p1CanBuyReserve(Card * card , bool turn){
  //if card isn't null ptr
  if(card != nullptr){
    //check if you can buy card
    if(CanBuyCard(card,turn)){
      //if it returns true. add card to player deck
      //add prestige and discount from card, and remove card from reserves
      p1cards.push_back(card);
      player_1.addPrestige(card -> getPrestige());
      player_1.addDiscount(card -> getGemColor());
      player_1.removeReserve(card);
    }
    //can't afford card
    else{
      cout << "Invalid move (cannot afford card) - enter a valid move: ";
      return false;
    }
  }else{ // no reserve at index
    cout << "Invalid move (no card at that index) - enter a valid move: ";
    return false;
  }
  //if the reserve was bought
  return true;
}

/* p2CanBuyReserve
  * Arguements: Card * card, bool turn
 * checks if player 2 can buy the reserve by calling CanBuyCard
 * if it can, all available discounts and yellow gems are applied.
  */
bool Game:: p2CanBuyReserve(Card * card , bool turn){
  //if card isn't null ptr
  if(card != nullptr){
    //check if you can buy card
    if(CanBuyCard(card,turn)){
      //if it returns true. add card to player deck
      //add prestige and discount from card, and remove card from reserves
      p2cards.push_back(card);
      player_2.addPrestige(card -> getPrestige());
      player_2.addDiscount(card -> getGemColor());
      player_2.removeReserve(card);
    }
    else{
      cout << "Invalid move (cannot afford card) - enter a valid move: ";
      return false;
    }
  }else{
    cout << "Invalid move (no card at that index) - enter a valid move: ";
    return false;
  }
  return true;
}

/* GameQuery
  * Arguements: bool player1_turn and bool *  game_over
 * runs the full game query for either player 1 or player 2
 * modifies the bool pointer to be true in the case either player quits
 */
void Game:: GameQuery(bool player1_turn , bool * game_over){
  string query; bool complete_query = false; 
  // player1_turn == true, player 1 turn , else player 2 turn
  if(player1_turn){cout << "PLAYER 1, enter your next move: ";}
  if(!player1_turn){cout << "PLAYER 2, enter your next move: ";}
  while(!complete_query){ //run query until complete_query = true;
    cin >> query; //read in user input
    if(query == P2){validP2(player1_turn , &complete_query);}
    else if(query == P3){validP3(player1_turn, &complete_query);}
    else if(query == RESERVE){validR(player1_turn,&complete_query);}
    else if(query == BUY){validB(player1_turn,&complete_query);}
    else if(query == BUYRESERVE){validBR(player1_turn,&complete_query);}
    else if(query == QUIT){
      //if quit is entered, game is over, and delete memory in heap
      complete_query = true;
      *game_over = true;
      quit();
    }else{ //there doesn't exists query with the given input
      cout << "Invalid move - enter a valid move: ";
    }
  }
}
/* validP2
  * Arguements: bool player1_turn and bool *  complete_query
 * runs through the p2 player query, if the use is able to complete 
 *move, *complete_query is set to true
 */
void Game:: validP2(bool player1_turn , bool * complete_query){
  string color;
  cin >> color; 
  if(p2query(color,player1_turn)){*complete_query = true;}
}
/* validP3
  * Arguements: bool player1_turn and bool *  complete_query
 * runs through the p3 player query, if the use is able to complete 
 *move, *complete_query is set to true
 */
void Game:: validP3(bool player1_turn,bool * complete_query){
  string color1,color2,color3;
  cin >> color1 >> color2 >> color3;
  if(p3query(color1,color2,color3,player1_turn)){*complete_query = true;}
}
/* validR
  * Arguements: bool player1_turn and bool *  complete_query
 * runs through the reserve player query, if the use is able to complete 
 *move, *complete_query is set to true
 * move won't be completd if reserves for player are full
 */
void Game:: validR(bool player1_turn,bool * complete_query){
  string deck; int index;
  cin >> deck >> index;
  if(ReservesFree(player1_turn)){ //if player reserves is free
    //check if you can reserve the card
    if(reserve(deck,index,player1_turn)){*complete_query = true;}
  }
  else{
    cout << "Invalid move (reserve is already full) - enter a valid move: ";
  }
}
/* validB
  * Arguements: bool player1_turn and bool *  complete_query
 * runs through the buy player query, if the use is able to complete 
 *move, *complete_query is set to true
 */
void Game::validB(bool player1_turn,bool * complete_query){
  string deck; int index;
  cin >> deck >> index;
  if(buyCard(deck,index,player1_turn)){*complete_query = true;}
}
/* validBR
  * Arguements: bool player1_turn and bool *  complete_query
 * runs through the buy reserve player query, if the use is able to complete 
 *move, *complete_query is set to true
 */
void Game::validBR(bool player1_turn,bool * complete_query){
  int index;
  cin >> index;
  if(buyReserveCard(index,player1_turn)){*complete_query = true;}
}
/* p2query
  * Arguements: string color and bool turn
 * returns true if you success added two of the same color gem 
 */
bool Game:: p2query(string color, bool turn){
  //if invalid color is entered, recall query
  if(!isColor(color)){ 
    cout << "Invalid move (invalid color) - enter a valid move: ";
    return false;
  }
  //p2 can't be called if there are less than 4 gems
  if(gemsInBank(color) < 4){ 
    cout << "Invalid move (unavailable gems) - enter a valid move: ";
    return false;
  }
  //add gems to player based on bool turn
  else{
      if(turn){
        player_1.addGem(color,2);
      }
      else{
        player_2.addGem(color,2);
      }
      //for every gem added, remove gem
      removeBankGems(color,2);
  }
    //gems sucessfully added
    return true;
}
/* p3query
  * Arguements: string color1 to color3 and bool turn
  * returns true if you success added one of each differen color gem
  * for the player based on bool turn.
 */
bool Game::p3query(string color1, string color2, string color3, bool turn){
  // if any of the colors enteredare not
  if(!isColor(color1) || !isColor(color2) || !isColor(color3)){ 
    cout << "Invalid move (invalid color) - enter a valid move: ";
    return false;
  }
  if(gemsInBank(color1) < 0 || gemsInBank(color2) < 0 
    || gemsInBank(color3) < 0){ 
    cout << "Invalid move (unavailable gems) - enter a valid move: ";
    return false;
  }
  //else add gems
  else{
    // 1 of every different color gem
      if(turn){
        player_1.addGem(color1,1);
        player_1.addGem(color2,1);
        player_1.addGem(color3,1);
      }
      else{
        player_2.addGem(color1,1);
        player_2.addGem(color2,1);
        player_2.addGem(color3,1);
      }
      //for every gem added, gems must also be removed
      removeBankGems(color1,1);
      removeBankGems(color2,1);
      removeBankGems(color3,1);
  }
  //gems sucessfully added
  return true;
}
/* reserve
  * Arguements: string row, int index, bool turn
  * returns true if you success added a reserve to player's reserve list.
 */
bool Game:: reserve(string row, int index, bool turn){
  //if wrong row string entered, invalid index.
  if(!(row == "m" || row == "t" || row == "v")){
    cout << "Invalid move (invalid card type) - enter a valid move: ";
    return false;

  }
  // if you entered wrong index
  if(index < 0 || index > CARD_COLS){
    cout << "Invalid move (invalid card column) - enter a valid move: ";
    return false;
  }
  // then add the reserve and a yellow gem if there are any more
  else{
    if(turn){
      player_1.addReserve(getGridCard(row,index - 1));
      if(gemsInBank("yellow") > 0){
        player_1.addGem("yellow",1);
        removeBankGems("yellow",1);
      }
    }
    else{
      player_2.addReserve(getGridCard(row,index - 1));
      if(gemsInBank("yellow") > 0){
        player_2.addGem("yellow",1);
        removeBankGems("yellow",1);
      }
    }
    //for every reserve added, and replace grid cards
    replaceGridCard(row,index - 1);
  }  
  //card successfully reserved
  return true;
}
/* buyCard
  * Arguements: string row, int index, bool turn
  * returns true if you success have bought card from grid
 */
bool Game::buyCard(string row, int index, bool turn){
  //generate the card from grid, with specific index.
  Card * card = getGridCard(row,index - 1);
  //if wrong row string entered, invalid index.
  if(!(row == "m" || row == "t" || row == "v")){
    cout << "Invalid move (invalid card type) - enter a valid move: ";
    return false;
  }
  //if index is out of bounds
  if(index < 1 || index > CARD_COLS){
    cout << "Invalid move (invalid card column) - enter a valid move: ";
    return false;
  }
  else{
    //if you can buy the card, then the card is added for respective
    //player, alongside the prestige points and discounts
    if(CanBuyCard(card,turn)){
      if(turn){
        p1cards.push_back(card);
        player_1.addPrestige(card -> getPrestige());
        player_1.addDiscount(card -> getGemColor());
      }
      else{
        p2cards.push_back(card);
        player_2.addPrestige(card -> getPrestige());
        player_2.addDiscount(card -> getGemColor());
      }
      //for every card bought, replace grid card
      replaceGridCard(row,index - 1);
    }
    //else you can't afford card, and turn is invalid
    else{
      cout << "Invalid move (cannot afford card) - enter a valid move: ";
      return false;
    }
  }
  //card was bought
  return true;
}

/* buyReserveCard
  * Arguements: int index, bool turn
  * returns true if you success have bought card from player's reserves
 */
bool Game::buyReserveCard(int index, bool turn){
  //generate the card from grid, with specific index.
  Card * card = nullptr;
  //if index is out of bounds
  if(index < 1 || index > 3){
    cout << "Invalid move (no card at that index) - enter a valid move: ";
    return false;
  }
  else{
    //if you can buy the card, then the card is added for respective
    //player, alongside the prestige points and discounts
      if(turn){
          card = player_1.getReserve(index - 1);
          if(!p1CanBuyReserve(card,turn)){return false;}
      }
      else{
          card = player_2.getReserve(index - 1);
          if(!p2CanBuyReserve(card,turn)){return false;}
      }
  }
  //reserve was bought
  return true;
}

/* quit
 * Deletes the vector cards and the grid cards from the heap
 */
void Game:: quit(){
  //loop through vectors and delete the allocated memory
 for (int i = mines.size() - 1; i >= 0 ; i--) {
   delete mines.at(i);
 }
 for (int i = transport.size() - 1; i >= 0; i--) {
   delete transport.at(i);
 }
 for (int i = vendors.size() - 1; i >= 0 ; i--) {
   delete vendors.at(i);
 }
 for (int i = 0; i < nobles.size(); i++) {
   delete nobles.at(i);
 }
 //delete all card pointers as this is the remaining memory in heap
 //since printCards moved cards from vectors into grid
 for (int i = 0; i < CARD_ROWS ; i++){
  for(int j = 0; j < CARD_COLS; j++){
    delete this -> grid[i][j];
  }
 }
 //deletes cards stored in player deck
for(int i = 0; i < p1cards.size(); i++){
   delete p1cards.at(i);
 }
 for(int i = 0; i < p2cards.size(); i++){
   delete p2cards.at(i);
 }
}