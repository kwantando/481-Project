#ifndef LIGHT_CONT_H
#define LIGHT_CONT_H

#include <string>

class Light_cont
{
public:
	Light_cont(std::string port);
	~Light_cont();
	void activate(int pad_a_f);
	void deactivate(int pad_a_f);

private:
	int fd; //file descriptor for serial communication with Arduino
};


#endif
