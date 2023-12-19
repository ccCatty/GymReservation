#include<bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#define ll long long
#define BASE (137)
#define MOD1 (998244353)
#define MOD2 (1000000007)
using namespace std;

class User;

class GymRes {
    private:
    	int userNum;//用户数量 
		map<int, pair<ll, ll> > password;//id到密码哈希的映射
    	map<pair<ll, ll>, int> id;//用户名哈希到id的映射 
		User **user;//用户信息
    public:
    	GymRes() {
    		puts("???");
    		password.clear();
    		puts("!!!");
    		id.clear();
    		puts("!!!");
		}
    	void Init();
        void Main();
        void Login();
        pair<ll, ll> stringHash(string s);
        int checkPassword(string username, string password);
        void completeInfomation(int userId);
        void typeChoose();
        void Register();
        bool Quit();
};
