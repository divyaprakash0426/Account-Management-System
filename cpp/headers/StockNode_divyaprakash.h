#pragma once
#include<iostream>
#include<string>
#include "Account_divyaprakash.h"
#include "StockAccount_divyaprakash.h"
using namespace std;

#ifndef STOCKNODE_DIVYAPRAKASH_H
#define STOCKNODE_DIVYAPRAKASH_H

class StockNode
{
	friend class StockAccount;

protected:
	StockNode *nextptr;
	StockNode *prevptr;

	//Each node contains no. of shares and stock symbol.
	int numshares;
	double price_per_share;      // price per share at the time of buying
	double temp_price_per_share; // temporary price per share at the time of sorting
	double tempval;              // value of a node = numshares*temp_price_per_share(/price_per_share)
	string symbol;
	string temp_string;
	int number;

public:
	StockNode()
	{
		this->nextptr = NULL;
		this->prevptr = NULL;
	}
};

#endif
