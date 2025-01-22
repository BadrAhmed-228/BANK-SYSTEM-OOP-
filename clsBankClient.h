#pragma once

#include <iostream>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsDate.h"

using namespace std;

class clsBankClient : public clsPerson
{

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 3 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkForDelete = false;

	void _RegisterTransfer(double Amount, clsBankClient DestinationClient, string UserName)
	{
		fstream file;

		file.open("Register Transfer.text", ios::out | ios::app);

		if (file.is_open())
		{
			string line;

			line = _PrepareRegisterTransferRecord(Amount, DestinationClient, UserName);

			file << line << endl;
		}
	}

	string _PrepareRegisterTransferRecord(double Amount, clsBankClient DestinationClient, string UserName, string Delimeter = "#//#")
	{
		string TransferRegisterRecord = "";

		TransferRegisterRecord += clsDate::GetSystemDateTimeString() + Delimeter;
		TransferRegisterRecord += AccountNumber() + Delimeter;
		TransferRegisterRecord += DestinationClient.AccountNumber() + Delimeter;
		TransferRegisterRecord += to_string(Amount) + Delimeter;
		TransferRegisterRecord += to_string(AccountBalance) + Delimeter;
		TransferRegisterRecord += to_string(DestinationClient.AccountBalance) + Delimeter;
		TransferRegisterRecord += UserName;

		return TransferRegisterRecord;
	}

	struct stTrnsferLogRecord;

	static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTrnsferLogRecord TrnsferLogRecord;

		vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;

	}

	static clsBankClient _ConvertLineToClientObject(string line, string delimeter = "#//#")
	{
		vector<string> vRecord = clsString::Split(line, delimeter);

		return clsBankClient(enMode::UpdateMode, vRecord[0], vRecord[1], vRecord[2], vRecord[3], vRecord[4], vRecord[5], stod(vRecord[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string delimeter = "#//#")
	{
		string sClient = "";

		sClient += Client.FirstName + delimeter;
		
		sClient += Client.LastName + delimeter;

		sClient += Client.Email + delimeter;

		sClient += Client.Phone + delimeter;

		sClient += Client.AccountNumber() + delimeter;

		sClient += Client.PinCode + delimeter;

		sClient += to_string(Client.AccountBalance);

		return sClient;
	}

	void _SaveClientsDataToFile(vector<clsBankClient> vClients)
	{
		fstream file;

		file.open("Clients.text", ios::out); // overwrite

		if (file.is_open())
		{
			for (clsBankClient C : vClients)
			{
				if (C._MarkForDelete == false)
				{
					string line = _ConvertClientObjectToLine(C);

					file << line << endl;
				}
			}

			file.close();
		}
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector<clsBankClient> vClients;

		fstream file;

		file.open("Clients.text", ios::in); // read mode

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);

				vClients.push_back(Client);
			}

			file.close();
		}

		return vClients;
	}

	void _Update()
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream file;

		file.open("Clients.text", ios::out | ios::app);

		if (file.is_open())
		{
			file << DataLine << endl;

			file.close();
		}
	}

	static clsBankClient _EmptyClient()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	struct stTrnsferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		this->_Mode = Mode;
		this->_AccountNumber = AccountNumber;
		this->_PinCode = PinCode;
		this->_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (this->_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return this->_AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		this->_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return this->_PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		this->_AccountBalance = AccountBalance;
	}

	double GetAccountBalance()
	{
		return this->_AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	string FullName()
	{
		return this->FirstName + " " + this->LastName;
	}

	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vClients;

		fstream file;

		file.open("Clients.text", ios::in); // read mode

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);

				if (AccountNumber == Client.AccountNumber())
				{
					file.close();

					return Client;
				}

				vClients.push_back(Client);
			}

			file.close();
		}

		return _EmptyClient();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> vClients;

		fstream file;

		file.open("Clients.text", ios::in); // read mode

		if (file.is_open())
		{
			string line;

			while (getline(file, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);

				if (AccountNumber == Client.AccountNumber() && PinCode == Client.PinCode)
				{
					file.close();

					return Client;
				}

				vClients.push_back(Client);
			}

			file.close();
		}

		return _EmptyClient();
	}

	enum enSaveResults { svFailEmptyObject = 0, svSucceeded = 1, svFailAccountNumberExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return enSaveResults::svFailEmptyObject;
		}

		case enMode::UpdateMode:
		{
			_Update();

			return enSaveResults::svSucceeded;
		}

		case enMode::AddNewMode:
		{
			if (IsClientExist(AccountNumber()))
			{
				return enSaveResults::svFailAccountNumberExists;
			}

			else
			{
				_AddNew();

				_Mode = enMode::UpdateMode;

				return enSaveResults::svSucceeded;
			}
		}

		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == this->_AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = _EmptyClient();

		return true;
	}

	static vector<clsBankClient> GetClientList()
	{
		return _LoadClientsDataFromFile();
	}

	void Deposite(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	static double GetTotalBalances()
	{
		double TotalBalances = 0;

		vector<clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient C : vClients)
		{
			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		this->Withdraw(Amount);

		DestinationClient.Deposite(Amount);

		_RegisterTransfer(Amount, DestinationClient, UserName);

		return true;
	}

	static  vector <stTrnsferLogRecord> GetTransfersLogList()
	{
		vector <stTrnsferLogRecord> vTransferLogRecord;

		fstream file;
		file.open("Register Transfer.text", ios::in);//read Mode

		if (file.is_open())
		{

			string Line;

			stTrnsferLogRecord TransferRecord;

			while (getline(file, Line))
			{

				TransferRecord = _ConvertTransferLogLineToRecord(Line);

				vTransferLogRecord.push_back(TransferRecord);

			}

			file.close();

		}

		return vTransferLogRecord;

	}

};