#ifndef LIGHT_CONT_H
#define LIGHT_CONT_H

#include <string>

class Light_cont
{
public:
	Light_cont(const std::string &port);
	~Light_cont();
	void activate(int pad);
	void deactivate(int pad);

private:
	int fd; //file descriptor for serial communication with Arduino
};


#endif
