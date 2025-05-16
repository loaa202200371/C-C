#include <iostream>
#include "AccountManager.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

bool AccountManager::verifyinfo(int userID, const string& PIN) {
    ifstream file("data.txt");
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> tokens;
            stringstream ss(line);
            string token;
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }
            if (tokens.size() >= 2) {
                try {
                    int storedID = stoi(tokens[0]);
                    string storedPIN = tokens[1];

                    if (storedID == userID && storedPIN == PIN) {
                        file.close();
                        return true;
                    }
                }
                catch (...) {
                    continue;
                }
            }
        }
        file.close();
    }
    else {
        cerr << "error >> can't open data.txt" << endl;
    }
    return false;
}