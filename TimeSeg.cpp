#include "TimeSeg.h"
using namespace std;

TimeSeg::TimeSeg(int y, int m, int d, int h) {
	year = y;
	month = m;
	day = d;
	hour = h;
}

void TimeSeg::addOneDay() {
    // 将天数增加1
    day++;
    
    // 检查当前月份的最大天数
    int maxDays = 31; // 默认月份的最大天数
    
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30; // 4月、6月、9月、11月有30天
    } else if (month == 2) {
        // 检查闰年
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            maxDays = 29; // 闰年2月有29天
        } else {
            maxDays = 28; // 非闰年2月有28天
        }
    }
    
    if (day > maxDays) {
        // 如果超过了当前月份的最大天数，则调整月份和天数
        month++;
        day = 1;
        
        if (month > 12) {
            // 如果月份超过12，则调整年份和月份
            year++;
            month = 1;
        }
    }
}

void TimeSeg::addTwoHours() {
	hour += 2;
	if(hour >= 24) {
		hour -= 24;
		addOneDay();
	}
}

int TimeSeg::getYear() {
	return year;
}

int TimeSeg::getMonth() {
	return month;
}

int TimeSeg::getDay() {
	return day;
}

int TimeSeg::getHour() {
	return hour;
}

void TimeSeg::setHour(int h) {
	hour = h;
}

TimeSeg TimeSeg::getCurrentSegment() {
	time_t now = std::time(NULL);
    tm* localTime = std::localtime(&now);
    int year = localTime->tm_year + 1900;
    int month = localTime->tm_mon;
    int day = localTime->tm_mday;
    int hour = localTime->tm_hour;
    int cnt = 0;
    hour = hour >> 1 << 1;//所在时间段的起始时间 
    return TimeSeg(year, month, day, hour);
}
