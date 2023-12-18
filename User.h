#include<bits/stdc++.h>
#define STUDENT 0//学生
#define FACULTY 1//教职工
#define OFFCAMP 2//校外人员
#define ADMINIS 3//管理员
using namespace std;

class Date;

class Court;

class User {//用户类
    typedef string Sno_t, college_t, name_t, ID_t, Pno_t;
    typedef int type_t;
    typedef map<Date*, Court*> Res;//用户的预约记录
    private:
        Sno_t Sno;//学号
        type_t type;//分类
        college_t college;//学院
        ID_t ID;//身份证号
        name_t name;//姓名
        Pno_t Pno;//电话

    public:
        Sno_t getSno();
        type_t getType();
        college_t getCollge();
        ID_t getID();
        name_t getName();
        Pno_t getPno();
};
