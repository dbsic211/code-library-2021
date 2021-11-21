#include "bits/stdc++.h"
using namespace std;
/*
Source: https://ali-ibrahim137.github.io/competitive/programming/2020/08/23/Stress-Testing.html

IMPORTANT: Input in readAns() should be done using fin
*/

//You may want to declare some global variables (e.g. input file) here.


int readAns(ifstream &fin){
    //Determine correctness of answer from stream fin.
}
int main(int argc, char *argv[]){
    ifstream inf("input_file", ifstream::in);
    ifstream ouf("myAnswer", ifstream::in);
    ifstream ans("correctAnswer", ifstream::in);
    //This section takes input from gen.cpp
    
    
    int myAnswer = readAns(ouf);
    int correctAnswer = readAns(ans);
    //Return -1 for every incorrect output. Return 0 for every correct output.
    //State the possible error encountered.
    //You must return something.
}
