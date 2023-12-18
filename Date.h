
const int Days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
class Date {
    typedef int year_t, month_t, day_t, period_t;
    private:
        year_t year;
        month_t month;
        day_t day;
        period_t period;//上午、下午或晚上
        bool isLeap();
    
};
