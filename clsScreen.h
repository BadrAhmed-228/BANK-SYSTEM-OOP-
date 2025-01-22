#pragma once

#include <iostream>
#include "clsBankUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{

protected:

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        clsDate Date;

        cout << "\t\t\t\t\t" << "Date: " << Date.DateToString() << endl;
        cout << "\t\t\t\t\t" << "User: " << CurrentUser.UserName() << endl;
        cout << "\n";
    }

    static bool CheckAccessRights(clsBankUser::enPermissions Permission)
    {
        if (!CurrentUser.CheckPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  " << "Access denied please contact your admin";
            cout << "\n\t\t\t\t\t______________________________________\n\n";

            return false;
        }
        else
        {
            return true;
        }
    }

};

