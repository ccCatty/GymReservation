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
    	int userNum;//用户数量 
		map<int, pair<ll, ll> > password;//id到密码哈希的映射
		map<int, pair<ll, ll> > username;//id到用户名哈希的映射 
    	map<pair<ll, ll>, int> id;//用户名哈希到id的映射 
		User* user;//各个用户的信息
		int* courtNum;//各种运动的信息
		Court** court;//各种运动的各个场地的信息
		map<pair<TimeSeg, Court>, int> res;//对应时间和场地的预约人数(一般的都是1或者0，只有游泳馆可能大于1) 
		
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
