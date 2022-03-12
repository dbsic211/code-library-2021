#include"bits/stdc++.h"
using namespace std;
#define int long long
vector<string> readAns(ifstream &fin) {
    vector<string> res;
    for(int i=0; i<1; i++) {
        string x;
        fin >> x;
        res.push_back(x);
    }
    return res;
}

int32_t main(int32_t argc, char * argv[]){
    ifstream inf("input_file", ifstream::in);
    ifstream ouf("myAnswer", ifstream::in);
    ifstream ans("correctAnswer", ifstream::in);
    //Take input from stream inf. 
    vector<string> myAnswer = readAns(ouf);
    vector<string> correctAnswer = readAns(ans);
    if(myAnswer != correctAnswer) {
        return -1;
    }
    return 0;
}
