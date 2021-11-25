#include "Galil.h";
#include <stdint.h>
#include<stdio.h>
#include "EmbeddedFunctions.h"
#include <string>
#include <iostream>
#include <chrono>
#include <Windows.h>





//constructors DONE
Galil::Galil() {// Default constructor. Initialize variables, open Galil connection and allocate memory. NOT AUTOMARKED
	Functions = new EmbeddedFunctions;	// Pointer to EmbeddedFunctions, through which all Galil Function calls will be made						// Connection handle for the Galil, passed through most Galil function call
	GCStringIn addy = "192.168.0.120 -d"; // d for dirrect
	g = 0;

	GReturn a = Functions->GOpen(addy, &g);     // AIGHT so here g is just gona be an int but whenever u use this int, its gona refer to this connection we set up
	if (a == 0) {
		printf("yo its not working bruh, couldnt connect\n");
		printf("yo its not working bruh, couldnt connect\n");
	}
}
Galil::Galil(EmbeddedFunctions* Funcs, GCStringIn address) {
	Functions = Funcs;	// Pointer to EmbeddedFunctions, through which all Galil Function calls will be made
	g = 0;
						// Connection handle for the Galil, passed through most Galil function call
	GReturn a = Functions->GOpen(address, &g);     // AIGHT so here g is just gona be an int but whenever u use this int, its gona refer to this connection we set up
	if (a == 0) {
		printf("yo its not working bruh, couldnt connect\n");
		printf("yo its not working bruh, couldnt connect\n");
	}
}

//destuctors  DONE
Galil::~Galil() {
	Functions->GClose(g);
}

// overall write to galil
void Galil::sendGalil(){

	Functions->GCommand(g, Command, ReadBuffer, sizeof(ReadBuffer), &NumRet);
	//Then should check it actually worked but cbs atm
}
											
// DIGITAL OUTPUTS DONE
										
void Galil::DigitalOutput(uint16_t a) { // Write to all 16 bits of digital output, 1 command to the Galil
	// this one we want 2 8bit ints, seperated 
	uint8_t lowB = a;
	uint8_t highb = a >> 8;
	sprintf_s(Command, sizeof(Command), "OP %d,%d:", lowB, highb);
	sendGalil();
	
}
void Galil::DigitalByteOutput(bool bank, uint8_t value) {// Write to one byte, either high or low byte, as specified by user in 'bank'
	if (bank) {// means we write to the high byte
		sprintf_s(Command, sizeof(Command), "OP 0,%d:", value);
	}
	else {
		sprintf_s(Command, sizeof(Command), "OP %d,0:", value);
	}
	sendGalil();
}												// 0 = low, 1 = high
void Galil::DigitalBitOutput(bool val, uint8_t bit) {			// Write single bit to digital outputs. 'bit' specifies which bit
	sprintf_s(Command, sizeof(Command), "OB %d,%d:", bit, val);
	sendGalil();
}


// DIGITAL INPUTS
uint16_t Galil::DigitalInput() {				// Return the 16 bits of input data
	
	
	
	uint16_t a = 5;
	return a;
}											// Query the digital inputs of the GALIL, See Galil command library @IN
uint8_t Galil::DigitalByteInput(bool bank) {	// Read either high or low byte, as specified by user in 'bank'
										// 0 = low, 1 = high
	

	uint8_t a = 5;
	return a;
}
bool Galil::DigitalBitInput(uint8_t bit) {		// Read single bit from current digital inputs. Above functions
										// may use this function

	return true;
}
bool Galil::CheckSuccessfulWrite() {	// Check the string response from the Galil to check that the last 
								// command executed correctly. 1 = succesful. NOT AUTOMARKED

	return true;
}

// ANALOG FUNCITONS
float Galil::AnalogInput(uint8_t channel) {						// Read Analog channel and return voltage	

	float a = 5;
	return a;
}
void Galil::AnalogOutput(uint8_t channel, double voltage) {		// Write to any channel of the Galil, send voltages as
														// 2 decimal place in the command string
}
void Galil::AnalogInputRange(uint8_t channel, uint8_t range) {	// Configure the range of the input channel with
														// the desired range code
}

// ENCODER / CONTROL FUNCTIONS
void Galil::WriteEncoder() {								// Manually Set the encoder value to zero
}
int Galil::ReadEncoder() {									// Read from Encoder

	int a = 5;
	return a;
}
void Galil::setSetPoint(int s) {							// Set the desired setpoint for control loops, counts or counts/sec
}
void Galil::setKp(double gain) {							// Set the proportional gain of the controller used in controlLoop()
}
void Galil::setKi(double gain) {							// Set the integral gain of the controller used in controlLoop()
}
void Galil::setKd(double gain) {							// Set the derivative gain of the controller used in controlLoop()
}
//void Galil::PositionControl(bool debug, int Motorchannel) {	// Run the control loop. ReadEncoder() is the input to the loop. The motor is the output.
													// The loop will run using the PID values specified in the data of this object, and has an 
													// automatic timeout of 10s. You do not need to implement this function, it is defined in
													// GalilControl.lib
//}
//void Galil::SpeedControl(bool debug, int Motorchannel) {	// same as above. Setpoint interpreted as counts per second
//}


// Operator overload for '<<' operator. So the user can say cout << Galil; This function should print out the
// output of GInfo and GVersion, with two newLines after each.
//std::ostream& operator<<(std::ostream& output, Galil& galil) {

//}