#pragma once
#include<iostream>
#include<fstream> 
#include<string>
#include<time.h>
#include "Account_divyaprakash.h"
#ifndef BANKACCOUNT_DIVYAPRAKASH_H
#define BANKACCOUNT_DIVYAPRAKASH_H
using namespace std;

// Class Bank account derived from base class Account.
class BankAccount : public Account
{
public:
	BankAccount();             // consructor
	~BankAccount();            // destructor
	void deposit_Cash(double);      // deposit cash
	void view_Balance();            // view cash balance
	void withdraw_cash(double);      // withdraw cash
	virtual void printTrans();   // print history
private:
	ofstream txt1;
	string line1;
	double depositMoney;
	ifstream Readfile;
	ofstream writeBalance;
	double withdraw_tempval;
	string currentTime();
};
#endif
	