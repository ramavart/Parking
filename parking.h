#pragma once
#include <list>
#include "CTransaction.h"
#include "car.h"
#include "settings.h"
#include <iostream>
#include <mutex>
#include <atomic> 

using namespace std;

class parking
{
public:

	
	static parking& instance() {
		static parking object;
		return object;
	}
	//должен ли в конце удалять листы?
	~parking() { flagStopThread = true; };
	float payment(Car * Vehicle);
	float getParkingBalance() { return ParkingBalance; }
	void changeParkingBalance(float pay);
	int friend PaymentProcessor( Car * Vehicle, parking * parkingObj);
	void addTransaction(Car * Vehicle, float transactionSum); 
	int addCar(string Num, string Type, float Balance, thread * ptr);
	int removeCar(string carNum);
	Car * findCar(string carNumber, Car * ptr);

	void writeLastTransactionsToFile();

	void showTransactionLog();
	void showLastMinuteTransactions();

	int getNumberFreeParkingPlaces() { return numberFreeParkingPlaces; }
	float getlastMinuteTransactionSum();

	atomic<bool> flagStopThread;
	mutex transactionLocker;
	mutex paymentLocker;

private:
	parking() : ParkingBalance(0), numberFreeParkingPlaces(settings::GetParkingSpace()), WriteToFile(&parking::writeLastTransactionsToFile, this), flagStopThread(false)  {
		WriteToFile.detach();
	};

	list <CTransaction *> transactionList;
	list <pair<string, Car *>> carList;
	float ParkingBalance;
	int numberFreeParkingPlaces;
	thread WriteToFile;
};

