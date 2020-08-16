#include <iostream>
#include <fstream>

using namespace std;

int add (int a, int b);
int sub(int a, int b);
int multiply(int a, int b);
int rem (int a, int b);


int main(){
    // Part I: Functions
    //int result_1 = 5 * 6 - 10 % 4 * 3 + 2 - 10 + 9 % 5 + 5; 
    int a = multiply(5,6);

    int b = rem(10,4);

    int c = multiply(b,3);
  
    int d = rem(9,5);

    int e = add(d,5);

    int f = add(e,2);

    int g = add(a,f);
  
    int h = add(c,10);

    int result_1 = sub(g,h);
     
    cout << result_1 << endl;
    
    //int result_2 = ((2 + 5) * 6 - 10 % 4) * (3 + (6 - 4)) + 9 % 5 - 15;
    int i = add(2,5);
    int j = multiply(i,6);
    int k = rem(10,4);
    int l = sub(j,k);
    int m = sub(6,4);
    int n = add(3,m);
    int o = l *n;
    int p = rem(9,5);
    int q = o + p;
    int result_2 = sub(q,15);
    cout << result_2 << endl;



    // Part II: Pointers
    int trix[4][6]; 
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 6; j++){
            trix[i][j] = (i * 6) + j;
        }
    }

    int *x = &trix[1][1];
    int **y = &x;
    int ***z = &y;

    // DO NOT UNCOMMENT THESE UNTIL YOU HAVE COMPUTED THE ANSWER ON PAPER
    //cout << trix[3][5] << endl;
    //cout << *(x + 2) << endl;
    //cout << x[6] << endl;
    //cout << *((*y) - 1) << endl;
    //cout << (*(*z))[1] << endl;
    //cout << *((*(&x)) + 12) << endl;
    //cout << z << endl;

    return 0;
}

int add (int a, int b){
  return a+b;
}
int sub(int a, int b){
  return a - b;
}

int multiply(int a, int b){
  return a*b;
}

int rem (int a, int b){
  return a % b;
}





