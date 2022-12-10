//
// Created by Clayton Nguyen on 1/11/22.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
    if(argc > 1) {
        for(int i = 1; i < argc; i++) {
            ifstream file;
            string line;
            file.open(argv[i]);

            if (file.is_open()) {
                char newline = '\n';
                char space = ' ';
                int one = 1;
                while (getline(file, line)) {
                    int set = 0;
                    istringstream ss(line);
                    string word;
                    while (ss >> word) {
                        if (set != 0) {
                            cout.write((char *) &one, sizeof(int));
                            cout.write((char *) &space, sizeof(char));
                        }
                        char prev = word[0];
                        int count = 0;
                        for (int i = 0; i < word.length() + 1; i++) {
                            if (word[i] != prev) {
                                if (i == word.length()) {
                                    cout.write((char *) &count, sizeof(int));
                                    cout.write((char *) &prev, sizeof(char));
                                } else {
                                    cout.write((char *) &count, sizeof(int));
                                    cout.write((char *) &prev, sizeof(char));
                                    prev = word[i];
                                    count = 1;
                                }
                            } else {
                                count++;
                            }
                        }
                        set++;
                    }
                    cout.write((char *) &one, sizeof(int));
                    cout.write((char *) &newline, sizeof(char));
                }
                file.close();
            } else {
                cout << "wzip: cannot open file" << endl;
                return 1;
            }
        }
    } else {
        cout << "wzip: file1 [file2 ...] > file.z" << endl;
        return 1;
    }
    return 0;
}