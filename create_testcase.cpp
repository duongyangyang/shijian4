#include <cstdlib> 
#include <iostream> 
#include <time.h> 
#include <fstream>
#include <vector>
using namespace std; 


int main() 
{ 
    ofstream fileOutput("output.txt", ios::trunc);
    if (fileOutput.fail()){ 
        ofstream {"output.txt"}; 
    }

    int n; int x; int y;
    cin >> n; //棋盘上的棋子的个数
    fileOutput << n << endl;
    cin >> x >> y; //Prices
    fileOutput << x << " " << y << endl;
    int p; cin >> p; //指令的个数
    fileOutput << p << endl;

    srand(time(0)); 
    for (int i = 0; i < p ; i++){
        fileOutput << rand()%(2*n) << " "; 
        int r = rand()%2;
        if(r==1){fileOutput << "L" << endl;}
        else{fileOutput << "R" << endl;}
    }
 
    return 0; 
}