#pragma once
#ifndef CURRTIME_DIVYAPRAKASH_H
#define CURRTIME_DIVYAPRAKASH_H
#include <iostream> 
#include <iomanip> 
#include <string> 

class currtime {
public:
	int day;
	int month;
	int year;
	int hour;
	int min;
	int sec;
	void calculate();
};
#endif // !CURRTIME_H
