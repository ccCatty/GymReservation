#include<bits/stdc++.h>
#define STUDENT 0//ѧ��
#define FACULTY 1//��ְ��
#define OFFCAMP 2//У����Ա
#define ADMINIS 3//����Ա
using namespace std;

const string userTypeName[4] = {"ѧ��", "��ְ��", "У����Ա", "����Ա"};

class Date;

class Court;

class User {//�û���
    private:
        string Sno;//ѧ��
        int userType;//����
        string college;//ѧԺ
        string ID;//���֤��
        string userName;//����
        string Pno;//�绰

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
