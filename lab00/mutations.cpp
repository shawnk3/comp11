#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
  
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

int main(int argc, char *  argv[]){
  if (argc < 2) {
   cerr << "ERROR: No filename provided as an argument" << endl;
   exit(EXIT_FAILURE);
 }
 
 //read in gene data from file.
 int num_genes; 
 Gene *genes = read_file(argv[1] ,&num_genes);
 
 // Perform the main loop of requesting and executing queries
 string query;
 cout << "Enter a query: ";

 while (cin >> query) { 
     cin.ignore();

     if (query == PRINT) {
        
         /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *             (execute the "print" query)
         * prints every mutation in this format
         *  == [Gene] ==
              Mutations:
              [Mutated Gene] - Cost: [Cost]
              [Mutated Gene] - Cost: [Cost]

         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
         cout << num_genes << endl;
         for (int i = 0 ; i < num_genes ; i++){
           cout<< " == " << genes[i].name  << "=="<<endl;
           
           cout << "Mutations:"<<endl;
           cout << genes[i].length << endl;
        
           int j = 0;
           /*
           while ( j < genes[i].length) {
               cout<< genes[i].mutations[j].name << "- Cost:" <<  
              genes[i].mutations[j].energy <<endl; 
              j++;
           } 
           */

           
         }
         
         
     } else if (query == MUTS_POSSIBLE) {
         string target, source;
         cout << "Source Gene: ";
         getline(cin, source);
         cout << "Target Gene: ";
         getline(cin, target);
         /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *            (execute the "mutations possible" query)
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
     } else if (query == MUTS_ENERGY) {
       string target, source, energy;
       cout << "Source Gene: ";
       getline(cin, source);
       cout << "Target Gene: ";
       getline(cin, target);
       cout << "Energy:";
       getline(cin, energy);
         /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *            (execute the  mutation with energy query)
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
     }else if (query == QUIT) {
         return 0;
     } else {
         cout << query << " not recognized." << endl;
     }
     cout << endl << "Enter a query: ";
 }
 delete [] genes;
 
}

Gene *find_gene (Gene *genes, int num_genes , string gene_name){
  for( int i = 0; i < num_genes ; i++){
    if(genes[i].name == gene_name){
        return &genes[i];
    }
  }
  return nullptr;
}

Gene * read_file (string filename, int * num_genes){
  ifstream infile(filename.c_str());
  if(infile.fail()){
    cerr << "ERROR: The file " << filename << " failed to open correctly." << endl;
    exit(EXIT_FAILURE);
  }
  
  infile >> *num_genes;
  
  if (infile.fail()) {
  cerr << "ERROR: Reading the number of monsters failed." << endl;
  exit(EXIT_FAILURE);
  }
  infile.close();
  
  Gene *new_genes = new Gene[*num_genes];
  initialize(new_genes, *num_genes , filename);
  
  return new_genes;
  
}


void initialize(Gene * genes, int num_genes, string filename){
  string gene, mutation, energy , line_info;
  
  ifstream infile(filename);
  getline(infile, line_info);
  
  istringstream line_stream;
  //first pass, set the name of every gene.
  for(int i = 0; i < num_genes ; i++){
    getline(infile, line_info);
    line_stream.str(line_info);
    line_stream >> gene;
    genes[i].name = gene;
    //cout<<"gemes[i]:"<< genes[i].name <<endl;
    line_stream.clear(); 
  }
  infile.close();
  infile.open(filename);
  getline(infile,line_info);
  
  //seconds pass: initialize mutations.
  int index;
  for(int i = 0; i < num_genes ; i++){
    getline(infile, line_info);
    line_stream.str(line_info); 
    line_stream >> gene; // read past the name of gene
    
    line_stream >> mutation >> energy;
    index = 0;
    while(!line_stream.fail()){
      //add mutation to current Gene array;
      Gene * check_gene = find_gene(genes, num_genes, gene);
      genes[i].mutations[index].name = mutation; 
      //cout << genes[i].mutations[index].name << endl;
      genes[i].mutations[index].energy = energy;
      //cout << genes[i].mutations[index].energy << endl;
      genes[i].mutations[index].gene = check_gene;
      //cout << genes[i].mutations[index].gene -> name <<endl;
      //try and read in next iteration
      line_stream >> mutation >> energy;
      index++;
    }
    genes[i].length = index;
    line_stream.clear();
  }
  infile.close();

}