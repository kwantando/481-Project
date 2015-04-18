#include "Light_cont.h"
#include "Arduino_cont.h"
#include <iostream>
#include <unistd.h> 
#include <string>
using std::cout;
using std::endl;

Light_cont::Light_cont(const std::string &port)
{
	fd = serialport_init(port.c_str());
}

Light_cont::~Light_cont()
{
	close(fd);
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
	int ret_val = serialport_write(fd, &to_write, 1);
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
	int ret_val = serialport_write(fd, &to_write, 1);
	cout << ret_val << endl;
	return;
}
