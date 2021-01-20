#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<iostream>
#include<fstream> 
#include<string>
#include<time.h>
#include<sstream>
#include<utility>
#include<map>
#include<ctime>

using namespace std;

#include"CurrTime_divyaprakash.h"
#include "Account_divyaprakash.h"
#include "StockNode_divyaprakash.h"

void currtime::calculate() {

	time_t  now = time(0);
	tm *local = localtime(&now);
	cout << "\nYear" << local->tm_year << "\nMonth" << local->tm_mon << "\nDay" << local->tm_mday
		<< "\nTime: " << local->tm_hour << ":" << local->tm_min << ":" << local->tm_sec << "\n";

	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	std::string str(buffer);
}
