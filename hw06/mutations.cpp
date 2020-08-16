/*
 * mutations.cpp
 * Purpose: provides ability to use querey to determine 
 * characteristics of a sample of gene data
 * Submitted by: {Shawn Kuriakose skuria01}
 */
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
// Hard coded queries that the user can execute  
const string PRINT = "p";
const string MUTS_POSSIBLE = "m";
const string MUTS_ENERGY = "me";
const string QUIT = "q";

struct Gene;

struct Mutate{
  string name;
  string energy;
  Gene *gene;
};

struct Gene{
  string name;
  int length;
  Mutate mutations[5];
};


Gene *find_gene (Gene *genes, int num_genes , string gene_name);
Gene * read_file (string filename, int *  num_genes);
void initialize(Gene * genes, int num_genes, string filename);

int main(){
 //declare file to read in 
 string file;
 cout << "Enter data file name:";
 cin >> file;

 //read in gene data from file.
 int num_genes; 
 Gene *genes = read_file(file ,&num_genes);
 
 // Perform the main loop of requesting and executing queries
 string query;
 cout << " Enter a query: ";

 while (cin >> query) { 
     cin.ignore();

     if (query == PRINT) {
        
         /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *             (execute the "print" query)
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
       //loop through array of gene structs and print out in 
       // format shown in spec
         for (int i = 0 ; i < num_genes ; i++){
           cout<< "== " << genes[i].name  << " =="<<endl;
           cout << "Mutations:" << endl;
           int j = 0;
           //print none if there are no mutations
           if(genes[i].length == 0){
             cout << "None" << endl;
           }
           //run loop until you exceed the number of max mutations
           while ( j < genes[i].length) {    
               cout<< genes[i].mutations[j].name << " - Cost: " <<  
              genes[i].mutations[j].energy <<endl; 
              j++;
           } 
         }
         
         
     } else if (query == MUTS_POSSIBLE) {
         string target, source;
         //read in source and target from input
         cin >> source >> target;
        
         /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *            (execute the "mutations possible" query)
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
         bool q = false; //initialize boolean to check for match
         //loop and check if you can perform mutation 
         //by checking if any of the source mutations match the target
         for (int i = 0; i < num_genes; i++){
           //only checks mutations if you found source
          if(genes[i].name == source){ 
           int j = 0;
           while( j < genes[i].length){  
             //only print mutation possible if you find target
             if(genes[i].mutations[j].name == target){
               cout << source << " can mutate into "<< target << endl;
               q = true;
             }
             j++;
           }
          }
        }
        //if match never found , then print not found
        if(!q){ 
         cout << source << " cannot mutate into "<< target << endl;
        }
        
     } else if (query == MUTS_ENERGY) {
       string target, source, cost;
       //read in input for variables
       cin >> source >> target >> cost;
         /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *            (execute the  mutation with energy query)
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
       bool q = false;
       // loop through and check if you can find a match
      //by checking if any of the source mutations match the target
       for (int i = 0; i < num_genes; i++){
         //only loop through mutations if you find source
        if(genes[i].name == source){  
         int j = 0;
         while( j < genes[i].length){  
           //only compare energies if you find target 
           if(genes[i].mutations[j].name == target){
             //if match is found see if cost input is >= energy to mutate
             //stoi converts string to integer
              if(stoi(cost) >= stoi(genes[i].mutations[j].energy)){
                cout << source << " can mutate into "<< target <<
                 " with evolutionary cost "<< cost << endl;
              }
              else{
                cout << source << " can mutate into "<< target <<
                 " but not with evolutionary cost "<< cost << endl;
              }
              q = true;
           }
           j++;
         }
        }
       }  
       // print if match was never found
       if(!q){ 
         cout << source << " cannot mutate into "<< target << endl;
       } 
     }else if (query == QUIT) {
       //delete memory
         delete [] genes;
         return 0;
     } else {
         cout << query << " not recognized." << endl;
     }
     cout << endl << "Enter a query: ";
 }
 
 
}
//sees if name matches the name of a struct in array
//returns address to pointer, else nullptr
Gene *find_gene (Gene *genes, int num_genes , string gene_name){
  for( int i = 0; i < num_genes ; i++){
    if(genes[i].name == gene_name){
        return &genes[i];
    }
  }
  return nullptr;
}

//reads file and returns array of Gene structs
Gene * read_file (string filename, int * num_genes){
  //open the file
  ifstream infile(filename.c_str());
 //error check
  if(infile.fail()){
    cerr << "ERROR OPENING FILE: Exiting Program" << endl;
    exit(EXIT_FAILURE);
  }
  //read size of array from first line
  infile >> *num_genes;
  //error reading number of genes
  if (infile.fail()) {
  cerr << "ERROR: Reading the number of genes failed." << endl;
  exit(EXIT_FAILURE);
  }
  //close file so we can use in initialize function
  infile.close();
  //allocate memory and populate memory for genes
  Gene *new_genes = new Gene[*num_genes];
  initialize(new_genes, *num_genes , filename);
  
  return new_genes;  
}

//read genes data from file and populate array of genes
void initialize(Gene * genes, int num_genes, string filename){
  string gene, mutation, energy , line_info;
  
  ifstream infile(filename);
  getline(infile, line_info); //read file for pass one
  
  istringstream line_stream;
  //first pass, set the name of every gene.
  for(int i = 0; i < num_genes ; i++){
    getline(infile, line_info); //read line
    line_stream.str(line_info); // convert to string for line_stream
    line_stream >> gene; // initalize gene to be first data in line_stream
    genes[i].name = gene; //initalize gene to be name of struct
    line_stream.clear(); //clear linestream to get next piece of data
  }
  infile.close();
  infile.open(filename);
  getline(infile,line_info); //read file in again for pass two
  
  //seconds pass: initialize mutations.
  int index; //declare index as iterator
  for(int i = 0; i < num_genes ; i++){
    getline(infile, line_info); // read in line to line info
    line_stream.str(line_info); //convert data to string
    line_stream >> gene; // read past the name of gene
    line_stream >> mutation >> energy; // read it to mutatio and energy vars
    index = 0;
    while(!line_stream.fail()){
      //add mutation to current Gene array;
      Gene * check_gene = find_gene(genes, num_genes, gene);
      // check if you are able to initialize to correct struct
      //initalize mutation, energy, and gene pointer 
      genes[i].mutations[index].name = mutation; 
      genes[i].mutations[index].energy = energy;
      genes[i].mutations[index].gene = check_gene;
      //try and read in next iteration
      line_stream >> mutation >> energy;
      index++;
    }
    genes[i].length = index; // index = number of mutations
    line_stream.clear();
  }
  infile.close();

}