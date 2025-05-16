// Transaction.h
#pragma once
#include <string>
using namespace std;



class Transaction {
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void transfer(string receiver, double amount) = 0;
};