#include "Light_cont.h"
#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h> 
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>
#include "Arduino_cont.h"
#include <string>

/* Derek's Machine, for example
/  /dev/cu.usbmodemfd121
/  /dev/tty.usbmodemfd121 ** use tty port
*/

Light_cont::Light_cont(std::string port)
{
	int baud = B9600;
	fd = serialport_init("/dev/cu.usbmodemfd121", baud);
}

Light_cont::~Light_cont()
{
	close(fd);
}

void Light_cont::activate(int pad_a_f)
{
	char to_write = 'a';
	switch(pad_a_f){
		case 1:
			to_write = 'a';
			//fprintf(file, "a");
		case 2:
			to_write = 'b';
			//fprintf(file, "b");
		case 3:
			to_write = 'c';
			//fprintf(file, "c");
		case 4:
			to_write = 'd';
			//fprintf(file, "d");
		case 5:
			to_write = 'e';
			//fprintf(file, "e");
		case 6:
			to_write = 'f';
			//fprintf(file, "f");
		default:
			return;
	}
	serialport_writebyte(fd, (uint8_t)to_write);
	return;
}

void Light_cont::deactivate(int pad_a_f)
{
	char to_write = 'A';
	switch(pad_a_f){
		case 1:
			to_write = 'A';
			//fprintf(file, "a");
		case 2:
			to_write = 'B';
			//fprintf(file, "b");
		case 3:
			to_write = 'C';
			//fprintf(file, "c");
		case 4:
			to_write = 'D';
			//fprintf(file, "d");
		case 5:
			to_write = 'E';
			//fprintf(file, "e");
		case 6:
			to_write = 'F';
			//fprintf(file, "f");
		default:
			return;
	}
	serialport_writebyte(fd, (uint8_t)to_write);
	return;
}
