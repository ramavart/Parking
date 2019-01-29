#include "pch.h"
#include "CInterface.h"

using namespace std;

CInterface::CInterface()
{
}


CInterface::~CInterface()
{
}

//так же необходимо предусмотреть функции выхода в меню
//из любой части интерфейса
void CInterface::showInterface(parking * parkingInstance) {

	string numberHolder;
	int pointOfMenu = 0;
	for (;;) {
		
			cout << "==========  Menu  ==========" << endl;
			cout << "1. Registrate new car on parking" << endl;
			cout << "2. Fill up car balance" << endl;
			cout << "3. Remove car" << endl;
			cout << "4. Show last minute transactions" << endl;
			cout << "5. Show last minute parking revenue" << endl;
			cout << "6. Show parking revenue" << endl;
			cout << "7. Show number of free parking spaces" << endl;
			cout << "8. Show transaction Log" << endl;
			
			while(pointOfMenu < 1 || pointOfMenu > 8){
				cout << "Please choose the action you need and enter the proper number between 1 and 8"<<endl;
				getline(cin, numberHolder);
				pointOfMenu = atoi(numberHolder.c_str());
			}
		
		switch (pointOfMenu)
		{
		case 1: addNewCar(parkingInstance); pointOfMenu = 0; break;
		case 2: fillUpCarBalance(parkingInstance); pointOfMenu = 0; break;
		case 3: removeCar(parkingInstance); pointOfMenu = 0; break;
		case 4: showLastMinuteTransaction(parkingInstance); pointOfMenu = 0; break;
		case 5: showLastMinuteParkingRevenue(parkingInstance); pointOfMenu = 0; break;
		case 6: showParkingRevenue(parkingInstance); pointOfMenu = 0; break;
		case 7: showNumberFreePlaces(parkingInstance); pointOfMenu = 0; break;
		case 8: showTransactionLog(parkingInstance); pointOfMenu = 0; break;
		}
	}
}


void CInterface::addNewCar(parking * parkingInstance) {

	string carNumber;
	string moneyHolder;
	string carTypeHolder;
	int carTypeIndex = 0;
	string carType;
	float money = 0;

	while (carNumber[0] == ' ' || carNumber[0] == '\0') {
		cout << "Please enter car Number" << endl;
		getline(cin, carNumber);
	}
	
	while (money <= 0 || money > numeric_limits<float>::max()) {
		cout << "How much money would you like to put on the car balance?" << endl;
		getline(cin, moneyHolder);
		money = atof(moneyHolder.c_str());
	}

	cout << "What is the type of your car?" << endl;
	cout << "Please enter the number the corresponds to the type of your car" << endl;
	cout << "1. Car" << endl;
	cout << "2. Bus" << endl;
	cout << "3. Truck" << endl;
	cout << "4. Motorcycle" << endl;

	while (carTypeIndex < 1 || carTypeIndex > 4) {
		cout << "The number should be between 1 and 4 including" << endl;
			getline(cin, carTypeHolder);
			carTypeIndex = atoi(carTypeHolder.c_str());
			cout << carTypeIndex << endl;
	}

	switch (carTypeIndex)
	{
	case 1: carType = "CAR"; break;
	case 2: carType = "BUS"; break;
	case 3: carType = "TRUCK"; break;
	case 4: carType = "MOTORCYCLE"; break;
	}

	parkingInstance->addCar(carNumber,carType, money, 0);
}

void CInterface::fillUpCarBalance(parking * parkingInstance) {

	string carNumber;
	Car * carptr = 0;
	string money;
	float paysum;

	for (;;) {
			cout << "Please enter car Valid Number" << endl;
		getline(cin,carNumber);
		cout << carNumber << endl;
		if (carptr = parkingInstance->findCar(carNumber, carptr)) break;
	}
	
	for (; ;) {
		cout << "Please enter a sum which you would like to put on your car balance" << endl;
		cout << "The payment should  be less than" << fixed << numeric_limits<float>::max() << " and more than zero" << endl;
		getline(cin , money);
		paysum = atof(money.c_str());
		if (paysum > 0) {
			if (paysum <=  numeric_limits<float>::max() ) {
				carptr->SetCarBalance(paysum);
				cout << "Payment successfly apply" << endl;
				break;
			}
		}
	}
}


void CInterface::removeCar(parking * parkingInstance) {
	string carNumber;
	Car * carptr = 0;

	for (;;) {
		cout << "Please enter car Valid Number" << endl;
		getline(cin, carNumber);

		if (parkingInstance->removeCar(carNumber)) { 
			cout << "Car has been removed" << endl;
			return; 
		}
		else if(parkingInstance->removeCar(carNumber) == 0){
			cout << "Please fill up car balance" << endl;
			break;
		}
		else break;
	}
}

void CInterface::showLastMinuteTransaction(parking * parkingInstance) {
	parkingInstance->showLastMinuteTransactions();
}

void CInterface::showLastMinuteParkingRevenue(parking * parkingInstance) {
	cout << "Parking revenue for the last minute: " << -1 * parkingInstance->getlastMinuteTransactionSum() << endl;
}

void CInterface::showTransactionLog(parking * parkingInstance) {
	parkingInstance->showTransactionLog();
}

void CInterface::showNumberFreePlaces(parking * parkingInstance) {
	cout << "There were left: " <<  parkingInstance->getNumberFreeParkingPlaces() << " free parking places" << endl;
}

void CInterface::showParkingRevenue(parking * parkingInstance) {
	cout << "Parking revenue now is: " << parkingInstance->getParkingBalance() << endl;
}