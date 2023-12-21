#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "User.h"
#include "Court.h"
#include "TimeSeg.h"
#define ll long long
#define BASE (137)
#define MOD1 (998244353)
#define MOD2 (1000000007)
using namespace std;

class GymRes {
    private:
    	int userNum;//�û����� 
		map<int, pair<ll, ll> > password;//id�������ϣ��ӳ��
		map<int, pair<ll, ll> > username;//id���û�����ϣ��ӳ�� 
    	map<pair<ll, ll>, int> id;//�û�����ϣ��id��ӳ�� 
		User* user;//�����û�����Ϣ
		int* courtNum;//�����˶�����Ϣ
		Court** court;//�����˶��ĸ������ص���Ϣ
		map<pair<TimeSeg, Court>, vector<int> > res;//��Ӧʱ��ͳ��ص��û�id(һ������ֻ��1��Ԫ�أ�ֻ����Ӿ�ݿ��ܴ���1) 
		
    public:
    	GymRes();
    	void Init();
        void Main();
        void Login();
        pair<ll, ll> stringHash(string s);
        int checkPassword(string username, string password);
        void functionChoose(int userId);
        void sportsChoose(int userId);
		void courtChoose(int userId, Court* crt, int num);
		void timeChoose(int userId, Court crt);
		void doRes(int usrId, TimeSeg tsg, Court crt);
        void Register();
        bool Quit();
};
