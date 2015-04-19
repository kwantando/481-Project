#ifndef ARDUINO_CONT_H
#define ARDUINO_CONT_H

int serialport_init(const char* serialport);
int serialport_write(int fd, const char* str, int len);

#endif