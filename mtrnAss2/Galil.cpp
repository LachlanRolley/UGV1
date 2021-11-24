#include "Galil.h";
#include <stdint.h>
#include<stdio.h>
#include "EmbeddedFunctions.h"
#include <string>
#include <iostream>
#include <chrono>
#include <Windows.h>



//constructors 
Galil::Galil() {// Default constructor. Initialize variables, open Galil connection and allocate memory. NOT AUTOMARKED
	EmbeddedFunctions* Functions = new EmbeddedFunctions;	// Pointer to EmbeddedFunctions, through which all Galil Function calls will be made
	GCon g;							// Connection handle for the Galil, passed through most Galil function calls
	char ReadBuffer[1024];			// Buffer to restore responses from the Galil
	double ControlParameters[3];	// Contains the controller gain values: K_p, K_i, K_d in that order 
	int setPoint;
	GCStringIn addy = "192.168.0.120";

	GReturn a = Functions->GOpen(addy, &g);     // AIGHT so here g is just gona be an int but whenever u use this int, its gona refer to this connection we set up
}
Galil::Galil(EmbeddedFunctions* Funcs, GCStringIn address) {
	EmbeddedFunctions* Functions = Funcs;	// Pointer to EmbeddedFunctions, through which all Galil Function calls will be made
	GCon g;							// Connection handle for the Galil, passed through most Galil function calls
	char ReadBuffer[1024];			// Buffer to restore responses from the Galil
	double ControlParameters[3];	// Contains the controller gain values: K_p, K_i, K_d in that order 
	int setPoint;
	

	GReturn a = Functions->GOpen(address, &g);     // AIGHT so here g is just gona be an int but whenever u use this int, its gona refer to this connection we set up
	if (a == 0) {
		printf("yo its not working bruh, couldnt connect\n");
		printf("yo its not working bruh, couldnt connect\n");
	}
}


//destuctors
Galil::~Galil() {
	Functions->GClose(g);
}


											
// DIGITAL OUTPUTS
						// Write to all 16 bits of digital output, 1 command to the Galil
void Galil::DigitalOutput(uint16_t a) {

}
void Galil::DigitalByteOutput(bool bank, uint8_t value) {// Write to one byte, either high or low byte, as specified by user in 'bank'
	
}												// 0 = low, 1 = high
void Galil::DigitalBitOutput(bool val, uint8_t bit) {			// Write single bit to digital outputs. 'bit' specifies which bit

}

// DIGITAL INPUTS
uint16_t Galil::DigitalInput() {				// Return the 16 bits of input data

}											// Query the digital inputs of the GALIL, See Galil command library @IN
uint8_t Galil::DigitalByteInput(bool bank) {	// Read either high or low byte, as specified by user in 'bank'
										// 0 = low, 1 = high
}
bool Galil::DigitalBitInput(uint8_t bit) {		// Read single bit from current digital inputs. Above functions
										// may use this function
}
bool Galil::CheckSuccessfulWrite() {	// Check the string response from the Galil to check that the last 
								// command executed correctly. 1 = succesful. NOT AUTOMARKED
}

// ANALOG FUNCITONS
float Galil::AnalogInput(uint8_t channel) {						// Read Analog channel and return voltage	
}
void Galil::AnalogOutput(uint8_t channel, double voltage) {		// Write to any channel of the Galil, send voltages as
														// 2 decimal place in the command string
}
void AnalogInputRange(uint8_t channel, uint8_t range) {	// Configure the range of the input channel with
														// the desired range code
}

// ENCODER / CONTROL FUNCTIONS
void Galil::WriteEncoder() {								// Manually Set the encoder value to zero
}
int Galil::ReadEncoder() {									// Read from Encoder
}
void Galil::setSetPoint(int s) {							// Set the desired setpoint for control loops, counts or counts/sec
}
void Galil::setKp(double gain) {							// Set the proportional gain of the controller used in controlLoop()
}
void Galil::setKi(double gain) {							// Set the integral gain of the controller used in controlLoop()
}
void Galil::setKd(double gain) {							// Set the derivative gain of the controller used in controlLoop()
}
void Galil::PositionControl(bool debug, int Motorchannel) {	// Run the control loop. ReadEncoder() is the input to the loop. The motor is the output.
													// The loop will run using the PID values specified in the data of this object, and has an 
													// automatic timeout of 10s. You do not need to implement this function, it is defined in
													// GalilControl.lib
}
void Galil::SpeedControl(bool debug, int Motorchannel) {	// same as above. Setpoint interpreted as counts per second
}


// Operator overload for '<<' operator. So the user can say cout << Galil; This function should print out the
// output of GInfo and GVersion, with two newLines after each.
std::ostream& operator<<(std::ostream& output, Galil& galil) {

}