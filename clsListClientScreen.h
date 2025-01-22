#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include <string>
#include <iomanip>

class clsListClientScreen : protected clsScreen
{
	
public:

	static void ListClient()
    {
        if (!clsScreen::CheckAccessRights(clsBankUser::enPermissions::pListClient))
        {
            return;
        }

		vector<clsBankClient> vClients = clsBankClient::GetClientList();
		
		string Titel = "\t Client List Screen";
		string sub = "\t (" + to_string(vClients.size()) + ") Client(s)";

		clsScreen::_DrawScreenHeader(Titel, sub);

        cout << "\n\t---------------------------------------------------------------------------------------------------------------\n";
        cout << setw(8) << left << "" << "| " << setw(17) << left << "Acc. Number";
        cout << "| " << setw(25) << left << "Full Name";
        cout << "| " << setw(18) << left << "Email";
        cout << "| " << setw(15) << left << "Phone";
        cout << "| " << setw(15) << left << "PinCode";
        cout << "| " << setw(15) << left << "Balance";
        cout << "\n\t---------------------------------------------------------------------------------------------------------------\n\n";

        if (vClients.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available to show";
        }
        else
        {
            for (clsBankClient C : vClients)
            {
                cout << setw(8) << left << "" << "| " << setw(17) << left << C.AccountNumber();
                cout << "| " << setw(25) << left << C.FullName();
                cout << "| " << setw(18) << left << C.Email;
                cout << "| " << setw(15) << left << C.Phone;
                cout << "| " << setw(15) << left << C.PinCode;
                cout << "| " << setw(15) << left << C.AccountBalance;

                cout << "\n";
            }
        }

        cout << "\n\n\t---------------------------------------------------------------------------------------------------------------\n";
	}
};

