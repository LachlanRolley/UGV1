#include <stdlib.h>
#include <Galil.h>
#include <gclibo.h>
#include <gclib_errors.h>
#include <gclib_record.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;



int main(void) {
	EmbeddedFunctions* funcs = new EmbeddedFunctions();
	// addy = "192.168.0.120 -d"

	printf("wadup\n");
	printf("wadup\n");
	Galil myGalil(funcs, "192.168.0.120 -d");

	printf("galil setup\n");
	printf("galil setup\n");

	

	myGalil.DigitalOutput(8);
	//myGalil.WriteEncoder();
	//myGalil.setKp(5 / 3000.0);
	//myGalil.setKi(1 / 5000.0);
	//myGalil.setKd(0);

	//myGalil.setSetPoint(3000);

	while (!kbhit()) {
		//printf("i think shes working");
	}
	return 0;
}