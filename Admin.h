// admin.h
#pragma once
#include "ATM.h"
#include <string>
#include <limits>
using namespace std;

class Admin : public ATM
{
private:

    bool cardNumberExists(int cardNumber);
    bool adminIDExists(int adminID);

public:
    Admin();    // defualt constructor
    // string& is passing by reference instead of value as it insures the function doesn't accidentally change the original string.

    static bool verifyPasswords(const std::string& adminID, const std::string& password);
    bool adminLogin(const std::string& id, const std::string& pass) override;
    bool customerLogin(int, const std::string&) override;

    void showmainmenu() override;


    bool addUser();
    bool deleteUser(int cardNumber);
    bool addAdmin();
    bool deleteAdmin(int adminID);
    void viewUserBalance(int cardNumber);

};