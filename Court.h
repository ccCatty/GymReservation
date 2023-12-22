#include "Basics.h"
#define SPORTSNUM 5
#define PINGPONG 0
#define BADMINTON 1
#define BASKETBALL 2
#define VOLLEYBALL 3
#define SWIMMING 4
using namespace std;
const string sportsName[SPORTSNUM] = {"ƹ����", "��ë��", "����", "����", "��Ӿ"};
class Court {//������
    private:
        int sports;//�˶�������
        int ID;
        int cap;//ʣ������
        int courtId;//�ڼ�¼�ļ��е�˳��
		 
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
