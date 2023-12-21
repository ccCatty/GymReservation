#include "Basics.h"
using namespace std;

int getCurrentSegment() {
    std::time_t now = std::time(NULL);
    std::tm* localTime = std::localtime(&now);

    int current_hour = localTime->tm_hour;


    int current_segment = (current_hour - STARTHOUR) / SEGLENGTH;
    return current_segment;
}
