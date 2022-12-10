//
// Created by Clayton Nguyen on 1/11/22.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("%s\n", "wunzip: file1 [file2 ...]");
        return 1;
    } else {
        for(int i = 1; i < argc; i++) {
            ifstream file(argv[i]);
            if (file.is_open()) {
                int count = 0;
                char letter;
                while(file.read((char*)&count, sizeof(int))){
                    file.read((char*)&letter, sizeof(char));
                    for (int i = 0; i < count; i++) {
                        cout << letter;
                    }
                }
                file.close();
            } else {
                printf("%s\n", "wunzip: cannot open file");
                return 1;
            }
        }
    }
    return 0;
}