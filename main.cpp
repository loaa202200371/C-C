// main
#include <iostream>
#include <string>
#include "ATM.h"
#include "Admin.h"
#include "AccountManager.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "LoginHelper.h"

using namespace std;

int main() {
    int choice;
    do {
        cout << "\nwelcome to S_K_L_A Bank ATM\n"
            << "1. admin login\n"
            << "2. customer login\n"
            << "0. exit\n"
            << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Admin admin;
            if (LoginHelper::attemptAdminLogin(admin)) {
                admin.showmainmenu();
            }
            break;
        }

        case 2: {
            int cardNumber;
            cout << "Card Number: ";
            cin >> cardNumber;

            if (LoginHelper::attemptCustomerLogin(cardNumber)) {
                int accChoice;
                cout << "\nSelect Account Type:\n"
                    << "1. Checking Account\n"
                    << "2. Savings Account\n"
                    << "Choice: ";
                cin >> accChoice;

                string cn = to_string(cardNumber);
                if (accChoice == 1) {
                    CheckingAccount acct(cn);
                    acct.showMenu();
                }
                else if (accChoice == 2) {
                    SavingsAccount acct(cn);
                    acct.showMenu();
                }
                else {
                    cout << "Invalid account type.\n";
                }
            }
            break;
        }

        case 0:

            cout << "\n" << "Goodbye!\n";
            cout << "Our team:\n" << "Sarah Ahmed 202200164 \n"
                << "Karim Mohsen 202201822 \n"
                << "Loaa Ahmed 202200371 \n"
                << "Asmaa Hamed 202200900 \n" << "\n";
            break;

        default:
            cout << "Please enter 0, 1, or 2.\n";
        }

    } while (choice != 0);

    return 0;
}