#include "pch.h"
#include "car.h"

using namespace std;

int Car::Count = 0;

void Car::SetCarBalance(float value) { 

	if (value > 0.0 && Balance > 0.0) {

	}
		Balance += value;
};


