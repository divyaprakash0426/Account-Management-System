#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<utility>
#include "Account_divyaprakash.h"
#include "BankAccount_divyaprakash.h"
#include "StockAccount_divyaprakash.h"
#include "StockNode_divyaprakash.h"
#include "CurrTime_divyaprakash.h"
using namespace std;

int main()
{
	int choice1 = 0, choice2 = 0;
	double depAmount = 0, witAmount = 0;
	bool flag = true;

	BankAccount BkAcc;
	StockAccount *newptr = new StockAccount();
	StockNode *node = NULL;
	currtime ct;
	cout << "Welcome to the Account Management System.\n";
	cout << "Please Select the Account you wish to Access: \n";

Loop:
	// displaying main options.
	cout << "1. Stock Portfolio Account\n"
		<< "2. Bank Account\n"
		<< "3. Exit\n"
		<< "\nOption:";
	cin >> choice1;

	switch (choice1)
	{

	case 1:
		do
		{
			cout << "Stock Portfolio Account\n"
				<< "1. Display the price for a stock symbol\n"
				<< "2. Display the current portfolio\n"
				<< "3. Buy shares\n"
				<< "4. Sell shares\n"
				<< "5. View a graph for the portfolio value\n"
				<< "6. View transaction history\n"
				<< "7. Return to the previous menu\n"
				<< "\nOption: ";

			// Stock Account Options
			cin >> choice2;
			switch (choice2)
			{
			case 1:
				newptr->dispStockPrice();
				break;

			case 2:
				newptr->dispPortfolio();
				break;

			case 3:
				node = new StockNode();
				newptr->buyShares(node);
				break;

			case 4:
				newptr->sellShares();
				break;
			case 5:
				newptr->viewGraph();
				break;
			case 6:
				newptr->printTrans();
				break;

			case 7:
				goto Loop;
				main();

			}
		} while (choice2 != 7);

	case 2:
		do
		{
			// Bank account options
			cout << "\nBank Account";
			cout << "\n1. View Account Balance"
				<< "\n2. Deposit Money"
				<< "\n3. Withdraw Money"
				<< "\n4. Print History"
				<< "\n5. Return to Previous Menu";
			cout << "\nEnter Your Choice : ";
			cin >> choice2;

			switch (choice2)
			{
			case 1:
				BkAcc.view_Balance();
				break;
			case 2:
				cout << "\nEnter Amount in $ to be Deposited : ";
				cin >> depAmount;
				BkAcc.deposit_Cash(depAmount);
				break;
			case 3:
				cout << "\nEnter Amount  int $ to be Withdrawn : ";
				cin >> witAmount;
				BkAcc.withdraw_cash(witAmount);
				break;
			case 4:
				BkAcc.printTrans();
				break;
			case 5:
				goto Loop;
				main();
				break;
			default:
				cout << "\nEnter Valid Option!";
			}
		} while (choice2 != 5);
	case 3:
		newptr->savePortfolio();    // saving portfolio.
		newptr->savePortfolioVal();
		cout << "\nExit the Program.\n";
	}
	delete newptr;
	return 0;
}