#include "Basics.h"
using namespace std;

void Pause(string s) {
	while(_kbhit()) {
		getch();
	}
	cout << s << "\n";
	while(!_kbhit());
}

char idToChar(int x) {
	if(x < 10) {
		return x + '0';
	}
	if(x < 36) {
		return x - 10 + 'a';
	}
	return x - 36 + 'A';
}

int charToId(char x) {
	if(x >= '0' && x <= '9') {
		return x - '0';
	}
	if(x >= 'a' && x <= 'z') {
		return x - 'a' + 10;	
	}
	return x - 'A' + 36;
}
