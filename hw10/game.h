/*
 * game.h
 * COMP11 Splendor
 */

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <string>
#include "termfuncs.h"
#include "player.h"
#include "vector.h"

using namespace std;

class Game {
  public:
    //constructor
    Game(string filename, string play_nobles);
    
    //read file 
    void read_file(string filename);
    
    //quit the gameplay
    void quit();
    
    //initialize vectors
    void initializeVect(string row,int prestige, string discount, 
    int white,int red,int pink,int blue,int green);
    
    //convert index to color
    string indexToColor(int index);
    
    //convert color to index
    int colorToindex(string color);
    
    //void print grid cards
    void printCards();
    
    //player taking two gems
    bool p2query(string color, bool turn);
    
    //player taking three gems
    bool p3query(string color1, string color2, string color3, bool turn);
    
    //player reserving cards
    bool reserve(string row, int index, bool turn);
    
    //player purchasing cards
    bool buyCard(string row, int index, bool turn);
    
    //player purchasing reserves
    bool buyReserveCard(int index, bool turn);
    
    //player exceeding gems
    bool gemMaximized(bool turn);
    
    //populate gem_bank
    void populateBank();
    //main gameplay
    void playGame();
    
    //get the total gems in bank for specific gem
    int gemsInBank(string color);
    
    bool isColor(string color);
    
    //removing gems from bank
    void removeBankGems(string color, int amount);
    
    //all queries in single function
    void GameQuery(bool player1_turn, bool * game_over);
    
    //get grid card with specified index
    Card * getGridCard(string row, int col);
    
    //get index for grid specific row given deck string
    int gridRowIndex(string row);
    
    //replace card spot where reserve or bought card was 
    void replaceGridCard(string row, int col);
    
    //check if you can add more reserves
    bool ReservesFree(bool turn);
    
    //checks if you can buy the cards
    bool CanBuyCard(Card * card, bool turn);
    
    //check if prices match
    bool PriceMatch(Card * card , bool turn);
    
    //check if player1 has right gems
    bool p1Match(Card * card , int i);
    
    //check if player2 has the right gems
    bool p2Match(Card * card , int i);
    
    //check if player 1 can buy reserve
    bool p1CanBuyReserve(Card * card, bool turn);
    
    //check if player 2 can buy reserves
    bool p2CanBuyReserve(Card * card, bool turn);
    
    //check who won the game
    void GameWon(bool *game_over , bool turn);
    
    //setup game
    void setup();
    
    //reduced gem max for player_1
    bool p1GemMaximized();
    
    //reduce gem max for player_2
    bool p2GemMaximized();
    
    //functions that valid the use of any of the gameplay commands
    void validP2(bool player1_turn,bool * complete_query);
    void validP3(bool player1_turn,bool * complete_query);
    void validR(bool player1_turn,bool * complete_query);
    void validB(bool player1_turn,bool * complete_query);
    void validBR(bool player1_turn,bool * complete_query);
    
    //use yellow gems for player 1
    bool p1UseYellow(Card * card, int i);
    
    //use yellow gems for player 2
    bool p2UseYellow(Card * card, int i);
    
  private:
    //drawing functions
    void drawBoard();
    void drawNoble(int vpos, int hpos, Card *c);
    void drawPlayer(int vpos, int hpos, Player *p);
    void drawDeck(int vpos, int hpos, string type);
    void drawCard(int vpos, int hpos, Card *c);
    void drawGem(int vpos, int hpos, string color);
    void clearBoard();

    static const int BOARD_HEIGHT = 41;
    static const int BOARD_WIDTH = 120;
    static const int CARD_WIDTH = 13;
    static const int CARD_HEIGHT = 8;
    static const int CARD_ROWS = 3;
    static const int CARD_COLS = 4;
    static const int NUM_NOBLES = 3;
    static const int GEMS = 6;
    
    //gem bank for all the gems
    //{"white",	"red"	,"pink", "blue", "green","gold"};
    int gem_bank[6];

    //cards from the data file
    Vector vendors, transport, mines, nobles, p1cards, p2cards;
      
    //players for the splendor game
    Player player_1, player_2;
    
    //nobles activated true/false
    bool play_nobles;

    //cards in play
    Card *grid[CARD_ROWS][CARD_COLS];

    //display
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    string board_color[BOARD_HEIGHT][BOARD_WIDTH];
};

#endif