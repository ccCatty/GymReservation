#include<bits/stdc++.h>
#define STUDENT 0//ѧ��
#define FACULTY 1//��ְ��
#define OFFCAMP 2//У����Ա
#define ADMINIS 3//����Ա
using namespace std;

class Date;

class Court;

class User {//�û���
    typedef string Sno_t, college_t, name_t, ID_t, Pno_t;
    typedef int type_t;
    typedef map<Date*, Court*> Res;//�û���ԤԼ��¼
    private:
        Sno_t Sno;//ѧ��
        type_t type;//����
        college_t college;//ѧԺ
        ID_t ID;//���֤��
        name_t name;//����
        Pno_t Pno;//�绰

    public:
        Sno_t getSno();
        type_t getType();
        college_t getCollge();
        ID_t getID();
        name_t getName();
        Pno_t getPno();
};
