#ifndef LIGHT_CONT_H
#define LIGHT_CONT_H

#include <string>

enum Pads{
	TOP_LEFT,
	TOP_MID,
	TOP_RIGHT,
	BOT_LEFT,
	BOT_MID,
	BOT_RIGHT
};

class Light_cont
{
public:
	Light_cont(std::string port);
	~Light_cont();
	void activate(int pad_a_f);
	void deactivate(int pad_a_f);

private:
	FILE *file;
};


#endif
