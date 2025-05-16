// SavingsAccount.cpp
#include <iostream>
#include "SavingsAccount.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

SavingsAccount::SavingsAccount(string cn)
{
    cardNumber = cn;
    
}

void SavingsAccount::showMenu()
{
    int choice;
    do {
        cout << "\n//////////// SAVINGS ACCOUNT MENU //////////" << endl
            << "0. Exit" << endl
            << "1. View Balance" << endl
            << "2. Deposit" << endl
            << "3. Change PIN" << endl
            
            << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewBalance();
            break;
        case 2:
        {
            double amount;
            cout << "Enter deposit amount: $";
            cin >> amount;
            deposit(amount);
            break;
        }
        case 3:
            changePin();
            break;
        case 0:
            cout << "Returning to the main menu" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);
}

void SavingsAccount::deposit(double amount)
{
    vector<string> lines;
    ifstream in("data.txt");
    string line;
    bool found = false;

    while (getline(in, line))
    {
        stringstream ss(line);
        string currentCard;
        getline(ss, currentCard, ',');

        if (currentCard == cardNumber)
        {
            found = true;
            string pin, checking, saving;
            getline(ss, pin, ',');
            getline(ss, checking, ',');
            getline(ss, saving);

            double newSaving = stod(saving) + amount;
            ostringstream oss;
            oss << fixed << setprecision(2) << newSaving;

            line = currentCard + "," + pin + "," + checking + "," + oss.str();
        }
        lines.push_back(line);
    }
    in.close();

    if (!found)
    {
        cout << "Account not found" << endl;
        return;
    }

    ofstream out("data.txt");
    for (auto& l : lines) out << l << endl;
    out.close();

    cout << "Successfully deposited $" << fixed << setprecision(2) << amount << endl;
}

void SavingsAccount::viewBalance()
{
    ifstream file("data.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string currentCard, pin, checking, saving;

        getline(ss, currentCard, ',');
        getline(ss, pin, ',');
        getline(ss, checking, ',');
        getline(ss, saving);

        if (currentCard == cardNumber)
        {
            cout << "\nAccount Balances:" << endl
                << "Checking account balance: $" << checking << endl
                << "Savings account balance: $" << saving << endl;
            break;
        }
    }
    file.close();
}

void SavingsAccount::changePin()
{
    vector<string> lines;
    ifstream in("data.txt");
    string line;
    bool found = false;

    string newPin;
    cout << "Enter new PIN (4 digits): ";
    cin >> newPin;

    while (getline(in, line))
    {
        stringstream ss(line);
        string currentCard;
        getline(ss, currentCard, ',');

        if (currentCard == cardNumber)
        {
            found = true;
            string oldPin, checking, saving;
            getline(ss, oldPin, ',');
            getline(ss, checking, ',');
            getline(ss, saving);

            line = currentCard + "," + newPin + "," + checking + "," + saving;
        }
        lines.push_back(line);
    }
    in.close();

    if (!found)
    {
        cout << "Account not found" << endl;
        return;
    }

    ofstream out("data.txt");
    for (auto& l : lines)
        out << l << endl;
    out.close();

    cout << "PIN changed successfully" << endl;
}