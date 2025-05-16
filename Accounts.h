// Accounts.h / Base class
#pragma once
#include <string>
#include <vector>
using namespace std;

class Accounts
{
protected:  /// to inherit them in the other classes
    string cardNumber;
    vector<string> transactions;

public:
    virtual void viewBalance() = 0;  // pure vertual // called in all derived classes
    virtual void changePin() = 0;
    virtual void showMenu() = 0;
};