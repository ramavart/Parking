//#pragma once
#include <map>
#include <string>
using namespace std;

// Прототип
//Для конечной версии необходимо организовать инициализацию полей из файла
//реализовать свойство тайм-аут

class settings
{
public:
	settings() {};
	~settings() {};//удаляет мапу, реализовать
	static void SetParkingSpace(int value) { ParkingSpace = value; };
	static int GetParkingSpace() { return ParkingSpace; };
	static void SetFine(float finevalue) { Fine = finevalue; };
	static float GetFine() { return Fine; };
	static void SetDictionaryValue(string key, int value);
	static int GetDictionaryValue(string key);
	static int GetTimoutSeconds() { return timeoutSeconds; };
	static void SetTimeoutSeconds(int time) { timeoutSeconds = time; }

protected:
	static int ParkingSpace;
	static float Fine;
	static map <string, int> Dictionary;
	static int timeoutSeconds;
	//static chrono::duration<long long> timeoutSeconds;
	//static chrono::
};


