//
// Created by Clayton Nguyen on 1/11/22.
//
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

int main(int argc, char *argv[]){
    if (argc < 2) {
        cout << "wcat: file [file ...]" << endl;
        return 1;
    } else {
        ifstream myfile;
        string line;
        for (int i = 1; i < argc; i++) {
            myfile.open(argv[i]);
            if (myfile.is_open()) {
                while (getline(myfile, line)) {
                    cout << line << endl;
                }
                myfile.close();
            } else {
                printf("%s \n", "wcat: cannot open file");
                return 1;
            }
        }
    }
    return 0;
}