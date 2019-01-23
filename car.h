#pragma once
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <atomic> 

using namespace std;
//написать метод который будет автоматически деньги на счет парковки при пополнении минусового баланса
class Car
{
public:
	Car( string CNum = "", string CType = "0/", float CBalance = 0.0, thread * ptr = 0) :
		CarNumber(CNum), CarType(CType), Balance(CBalance), timerFlagStop(false) {
		Count++;
		id = Count;
	};
	~Car() {};
	int GetCarID() { return id; };
	string GetCarNumber() { return CarNumber; };
	void SetCarNumber(string value) { CarNumber = value; };
	string GetCarType() { return CarType; };
	void SetCarType(string type) { CarType = type; };
	float GetCarBalance() { return Balance; };
	void SetCarBalance(float value);

	static int Count;
	thread * ptimer;
	atomic<bool> timerFlagStop;

private:
	int id;
	string CarNumber;
	string CarType;
	float Balance;
};