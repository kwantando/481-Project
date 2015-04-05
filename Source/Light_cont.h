#ifdef LIGHT_CONT_H
#define LIGHT_CONT_H

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
	Light_cont();
	~Light_cont();
	activate(char pad_a_f);
	deactivate(char pad_a_f);

private:
	FILE *file;
}


#endif
