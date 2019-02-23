#include "pch.h"
#include "settings.h"

int	settings::ParkingSpace = 80;
float settings::Fine = 1.5;
map	<string, float> settings::Dictionary = { {"CAR", 3.0}, {"MOTORCYCLE",1.0}, {"BUS", 5.0}, {"TRUCK", 10.0} };
chrono::seconds settings::timeoutPayment(3);
chrono::seconds settings::timeoutTransactionWriting(20);
string settings::filepath = "E:\\Transaction.log";

chrono::seconds settings::GetTimeoutPayment() {
	return timeoutPayment;
}
chrono::seconds settings::GetTimeoutTransactionWriting() {
	return timeoutTransactionWriting;
}

float settings::GetDictionaryValue(string key) {
	return Dictionary[key];
}

/*
void settings::SetDictionaryValue(string key, float value) {
	Dictionary[key] = value;
}*/