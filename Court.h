#include"Date.h"
#define PINGPONG 0
#define BADMINTON 1
#define BASKETBALL 2
#define VOLLEYBALL 3
#define SWIMMING 4
using namespace std;
class Court {//������
    typedef int type_t, cap_t;
    private:
        type_t type;//�˶�������
        cap_t cap;//ʣ������
        
    public:
        Court();
};
