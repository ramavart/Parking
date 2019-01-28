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
//вынести пункты меню из цикла
void CInterface::showInterface(parking * parkingInstance) {
	char numberHolder[2];
	numberHolder[0] = 0;
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
				gets_s(numberHolder, 2);
				pointOfMenu = atoi(numberHolder);	
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


//перехват исключений выход за границы ??
void CInterface::addNewCar(parking * parkingInstance) {
	char carNumber[11];
	char moneyHolder[46];
	char carTypeHolder[2];
	int carTypeIndex = 0;
	string carType;
	float money = 0;
	for (int i = 0; i < sizeof(carNumber) / sizeof(char); i++) {
		carNumber[i] = '\0';
	}
	//реализовать тут валидацию значений
	//нельзя заполнять '\0'
	while (carNumber[0] == ' ' || carNumber[0] == '\0') {
		cout << "Please enter car Number" << endl;
		gets_s(carNumber, 11);
	}
	
	//сравнить с лимитом на меньше!!!!
	while (money <= 0 || money > numeric_limits<float>::max()) {
		cout << "How much money would you like to put on the car balance?" << endl;
		gets_s(moneyHolder, 46);
		money = atof(moneyHolder);
	}


	cout << "What is the type of your car?" << endl;

	cout << "Please enter the number the corresponds to the type of your car" << endl;
	cout << "1. Car" << endl;
	cout << "2. Bus" << endl;
	cout << "3. Truck" << endl;
	cout << "4. Motorcycle" << endl;

	while (carTypeIndex < 1 || carTypeIndex > 4) {
		cout << "The number should be between 1 and 4 including" << endl;
			gets_s(carTypeHolder,2);
			carTypeIndex = atoi(carTypeHolder);
			cout << carTypeIndex << endl;
	}

	switch (carTypeIndex)
	{
	case 1: carType = "CAR"; break;
	case 2: carType = "BUS"; break;
	case 3: carType = "TRUCK"; break;
	case 4: carType = "MOTORCYCLE"; break;
	default:
		break;
	}

	parkingInstance->addCar(carNumber,carType, money, 0);
}

void CInterface::fillUpCarBalance(parking * parkingInstance) {

	char carNumberHolder[11];
	string carNumber;
	Car * carptr = 0;
	char money[47];
	float paysum;
	for (int i = 0; i < sizeof(carNumberHolder) / sizeof(char); i++)
	{
		carNumberHolder[i] = ' ';
	}

	for (;;) {
			cout << "Please enter car Valid Number" << endl;
		gets_s(carNumberHolder, 11);
		carNumber = carNumberHolder;
		cout << carNumber << endl;
		if (carptr = parkingInstance->findCar(carNumber, carptr)) break;
	}
	
	for (; ;) {
		cout << "Please enter a sum which you would like to put on your car balance" << endl;
		cout << "The payment should  be less than" << fixed << numeric_limits<float>::max() << " and more than zero" << endl;
		gets_s(money, 47);
		paysum = atof(money);
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
	char carNumberHolder[11];
	string carNumber;
	Car * carptr = 0;

	for (int i = 0; i < sizeof(carNumberHolder) / sizeof(char); i++)
	{
		carNumberHolder [i] = ' ';
	}

	for (;;) {
		cout << "Please enter car Valid Number" << endl;
		gets_s(carNumberHolder, 11);
		carNumber = carNumberHolder;

		if (parkingInstance->removeCar(carNumber)) { 
			cout << "Car has been removed" << endl;
			return; 
		}
		else if(parkingInstance->removeCar(carNumber) == 0){
			cout << "Please fill up car balance" << endl;
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