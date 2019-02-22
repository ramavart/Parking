#pragma once

//класс должен реализовывать валидацию данных, согласно сигнатуре соответствующих методов
#include <iostream>
#include "parking.h"
class CInterface
{
public:
	CInterface();
	~CInterface();
	void showInterface(parking * object);
	void addNewCar(parking * parkingInstance);
	void fillUpCarBalance(parking * parkingInsatance);
	void removeCar(parking * parkingInstance);
	void showLastMinuteTransaction(parking * parkingInstance);
	void showTransactionLog(parking * parkingInstance);
	void showNumberFreePlaces(parking * parkingInstance);
	void showParkingRevenue(parking * parkingInstance);
	void showLastMinuteParkingRevenue(parking * parkingInstance);
	void programEnd(parking * parkingInstance);
};

