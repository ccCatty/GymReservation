#include<bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#define ll long long
#define BASE (137)
#define MOD1 (998244353)
#define MOD2 (1000000007)
using namespace std;
class GymRes {
    private:
        int *nums;//各个种类的场地数量

    public:
        void Main();
        void Login();
        pair<ll, ll> stringHash(string s);
        int checkPassword(string username, string password);
        void typeChoose();
        void Register();
        bool Quit();
};
