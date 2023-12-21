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
		map<int, pair<ll, ll> > idToPassword;//id�������ϣ��ӳ��
		map<int, pair<ll, ll> > idToUsername;//id���û�����ϣ��ӳ�� 
    	map<pair<ll, ll>, int> usernameToId;//�û�����ϣ��id��ӳ�� 
		User* user;//�����û�����Ϣ
		int* courtNum;//�����˶����ص����� 
		Court** court;//�����˶��ĸ������ص���Ϣ
		Court** idToCourt;//ָ�����飬�ó���id�ҵ���Ӧ���صĵ�ַ
		map<pair<TimeSeg, int>, vector<int> > res;//��Ӧʱ��ͳ���id���û�id(һ������ֻ��1��Ԫ�أ�ֻ����Ӿ�ݿ��ܴ���1) 
		
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
		void timeChoose(int userId, int crtId);
		void doRes(int usrId, TimeSeg tsg, int crtId);
        void Register();
        bool Quit();
};
