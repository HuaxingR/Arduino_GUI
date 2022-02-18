#include "ArduinoController.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include "SerialPort.h"
using namespace std;


ArduinoController::ArduinoController() {
}
ArduinoController::ArduinoController(string outputstr, char* portName){
	this->outputStr = outputstr;
}

string ArduinoController::getText() {
	return outputStr;
}

void ArduinoController::OpenArduino(char* portName) {
		
		SerialPort arduino(portName);
		char reading[MAX_DATA_LENGTH];
		if (arduino.isConnected()) {
			outputStr = "Arduino is Connected!\n";

		}
		else {
			outputStr = "Arduino is disconnected!";
		}
}

string ArduinoController::ReadArduino(SerialPort* arduino, char* portName) {

	char* output = new char[MAX_DATA_LENGTH];
	int check_readByte = 0;
	check_readByte = arduino->readSerialPort(output, MAX_DATA_LENGTH);
	if (check_readByte == 0) { return ""; }
	string readOutput(output);
	return readOutput.substr(0, check_readByte);
}

void ArduinoController::WriteArduino(SerialPort* arduino, char* portName, string command) {
	
	char* charArray = new char[command.size()];
	//copy the command to the char array
	copy(command.begin(), command.end(), charArray);
	//write the command to arduino
	arduino->writeSerialPort(charArray, MAX_DATA_LENGTH);
	delete[] charArray;
}

string convertToString(char* a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}


