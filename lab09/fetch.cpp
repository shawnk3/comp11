// fetch.cpp
// Purpose: Interact with a binary tree storing numbers and colors
// Written by: Megan Monroe (mmonroe)

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Node struct contains a number, a color, 
//and pointers to the left and right sub-trees
struct Node {
    int number;
    string color;
    Node *less_than;
    Node *greater_than;
};

const string INSERT = "i";
const string FETCH = "f";
const string RAINBOW = "r";
const string REVERSE = "rr";
const string QUIT = "q";

Node *new_node(int number, string color);
void insert_node(Node *curr_node, int number, string color);
void fetch(Node * curr_node, int number);
void rainbow(Node * curr_node , int number);
void reverse(Node * curr_node , int number);

int main(int argc, char *argv[]){
    //Initialize a root node and point to it
    Node *root = new_node(50, "black");

    //Loop to continually prompt for queries
    int number;
    string c, color;
    cout << "Enter your command: ";
    cin >> c;
    while (c != QUIT) {
        if (c == INSERT) {
            cin >> number >> color;
            insert_node(root, number, color);
        } else if (c == FETCH) {
            cin >> number;

            fetch(root, number);
        } else if (c == RAINBOW) {
            cin >> number;
            
           rainbow(root , number);
        } else if (c == REVERSE) {
            cin >> number;
            
          reverse(root,number);
        } else {
            cout << c << " not recognized." << endl;
        }
        cout << endl << "Enter your command: ";
        cin >> c;
    }

    return 0;
} 



//Starting from the current node, find where a node with the given number should
//be stored. If such a node already exists, update its color. Otherwise, create
//a new node in the proper location with the given number and color.
void insert_node(Node *curr_node, int number, string color){
    //Base Case 1: If that number is already stored, update the color
    if (curr_node->number == number) {
        curr_node->color = color;
    } 
    else if (curr_node->number > number) {
        if (curr_node->less_than == nullptr) {
            //Base Case 2: We found the correct spot, add the new node
            curr_node->less_than = new_node(number, color);
        } else {
            //Recursive Case 1: Move to the left ("less_than") subtree
            insert_node(curr_node->less_than, number, color);
        }
    } else {
        if (curr_node->greater_than == nullptr) {
            //Base Case 3: We found the correct spot, add the new node
            curr_node->greater_than = new_node(number, color);
        } else {
            //Recursive Case 2: Move to the right ("greater_than") subtree
            insert_node(curr_node->greater_than, number, color);
        }
    }
}

//Returns a pointer to a new node with the provided number and color. Note that
//a new node always has it's less_than and greather_than fields set to nullptr.
Node *new_node(int number, string color){
    Node *new_node = new Node;

    new_node->number = number;
    new_node->color = color;
    new_node->less_than = nullptr;
    new_node->greater_than = nullptr;

    return new_node;
}

void fetch(Node * curr_node, int number){
    if(curr_node -> number == number){
     cout << curr_node -> color << endl;
    }
    else if(number < curr_node -> number){
      if(curr_node -> less_than == nullptr){
          cout << "Node not found!" << endl;
      }
      else{
      fetch(curr_node -> less_than , number);
      }
    }
    else if(number > curr_node -> number){
      if(curr_node -> greater_than == nullptr){
          cout << "Node not found!" << endl;
      }
      else{
      fetch(curr_node -> greater_than, number);
      }
    }
    
}

void rainbow(Node * curr_node , int number){
  if(curr_node -> number == number){
   cout << curr_node -> color << endl;
  }
  else if(number < curr_node -> number){
    if(curr_node -> less_than != nullptr){
    cout << curr_node -> color << "->";
    fetch(curr_node -> less_than , number);
    }
  }
  else if(number > curr_node -> number){
    if(curr_node -> greater_than != nullptr){
    cout << curr_node -> color << "->";
    fetch(curr_node -> greater_than, number);
    }
  }
  
}

void reverse(Node * curr_node , int number){
  if(curr_node -> number == number){
   cout << curr_node -> color;
  }
  else if(number < curr_node -> number){
    if(curr_node -> less_than != nullptr){
    fetch(curr_node -> less_than , number);
    cout << "->" << curr_node -> color;
    }
  }
  else if(number > curr_node -> number){
    if(curr_node -> greater_than != nullptr){
    fetch(curr_node -> greater_than, number);
    ocout << "->" << curr_node -> color;
    }
  }
}