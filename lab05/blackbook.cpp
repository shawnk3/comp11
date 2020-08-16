// black_book.cpp
// Purpose: Lab 5 Starter Code
// Written by: Megan Monroe (mmonroe)

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Contact {
    string name;
    string number;
};

Contact *read_contacts(string filename, int *book_size);
Contact *find_contact(Contact *black_book, int book_size, string name);
void init_contacts(Contact *black_book, int book_size);
void print_contacts(Contact *black_book, int book_size);

int main(int argc, char *argv[]){
    //Make sure I was actually given a filename on the command-line
    if (argc < 2) {
        cerr << "ERROR: Expecting a file name as a command-line argument."; 
        cerr <<endl;
        exit(EXIT_FAILURE);
    }

    //Read in the contacts from the provided file
    int book_size;
    Contact *black_book = read_contacts(argv[1], &book_size);
    print_contacts(black_book, book_size);

    //Ask the user for updates until they no longer have any
    string continue_updating;
    cout << "Would you like to make an update? Enter \"y\" or \"n\": ";
    cin >> continue_updating;

    while (continue_updating == "y") {
        string name, number;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Phone Number: ";
        cin >> number;

        //Find either the existing contact, or the space for a new contact
        Contact *update_contact = find_contact(black_book, book_size, name);

        if (update_contact != nullptr) {
            update_contact->name = name;
            update_contact->number = number;
        } else {
            /*
             * If you finish writing the read_contacts and find_contact
             * functions, remove this comment and fill in this section. 
             * I.e., if you have run out  
             * of room for contacts, then you'll need a bigger array!
             */
        
             Contact *new_book = new Contact[book_size * 2];
             for(int i = 0 ; i < (book_size) ; i++){
               new_book[i] = black_book[i];
             }
             init_contacts((new_book + (book_size)), (book_size));
             
             //update_contact = find_contact(new_book, book_size, name);
             (*(new_book + book_size)).name = name;
             (new_book + book_size)->number =  number;
             
             delete [] black_book;
        
             black_book = new_book;
             
            
        }

        // Print the black book and prompt again
        print_contacts(black_book, book_size);
        cout << "Would you like to make another update? Enter \"y\" or \"n\": ";
        cin >> continue_updating;
    }

    cout << "Thank you. Goodbye!" << endl;
    delete [] black_book;

    return 0;
} 

/*
 * Description: This function reads a file of contact information 
 *              into an array of Contact structs
 * Input: The name of the file to read from, and the address of the
 *        integer that will store the total size of the black book
 * Output: A pointer to the finished array of Contact structs
 */
Contact *read_contacts(string filename, int *book_size) {
 
    //YOUR CODE GOES HERE
    ifstream infile(filename);
    if(infile.fail()){
      cerr<< "ERROR: error opening file, please  check filename."<<endl;
      exit(EXIT_FAILURE);
    }
    infile >> *book_size;
    *book_size *=2;
    Contact* contacts = new Contact[*book_size];
    
    for(int i = 0 ; i < (*book_size)/2; i++){
      infile >> contacts[i].name >> contacts[i].number; 
    }
    
    init_contacts((contacts + *(book_size)/2 ), (*book_size)/2);
    
    infile.close();
    
    return contacts;
}

/*
 * Description: This function finds the contact that needs to be updated. 
 *              If the provided name is already in the black book, it will 
 *              return an existing contact. Otherwise it will return the 
 *              first available blank entry in the black book.
 * Input: The Contact array (aka a pointer to its first element), the total 
 *        size of that array, and the name that will be updated/added
 * Output: A pointer to the Contact that needs to be updated/added or 
 *         nullptr if the black book is full
 */
Contact *find_contact(Contact *black_book, int book_size, string name) {
    
    //YOUR CODE GOES HERE
    for(int i = 0; i < book_size; i++){
      if(black_book[i].name == name){
          return (black_book + i);
      }
    }
    for(int i = 0; i < book_size; i++){
      if(black_book[i].name == ""){
          return (black_book + i);
      }
    }
    return nullptr;
}

//Print out the list of active contacts
void print_contacts(Contact *black_book, int book_size) {
    cout << endl;
    for (int i = 0; i < book_size; i++) {
        if (black_book[i].name == "") {
            break;
        }
        cout << black_book[i].name << ": "
             << black_book[i].number << endl;
    }
    cout << endl;
}

//Initialize the whole book to empty strings
void init_contacts(Contact *black_book, int book_size) {
    for (int i = 0; i < book_size; i++) {
        black_book[i].name = "";
        black_book[i].number = "";
    }
}
