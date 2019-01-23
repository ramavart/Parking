// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//попробовать гугл тесты
//разработать валидацию входящих значений
//реализовать таймер
//где генерировать время транзакции:
//1) При создании объекта транзакции
//2) Передавать в объект транзакции из функции float payment(Car Vehicle);

#include "pch.h"
#include "parking.h"
#include <iostream>
#include <thread>
#include <fstream>

using namespace std;


int main()
{
	
	parking & pointer = parking::instance();

	//проверка работы метода PaymentProcessor
	
	string c = "CN43908LN";
	string ctp = "CAR";
	float bal = 100.0;
	
	pointer.addCar(c, ctp, 100, 0);
	pointer.addCar("Cb48947GN", "BUS", 200, 0);

	//проверка удаления машин из списка парковки
	
	this_thread::sleep_for(chrono::seconds(30));
	pointer.showLastMinuteTransactions();
	pointer.removeCar("Cb48947GN");
	pointer.removeCar("CN43908LN");
	pointer.flagStopThread = true;

	//вывод из файла лога транзакций
	pointer.showTransactionLog();
	//pointer.removeCar("CN30892HT");

	/*
	//проверка инициализации инстанса парковки
	parking & pointer = parking::instance();
	cout<< pointer.getParkingBalance() << endl;

	//проверка метода payment
	string c = "CN43908LN";
	string ctp = "CAR";
	float bal = 100.0;
	Car Mazzerati(c, ctp, bal);
	cout << "Payment for this car is: " << pointer.payment(&Mazzerati) << endl;
	cout << "Parking balance before changes: " <<pointer.getParkingBalance() << endl;

	//проверка метода changeParkingBalance
	cout << "Parking balance was changed to the following value: "<< fixed << pointer.changeParkingBalance(&Mazzerati) << endl;
	cout << "Car Balance is: " << Mazzerati.GetCarBalance();
	*/

	/*
	Car BMW;
	cout << " BMW default initialization " << endl;
	cout << BMW.GetCarID()<<endl;
	cout << BMW.GetCarNumber() << endl;
	cout << BMW.GetCarType() << endl;
	cout << endl;

	string c = "CN43908LN";
	string ctp = "BUS";
	float bal = 16.0;
	Car Mercedes(c, ctp, bal);
	cout << " Mercedes inittilized " << endl;
	cout << Mercedes.GetCarID() << endl;
	cout << Mercedes.GetCarNumber() << endl;
	cout << Mercedes.GetCarType() << endl;
	cout << Mercedes.GetCarBalance() << endl;
	cout << endl;

	c = "BY85608TY";
	string CARTYPE = "TRUCK";
	Mercedes.SetCarBalance(20.0);
	Mercedes.SetCarNumber(c);//не поменяло значение
	Mercedes.SetCarType(CARTYPE);

	cout << " Mecedes after using set methods " << endl;
	cout << Mercedes.GetCarBalance() << endl;
	cout << Mercedes.GetCarID() << endl;
	cout << Mercedes.GetCarType() << endl;
	cout << Mercedes.GetCarNumber() << endl;
	cout << endl;*/

	/*

	//test for settings.h
	settings obj;
	cout << obj.GetParkingSpace() << endl;

	string cartype = "CAR";
	cout << obj.GetDictionaryValue(cartype) << endl;
	cout << obj.GetFine() << endl;

	cartype = "BUS";
	int price = 12;
	obj.SetDictionaryValue(cartype, price);
	cout << "New price " << obj.GetDictionaryValue(cartype) << endl;
	*/

	//pointer.~parking();
	system("pause");
	return 0;
};

