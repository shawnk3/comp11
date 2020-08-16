// aces.cpp
// Purpose: This program allows the user to randomly
//          draw cards from a 52-card deck.
// Written by: Megan Monroe (mmonroe)

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> 
#include "termfuncs.h"
#include "card.h"

using namespace std;

const int DECK_COUNT = 52;
const int SUIT_COUNT = 4;
const string SUITS[] = { "Spade", "Club", "Heart", "Diamond" };
const string NUMBERS[] = { "Two", "Three", "Four", "Five",
                           "Six", "Seven", "Eight", "Nine", "Ten",
                           "Jack", "Queen", "King", "Ace" };
                           
void print_card (int suit, int number);

int main() {
    // Set the screen-color "mood"
    screen_bg("black");
    screen_fg("white");
    
    // Declare a deck of 52 cards
    //Card deck[DECK_COUNT];
    Card * deck[DECK_COUNT];
    
    // Initialize each card to a particular suit and number
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < DECK_COUNT / 4; j++) {
            int index = (DECK_COUNT / 4) * i + j;
            
            //deck[index].setSuit(i);
            //deck[index].setNumber(j);
            deck[index] = new Card(i,j); //switch from array to array of pointers
            //delete deck[index];
        }
    }
    
    char draw_again;
    srand(time(0)); // Initialize the random number genrator
    
    // Prompt the user to draw a card at random from the deck
    cout << "Would you like to draw a card? Enter y/n: ";
    cin >> draw_again;
    
    while (draw_again == 'y') {
        int i = (rand() % 52); // Generate a random number between 0 and 51
        
        // Print out the card
        print_card(deck[i]->getNum(), deck[i]->getSuit());
        
        cout << "Would you like to draw a card? Enter y/n: ";
        cin >> draw_again;
    }
    
    // Return to original "mood"
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < DECK_COUNT / 4; j++) {
            int index = (DECK_COUNT / 4) * i + j;
                delete deck[index];
        }
    }
    screen_reset();
    return 0;
} 

void print_card(int number, int suit) {
    string top = "  _________  \n";
    string second = " /         \\ \n";
    string blank = "|           |\n";
    string bottom = " \\_________/ \n";
    
    // Determine the "number" to print on the card
    string num_str;
    if (number < 8) {
        num_str = to_string(number + 2);
    } else {
        num_str = NUMBERS[number][0];
    }
    
    // Print the card
    cout << top << second;
    cout << "| ";
    if (suit > 1) {
        screen_fg("red");
    }
    cout << num_str;
    screen_fg("white");
    cout << "         |\n";
    cout << "| ";
    if (suit > 1) {
        screen_fg("red");
    }
    cout << SUITS[suit][0];
    screen_fg("white");
    cout << "         |\n";
    for (int i = 0; i < 3; i++) {
        cout << blank;
    }
    cout << "|         ";
    if (suit > 1) {
        screen_fg("red");
    }
    cout << SUITS[suit][0];
    screen_fg("white");
    cout << " |\n";
    cout << "|         ";
    if (suit > 1) {
        screen_fg("red");
    }
    cout << num_str;
    screen_fg("white");
    cout << " |\n";
    cout << bottom;
    cout << NUMBERS[number] << " of " << SUITS[suit] << "s\n\n";
    
}
