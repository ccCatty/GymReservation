#include"Date.h"
#define PINGPONG 0
#define BADMINTON 1
#define BASKETBALL 2
#define VOLLEYBALL 3
#define SWIMMING 4
using namespace std;
class Court {//场地类
    typedef int type_t, cap_t;
    private:
        type_t type;//运动的种类
        cap_t cap;//剩余容量
        
    public:
        Court();
};
