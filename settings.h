#pragma once
#include <map>
#include <string>
#include <chrono>
using namespace std;

class settings
{
public:
	
	//should it be better do remove set methods?
	//static void SetParkingSpace(int value) { ParkingSpace = value; };
	static int GetParkingSpace() { return ParkingSpace; };
	//static void SetFine(float finevalue) { Fine = finevalue; };
	static float GetFine() { return Fine; };
	//static void SetDictionaryValue(string key, float value);
	static float GetDictionaryValue(string key);
	static chrono::seconds GetTimeoutPayment();
	static chrono::seconds GetTimeoutTransactionWriting();
	static string filepath;
	//static int GetTimoutSeconds() { return timeoutSeconds; };
	//static void SetTimeoutSeconds(int time) { timeoutSeconds = time; }

protected:
	settings() {};
	~settings() {};
	static int ParkingSpace;
	static float Fine;
	static map <string, float> Dictionary;
	//static int timeoutSeconds;
	static chrono::duration<long long> timeoutPayment;
	static chrono::seconds timeoutTransactionWriting;
};


