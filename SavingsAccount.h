//SavingsAccount.h (header)
#pragma once
#include "Accounts.h"
#include "Transaction.h"

class SavingsAccount : public Accounts, public Transaction
{
public:
    SavingsAccount(string cn);
    void showMenu() override;
    void viewBalance() override;
    void deposit(double amount) override;
    void withdraw(double amount) override {}
    void transfer(string, double) override {}
    void changePin() override;
};