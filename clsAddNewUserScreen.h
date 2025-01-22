#pragma once

#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{
	
private:

	static int _ReadPermissions()
	{
		int Permissions = 0;
		
		char YN = 'y';

		cout << "\nDo you want to give full access Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to : \n";

		cout << "\nShow client list Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pListClient;
		}

		cout << "\nAdd new client Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pAddNnewClient;
		}

		cout << "\nUpdate client Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pUpdateClient;
		}

		cout << "\nDelete client Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pDeleteClient;
		}

		cout << "\nFind client Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pTransactions;
		}

		cout << "\nManage Users Y/N ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pManageUser;
		}

		cout << "\nRegister Login YN ? ";
		cin >> YN;
		if (tolower(YN) == 'y')
		{
			Permissions += clsBankUser::enPermissions::pLoginRegister;
		}

		return Permissions;
	}

	static void _ReadUserInfo(clsBankUser& User)
	{
		cout << "Enter First Name: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "Enter Last Name: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "Enter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "Enter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "Enter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "Enter Permissions: ";
		User.Permissions = _ReadPermissions();
	}

	static void _PrintUser(clsBankUser User)
	{
		cout << "\nUserrd: \n";
		cout << "-------------------------------";
		cout << "\nFirst Name  : " << User.FirstName;
		cout << "\nLast Name   : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName();
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n-------------------------------";
	}

public:

	static void AddNewUser()
	{
		clsScreen::_DrawScreenHeader("\tAdd New User Screen");

		string UserName = "";

		cout << "\nEnter User Name: ";

		UserName = clsInputValidate::ReadString();

		while (clsBankUser::IsUserExist(UserName))
		{
			cout << "\nUser Name [" << UserName << "] is already exist Enter another one : ";

			UserName = clsInputValidate::ReadString();
		}

		clsBankUser NewUser = clsBankUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		clsBankUser::enSaveResults SaveResults;

		SaveResults = NewUser.Save();

		switch (SaveResults)
		{
		case clsBankUser::enSaveResults::svFailUserExist:
		{
			cout << "\nError Account Number is already exist";
			break;
		}

		case clsBankUser::enSaveResults::svSuccssed:
		{
			cout << "\n\nClient Added Successfully...\n\n";
			_PrintUser(NewUser);
			break;
		}

		case clsBankUser::enSaveResults::svFailEmptyObject:
		{
			cout << "\n\nError Empty object.";
			break;
		}

		}
	}

};

