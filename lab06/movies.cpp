#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Hard coded queries that the user can execute
struct Actor;

struct Movie{
  string title;
  string year;
  int gross;
  string director;
  Actor *actors[5];
};

struct Actor{
  string actor;
  int num_movies;
  int num_actors;
  Movie * movies[100];
};

Movie * read_file(string filename, int *num_movies, Actor * actors);
void populate_movies(Movie *movies, int num_movies , string filename , Actor * actors);
Movie *find_movie(Movie *movies, int size, string name);
Movie *find_movies(Movie *movies, int size, string name);
Actor *find_actor(Actor *actors , int size, string name);

const string PRINT_MOVIE = "p";
const string ADD_GROSS = "a";
const string FILMOGRAPHY = "f";
const string STAR_POWER = "s";
const string QUIT = "q";


int main(int argc, char *argv[]){
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }

    // * * * * * * * * * * * YOUR CODE * * * * * * * * * * * * *
     //* (read in movieinfo.data and store it in your data structure)
     int num_movies = 0;
     Actor * all_actors = new Actor[2250];
     Movie * all_movies = read_file (argv[1], &num_movies , all_actors);
    // * * * * * * * * * * * * YOUR CODE * * * * * * * * * * * * 
  

    // Perform the main loop of requesting and executing queries
    string query;
    cout << "Enter a query: ";
    
    // For reference on why this loop condition works, check out:
    // https://stackoverflow.com/questions/6791520/if-cin-x-why-can-you-use-that-condition
    while (cin >> query) { 
        cin.ignore();

        if (query == PRINT_MOVIE) {
            string movie_name;
            cout << "Movie Name: ";
            getline(cin, movie_name);

            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *             (execute the "print movie" query)   *
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
            if(find_movies(all_movies,num_movies,movie_name)!=nullptr){
              Movie * movie  = find_movies(all_movies,num_movies,movie_name);
              cout<<"Title:" << movie -> title<<endl;
              cout<< "Year:" << movie -> year << endl;
              cout<< "Gross:" << movie -> gross << endl;
             cout << "Director:" << movie -> director << endl;
              cout<<"Actors:" << endl;
              for( int j = 0 ; j < 5; j++){
                   cout<< movie -> actors[j] -> actor <<endl;
              }     
            }
        } else if (query == ADD_GROSS) {
            string movie_name;
            int dollars;
            cout << "Movie Name: ";
            getline(cin, movie_name);
            cout << "Dollar amount to add: ";
            cin >> dollars;

            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *            (execute the "add to gross" query)
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        } else if (query == FILMOGRAPHY) {
            string actor_name;
            cout << "Actor Name: ";
            getline(cin, actor_name);

            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *            (execute the "filography" query)
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
            for(int i = 0; i < 2250; i++){
              if(all_actors[i].actor == actor_name){
                cout << "Movies: " << endl;
                for(int k = 0; k < all_actors[i].num_movies; k++){
                  cout << all_actors[i].movies[k] -> title << endl;
                } 
              }
            }
            
        } else if (query == STAR_POWER) {
            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *            (execute the "star power" query)
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        }else if (query == QUIT) {
          delete []all_actors;
          delete []all_movies;
            return 0;
        } else {
            cout << query << " not recognized." << endl;
        }
        cout << endl << "Enter a query: ";
    }

    return 0;
}

Movie * read_file(string filename, int *num_movies, Actor * actors){
  
    ifstream infile(filename.c_str());
    if(infile.fail()){
      cerr << "ERROR: the file" << filename 
      << "failed to open correctly." << endl;
      exit(EXIT_FAILURE);
    }
    infile >> *num_movies;
    if(infile.fail()){
        cerr << "ERROR: Reading the number of monsters failed." << endl;
        exit(EXIT_FAILURE);
    }
    infile.close();
    Movie *all_movies = new Movie[*num_movies];
    populate_movies(all_movies, *num_movies, filename , actors);
    return all_movies;
}


void populate_movies(Movie *movies, int num_movies, string filename,Actor * all_actors){ 
  string line_info;
  
  ifstream infile(filename.c_str());
  if(infile.fail()){
    cerr << "ERROR: the file " << filename 
    << "failed to open correctly." << endl;
    exit(EXIT_FAILURE);
  }

  getline(infile, line_info);
  string director;
  int k = 0; int l = 0;
  for (int i = 0; i < num_movies;  i++){
    getline(infile, line_info);
    movies[i].title = line_info;
    getline(infile, line_info);
    movies[i].year = line_info;
    getline(infile, line_info);
    movies[i].gross = stoi(line_info);
    getline(infile, line_info);
    movies[i].director = line_info;
    director = movies[i].director;
    cout << "l:" << l << endl;
    for( int j = 0; j < 5; j ++){
        getline(infile, line_info);
        // /cout << line_info << endl;
        if(find_actor(all_actors,2250,line_info) == nullptr){
          all_actors[k].actor = line_info;
          //cout <<"1:"<< all_actors[k].actor << "," << all_actors[k].movies[l] -> title;
        }
        else{
            Actor *temp = find_actor(all_actors,2250,line_info);
            all_actors[k] = *temp;
        }
        if(find_movie(movies,num_movies,director)!= nullptr){
        if(find_actor(all_actors,2250,line_info) != nullptr){
          movies[i].actors[j] = &all_actors[k];
          all_actors[k].movies[l] = &movies[i];
        
          cout <<"1:"<< all_actors[k].actor << "," << all_actors[k].movies[l] -> title << endl;
        }
       }
       k++;
    }
    l++;
  }
  all_actors -> num_actors = k;
  all_actors -> num_movies = l;
  infile.close();
}

Movie *find_movie(Movie *movies, int size, string name) {
    //YOUR CODE GOES HERE
    for(int i = 0; i < size; i++){
      if(movies[i].director == name){
          return (movies + i);
      }
    }
    return nullptr;
}

Movie *find_movies(Movie *movies, int size, string name) {
    //YOUR CODE GOES HERE
    for(int i = 0; i < size; i++){
      if(movies[i].title == name){
          return (movies + i);
      }
    }
    return nullptr;
}


Actor *find_actor(Actor *actors , int size, string name){
  for(int i = 0; i < size; i++){
    if(actors[i].actor == name){
        return (actors + i);
    }
  }
  return nullptr;
}


