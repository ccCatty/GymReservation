#include "Basics.h"
using namespace std;




class TimeSeg {
	private:
		int year, month, day, hour;
		
	public:
		TimeSeg(int y = 0, int m = 0, int d = 0, int h = 0);
		void addOneDay();
		void addTwoHours();
		int getYear();
		int getMonth();
		int getDay();
		int getHour();
		void setHour(int h);
		TimeSeg getCurrentSegment();
		bool friend operator < (TimeSeg x, TimeSeg y) {
			if(x.year != y.year) {
				return x.year < y.year;
			}
			if(x.month != y.month) {
				return x.month < y.month;
			}
			if(x.day != y.day) {
				return x.day < y.day;
			}
			return x.hour < y.hour;
		}
};
