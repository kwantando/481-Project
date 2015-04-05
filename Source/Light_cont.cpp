#include "Light_cont.h"
#include <string>

/* Derek's Machine, for example
/  /dev/cu.usbmodemfd121
/  /dev/tty.usbmodemfd121 ** use tty port
*/

Light_cont::Light_cont(std::string port)
{
	file = fopen(port.c_str(),"w");
}

Light_cont::~Light_cont()
{
	fclose(file);
}

void Light_cont::activate(int pad_a_f)
{
	switch(pad_a_f){
		case '1':
			fprintf(file, "a");
		case '2':
			fprintf(file, "b");
		case '3':
			fprintf(file, "c");
		case '4':
			fprintf(file, "d");
		case '5':
			fprintf(file, "e");
		case '6':
			fprintf(file, "f");
		default:
			return;
	}
	return;
}

void Light_cont::deactivate(int pad_a_f)
{
		switch(pad_a_f){
		case '1':
			fprintf(file, "A");
		case '2':
			fprintf(file, "B");
		case '3':
			fprintf(file, "C");
		case '4':
			fprintf(file, "D");
		case '5':
			fprintf(file, "E");
		case '6':
			fprintf(file, "F");
		default:
			return;
	}
	return;
}
