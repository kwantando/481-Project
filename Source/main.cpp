#include "Controller.h"

int main()
{

	Controller main_ctrl{ "filedata.txt" };
	main_ctrl.start_reading_input();

    return EXIT_SUCCESS;

}
