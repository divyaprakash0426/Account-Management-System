#pragma once
#include<iostream>
#include<fstream> 
#include<string>
#include<time.h>
#include<sstream>
#include<utility>
#include<map>
#include "Account_divyaprakash.h"
#include "StockNode_divyaprakash.h"

using namespace std;


#ifndef STOCKACCOUNT_DIVYAPRAKASH_H
#define STOCKACCOUNT_DIVYAPRAKASH_H

class StockNode;

class StockAccount : public Account
{
public:
	// constructor of StockAccount
	StockAccount();
	// destructor of StockAccount
	~StockAccount();
	// display stock price
	void dispStockPrice();
	void dispPortfolio();        // display current portfolio
	void buyShares(StockNode *); // buying shares
	int judgeBuy();
	void sellShares();           // selling shares
	int judgeSell();
	void viewGraph();        // view portfolio value variation graph
	virtual void printTrans();     // overriding printTrans function to print stock history
	bool sortStockList();        // sorting stock list
	void savePortfolio();        // saving portfolio
	void retrievePortfolio();    // retrieve portfolio at the beginning
	void savePortfolioVal();     // save the value and transaction time in portfolio value 
	void retrievePortVal();      // retrieve values from portfolio 
	void write_in_bank_stock_history();
	double random(int);
	string SymbolOfTicker;
	string currentTime();
	int random_file_generate;
	map<string, double> result1, result2;
	map<string, int> portfolio;

	StockNode *cur = TheFirstPointer;

	int size;
	int counter2;
	double portfolioval;
	double valArray2[100];
	int ShareNumber;
	double maxPrice;
	double minPrice;
	double price1;
	double totalPrice;

	ifstream txt;
	ifstream balancefile;
	ifstream portfile;
	ifstream portvalfile;
	ifstream txt1;
	ifstream txt2;

	string timeArr[100];
	string tempp;

	stringstream a;
	stringstream b;
	stringstream c;

	string line1;
	string line2;
	string symbol1;

	ofstream writeBalance;
	ofstream writeUserfile;
	ofstream writePortfolio;

	StockNode *prev = NULL;
	StockNode *TheFirstPointer;
	StockNode *tailptr;
};

#endif
	