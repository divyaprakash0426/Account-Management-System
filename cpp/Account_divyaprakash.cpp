#include<iostream>
#include<iomanip>
#include<time.h>  
#include<fstream>  
#include<string>
#include<stdlib.h>
#include "Account_divyaprakash.h"

using namespace std;

double Account::getCashRemain()
{
	return CashBalance;
}

void Account::setCashRemain()
{
	streampos length;
	ifstream filestr;
	filestr.open("balancefile.txt", ios::binary);     // open your file
	if (filestr.is_open())
	{
		filestr.seekg(0, ios::end);              // place the cursor at the end of the file
		length = filestr.tellg();                // find the position of the cursor
		filestr.close();                         // close your file
	}

	if (!length) // if length is not found, create the file and put 10,000 cash balance into it.
	{
		double putbalance = 10000.00;
		ofstream outputfile;
		outputfile.open("balancefile.txt", ios_base::out);
		outputfile << putbalance;
		outputfile.close();

		// setting the balance of 10,000
		ifstream readbal("balancefile.txt", ios_base::in);
		readbal >> CashBalance;
		readbal.close();
	}
	else
	{
		// else setting balance from existing cash balance file.
		ifstream readbalance("balancefile.txt", ios_base::in);
		readbalance >> CashBalance;
		readbalance.close();
	}
}