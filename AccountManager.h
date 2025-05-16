#pragma once
#include <string>
using namespace std;
class AccountManager {
public:
    static bool verifyinfo(int userID, const string& PIN);
};