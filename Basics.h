#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
#define STARTHOUR 8
#define ENDHOUR 22
#define SEGLENGTH 2
#define SEGNUM 7
using namespace std;

char id2char(int x) {
	if(x < 10) {
		return x + '0';
	}
	return x - 10 + 'a';
}

int char2id(char x) {
	if(x >= '1' && x <= '9') {
		return x - '0';
	}
	if(x >= 'a' && x <= 'z') {
		return x - 'a' + 10;	
	}
	return 0;
}

int getCurrentSegment();
