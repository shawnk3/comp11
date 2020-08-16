// advising.cpp
// Purpose: Query advising bureaucracy
// Written by: Shawn Kuriakose (skuria01)

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    string name;
    Node *supervisee_1;
    Node *supervisee_2;
    int advisee_count;
};

const string PRINT = "p";
const string ADD_A = "a";
const string ADD_F = "f";
const string TOTAL = "t";
const string SLACKER = "s";
const string QUIT = "q";

Node *new_node(string name);
Node *read_file(string filename);
void print_advisees(Node *curr_node, string bureaucracy);
Node *find_node(Node *curr_node, string name);
void total_advisees(Node * curr_node , int * count); 
void slackers(Node * curr_node);
void deletes(Node *curr_node);


//STYLE NOTE: You do not have to worry about making main() fit in 30 lines for
//this assignment. 
int main(int argc, char *argv[]){
    //Prompt the user for the data file name
    string filename;
    cout << "Enter data file name: ";
    cin >> filename;
	  Node *boss = read_file(filename);

    //Loop to continually prompt for queries
    string c;
    cout << "Enter a query: ";
    while (cin >> c) {
        if (c == PRINT) {
            print_advisees(boss, "");
        } else if (c == TOTAL) {
           //declare variables
           string name;
           //read in string from input
           cin >> name;  
           //call find node to see if there is node with user inputed name
           Node *curr_node = find_node(boss,name);
           //if you found the node with the user input name
           if(curr_node != nullptr){
             int total = 0; 
             // pass in address for integer total and call total_advisees
             total_advisees(curr_node, &total);
             //function changes the value of total 
             cout << name << " is responsible for " << total 
             << " advisee(s)."<<endl;
           }
           //if you didn't find the node
           else{
             cout << name << " doesn't work here!" << endl;
           }
  
        } else if (c == SLACKER) {
          //call slackers func
          slackers(boss);
        } else if (c == QUIT) {
            //call deletes function
            deletes(boss);
            //to end program
            return 0;
            
        } else if (c == ADD_A) {
            
            ///// (OPTIONAL) YOUR CODE GOES HERE ///// 
            
        } else if (c == ADD_F) {

            ///// (OPTIONAL) YOUR CODE GOES HERE /////
            
        } else {
            cout << c << " not recognized." << endl;
        }
        cout << endl << "Enter a query: ";
    }
} 



//Print the tree path of every person who has advisees
void print_advisees(Node *curr_node, string bureaucracy){
    //Base Case: If we are at a person who has advisees, print the count
    if(curr_node->advisee_count > 0){
        cout << bureaucracy;
        cout << curr_node->name + "->";
        cout << curr_node->advisee_count << endl;
    //Recursive Cases: If we are at a person who doesn't have advisees, recurse to their subtrees
    }else{
        if(curr_node->supervisee_1 != nullptr){
            string bureaucracy_left = bureaucracy + curr_node->name + "->";
            print_advisees(curr_node->supervisee_1, bureaucracy_left);
        }

        if(curr_node->supervisee_2 != nullptr){
            string bureaucracy_right = bureaucracy + curr_node->name + "->";
            print_advisees(curr_node->supervisee_2, bureaucracy_right);
        }
    }
}

//Read file and build tree structure, returning root "boss" node.
//STYLE NOTE: You do not have to worry about paring down read_file() to a
//30-line limit for this assignment.
Node *read_file(string filename){
    //Open the given file
    ifstream infile(filename.c_str());
    if (infile.fail()) {
        cerr << "ERROR: Error opening file, please check file name: " 
             << filename << endl;
        exit(EXIT_FAILURE);
    }

    //Read the first line of the file
    string supervisor;
    string supervisee;

    infile >> supervisor;
    infile >> supervisee;
    Node *boss = new_node(supervisor);
    bool first_line = true;
    
    //Process each line of the file
    while(!infile.eof()){
        Node *supervisor_node;

        //Initialize the root node if we're on the first line of the file
        if(first_line){
            supervisor_node = boss;
            first_line = false;
        }else{
            supervisor_node = find_node(boss, supervisor);
        }

        //Check if we're dealing with an advisor or a supervisor
        if(supervisee == "Advisee"){
            supervisor_node->advisee_count++;
        }else{
            //Determine if the supervisee should be the first or second supervisee
            if(supervisor > supervisee){
                supervisor_node->supervisee_1 = new_node(supervisee);
            }else{
                supervisor_node->supervisee_2 = new_node(supervisee);
            }
        }

        //Read the next line
        infile >> supervisor;
        infile >> supervisee;
    }

    return boss;
}

//Finds and returns the node with the given name
Node *find_node(Node *curr_node, string name){
    //Base Case: If curr_node is the person we're looking for, return it 
    if(curr_node->name == name){
        return curr_node;
    //Recursive Cases: Search either the left or right subtree for the name
    }else if(curr_node->name > name){
        if(curr_node->supervisee_1 == nullptr) return nullptr;
        return find_node(curr_node->supervisee_1, name);
    }else{
        if(curr_node->supervisee_2 == nullptr) return nullptr;
        return find_node(curr_node->supervisee_2, name);
    }

    return nullptr;
}

//Returns a new node that is blank except for the provided name
Node *new_node(string name){
    Node *new_node = new Node;

    new_node->name = name;
    new_node->supervisee_1 = nullptr;
    new_node->supervisee_2 = nullptr;
    new_node->advisee_count = 0;

    return new_node;
}

/* total_advisees
 * Arguments: one pointer to Node struct and pointer to integer
 * Description: counts the total advisee count, both direct 
 * and indirect for a specific advisor. The node for supervisor
 * is passed in, and the advisee count is added to the integer 
 * pointer count. 
 * Return value: no return value
 */
void total_advisees(Node * curr_node , int * count){
  //Base case: if the node with advisee count is 
  // found, the advisee count is added to count pointer.
  if(curr_node -> advisee_count > 0){
     *count += curr_node ->advisee_count;
  }
  //Recursive: else count pointer is passed again either 
  //through the left or right side of the binary tree 
  //if there exists supervisees for the node.
   else{
      if(curr_node->supervisee_1 != nullptr){
        //pass through the left side of tree
          total_advisees(curr_node-> supervisee_1 , count);
      } 
      //pass through right side of tree
     if(curr_node->supervisee_2 != nullptr){
          total_advisees(curr_node-> supervisee_2 , count);
     }
   }
}

/* slackers
 * Arguments: one pointer to Node struct
 * Description: Prints out which of the nodes has two leafs
 * (no supervisees) and has an advisee count of zero.
 * Return value: no return value
 */
void slackers(Node * curr_node){
  //initialize variables to do case checks
  Node *case1 = curr_node -> supervisee_1;
  Node * case2 = curr_node -> supervisee_2;
  int count = curr_node -> advisee_count;
  //Base case: if there are no supervisees and advisees for a node
  // then the node is a slacker, and name of node should be printed out
  if(case1 == nullptr && case2 == nullptr && count == 0){
    cout << "Slacker: " << curr_node -> name << endl;
  }
  //Recursive case: the slackers function should be
  //called again by going through either the left side 
  // or right side of binary tree to find slackers
  else{
    if(case1 != nullptr){
      //check left side for slackers
       slackers(case1);
    } 
   if(case2 != nullptr){
     //check right side for slackers
       slackers(case2);
   }
  }
}
/* deletes
 * Arguments: one pointer to Node struct
 * Description: Delete all the memory in the heap
 * by going through the binary tree and deleting every node.
* Return value: no return value
 */
void deletes(Node *curr_node){
  //initalize variables to do case checks
  Node *case1 = curr_node -> supervisee_1;
  Node * case2 = curr_node -> supervisee_2;
  // Base Case:
  //if the node is a leaf,  then the node should be immediately deleted.
  if(case1 == nullptr && case2 == nullptr ){
    delete curr_node;
  }
  //Recursive Case: 
  // Since node is not a leaf, then we need to go through the tree
  // through both sides until we've deleted all the nodes
  else{
    if(case1 != nullptr){
      //go through left side of tree
      deletes(case1);
    } 
    if(case2 != nullptr){
      //go through right side of binary tree
      deletes(case2);
    }
    //delete the head node and then all memory is cleared.
    delete curr_node;
  }
}
