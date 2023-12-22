#include "Basics.h"
#define SPORTSNUM 5
#define PINGPONG 0
#define BADMINTON 1
#define BASKETBALL 2
#define VOLLEYBALL 3
#define SWIMMING 4
using namespace std;
const string sportsName[SPORTSNUM] = {"乒乓球", "羽毛球", "篮球", "排球", "游泳"};
class Court {//场地类
    private:
        int sports;//运动的种类
        int ID;
        int cap;//剩余容量
        int courtId;//在记录文件中的顺序
		 
    public:
        Court();
        int getSports();
        void setSports(int s);
        int getID();
        void setID(int i);
        int getCap();
        void setCap(int c);
        int getCourtId(); 
        void setCourtId(int c);
        bool friend operator < (Court x, Court y) {
        	if(x.sports != y.sports) {
        		return x.sports < y.sports;
			}
			return x.ID < y.ID;
		}
};
