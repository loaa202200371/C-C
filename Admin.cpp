//admin.cpp
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
using namespace std;

Admin::Admin()
{
    srand(static_cast<unsigned>(time(nullptr)));
}

bool Admin::verifyPasswords(const string& adminID, const string& password)
{
    ifstream file("Admin.txt");
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string storedID, storedPass;
        getline(ss, storedID, ',');
        getline(ss, storedPass, ',');

        if (storedID == adminID && storedPass == password)
        {
            return true;
        }
    }
    return false;  // if not in file
}

bool Admin::adminLogin(const string& id, const string& pass)
{
    return verifyPasswords(id, pass);
}

bool Admin::customerLogin(int, const string&)
{
    return false;
}

void Admin::showmainmenu()
{
    int choice = -1;
    while (true)
    {
        cout << "\n /////////// Admin Menu //////////// " << endl
            << "0. Exit" << endl
            << "1. Add User Account" << endl
            << "2. Delete User Account" << endl
            << "3. Add Admin Account" << endl
            << "4. Delete Admin Account" << endl
            << "5. View User Checking and Savings balance" << endl
            << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "invalid choice , Enter a number between 0 and 5" << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            addUser();
            break;
        case 2:
        {
            int card;
            cout << "Enter user card number that you want to delete: ";
            cin >> card;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (deleteUser(card)) cout << "User account is deleted." << endl;
            else cout << "User is not found." << endl;
            break;
        }
        case 3:
            addAdmin();
            break;
        case 4:
        {
            int adminID;
            cout << "Enter admin ID you want to delete: ";
            cin >> adminID;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (deleteAdmin(adminID)) cout << "Admin deleted." << endl;
            else cout << "Can't delete admin." << endl;
            break;
        }
        case 5:
        {
            int card;
            cout << "Enter user card number: ";
            cin >> card;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            viewUserBalance(card);
            break;
        }
        case 0:
            // Exiting admin menu
            return;
        default:
            cout << "Invalid choice, select a number from 0 to 5" << endl;
        }
    }
}

bool Admin::addUser()
{
    int cardNumber = 10000000;
    ifstream datafile("data.txt");
    string line;
    while (getline(datafile, line))
        cardNumber++;
    while (cardNumberExists(cardNumber))
        cardNumber++;

    int pin = 1000 + (rand() % 9000);
    ofstream out("data.txt", ios::app);
    if (!out)
    {
        return false;
    }
    out << cardNumber << "," << pin << ",0.00,0.00\n";
    cout << "User created, Card number is: " << cardNumber << ", Pin is: " << pin << endl;
    return true;
}

bool Admin::deleteUser(int cardNumber)
{
    vector<string> lines;
    bool found = false;
    ifstream in("data.txt");
    string line;
    while (getline(in, line))
    {
        stringstream ss(line);
        string current;
        getline(ss, current, ',');
        if (stoi(current) != cardNumber) lines.push_back(line);
        else found = true;
    }
    if (!found)
    {
        return false;
    }
    ofstream out("data.txt");
    for (auto& l : lines)
        out << l << '\n';
    return true;
}

bool Admin::addAdmin()
{
    int adminID = 400000;
    ifstream adminfile("Admin.txt");
    string line;
    while (getline(adminfile, line))
        adminID++;

    string password;
    cout << "Enter new admin password: ";
    cin >> password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ofstream out("Admin.txt", ios::app);
    if (!out)
    {
        return false;
    }
    out << adminID << "," << password << "\n";
    cout << "Admin created, id is: " << adminID << endl;
    return true;
}

bool Admin::deleteAdmin(int adminID)
{
    vector<string> lines;
    int adminCount = 0;
    bool found = false;
    ifstream in("Admin.txt");
    string line;
    while (getline(in, line))
    {
        stringstream ss(line);
        string current;
        getline(ss, current, ',');
        if (stoi(current) != adminID)
        {
            lines.push_back(line);
            adminCount++;
        }
        else 
        {
            found = true;
        }
    }
    if (!found || adminCount < 1)
    { 
        return false;
    }
    ofstream out("Admin.txt");
    for (auto& l : lines)
        out << l << '\n';
    return true;
}

void Admin::viewUserBalance(int cardNumber)
{
    ifstream file("data.txt");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string currentCard, pin, checking, saving;
        getline(ss, currentCard, ',');
        getline(ss, pin, ',');
        getline(ss, checking, ',');
        getline(ss, saving);
        if (stoi(currentCard) == cardNumber)
        {
            cout << "Account Details:  Card number: " << currentCard
                << ", Checking account balance: $" << fixed << setprecision(2) << stod(checking)
                << ", Savings account balance: $" << fixed << setprecision(2) << stod(saving) << endl;
            return;
        }
    }
    cout << "User not found" << endl;
}

bool Admin::cardNumberExists(int cardNumber)
{
    ifstream file("data.txt");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string current;
        getline(ss, current, ',');
        if (stoi(current) == cardNumber) return true;
    }
    return false;
}

bool Admin::adminIDExists(int adminID)
{
    ifstream file("Admin.txt");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string current;
        getline(ss, current, ',');
        if (stoi(current) == adminID) return true;
    }
    return false;
}