#include "TimeSeg.h"
using namespace std;

TimeSeg::TimeSeg(int y, int m, int d, int h) {
	year = y;
	month = m;
	day = d;
	hour = h;
}

void TimeSeg::addOneDay() {
    // ����������1
    day++;
    
    // ��鵱ǰ�·ݵ��������
    int maxDays = 31; // Ĭ���·ݵ��������
    
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30; // 4�¡�6�¡�9�¡�11����30��
    } else if (month == 2) {
        // �������
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            maxDays = 29; // ����2����29��
        } else {
            maxDays = 28; // ������2����28��
        }
    }
    
    if (day > maxDays) {
        // ��������˵�ǰ�·ݵ����������������·ݺ�����
        month++;
        day = 1;
        
        if (month > 12) {
            // ����·ݳ���12���������ݺ��·�
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
    hour = hour >> 1 << 1;//����ʱ��ε���ʼʱ�� 
    return TimeSeg(year, month, day, hour);
}
