#include "Light_cont.h"
#include <iostream>
#include <string>

#ifndef _WIN32
#include <unistd.h> 
#include "Arduino_cont.h"
#endif

#ifdef _WIN32
#include "SerialClass.h"
#endif

using std::cout;
using std::endl;
using std::string;

#ifndef _WIN32

Light_cont::Light_cont(const std::string &port)
{
	fd = serialport_init(port.c_str());
}

#else

Light_cont::Light_cont(const std::string &port) {
	serialcomm = new SerialClass(port.c_str());
}

#endif


Light_cont::~Light_cont()
{
	for(int i = 1; i <= 6; i++) {
		deactivate(i);
	}
#ifndef _WIN32
	close(fd);
#else
	delete serialcomm;
#endif
}

void Light_cont::activate(int pad)
{
	char to_write = 'a';
	switch(pad){
		case 1:
			to_write = 'a';
			break;
		case 2:
			to_write = 'b';
			break;
		case 3:
			to_write = 'c';
			break;
		case 4:
			to_write = 'd';
			break;
		case 5:
			to_write = 'e';
			break;
		case 6:
			to_write = 'f';
			break;
		default:
			return;
	}
#ifdef _WIN32
	char* buf = new char[2];
	buf[0] = to_write;
	buf[1] = '\0';
	int ret_val = serialcomm->WriteData(buf, 1);
	delete buf;
#else
	int ret_val = serialport_write(fd, &to_write, 1);
#endif
	cout << ret_val << endl;
	return;
}

void Light_cont::deactivate(int pad)
{
	char to_write = 'A';
	switch(pad){
		case 1:
			to_write = 'A';
			break;
		case 2:
			to_write = 'B';
			break;
		case 3:
			to_write = 'C';
			break;
		case 4:
			to_write = 'D';
			break;
		case 5:
			to_write = 'E';
			break;
		case 6:
			to_write = 'F';
			break;
		default:
			return;
	}

#ifdef _WIN32
	char* buf = new char[2];
	buf[0] = to_write;
	buf[1] = '\0';
	int ret_val = serialcomm->WriteData(buf, 1);
	delete buf;
#else
	int ret_val = serialport_write(fd, &to_write, 1);
#endif
	cout << ret_val << endl;
	return;
}
