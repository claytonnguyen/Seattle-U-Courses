//
// Created by Clayton Nguyen on 1/11/22.
//
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
    if (argc > 2) {
        ifstream myfile;
        string line;
        for (int i = 2; i < argc; i++) {
            myfile.open(argv[i]);
            if (myfile.is_open()) {
                while (getline(myfile, line)) {
                    if (line.find((string) argv[1]) != string::npos) {
                        cout << line << '\n';
                    }
                }
                myfile.close();
            } else {
                cout << "wgrep: cannot open file" << endl;
                return 1;
            }
        }
        myfile.close();
    } else if (argc > 1){
        string line;
        while(getline(cin, line)){
            if (line.find((string) argv[1]) != string::npos) {
                    cout << line << '\n';
            }
        }
    } else {
        cout << "wgrep: searchterm [file ...]" << endl;
        return 1;
    }
    return 0;
}