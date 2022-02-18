#ifndef ARDUINOCONTROLLER_H
#define ARDUINOCONTROLLER_H
using namespace std;
#include <wx/artprov.h> //get the bit map
#include <string>
#include "SerialPort.h"
using namespace std;

class ArduinoController
{
	string outputStr;
public:
	ArduinoController();
	ArduinoController(string outputStr, char* portName);

	string getText();
	
	void OpenArduino(char* portName);
	string ReadArduino(SerialPort* arduino, char* portName);
	void WriteArduino(SerialPort* arduino, char* portName, string command);
	string convertToString(char* a, int size);

};


#endif