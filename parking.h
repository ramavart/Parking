#pragma once
#include <list>
#include "CTransaction.h"
#include "car.h"
#include "settings.h"
#include <iostream>
#include <mutex>
#include <atomic> 
#include <algorithm>

using namespace std;

class parking
{
public:

	
	static parking& instance() {
		static parking object;
		return object;
	}
	//должен удалять листинги
	//1 правка

	//так же удаление машины происходит в потоке если флаг flagStopThread установлен в true
	~parking() { 
		

		int i = 0;
		for (auto &carPtr : carList) {
			cout << "round " << i << endl;
			i++;
			delete carPtr.second;

		}
		for (auto &trnsPtr : transactionList) {
			cout << "found " << i << endl;
			delete trnsPtr;
		}
	};

	void cleanUpParking();

	float payment(Car * Vehicle);
	float getParkingBalance() { return ParkingBalance; }
	void changeParkingBalance(float pay);
	int friend PaymentProcessor( Car * Vehicle, parking * parkingObject);
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

