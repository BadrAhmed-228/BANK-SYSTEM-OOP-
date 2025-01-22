#pragma once

#include <iostream>
#include "clsPerson.h"
#include <fstream>
#include "clsString.h"
#include <vector>
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsBankUser : public clsPerson
{

private:

	enum enMode { eEmptyMode = 1, eUpdateMode = 2, eAddNewMode = 3 };
	enMode _Mode;
	
	string _UserName;
	string _Password;
	int _Permessions;

	bool _MarkForDelete = false;

	struct stRegisterLogin;

	string _PrepareLoginRecord(string dlimeter = "#//#")
	{
		string LoginRecord = "";

		LoginRecord = clsDate::GetSystemDateTimeString() + dlimeter;
		LoginRecord += UserName() + dlimeter;
		//Encrypt password in file.
		LoginRecord += clsUtil::EncryptText(Password, 3) + dlimeter;
		LoginRecord += to_string(Permissions);

		return LoginRecord;
	}

	static stRegisterLogin _ConvertLineToStruct(string Line, string Delimeter = "#//#")
	{
		stRegisterLogin Register;

		vector<string> vLine = clsString::Split(Line, Delimeter);

		Register.stDate = vLine[0];
		Register.stUserName = vLine[1];
		Register.stPassword = clsUtil::DecryptText(vLine[2], 3);
		Register.stPermissions = stoi(vLine[3]);

		return Register;
	}

	static vector<stRegisterLogin> _LoadRegisterations()
	{
		vector<stRegisterLogin> vRegestrations;

		fstream file;

		file.open("Login Register.text", ios::in); //read mode

		if (file.is_open())
		{
			string line = "";

			stRegisterLogin Register;

			while (getline(file, line))
			{
				Register = _ConvertLineToStruct(line);

				vRegestrations.push_back(Register);
			}

			file.close();
		}

		return vRegestrations;
	}

	static clsBankUser _ConvertLineToUserObject(string line, string delimeter = "#//#")
	{
		vector<string> vRecord = clsString::Split(line, delimeter);

		return clsBankUser(enMode::eUpdateMode, vRecord[0], vRecord[1], vRecord[2], vRecord[3], vRecord[4], clsUtil::DecryptText(vRecord[5], 3), stoi(vRecord[6]));
	}

	static string _ConvertUserObjectToLine(clsBankUser User, string delimeter = "#//#")
	{
		string sUser = "";

		sUser += User.FirstName + delimeter;

		sUser += User.LastName + delimeter;

		sUser += User.Email + delimeter;

		sUser += User.Phone + delimeter;

		sUser += User.UserName() + delimeter;

		//Encrypt password in file.
		sUser += clsUtil::EncryptText(User.Password, 3) + delimeter;

		sUser += to_string(User.Permissions);

		return sUser;
	}

	void _SaveUsersDataToFile(vector<clsBankUser>& vUsers)
	{
		fstream file;

		file.open("Users.text", ios::out); // overwrite

		if (file.is_open())
		{
			for (clsBankUser C : vUsers)
			{
				if (C._MarkForDelete == false)
				{
					string line = _ConvertUserObjectToLine(C);

					file << line << endl;
				}
			}

			file.close();
		}

		//vUsers = _LoadUsersDataFromFile();
	}

	static vector<clsBankUser> _LoadUsersDataFromFile()
	{
		vector<clsBankUser> vUsers;

		fstream file;

		file.open("Users.text", ios::in); // read mode

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				clsBankUser User = _ConvertLineToUserObject(line);

				vUsers.push_back(User);
			}

			file.close();
		}

		return vUsers;
	}

	void _Update()
	{
		vector<clsBankUser> vUsers = _LoadUsersDataFromFile();

		for (clsBankUser& U : vUsers)
		{
			if (_UserName == U.UserName())
			{
				U = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream file;

		file.open("Users.text", ios::out | ios::app); // write Mode

		if (file.is_open())
		{
			file << DataLine << endl;

			file.close();
		}
	}

	static clsBankUser _GetEmptyUser()
	{
		return clsBankUser(enMode::eEmptyMode, "", "", "", "", "", "", 0);
	}

public:

	struct stRegisterLogin
	{
		string stDate = "";
		string stUserName = "";
		string stPassword = "";
		int stPermissions = 0;
	};

	enum enPermissions { pAll = -1, pListClient = 1, pAddNnewClient = 2, pUpdateClient = 4, 
		pDeleteClient = 8, pFindClient = 16, pTransactions = 32, pManageUser = 64, pLoginRegister = 128 }; // using binary

	clsBankUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permessions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		this->_Mode = Mode;
		this->_UserName = UserName;
		this->_Password = Password;
		this->_Permessions = Permessions;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::eEmptyMode);
	}

	bool MarkForDelete()
	{
		return this->_MarkForDelete;
	}

	string FullName()
	{
		return FirstName + " " + LastName;
	}

	string UserName()
	{
		return this->_UserName;
	}

	void SetPassword(string Password)
	{
		this->_Password = Password;
	}

	string GetPassword()
	{
		return this->_Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermessions(int Permessions)
	{
		this->_Permessions = Permessions;
	}

	int GetPermessions()
	{
		return this->_Permessions;
	}

	__declspec(property(get = GetPermessions, put = SetPermessions)) int Permissions;

	static clsBankUser Find(string UserName)
	{
		fstream file;

		file.open("Users.text", ios::in); //read Mode

		if (file.is_open())
		{
			string line = "";

			while (getline(file, line))
			{
				clsBankUser User = _ConvertLineToUserObject(line);

				if (UserName == User._UserName)
				{
					file.close();
					
					return User;
				}
			}

			file.close();
		}

		return _GetEmptyUser();
	}

	static clsBankUser Find(string UserName, string Password)
	{
		fstream file;

		file.open("Users.text", ios::in); //read Mode

		if (file.is_open())
		{
			string line = "";

			while (getline(file, line))
			{
				clsBankUser User = _ConvertLineToUserObject(line);

				if (UserName == User._UserName && Password == User.Password)
				{
					file.close();

					return User;
				}
			}

			file.close();
		}

		return _GetEmptyUser();
	}

	enum enSaveResults { svFailEmptyObject = 1, svSuccssed = 2, svFailUserExist = 3 };

	enSaveResults Save()
	{
		switch (_Mode)
		{

		case enMode::eEmptyMode:
		{
			return enSaveResults::svFailEmptyObject;
		}
		case enMode::eUpdateMode:
		{
			_Update();

			return enSaveResults::svSuccssed;
		}
		case enMode::eAddNewMode:
		{
			if (IsUserExist(UserName()))
			{
				return enSaveResults::svFailUserExist;
			}
			else
			{
				_AddNew();

				_Mode = enMode::eUpdateMode;

				return enSaveResults::svSuccssed;
			}
		}
		
		}
	}

	static bool IsUserExist(string UserName)
	{
		clsBankUser User = clsBankUser::Find(UserName);

		return (!User.IsEmpty());
	}

	static clsBankUser GetAddNewUserObject(string UserName)
	{
		return clsBankUser(enMode::eAddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete()
	{
		vector<clsBankUser> vUsers = _LoadUsersDataFromFile();

		for (clsBankUser& U : vUsers)
		{
			if (U.UserName() == this->_UserName)
			{
				U._MarkForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUser();

		return true;
	}

	static vector<clsBankUser> GetUserList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckPermission(enPermissions Permission)
	{
		if (this->_Permessions == enPermissions::pAll)
		{
			return true;
		}
		if ((Permission & this->_Permessions) == Permission)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void RegisterLogin()
	{
		string sDataLine = this->_PrepareLoginRecord();

		fstream file;

		file.open("Login Register.text", ios::out | ios::app);

		if (file.is_open())
		{
			file << sDataLine << endl;

			file.close();
		}
	}

	static vector<stRegisterLogin> GetRegisterations()
	{
		return _LoadRegisterations();
	}

};

