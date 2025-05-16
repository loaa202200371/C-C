#pragma once
#include "LoginHelper.h"
#include <string>
#include "Admin.h"           
#include "AccountManager.h"  

namespace LoginHelper
{
	bool attemptAdminLogin(::Admin& admin, int maxAttempts = 3);
	bool attemptCustomerLogin(int cardNumber, int maxAttempts = 3);
}
