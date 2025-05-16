// atm.h
#pragma once
#include <string>
using namespace std;

class ATM {
protected:
    int failedAttempts = 0;

    void lockthesystem();
    void handleFailedAttempt();
public:
    virtual void showmainmenu() = 0;
    virtual bool adminLogin(const string&, const string&) = 0;
    virtual bool customerLogin(int, const string&) = 0;
    virtual ~ATM() = default;
};