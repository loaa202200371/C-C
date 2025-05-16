#include "LoginHelper.h"
#include <iostream>
#include <cstdlib>

using namespace std;
namespace LoginHelper
{

    bool attemptAdminLogin(::Admin& admin, int maxAttempts)
    {
        string id, pass;
        for (int i = 0; i < maxAttempts; ++i)
        {
            cout << "Admin ID: ";
            cin >> id;
            cout << "Password: ";
            cin >> pass;

            if (admin.adminLogin(id, pass))
                return true;

            int left = maxAttempts - i - 1;
            if (left > 0)
                cout << "Invalid credentials. " << left << " attempt" << (left > 1 ? "s" : "") << " remaining.\n";
        }
        cout << "\nToo many failed attempts. SYSTEM LOCKED.\n";
        exit(1);
    }

    bool attemptCustomerLogin(int cardNumber, int maxAttempts)
    {
        string pin;
        for (int i = 0; i < maxAttempts; ++i)
        {
            cout << "PIN: ";
            cin >> pin;

            if (AccountManager::verifyinfo(cardNumber, pin))
                return true;

            int left = maxAttempts - i - 1;
            if (left > 0)
                cout << "Invalid PIN. " << left << " attempt" << (left > 1 ? "s" : "") << " remaining.\n";
        }
        cout << "\nToo many failed attempts. SYSTEM LOCKED.\n";
        exit(1);
    }

}
