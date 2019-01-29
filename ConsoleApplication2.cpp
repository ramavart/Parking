//попробовать гугл тесты

#include "pch.h"
#include "parking.h"
#include "CInterface.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <stdio.h>


using namespace std;


int main()
{	
	parking * pointer = &parking::instance();
	CInterface programInterface;
	programInterface.showInterface(pointer);
	
	system("pause");
	return 0;
};

