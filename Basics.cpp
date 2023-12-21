#include "Basics.h"
using namespace std;

char idToChar(int x) {
	if(x < 10) {
		return x + '0';
	}
	return x - 10 + 'a';
}

int charToId(char x) {
	if(x >= '1' && x <= '9') {
		return x - '0';
	}
	if(x >= 'a' && x <= 'z') {
		return x - 'a' + 10;	
	}
	return 0;
}

int getCurrentSegment() {
    std::time_t now = std::time(NULL);
    std::tm* localTime = std::localtime(&now);

    int current_hour = localTime->tm_hour;


    int current_segment = (current_hour - STARTHOUR) / SEGLENGTH;
    return current_segment;
}
