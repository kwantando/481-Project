#include "Utility.h"
#include "Debug_msg.h"
using namespace std;

vector<keypads_e> convert_int_to_keypads(const vector<int>& vc) {

	vector<keypads_e> retvec;

	for (const int& val : vc) {

		keypads_e key_val;

		switch (val) {

		case 0:
			key_val = KEYPAD1;
			break;
		case 1:
			key_val = KEYPAD2;
			break;
		case 2:
			key_val = KEYPAD3;
			break;
		case 3:
			key_val = KEYPAD4;
			break;
		case 4:
			key_val = KEYPAD5;
			break;
		case 5:
			key_val = KEYPAD6;
			break;
		default:
			DEBUG_MSG("ERROR. Incorrect value found in sequence.");

		}

		retvec.push_back(key_val);

	}

	return retvec;
}