
#include <iostream>
#include "CheckingAccount.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

CheckingAccount::CheckingAccount(string cn) {
    cardNumber = cn;
    // cout << endl << "Checking Account Activated" << endl;

}

void CheckingAccount::showMenu() {
    int choice;
    do {
        cout << endl << "///////////////CHECKING ACCOUNT MENU////////////////////" << endl;
        cout << "1. View Balance" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Transfer" << endl;
        cout << "5. Change PIN" << endl;
        cout << "0.Exit" << endl;
        cout << "Choice: ";
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
        {
            double amount;
            cout << "Enter withdrawal amount: $";
            cin >> amount;
            withdraw(amount);
            break;
        }
        case 4:
        {
            string receiver;
            double amount;
            cout << "Enter receivers card number: ";
            cin >> receiver;
            cout << "Enter transfer amount: $";
            cin >> amount;
            transfer(receiver, amount);
            break;
        }
        case 5:
            changePin();
            break;
        case 0:
            cout << "/////////////Returned to main menu//////////////////" << endl;
            break;
        default:
            cout << "Invalid choice, enter 1,2,3,4,5, or select 0 to exit" << endl;
        }
    } while (choice != 0);
}

void CheckingAccount::deposit(double amount) {
    vector<string> lines;
    ifstream in("data.txt");
    string line;
    bool found = false;

    while (getline(in, line)) {
        stringstream Lseg(line);
        string currentCard;
        getline(Lseg, currentCard, ',');

        if (currentCard == cardNumber) {

            found = true;
            string pin, checking, saving;
            getline(Lseg, pin, ',');

            getline(Lseg, checking, ',');
            getline(Lseg, saving);
            double newChecking = stod(checking) + amount;
            ostringstream obl;
            obl << fixed << setprecision(2) << newChecking;

            line = currentCard + "," + pin + "," + obl.str() + "," + saving;
        }
        lines.push_back(line);
    }
    in.close();

    if (!found) {
        cout << "Account not found" << endl;
        return;
    }

    ofstream out("data.txt");
    for (auto& l : lines) {
        out << l << endl;

    }
    out.close();

    cout << "Successfully deposited $" << fixed << setprecision(2) << amount << endl;
}

void CheckingAccount::withdraw(double amount) {
    vector<string> lines;
    ifstream in("data.txt");
    string line;
    bool found = false;
    bool insufficient = false;

    while (getline(in, line)) {
        stringstream Lseg(line);
        string currentCard;
        getline(Lseg, currentCard, ',');

        if (currentCard == cardNumber) {
            found = true;
            string pin, checking, saving;
            getline(Lseg, pin, ',');
            getline(Lseg, checking, ',');
            getline(Lseg, saving);

            double current = stod(checking);
            if (current < amount) {
                insufficient = true;
                break;
            }

            ostringstream obl;
            obl << fixed << setprecision(2) << (current - amount);
            line = currentCard + "," + pin + "," + obl.str() + "," + saving;
        }
        lines.push_back(line);
    }
    in.close();

    if (!found) {
        cout << "Account not found" << endl;
        return;
    }
    if (insufficient) {
        cout << "Insufficient amount" << endl;
        return;
    }

    ofstream out("data.txt");
    for (auto& l : lines) out << l << endl;
    out.close();

    cout << "Successfully withdrew $" << fixed << setprecision(2) << amount << endl;
}

void CheckingAccount::transfer(string receiver, double amount) {
    ifstream in("data.txt");
    string line;
    bool senderFound = false;
    bool receiverFound = false;
    bool sufficient = false;

    while (getline(in, line)) {
        stringstream Lseg(line);
        string currentCard;
        getline(Lseg, currentCard, ',');

        if (currentCard == cardNumber) {
            senderFound = true;
            string pin, checking, saving;
            getline(Lseg, pin, ',');
            getline(Lseg, checking, ',');
            getline(Lseg, saving);

            if (stod(checking) >= amount) sufficient = true;
        }
        else if (currentCard == receiver) {
            receiverFound = true;
        }
    }
    in.close();

    if (!senderFound) {
        cout << "Invalid sender cardnumber was added please check the details again" << endl;
        return;
    }
    if (!receiverFound) {
        cout << "Invalid reciver cardnumber was added please check the details again" << endl;
        return;
    }
    if (!sufficient) {
        cout << "your funds for transfer have exceeded the ammount in your account" << endl;
        return;
    }

    vector<string> lines;
    in.open("data.txt");
    while (getline(in, line)) {
        stringstream Lseg(line);
        string currentCard;
        getline(Lseg, currentCard, ',');

        if (currentCard == cardNumber) {
            string pin, checking, saving;
            getline(Lseg, pin, ',');
            getline(Lseg, checking, ',');
            getline(Lseg, saving);

            double newChecking = stod(checking) - amount;
            ostringstream obl;
            obl << fixed << setprecision(2) << newChecking;
            line = currentCard + "," + pin + "," + obl.str() + "," + saving;
        }
        else if (currentCard == receiver) {
            string pin, checking, saving;
            getline(Lseg, pin, ',');
            getline(Lseg, checking, ',');
            getline(Lseg, saving);

            double newChecking = stod(checking) + amount;
            ostringstream oss;
            oss << fixed << setprecision(2) << newChecking;
            line = currentCard + "," + pin + "," + oss.str() + "," + saving;
        }
        lines.push_back(line);
    }
    in.close();

    ofstream out("data.txt");
    for (auto& l : lines)
        out << l << endl;
    out.close();

    cout << "Successfully transferred $" << fixed << setprecision(2) << amount << endl;
}

void CheckingAccount::viewBalance() {
    ifstream file("data.txt");
    string line;
    while (getline(file, line)) {
        stringstream Lseg(line);
        string currentCard, pin, checking, saving;

        getline(Lseg, currentCard, ',');
        getline(Lseg, pin, ',');
        getline(Lseg, checking, ',');
        getline(Lseg, saving);

        if (currentCard == cardNumber) {
            cout << "\nAccount Balances:" << endl
                << "Checking account balance: $" << checking << endl
                << "Savings account balance: $" << saving << endl;
            break;
        }
    }
    file.close();
}

void CheckingAccount::changePin() {
    vector<string> lines;
    ifstream in("data.txt");
    string line;
    bool found = false;

    string newPin;
    cout << "enter new PIN (4 digits): ";
    cin >> newPin;

    while (getline(in, line)) {
        stringstream Lseg(line);
        string currentCard;
        getline(Lseg, currentCard, ',');

        if (currentCard == cardNumber) {
            found = true;
            string oldPin, checking, saving;
            getline(Lseg, oldPin, ',');
            getline(Lseg, checking, ',');
            getline(Lseg, saving);

            line = currentCard + "," + newPin + "," + checking + "," + saving;
        }
        lines.push_back(line);
    }
    in.close();

    if (!found) {
        cout << "/////////Account not found///////////////////" << endl;
        return;
    }

    ofstream out("data.txt");
    for (auto& l : lines)
        out << l << endl;
    out.close();

    cout << "/////////////////PIN changed successfully///////////////////" << endl;
}