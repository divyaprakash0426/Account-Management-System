#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )  
#pragma comment( lib, "libeng.lib" )
#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
#include<engine.h>
#include<cmath>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<map>
#include<cstdlib>
#include<utility>
#include<sstream>
#include<fstream>  
#include<string>
#include<stdlib.h>
#include "StockAccount_divyaprakash.h"
#include "StockNode_divyaprakash.h"

using namespace std;

StockAccount::StockAccount()
{
	TheFirstPointer = NULL;
	tailptr = NULL;

	valArray2[20] = { 0 };
	counter2 = 0;
	portfolioval = 0;

	setCashRemain();

	srand((unsigned int)time(NULL));

	// code to copy data from result-1 and result-2 into two maps for better data accessability.
	txt1.open("Result_1.txt");
	txt2.open("Result_2.txt");
	if (txt1.is_open() && txt2.is_open())
	{
		while (!txt1.eof() && !txt2.eof())
		{
			getline(txt1, line1);
			a << line1;
			a >> symbol1 >> price1;
			result1.insert(pair<string, double>(symbol1, price1));
			a.str("");
			a.clear();

			getline(txt2, line1);
			a << line1;
			a >> symbol1 >> price1;
			result2.insert(pair<string, double>(symbol1, price1));
			a.str("");
			a.clear();
		}
	}
	txt1.close();
	txt2.close();

	// getting size of previously stored portfolio (doubly linked list)
	txt1.open("size.txt", ios_base::in);
	txt1 >> size;
	txt1.close();
	if (size != 0)
		this->retrievePortfolio(); 	// retrieing the previously stored portfolio in a double linked list
	this->retrievePortVal(); // retrieve portflio value in double array for plotting
}
// destructor
StockAccount::~StockAccount() {}
//display stock price for one file
void StockAccount::dispStockPrice()
{
	bool flag = false;

	cout << "\nEnter Stock Symbol : ";
	cin >> SymbolOfTicker;

	random_file_generate = rand() % 2; // generate random numbers for selecting between two text files

									   //if random no. is 0, then search for stock symbol in Results_1.txt file
	if (random_file_generate == 0)
	{
		// iterating through map
		map<string, double>::iterator itr;
		for ( itr = result1.begin(); itr != result1.end(); itr++)
		{
			// if symbol is found then display its stock price
			if (SymbolOfTicker == (*itr).first)
			{
				cout << left << setw(10) << "Symbol";
				cout << left << setw(10) << "Price/Share" << endl;
				cout << left << setw(10) << (*itr).first;
				cout << left << setw(10) << (*itr).second << endl << endl;
				break;
			}
		}
		if (itr == result1.end())
		{
			cout << "\nSymbol not found!\n";
			return;
		}
	}

	//if random no. is 1, then search for stock symbol in Results_2.txt file
	else if (random_file_generate == 1)
	{
		// iterating through map
		map<string, double>::iterator DieDai;
		for ( DieDai = result2.begin(); DieDai != result2.end(); DieDai++)
		{
			// if symbol is found then display its stock price
			if (SymbolOfTicker == (*DieDai).first)
			{
				cout << left << setw(10) << "Symbol";
				cout << left << setw(10) << "Price/Share" << endl;
				cout << left << setw(10) << (*DieDai).first;
				cout << left << setw(10) << (*DieDai).second << endl << endl;
				break;
			}
		}
		// if symbol not found then print that.
		if (DieDai == result2.end())
		{ 
			cout << "\nSymbol not found!\n";
			return;
		}
	}
}
// display portfolio
void StockAccount::dispPortfolio()
{
	setCashRemain();
	double CashBalance = getCashRemain();
	while (cur != NULL)
	{
		random_file_generate = rand() % 2;
		// if random number is 0 then assign temporary stock price to corresponding symbol in portfolio and calculate temporary value of the node
		if (random_file_generate == 0)
		{
			for (map<string, double>::iterator DieDai = result1.begin(); DieDai != result1.end(); DieDai++)
			{
				// checking whether node symbol is matched
				if (cur->symbol == (*DieDai).first)
				{
					cur->temp_price_per_share = (*DieDai).second;                // assign current stock price to each symbol in portfolio
					cur->tempval = cur->numshares*cur->temp_price_per_share; // calculate temp node value
				}
			}
		}
		// if random number is 1 then assign temporary stock price to corresponding symbol in portfolio and calculate temporary value of the node
		else if (random_file_generate == 1)
		{
			for (map<string, double>::iterator DieDai = result2.begin(); DieDai != result2.end(); DieDai++)
			{
				// checking whether node symbol is matched
				if (cur->symbol == (*DieDai).first)
				{
					// assign current stock price to each symbol in portfolio
					cur->temp_price_per_share = (*DieDai).second;
					// calculate temp node value
					cur->tempval = cur->numshares*cur->temp_price_per_share;
				}
			}
		}
		cur = cur->nextptr; // advance to next node
	}
	this->sortStockList(); // sorting the potfolio before displaying to show dynamic changes according to share values.
						   // checking if size is greater than 0
	double stockval = 0;
	if (size > 0) // checking if size is greater than 0
	{
		cout << "\n" << setw(13) << "Symbol" << setw(13) << "Shares" 
			<< setw(22) << "Price per Share($)" << setw(22) << "Total Value($)" << "\n";
		cur = TheFirstPointer;  // dummy node pointer for iterating loop
		while (cur != NULL)
		{
			//prints symbol, no. of share, current price of share, current value.
			cout << setw(13) << cur->symbol << setw(13) << cur->numshares
				<< setw(22) << cur->temp_price_per_share << setw(22) << cur->tempval << "\n";

			stockval = stockval + cur->tempval;
			cur = cur->nextptr; // increment the pointer
		}
		portfolioval = CashBalance + stockval;
		cout << "\nCash Balance  : $" << CashBalance;
		cout << "\nStock Balance : $" << stockval;
		cout << "\nTotal Portfolio value is : $" << portfolioval << "\n\n"; // print total portfolio value

		valArray2[counter2] = portfolioval; // store portfolio value changes in double type array.
		counter2++;
	}
	// if size is 0, print that.
	else if (size == 0)
	{
		portfolioval = CashBalance;
		cout << "\nYou don't have any shares right now!\n";
	}
}

int StockAccount::judgeBuy()
{
	map<string, double>::iterator DieDai;
	for (DieDai = result1.begin(); DieDai != result1.end(); DieDai++)
	{
		if (SymbolOfTicker == (*DieDai).first)
			return 1;
	}
	if (DieDai == result1.end())	// if it is not present then show that and return.
	{
		cout << "\nSymbol Not found!\n";
		return 0;
	}
}
// selling the shares
void StockAccount::sellShares()
{
	bool flag3 = false;
	setCashRemain();
	CashBalance = getCashRemain();

	cout << "\nEnter the Symbol of a company that you want to sell shares : ";
	cin >> SymbolOfTicker;
	int judge = judgeSell();

	/************************************************************************/
	if (judge == 0)
		return;
	// sell shares
	cout << "\nEnter the no. of share you want to sell : ";
	cin >> ShareNumber;
	cout << "\nEnter Minimum Amount you are willing to pay for each share : ";
	cin >> minPrice;

	if (size > 0) // checking if size is greater than 0
	{
		StockNode *cur = TheFirstPointer;  // temp node pointer for iterating loop

		while (cur != NULL)
		{
			if (SymbolOfTicker == cur->symbol && ShareNumber <= cur->numshares)
			{
				flag3 = true;
				cur->numshares = cur->numshares - ShareNumber;
				//updating balance after selling the shares.
				double theRandomNumber = random(0);
				if (theRandomNumber == 0)
					return;
				totalPrice = ShareNumber * theRandomNumber;
				CashBalance = CashBalance + totalPrice;
				// print the statement for share sell.
				cout << "\nYou have sold " << ShareNumber << " shares of "
					<< SymbolOfTicker << " at rate " << price1 << " per share\n";
				//generating the current date and time for updating withdrawing from bank transaction
				write_in_bank_stock_history();
				//updating current balance in the balancefile
				writeBalance.open("balfile.txt", std::ios_base::out);
				writeBalance << CashBalance;
				writeBalance.close();
				//if no. of shares of particular symbol are zero then delete the node.
				if (cur->numshares == 0)
				{
					//if current node is head
					if (cur == TheFirstPointer)
					{
						if (cur == tailptr)
						{
							TheFirstPointer = NULL;
							tailptr = NULL;
							delete cur;
							size--;
							return;
						}
						StockNode *temp = cur->nextptr;
						TheFirstPointer = cur->nextptr;
						temp->prevptr = NULL;
						delete cur; // delete the node.
						size--;     // reduce the size.
						return;
					}
					//if current node is tail
					else if (cur == tailptr)
					{
						if (cur == TheFirstPointer)
						{
							TheFirstPointer = NULL;
							tailptr = NULL;
							delete cur;
							size--;
							return;
						}
						StockNode *temp2 = cur->prevptr;
						tailptr = cur->prevptr;
						temp2->nextptr = NULL;
						delete cur;    // delete the node
						size--;        // reduce the size.
						return;
					}
					//else is the current node is middle node
					else
					{
						StockNode *temp3 = cur->prevptr;
						StockNode *temp4 = cur->nextptr;
						temp3->nextptr = cur->nextptr;  // prev node's next pointer should be current node's next pointer.
						temp4->prevptr = cur->prevptr;  // current node's next node prev pointer should be current node's prev. pointer
						delete cur;                     // delete current node.
						size--;                         // reduce the size.
						return;
					}
				}
				savePortfolio();    // saving portfolio.
				savePortfolioVal(); //saving portfolioval.
				return;
			}
			cur = cur->nextptr; // increment the pointer
		}
	}
	if (flag3 == false)
		cout << "\nEnter Number of shares within range of your portfolio!\n"; // if  entered no. of shares are greater than current shares.
}
// buying shares
void StockAccount::buyShares(StockNode *n)
{
	setCashRemain();
	bool flag2 = true, flag3 = true, flag4 = true, flag5 = true;
	double shareval1, shareval2;
	CashBalance = getCashRemain();
	double totalPrice;

	cout << "\nEnter the Ticker Symbol : ";
	cin >> SymbolOfTicker;

	// iterating in any map (result1/result2) to check the symbol is present or not!
	int judge = judgeBuy();
	if (judge == 0)
		return;
	//else ask for furthur inforamtion.
	cout << "\nEnter the Number of shares you want to buy : ";
	cin >> ShareNumber;
	cout << "\nEnter the Maximum Amount you are willing to pay per share : ";
	cin >> maxPrice;

	// iterating both the maps and getting corresponding share values for entered symbol.
	for (map<string, double>::iterator DieDai = result1.begin(); DieDai != result1.end(); DieDai++)
	{
		if (SymbolOfTicker == (*DieDai).first)
		{
			shareval1 = (*DieDai).second;
		}
	}
	for (map<string, double>::iterator DieDai = result2.begin(); DieDai != result2.end(); DieDai++)
	{
		if (SymbolOfTicker == (*DieDai).first)
		{
			shareval2 = (*DieDai).second;
		}
	}
	double theRandomNumber = random(1);
	if (theRandomNumber == 0)
		return;
	totalPrice = ShareNumber * theRandomNumber;
	// if total amount is greater than current cash balance display can't buy and return.
	CashBalance = CashBalance - totalPrice;
	if (CashBalance > 0)
	{
		cout << "\nYou have purchased " << ShareNumber << " shares of " 
			<< SymbolOfTicker << " for a total of $" << totalPrice << "\n\n";
		//writing to a balance file.
		writeBalance.open("balancefile.txt", std::ios_base::out);
		writeBalance << CashBalance;
		writeBalance.close();
		//generating the current date and time for updating withdrawing from bank transaction
		write_in_bank_stock_history();
		savePortfolio();    // saving portfolio.
		savePortfolioVal();
		//updating doubly linked list
		// if you are inserting first node
		if (tailptr == NULL&&TheFirstPointer == NULL)
		{
			//if appending, then head and tail should point to the same node
			tailptr = n;
			TheFirstPointer = n;
			n->symbol = SymbolOfTicker;
			n->numshares = ShareNumber;
			n->price_per_share = price1;
		}
		// else updating current node or adding node at the end.
		else
		{
			StockNode *cur = TheFirstPointer;
			while (cur != NULL)
			{
				// if shares of same symbol- update existing node shares.
				if (SymbolOfTicker == cur->symbol)
				{
					cur->numshares = cur->numshares + ShareNumber;
					return;
				}
				cur = cur->nextptr;
			}
			// adding new node at the end with new symbol and new no. of shares.
			StockNode *copy = tailptr;
			tailptr->nextptr = n;
			tailptr = n;
			tailptr->prevptr = copy;
			n->symbol = SymbolOfTicker;
			n->numshares = ShareNumber;
			n->price_per_share = price1;
		}
		size++; // increasing size of list
	}
	// else 
	else
	{
		cout << "\nTotal Amount Exceeds the available Cash Balance!\n";
		return;
	}
}
void StockAccount::write_in_bank_stock_history()
{
	std::string str(currentTime());
	// writing event transaction to stock_transaction_history.txt file
	writeUserfile.open("stock_transaction_history.txt", ios::app);
	writeUserfile << "\n" << left << setw(7) << "Buy";
	writeUserfile << left << setw(14) << SymbolOfTicker;
	writeUserfile << left << setw(7) << ShareNumber;
	writeUserfile << left << setw(14) << price1;
	writeUserfile << left << setw(10) << totalPrice;
	writeUserfile << left << setw(15) << str;
	writeUserfile.close();
	// writing deposit transaction to bank_transaction_history.txt file
	writeUserfile.open("bank_transaction_history.txt", ios::app);
	writeUserfile << left << setw(30) << "Debited to Stock Acct.";
	writeUserfile << left << setw(1) << "$";
	writeUserfile << left << setw(15) << totalPrice;
	writeUserfile << right << setw(15) << str;
	writeUserfile << right << setw(5) << "$" << CashBalance;
	writeUserfile.close();
}


double StockAccount::random(int a)
{
random_file_generate = rand() % 2;
//finding the current value of share to sell 
if (random_file_generate == 0)
{
	//get price1 from result1 
	for (map<string, double>::iterator DieDai = result1.begin(); DieDai != result1.end(); DieDai++)
	{
		// stock symbol is found.
		if (SymbolOfTicker == (*DieDai).first)
		{
			price1 = (*DieDai).second; // if found then shares at this price.
			if (a == 0)
			{
				if (minPrice > ((*DieDai).second))
				{
					cout << "\nMinimum Value entered is greater than current Share value! Can't sell shares right now at this value!\n";
					return 0.0;
				}
			}
			if(a == 1)
			{ 
				if (maxPrice < ((*DieDai).second))
				{
					cout << "\nAs the Maximum Value entered is less than current Share value! Cannot buy shares! \n";
					return 0.0;
				}
			}
		}
	}
}
else if (random_file_generate == 1)
{
	//get price1 from result2
	for (map<string, double>::iterator DieDai = result2.begin(); DieDai != result2.end(); DieDai++)
	{
		if (SymbolOfTicker == (*DieDai).first)
		{
			price1 = (*DieDai).second;
			// if min. price entered is greater than current share value then print can't sell and return.
			if (a == 0)
			{
				if (minPrice > ((*DieDai).second))
				{
					cout << "\nMinimum Value entered is greater than current Share value! Can't sell shares right now at this value!\n";
					return 0;
				}
			}
			if (a == 1)
			{
				if (maxPrice < ((*DieDai).second))
				{
					cout << "\nAs the Maximum Value entered is less than current Share value! Cannot buy shares! \n";
					return 0;
				}
			}
		}
	}
}
return price1;
}
int StockAccount::judgeSell()
{
	StockNode *curtemp = TheFirstPointer;

	// checking if the symbol entered is present in your portfolio by iterating from start to end 
	while (curtemp != NULL)
	{
		if (SymbolOfTicker == curtemp->symbol)
			return 1;
		curtemp = curtemp->nextptr;
		// if not present then display that and return.
		if (curtemp == NULL)
		{ 
			cout << "\nSymbol not found in your portfolio!\n";
			return 0;
		}
	}
}
void StockAccount::retrievePortfolio()
{
	int sharetempp;
	// open the portfolio text file and save everything in that text file into the STL map with key=Symbol and value=Price/share
	portfile.open("portfolio.txt", ios_base::in);
	if (portfile.is_open())
	{
		while (!portfile.eof())
		{
			getline(portfile, line1);
			b << line1;             // getting line1 into the stringstream object 
			b >> tempp >> sharetempp;  // dividing stringstream object into string and double value 
			portfolio.insert(pair<string, int>(tempp, sharetempp)); // inserting it into map pairwise
			b.clear();
		}
	}
	portfile.close();

	// iterating into map and creating double linked list.
	for (map<string, int>::iterator DieDai = portfolio.begin(); DieDai != portfolio.end(); ++DieDai)
	{
		StockNode *current = new StockNode();
		current->symbol = (*DieDai).first;
		current->numshares = (*DieDai).second;
		// if entering first node
		if (prev == NULL)
		{
			current->prevptr = NULL;
			current->nextptr = NULL;
			TheFirstPointer = current;
			tailptr = current;
		}
		// enter the node at the end.
		else
		{
			current->prevptr = prev;
			prev->nextptr = current;
		}
		prev = current;
		tailptr = prev;
	}
	StockNode *cur = TheFirstPointer;
	while (cur != NULL)
	{
		random_file_generate = rand() % 2;
		// if random number is 0 then assign temporary stock price to corresponding symbol in portfolio and calculate temporary value of the node
		if (random_file_generate == 0)
		{
			for (map<string, double>::iterator DieDai = result1.begin(); DieDai != result1.end(); DieDai++)
			{
				// checking whether node symbol is matched
				if (cur->symbol == (*DieDai).first)
				{
					cur->temp_price_per_share = (*DieDai).second;                // assign current stock price to each symbol in portfolio
					cur->tempval = cur->numshares*cur->temp_price_per_share; // calculate temp node value
				}
			}
		}
		// if random number is 1 then assign temporary stock price to corresponding symbol in portfolio and calculate temporary value of the node
		else if (random_file_generate == 1)
		{
			for (map<string, double>::iterator DieDai = result2.begin(); DieDai != result2.end(); DieDai++)
			{
				// checking whether node symbol is matched
				if (cur->symbol == (*DieDai).first)
				{
					cur->temp_price_per_share = (*DieDai).second;                // assign current stock price to each symbol in portfolio
					cur->tempval = cur->numshares*cur->temp_price_per_share; // calculate temp node value
				}
			}
		}
		portfolioval = portfolioval + cur->tempval;
		cur = cur->nextptr; // advance to next node
	}
	portfolioval += CashBalance;
}

// viewvalue graph on matlab as well shows the variation in tabular form on console.
void StockAccount::savePortfolioVal()
{
	std::string str(currentTime());
	if (size == 0)
		portfolioval = CashBalance; // if at the time of exiting the program, size portfolio is empty, then store portfolio value as CashBalance.
	writePortfolio.open("portfolioValue.txt.", ios::app);
	writePortfolio << portfolioval << "  " << str << "\n";
	writePortfolio.close();
}

void StockAccount::viewGraph()
{
	//creating a pointer to the engine
	Engine *ep;
	ep = engOpen(NULL);

	// if matlab engine is not opened show error.
	if (ep == NULL)
	{
		cout << "Error: Not Found." << "\n";
		exit(1);
	}
	// end
	cout << "Potfolio Value" << setw(15) << "Date & Time" << "\n";
	for (int i = 0; i < counter2; i++)
	{
		cout << valArray2[i] << setw(30) << timeArr[i] << "\n";
	}
	// create mxArray and copy your c++ double array of portfolio value into it.
	mxArray *A;
	A = mxCreateDoubleMatrix(1, counter2, mxREAL);
	memcpy((void *)mxGetPr(A), (void *)valArray2, counter2 * sizeof(double));
	engPutVariable(ep, "yy", A);
	// plotting function.
	engEvalString(ep, "plot(yy);");
	// setting up the title for graph
	engEvalString(ep, "title('Portfolio Value Variation graph');");
	mxDestroyArray(A); // destroy mxArray A
}
// printing history
void StockAccount::printTrans()
{
	cout << "\n" << setw(7) << "Event" << setw(14) << "CompanySym" << setw(7) << "Shares"
		<< setw(14) << "Price/Share($)" << setw(10) << "Value($)" << setw(15) << "Date & Time\n";
	txt.open("stock_transaction_history.txt", ios::app); // open history file
														 // if the file is open, read the file line1 by line1 till the end.
	if (txt.is_open())
	{
		while (!txt.eof())
		{
			while (getline(txt, line2))
				cout << line2 << "\n";
		}
		txt.close();  // close the file
	}
	else
		cout << "Error in opening the file.\n";
}
// saing portfolio (only symbols and corresponding no. of shares) in separate text file
void StockAccount::savePortfolio()
{
	StockNode *itr = TheFirstPointer;
	writePortfolio.open("portfolio.txt", std::ios_base::out);
	// iterate thorugh the program and save compnay symbol and no. of shares 
	while (itr != NULL)
	{
		writePortfolio << itr->symbol << "\t" << itr->numshares << "\n";
		itr = itr->nextptr;
	}
	writePortfolio.close();
	// save size of the doubly linked list.
	writePortfolio.open("size.txt");
	writePortfolio << size;
	writePortfolio.close();
}
//sorting the list
//Design pattern
bool StockAccount::sortStockList()
{
	StockNode *cur = TheFirstPointer;
	int counter = 0;

	//getting random price of a share before sorting;
	while (cur != NULL)
	{
		random_file_generate = rand() % 2;
		if (random_file_generate == 0)
		{
			for (map<string, double>::iterator DieDai = result1.begin(); DieDai != result1.end(); DieDai++) // map iterater
			{
				if (cur->symbol == (*DieDai).first)
				{
					cur->temp_price_per_share = (*DieDai).second;
					cur->tempval = cur->numshares*cur->temp_price_per_share; // temp node value for sorting
				}
			}
		}
		else if (random_file_generate == 1)
		{
			for (map<string, double>::iterator DieDai = result2.begin(); DieDai != result2.end(); DieDai++) // map iterater
			{
				if (cur->symbol == (*DieDai).first)
				{
					cur->temp_price_per_share = (*DieDai).second;
					cur->tempval = cur->numshares*cur->temp_price_per_share; // temp node value for sorting
				}
			}
		}
		cur = cur->nextptr; // increment the node
	}

	StockNode *current = TheFirstPointer;

	if (TheFirstPointer != NULL) // checking if list not empty.
	{
		StockNode* prev = 0;
		StockNode *tempPtr = NULL;
		int swapFlag = 0;

		// outer bubble sort loop iteration.
		for (int i = 0; i < size; i++)
		{
			// inner bubble sort loop iteration.
			while (current->nextptr != 0) // checking if it is not a tail pointer
			{
				tempPtr = current->nextptr;
				if (current->tempval < tempPtr->tempval)
				{
					tempPtr->prevptr = current->prevptr;
					current->prevptr = tempPtr;
					swapFlag = 1;
					current->nextptr = tempPtr->nextptr;
					if (current->nextptr != NULL) // checking for tail pointer
						current->nextptr->prevptr = current;
					tempPtr->nextptr = current;   // after swapping temptr's next pointer should be current.
					if (prev != 0)				  // if previous pointer to the current is not NULL
						prev->nextptr = tempPtr;  // then previous's next pointer should be temptr after swapping.
					prev = tempPtr;               // and for next iteration previous should be temptr.
					if (TheFirstPointer == current)       // if The first pointer is current, then after swapping, TheFirstPointer should be temptr.
						TheFirstPointer = tempPtr;
					if (current->nextptr == 0)    // if current's next pointer is tailpointer then after swapping, tailpointer should be current.
						tailptr = current;
				}
				else
				{
					prev = current;               // if no swapping, then for next iteration, previous pointer should be current.
					current = current->nextptr;   // increment the node.
				}
			}
			if (swapFlag == 0) // if no swapping in one iteration, then list is sorted! and break out of the loop.
				break;
			else               // else, start the next iteration from the head pointer.
			{
				prev = 0;
				current = TheFirstPointer;
				swapFlag = 0;
			}
		}
	}
	else // list is empty
	{
		return false;
		//cout << "\nList is Empty! Can't Sort!\n";
	}
	return true;
}
// retrieving portfolio in a doubly linked list at the start of program.s
void StockAccount::retrievePortVal()
{
	string line2, temp;
	//open portfolioValue text file and get the historical data from it and save it in two arrays.
	portvalfile.open("portfolioValue.txt", ios_base::in);
	if (portvalfile.is_open())
	{
		while (!portvalfile.eof())
		{
			getline(portvalfile, line2);
			c << line2;
			c >> valArray2[counter2] >> timeArr[counter2] >> temp; // storing porfolio values in valArray2.
			if (timeArr[counter2] == "") // retrieve corresponding date in timeArr
				continue;
			else
			{
				timeArr[counter2].append(" ");
				timeArr[counter2].append(temp); // append time to it.
			}
			counter2++; // increment counter for both arrays.
			c.clear();
		}
	}
	portvalfile.close();
}

// save portfolio value and time.
string StockAccount::currentTime()
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
