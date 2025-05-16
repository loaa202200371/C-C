#include "ATM.h"
#include "Admin.h"
#include <iostream>

void ATM::handleFailedAttempt() {
    if (++failedAttempts >= 3) lockthesystem();
    cout << "Invalid attempt.  Remaining attempts: " << 3 - failedAttempts << endl;
}

void ATM::lockthesystem() {
    cout << "\n you entered the password/id wrong for 3 times. system is now locked :( )" << endl;
    exit(1);
}