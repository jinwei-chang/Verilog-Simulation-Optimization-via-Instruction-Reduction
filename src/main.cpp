#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void parser(ifstream &in, ofstream &out){
    string line;
    while(getline(in, line)){
        stringstream ss(line);
        string kw;

        ss >> kw;
        if(kw.substr(0, 6) == "output"){

        }
        else if(kw.substr(0, 5) == "input"){

        }
        else if(kw == "wire"){
            
        }
        else if(kw == "assign"){
            
        }
        else{
            out << line << endl;
        }
    }
}

int main(int argc, char **argv){
    //* input original file
    ifstream fori(argv[1]);
    //* output optimized file
    ofstream fopt(argv[2]);

    parser(fori, fopt);

    return 0;
}