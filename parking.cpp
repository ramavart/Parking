#include "pch.h"
#include "parking.h"
#include <fstream>
#include <time.h>
#include <future>
#include <functional>

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

float parking::payment(Car *Vehicle) {
	float newBalance = 0;


	if (Vehicle->GetCarBalance() > settings::GetDictionaryValue(Vehicle->GetCarType())) {
		newBalance = -1 *(settings::GetDictionaryValue(Vehicle->GetCarType()));
		while(!paymentLocker.try_lock());
		Vehicle->SetCarBalance(newBalance);
		changeParkingBalance((-1*newBalance));
		paymentLocker.unlock();
		return newBalance;
	}
	else {
		
		while (paymentLocker.try_lock());
		newBalance = -1 * (settings::GetDictionaryValue(Vehicle->GetCarType()) * settings::GetFine());
		Vehicle->SetCarBalance(newBalance);

		if (Vehicle->GetCarBalance() > 0) {
			float transactionSum = Vehicle->GetCarBalance();
			changeParkingBalance(Vehicle->GetCarBalance());
			paymentLocker.unlock();
			return transactionSum;
		}
		paymentLocker.unlock();
	}
}

void parking::changeParkingBalance(float pay) {
	ParkingBalance = ParkingBalance + pay;
}

//it creates even nan transactions
//by design
int PaymentProcessor(Car * Vehicle, parking * parkingObject) {
	float transactionSum; 
	
	for (; ;) {

		this_thread::sleep_for(settings::GetTimeoutPayment());

		
		if (parkingObject->flagStopThread == true) {
			cout << "thread has been stopped - program end" << endl;
			return 1;
		}


		if (Vehicle->timerFlagStop == true) {
			cout << "thread has been stopped - remove car" << endl;
			delete Vehicle;
			return 1;
		};
		transactionSum = parkingObject->payment(Vehicle);
	/*
		cout << Vehicle->GetCarType() << "  " << Vehicle->GetCarNumber() << endl;
		cout << " Transaction sum is: " << transactionSum << endl;
		cout << " Parking balance now is: " << parkingObj->getParkingBalance() << endl;
		cout << "Car balance now is" << Vehicle->GetCarBalance() << endl;
		cout << endl;
		*/
		
		parkingObject->addTransaction(Vehicle, transactionSum);
	}
	return 1;
}

 void parking::addTransaction(Car * Vehicle, float transactionSum) {

	CTransaction * operation = new CTransaction(Vehicle->GetCarID(), transactionSum, Vehicle->GetCarNumber());
	while (!transactionLocker.try_lock());
	transactionList.insert(transactionList.end(), operation);
	transactionLocker.unlock();
}

 int parking::addCar(string Num, string Type, float Balance, thread * ptr) {

	 if (numberFreeParkingPlaces != 0) {
		 Car * Vehicle = new Car(Num, Type, Balance, ptr);
		 pair <string, Car *> node(Num, Vehicle);
		 carList.insert(carList.begin(), node);
		 numberFreeParkingPlaces--;
		 
		 //packaged_task<int()>task(bind(&parking::PaymentProcessor, this, Vehicle));

		 thread timer(PaymentProcessor, Vehicle, this);

		 //thread timer(task);
		 Vehicle->ptimer = &timer;
		 timer.detach();
		 return 1;
	 }
	 else return 0;
 }

 //1 ���� ������� ������
 //0 ���� ��������� ���������� ������� ������
 //2 ���� ��� ������
 int parking::removeCar(string carNum) {
	 
	 auto itr = carList.begin();
	 while (itr != carList.end()) {
		 if (itr->first == carNum) {
			 if (itr->second->GetCarBalance() > 0) {
				 cout << " Thread will be deleted " << endl;

				 itr->second->timerFlagStop = true;
				 carList.erase(itr);
				 return 1;
			 } else return 0;
		 }
		 else return 2;
		 itr++;
	 }
	 
 }

Car * parking::findCar(string carNumber, Car * carptr) {

	 auto itr = carList.begin();
	 while (itr != carList.end()) {
		 if (itr->first == carNumber) { 
			 carptr = itr->second;
			 return carptr; 
		 }
	 }
	 return 0;
 }

 void parking::writeLastTransactionsToFile() {
	 ofstream out;
	 list<CTransaction *>::iterator transactionPtrDecrement;
	 list<CTransaction *>::iterator lastMinuteEndPtr;
	 for (; ;) {
		 this_thread::sleep_for(settings::GetTimeoutTransactionWriting());


		 lastMinuteEndPtr = transactionPtrDecrement = transactionList.end();
		 if (flagStopThread == true) {
			cout << "writting has been stopped" << endl;
			return;
	 }
				if (transactionList.empty()) {
					continue;
				}
				transactionPtrDecrement--;
				out.open(settings::filepath, ios::app);
				while (transactionPtrDecrement != transactionList.begin()) {
					//cout << "Starting wrting to the file" << endl;
	
					char timepoint[70];
					asctime_s(timepoint, sizeof timepoint, gmtime((*transactionPtrDecrement)->getDate()));
						out << "System car ID: " << (*transactionPtrDecrement)->getCarId() << " || " << "Car Number: " << (*transactionPtrDecrement)->getCarNumber() << " || " <<
						"Sum : " << (*transactionPtrDecrement)->getTransactionSum() << " || " << "Date: " << timepoint << endl;

						transactionPtrDecrement--;

				}
				out.close();

				while (!transactionLocker.try_lock());
				transactionList.erase(transactionList.begin(), lastMinuteEndPtr);
				transactionLocker.unlock();
	 }
 }

 void parking::showTransactionLog() {
	 ifstream log;
	 string strholder;
	 log.open(settings::filepath, ios::in);
	 std::getline(log, strholder, '\0');
	 cout <<" this is transaction log " << endl;
	 cout << strholder << endl;
}

 float parking::getlastMinuteTransactionSum() {
	 float sum = 0;
	 list<CTransaction *>::iterator transactionPtrDecrement;

	 transactionPtrDecrement = transactionList.end();
	 if (transactionList.empty()) return sum = 0;
	 else transactionPtrDecrement--;
	 sum =+ (*transactionPtrDecrement)->getTransactionSum();
	 return sum;

 }

 void parking::showLastMinuteTransactions() {
	 list<CTransaction *>::iterator transactionPtrDecrement;
	 transactionPtrDecrement = transactionList.end();

	 if (!transactionList.empty()) {
		 transactionPtrDecrement--;
		 while (transactionPtrDecrement != transactionList.begin()) {
			 char timepoint[70];
			 asctime_s(timepoint, sizeof timepoint, gmtime((*transactionPtrDecrement)->getDate()));
			 cout << "System car ID: " << (*transactionPtrDecrement)->getCarId() << " || " << "Car Number: " << (*transactionPtrDecrement)->getCarNumber() << " || " <<
				 "Sum : " << (*transactionPtrDecrement)->getTransactionSum() << " || " << "Date: " << timepoint << endl;

			 transactionPtrDecrement--;
		 }

	 }
	 else cout << "There were no transactions during last minute " << endl;
 }

