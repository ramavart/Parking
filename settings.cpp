#include "pch.h"
#include "settings.h"

int	settings::ParkingSpace = 80;
float settings::Fine = 1.5;
map	<string, int> settings::Dictionary = { {"CAR", 3}, {"MOTORCYCLE",1}, {"BUS", 5}, {"TRUCK", 10} };
int timeoutSeconds = 3;

int settings::GetDictionaryValue(string key) {
	return Dictionary[key];
}

void settings::SetDictionaryValue(string key, int value) {
	Dictionary[key] = value;
}