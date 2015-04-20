#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define ARDUINO_WAIT_TIME 2000

// We took this code from a tutorial that shows how to interface
// with an Arduino serial on Windows.
// http://playground.arduino.cc/Interfacing/CPPWindows

class SerialClass {

private:
	//Serial comm handler
	HANDLE hSerial;
	//Connection status
	bool connected;
	//Get various information about the connection
	COMSTAT status;
	//Keep track of last error
	DWORD errors;

public:
	SerialClass(const char* portName);

	~SerialClass();

	bool WriteData(char *buffer, unsigned int nbChar);

	bool IsConnected();

};
