#pragma once

#include "clsScreen.h"
#include "clsBankUser.h"
#include <iomanip>

class clsListUserScreen : protected clsScreen
{

public:

	static void ListScreen()
	{
        vector<clsBankUser> vUsers = clsBankUser::GetUserList();

        string Titel = "\t Client List Screen";
        string sub = "\t (" + to_string(vUsers.size()) + ") Client(s)";

        clsScreen::_DrawScreenHeader(Titel, sub);

        cout << "\n\t---------------------------------------------------------------------------------------------------------------\n";
        cout << setw(8) << left << "" << "| " << setw(17) << left << "User Name";
        cout << "| " << setw(25) << left << "Full Name";
        cout << "| " << setw(18) << left << "Email";
        cout << "| " << setw(15) << left << "Phone";
        cout << "| " << setw(15) << left << "Password";
        cout << "| " << setw(15) << left << "Permissions";
        cout << "\n\t---------------------------------------------------------------------------------------------------------------\n\n";

        if (vUsers.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available to show";
        }
        else
        {
            for (clsBankUser U : vUsers)
            {
                cout << setw(8) << left << "" << "| " << setw(17) << left << U.UserName();
                cout << "| " << setw(25) << left << U.FullName();
                cout << "| " << setw(18) << left << U.Email;
                cout << "| " << setw(15) << left << U.Phone;
                cout << "| " << setw(15) << left << U.Password;
                cout << "| " << setw(15) << left << U.Permissions;

                cout << "\n";
            }
        }

        cout << "\n\n\t---------------------------------------------------------------------------------------------------------------\n";
    }

};

