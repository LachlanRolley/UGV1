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

	
	Galil myGalil(funcs, "192.168.0.120 -d");

	
	printf("galil setup\n");
	myGalil.DigitalOutput(0);

	Console::ReadKey();



	// DIGITAL OUTPUTS
	myGalil.DigitalOutput(252);
	Console::ReadKey();
	myGalil.DigitalByteOutput(true, 4);		// Write to one byte, either high or low byte, as specified by user in 'bank'
	Console::ReadKey();

	myGalil.DigitalBitOutput(true, 15);			// Write single bit to digital outputs. 'bit' specifies which bit
	Console::ReadKey();

	myGalil.DigitalOutput(5);

	// DIGITAL INPUTS
	uint16_t aa = myGalil.DigitalInput();				// Return the 16 bits of input data
	printf(" 16 bit digital input is %u\n",(unsigned)aa);
	Console::ReadKey();


	aa = myGalil.DigitalByteInput(false);	// Read either high or low byte, as specified by user in 'bank'
	printf(" low byte digital input is %u\n", (unsigned)aa);
	Console::ReadKey();
	
	
	if (myGalil.DigitalBitInput(3)) {
		printf(" bit 3 is 1\n");
	}// Read single bit from current digital inputs. Above functions
	else printf(" bit 3 is 0\n");
	Console::ReadKey();
	// 0 = low, 1 = high

	// Check the string response from the Galil to check that the last 
	if (myGalil.CheckSuccessfulWrite()) {
		printf("successful write\n");		// Read single bit from current digital inputs. Above functions
	}
	else printf("not successful write\n");
	Console::ReadKey();
	// command executed correctly. 1 = succesful. NOT AUTOMARKED







	// ANALOG FUNCITONS
	float b =  myGalil.AnalogInput(3);						// Read Analog channel and return voltage	
	printf("analoge inp 3 is %f\n",b);
	Console::ReadKey();
	myGalil.AnalogOutput(3, 5.00);		// Write to any channel of the Galil, send voltages as

	if (myGalil.CheckSuccessfulWrite()) printf("successful write channel 3 voltage should be 5\n");		// Read single bit from current digital inputs. Above functions
	else printf("not successful write\n");
	Console::ReadKey();

	float c = myGalil.AnalogInput(3);
	printf("analoge inp 3 is now %f\n", c);
	Console::ReadKey();// 2 decimal place in the command string
	
	void AnalogInputRange(uint8_t channel, uint8_t range);	// Configure the range of the input channel with
															// the desired range code

// ENCODER / CONTROL FUNCTIONS
	void WriteEncoder();								// Manually Set the encoder value to zero
	int ReadEncoder();									// Read from Encoder
	void setSetPoint(int s);							// Set the desired setpoint for control loops, counts or counts/sec
	void setKp(double gain);							// Set the proportional gain of the controller used in controlLoop()
	void setKi(double gain);							// Set the integral gain of the controller used in controlLoop()
	void setKd(double gain);							// Set the derivative gain of the controller used in controlLoop()
	void PositionControl(bool debug, int Motorchannel);	// Run the control loop. ReadEncoder() is the input to the loop. The motor is the output.
	
	
	//myGalil.WriteEncoder();
	//myGalil.setKp(5 / 3000.0);
	//myGalil.setKi(1 / 5000.0);
	//myGalil.setKd(0);
	//myGalil.setSetPoint(3000);


	Console::ReadKey();


	
	return 0;
}