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
		map<pair<TimeSeg, Court>, int> res;//��Ӧʱ��ͳ��ص�ԤԼ����(һ��Ķ���1����0��ֻ����Ӿ�ݿ��ܴ���1) 
		
    public:
    	GymRes() {
    		password.clear();
    		username.clear(); 
    		id.clear();
			court = new Court *[SPORTSNUM + 1];
			courtNum = new int[SPORTSNUM + 1];
			for(int i = 0; i <= SPORTSNUM; ++i) {
				court[i] = NULL;
				courtNum[i] = 0;
			}
			res.clear(); 
		}
    	void Init();
        void Main();
        void Login();
        pair<ll, ll> stringHash(string s);
        int checkPassword(string username, string password);
        void functionChoose(User user);
        void sportsChoose();
		void courtChoose(Court* crt, int num);
		void timeChoose(Court crt);
        void Register();
        bool Quit();
};
