#include "GymRes.h"
using namespace std;

void GymRes::Main() {
	
	
	
//	��������δ�����ע�ͺ����������ɹ���Ա���˺����� 
//	pair<ll, ll> a = stringHash("Administrator"), b = stringHash("123456");
//	freopen("CipherBook.txt", "w", stdout);
//	puts("1");
//	printf("%lld %lld %lld %lld\n", a.first, a.second, b.first, b.second);
//	return;



    while(1) {
//    	system("pause");
        system("CLS");
        printf("��ӭ����������ԤԼϵͳ\n1-��¼\n2-ע��\n3-�˳�");
        int t = getch();
        if(t == '1') {
            Login();
        }
        else if(t == '2') {
        	Register();
		} 
        else if(t == '3') {
            if(Quit()) {
            	return;
			}
        }
        Sleep(200);
        while (_kbhit()) {
            getch();
        }
    }
}

pair<ll, ll> GymRes::stringHash(string s) {
	pair<ll, ll> p;
	p.first = p.second = 0;
	int n = s.length();
	for(int i = 0; i < n; ++i) {
		p.first = (p.first * BASE + s[i]) % MOD1;
		p.second = (p.second * BASE + s[i]) % MOD2;
	}
	return p;
}

int GymRes::checkPassword(string username, string password) {
	pair<ll, ll> unHash = stringHash(username);
	pair<ll, ll> pdHash = stringHash(password);
	FILE* fp = freopen("CipherBook.txt", "r", stdin);
	int userNum;
	cin >> userNum;
	ll a, b, c, d;
	for(int i = 1; i <= userNum; ++i) {
		cin >> a >> b >> c >> d;
		if(a == unHash.first && b == unHash.second) {
			if(c == pdHash.first && d == pdHash.second) {
				fflush(fp);
				freopen("CON", "r", stdin);
				return 1;//��¼�ɹ� 
			}
			else {
				fflush(fp);
				freopen("CON", "r", stdin);
				return 0;//���ҵ��û������������ 
			}
		}
	}
	fflush(fp);
	freopen("CON", "r", stdin);
	return -1;//�û��������� 
}

void GymRes::Login() {
    string username, password;
    int wrongTime;
	while(1) {
		system("CLS");
    	puts("�������û���");
		if(username == "") {
			cin >> username;
		}
		else {
			cout << username << "\n����������\n";
			char t = getch();
			if(t != '\r') {
				password += t;
			}
			else {
//				cout << password << "\n";
//				system("pause");
				int t = checkPassword(username, password);
				if(t == 1) {
					typeChoose();
				}
				else {
					if(++wrongTime == 3){
						puts("��������ﵽ����");
						Sleep(2000);
						return;
					}
					if(t == 0)
						puts("�������");
					else {
						puts("�û���������"); 
						return;
					}
					Sleep(1800);
				}
				password.clear();
				while(_kbhit()) {
	                getch();
	            }
			}
		}
	}
}

void GymRes::typeChoose() {
	puts("ѡ���˶�");
//	system("pause");
	Sleep(1000);
}

void GymRes::Register() {
	puts("ע�����");
	Sleep(1000);
}
bool GymRes::Quit() {
	while(1) {
    	system("CLS");
    	puts("ȷ��Ҫ�˳���y/n");
    	int t = getch();
        if(t == 'y') {
            return 1;
        }
        else if(t == 'n') {
        	return 0;
        }
        while (_kbhit()) {
            getch();
        }
        Sleep(200);
	}
}
