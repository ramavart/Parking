#pragma once
#include <chrono>
#include <string>
#include <time.h>

using namespace std;

class CTransaction
{
public:
	CTransaction(int id, float Sum, string Num) : carId(id), transactionSum(Sum), carNumber(Num) { 	
		date = time(NULL);
	};
	~CTransaction() {};
	int getCarId() { return carId; };
	string getCarNumber(){ return carNumber; };
	float getTransactionSum() { return transactionSum; };
	time_t * getDate() { return &date; };

private:
	int carId;
	string carNumber;
	float transactionSum;
	time_t date;
};

