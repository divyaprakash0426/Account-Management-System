#include<iostream>
#include<iomanip>
#include<fstream>  
#include<string>
#include<stdlib.h>
using namespace std;

#include "BankAccount_divyaprakash.h"

//constructor
BankAccount::BankAccount()
{
}

// destructor
BankAccount::~BankAccount()
{
}

//printing history
void BankAccount::printTrans()
{
	Readfile.open("bank_transaction_history.txt", ios::app);
	cout << "\n" << left << setw(30) << "Activity";
	cout << left << setw(20) << "Amount";
	cout << left << setw(20) << "Date & Time";
	cout << right << setw(15) << "Balance" << "\n";
	if (Readfile.is_open())
	{
		while (!Readfile.eof())
		{
			while (getline(Readfile, line1))
				cout << line1 << "\n";
		}
	}
	Readfile.close();
}

//function for viewing balance

//function for depositing cash
void BankAccount::deposit_Cash(double depAmount)
{
	depositMoney = depAmount;
	//setCashRemain();
	CashBalance = getCashRemain();

	CashBalance = CashBalance + depositMoney;
	cout << "\nAmount of $" << depositMoney << " is deposited to the Account\n";

	//generating the current date and time for deposit transaction
	string str(currentTime());

	// writing the deposit transaction to bank_transaction_history.txt file
	txt1.open("bank_transaction_history.txt", ios::app);
	txt1 << "\n" << left << setw(30) << "Deposit";
	txt1 << left << setw(1) << "$";
	txt1 << left << setw(15) << depositMoney;
	txt1 << right << setw(15) << str;
	txt1 << right << setw(5) << "$" << CashBalance;
	txt1.close();

	// writing to a balance file
	writeBalance.open("balancefile.txt", std::ios_base::out);
	writeBalance << CashBalance;
	writeBalance.close();

}

void BankAccount::view_Balance()
{
	setCashRemain();
	//display the current cash balance
	cout << "\nCurrent Balance is : " << "$" << getCashRemain() << "\n";
}

string BankAccount::currentTime()
{
	//generating the current date and time for updating withdrawing from bank transaction
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%I:%M:%S", &timeinfo);
	return buffer;
}

//withdrawing cash
void BankAccount::withdraw_cash(double witAmount)
{
	withdraw_tempval = witAmount;
	setCashRemain();
	CashBalance = getCashRemain();

	//to check if the cash balance is greater than 0 
	if (CashBalance > 0)
	{
		//check if withdrwal amount is greater than cash balance 
		if (withdraw_tempval > CashBalance)
		{
			cout << "\nBalance is Not Sufficient! Please Check the Balance before Withdrawing!\n"; //withdrawal operation cancelled
			return;
		}

		//withdrawal operation
		else
		{
			CashBalance = CashBalance - withdraw_tempval;
			cout << "\nAmount of $" << withdraw_tempval << " is withdrawn from the Account\n";

			//generating the current date and time for withdrawal transaction
			string str(currentTime());

			// writing withdrawal transaction to bank_transaction_history.txt file
			txt1.open("bank_transaction_history.txt", ios::app);
			txt1 << "\n" << left << setw(30) << "Withdrawal";
			txt1 << left << setw(1) << "$";
			txt1 << left << setw(15) << withdraw_tempval;
			txt1 << right << setw(15) << str;
			txt1 << right << setw(5) << "$" << CashBalance;
			txt1.close();

			// writing the same to the balancefile.txt
			writeBalance.open("balancefile.txt", std::ios_base::out);
			writeBalance << CashBalance;
			writeBalance.close();
			return;
		}
	}
	else
	{
		cout << "\nError : The Account Balance is 0$, can't withdraw Anything now!\n";
	}
}
