#include "Galil.h";
#include <stdint.h>
#include<stdio.h>
#include "EmbeddedFunctions.h"
#include <string.h>
#include <iostream>
#include <chrono>
#include <Windows.h>
#include <stdlib.h>





//CONSTRUCTORS DONE
Galil::Galil() {// Default constructor. Initialize variables, open Galil connection and allocate memory. NOT AUTOMARKED
	Functions = new EmbeddedFunctions;	// Pointer to EmbeddedFunctions, through which all Galil Function calls will be made						// Connection handle for the Galil, passed through most Galil function call
	GCStringIn addy = "192.168.0.120 -d"; // d for dirrect
	g = 0;

	GReturn a = Functions->GOpen(addy, &g);     // AIGHT so here g is just gona be an int but whenever u use this int, its gona refer to this connection we set up
	if (g == 0) {
		printf("yo its not working bruh, couldnt connect\n");
		printf("yo its not working bruh, couldnt connect\n");
	}
}
Galil::Galil(EmbeddedFunctions* Funcs, GCStringIn address) {
	Functions = Funcs;	// Pointer to EmbeddedFunctions, through which all Galil Function calls will be made
	g = 0;
						// Connection handle for the Galil, passed through most Galil function call
	GReturn a = Functions->GOpen(address, &g);     // AIGHT so here g is just gona be an int but whenever u use this int, its gona refer to this connection we set up
	if (g == 0) {
		printf("yo its not working bruh, couldnt connect\n");
		printf("yo its not working bruh, couldnt connect\n");
	}
}

//DESTRUCTORS  DONE
Galil::~Galil() {
	Functions->GClose(g);
}

//WRITE TO GALIL
void Galil::sendGalil(){
	/*int a = (int)g;
	printf("g is %d\n",a);
	printf("the command string is %s\n", Command);

	printf("the address of g is %p\n", &g);
	printf("the address of Command is %p\n", &Command);
	printf("the address of ReadBuffer is %p\n", &ReadBuffer);
	printf("the address of NumRet is %p\n", &NumRet);*/

	Functions->GCommand(g, Command, ReadBuffer, sizeof(ReadBuffer), &NumRet);
	//Then should check it actually worked but cbs atm
}
											
//DIGITAL OUTPUTS DONE								
void Galil::DigitalOutput(uint16_t a) { // Write to all 16 bits of digital output, 1 command to the Galil
	// this one we want 2 8bit ints, seperated 
	uint8_t lowB = a;
	uint16_t highb = a >> 8;
	//printf("lowb is %d, highb is %d\n", lowB, highb);
	sprintf_s(Command, sizeof(Command), "OP %d,%d;", lowB, highb);
	sendGalil();
	
}
void Galil::DigitalByteOutput(bool bank, uint8_t value) {// Write to one byte, either high or low byte, as specified by user in 'bank'
	if (bank) {// means we write to the high byte
		sprintf_s(Command, sizeof(Command), "OP 0,%d;", value);
	}
	else {
		sprintf_s(Command, sizeof(Command), "OP %d,0;", value);
	}
	sendGalil();
}												// 0 = low, 1 = high
void Galil::DigitalBitOutput(bool val, uint8_t bit) {			// Write single bit to digital outputs. 'bit' specifies which bit
	sprintf_s(Command, sizeof(Command), "OB %d,%d;", bit, val);
	sendGalil();
}


//DIGITAL INPUTS 
uint16_t Galil::DigitalInput() {				// Return the 16 bits of input data
	//gona have to go 1 by one with MG @in[%d]
	
	uint16_t final = 0;
	uint16_t lowB = DigitalByteInput(0);
	uint16_t highB = DigitalByteInput(1) << 8;
	printf("lowb is %d, highb is %d\n", lowB, highB);
	final = lowB | highB;


	return final;
}											// Query the digital inputs of the GALIL, See Galil command library @IN
uint8_t Galil::DigitalByteInput(bool bank) {	// Read either high or low byte, as specified by user in 'bank'
													// 0 = low, 1 = high				
	uint8_t finNum = 0;
	uint8_t mask = 0;
	uint8_t offset = 0;
	if (bank) offset = 8;

	for (uint8_t i = 0; i < 8; i++) {
		//look through bits, if is 1, put it on a mask and || with final
		if (DigitalBitInput(i + offset)) {
			mask = 1 << i;
		}

		finNum = mask | finNum; 
	}

	return finNum;
}
bool Galil::DigitalBitInput(uint8_t bit) {		// Read single bit from current digital inputs. Above functions
										// may use this function
	//gona have to go 1 by one with MG @in[%d]
	sprintf_s(Command, sizeof(Command), "MG @IN[%d];", bit);
	sendGalil();
	//aight here we will have a value in ReadBuffer, so we wana string compare if its 1.0000 or 0.0000
	
	//char oneString[1024] = "1.0000";  // might wana try ReadBuffer[0] == 1
	//printf("Readbuffer[0], [1] is %d, %d\n", ReadBuffer[0], ReadBuffer[1]);
	if (ReadBuffer[1] == 49) {
		return true;
	}
	return false;
}
bool Galil::CheckSuccessfulWrite() {	// Check the string response from the Galil to check that the last 
								// command executed correctly. 1 = succesful. NOT AUTOMARKED
	//write always returns a ":"
	if (NumRet > 1)return true;
	if (ReadBuffer[0] == ':') return true;
	return false;
}


// ANALOG FUNCITONS DONE
float Galil::AnalogInput(uint8_t channel) {						// Read Analog channel and return voltage	
	float final = 0;
	
	sprintf_s(Command, sizeof(Command), "MG @AN[%d];", channel);
	sendGalil();
	
	final = atof(ReadBuffer);  // mby need to use strtof
	
	return final;
}
void Galil::AnalogOutput(uint8_t channel, double voltage) {		// Write to any channel of the Galil, send voltages as
														// 2 decimal place in the command string
	sprintf_s(Command, sizeof(Command), "AO %d, %f;", channel, voltage);
	sendGalil();

}
void Galil::AnalogInputRange(uint8_t channel, uint8_t range) {	// Configure the range of the input channel with
														// the desired range code
	//heaps confused but it looks like u write the channel u want and for range, theres specific codes, (1 == +-5v,  2== +-10v.......)
	sprintf_s(Command, sizeof(Command), "AQ %d, %d;", channel, range);
	sendGalil();
}












// ENCODER / CONTROL FUNCTIONS
void Galil::WriteEncoder() {								// Manually Set the encoder value to zero
	//No clue what this shit does
	sprintf_s(Command, sizeof(Command), "WE %d, %d;", 0, 0);
	sendGalil();
}
int Galil::ReadEncoder() {									// Read from Encoder

	int a = 0;
	//if you dont say which channel, both get spat out so lets just go with 0
	sprintf_s(Command, sizeof(Command), "QE 0;");
	sendGalil();
	a = atoi(ReadBuffer);

	return a;
}
void Galil::setSetPoint(int s) {							// Set the desired setpoint for control loops, counts or counts/sec
	setPoint = s;
}
void Galil::setKp(double gain) {							// Set the proportional gain of the controller used in controlLoop()
	ControlParameters[0] = gain;
}
void Galil::setKi(double gain) {							// Set the integral gain of the controller used in controlLoop()
	ControlParameters[1] = gain;
}
void Galil::setKd(double gain) {							// Set the derivative gain of the controller used in controlLoop()
	ControlParameters[2] = gain;
	
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