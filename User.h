#include<bits/stdc++.h>
#define STUDENT 0//学生
#define FACULTY 1//教职工
#define OFFCAMP 2//校外人员
#define ADMINIS 3//管理员
using namespace std;

const string userTypeName[4] = {"学生", "教职工", "校外人员", "管理员"};

class Date;

class Court;

class User {//用户类
    private:
        string Sno;//学号
        int userType;//分类
        string college;//学院
        string ID;//身份证号
        string userName;//姓名
        string Pno;//电话

    public:
        User(string _Sno = "", int _userType = -1, string _college = "", string _ID = "", string _userName = "", string _Pno = "0");
//        void Set(string _Sno, int _userType, string _college, string _ID, string _userName, string _Pno);
		void Input();
		string getSno();
        int getUserType();
        string getCollege();
        string getID();
        string getUserName();
        string getPno();
        
};
