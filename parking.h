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
	//parking (parking const&) = delete;
	//void operator=(parking const&) = delete;
	
	static parking& instance() {
		static parking object;
		return object;
	}
	~parking() { flagStopThread = true; };//удаляет листы транзакций и  машин
	float payment(Car * Vehicle);
	float getParkingBalance() { return ParkingBalance; }
	void changeParkingBalance(float pay);
	int friend PaymentProcessor( Car * Vehicle, parking * parkingObj);
	void addTransaction(Car * Vehicle, float transactionSum);//необходимо протестировать
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

	//не понимаю синтаксиса, нужно разобраться
	// Don't forget to declare these two. You want to make sure they
	// are unacceptable otherwise you may accidentally get copies of
	// your singleton appearing.
	
	//parking(parking const&);        // Don't Implement
	//void operator=(parking const&); // Don't implement
	list <CTransaction *> transactionList;
	list <pair<string, Car *>> carList;
	float ParkingBalance;
	int numberFreeParkingPlaces;
	thread WriteToFile;
};

