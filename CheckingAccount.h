// CheckingAccount.h
#pragma once
#include "Accounts.h"
#include "Transaction.h"

class CheckingAccount : public Accounts, public Transaction
{
public:
    CheckingAccount(string cn);
    void showMenu() override;
    void viewBalance() override;
    void deposit(double amount) override;
    void withdraw(double amount) override;
    void transfer(string receiver, double amount) override;
    void changePin() override;
};