#include "GymRes.h"
using namespace std;


void GymRes::Init() {//���ļ��ж�ȡ��Ϣ 
	FILE *fp = freopen("CipherBook.txt", "r", stdin);
	scanf("%d", &userNum);
	ll a, b, c, d;
	for(int i = 1; i <= userNum; ++i) {
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
//		puts("???");
		password[i] = make_pair(c, d);
//		puts("!!!");
		id[make_pair(a, b)] = i;
//		puts("###");
	}
	fflush(fp);
	freopen("CON", "r", stdin);
}

void GymRes::Main() {
	
	
	
//	��������δ�����ע�ͺ����������ɹ���Ա���˺����� 
//	pair<ll, ll> a = stringHash("Administrator"), b = stringHash("123456");
//	freopen("CipherBook.txt", "w", stdout);
//	puts("1");
//	printf("%lld %lld %lld %lld\n", a.first, a.second, b.first, b.second);
//	return;


	Init();
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

int GymRes::checkPassword(string urn, string pwd) {
	pair<ll, ll> unHash = stringHash(urn);
	pair<ll, ll> pdHash = stringHash(pwd);
	int t = id[unHash];
	if(t) {
		if(password[t] == pdHash) {
			return t;
		}
		else {
			return 0;
		}
	}
	return -1;
//	FILE* fp = freopen("CipherBook.txt", "r", stdin);
//	int userNum;
//	cin >> userNum;
//	ll a, b, c, d;
//	for(int i = 1; i <= userNum; ++i) {
//		cin >> a >> b >> c >> d;
//		if(a == unHash.first && b == unHash.second) {
//			if(c == pdHash.first && d == pdHash.second) {
//				fflush(fp);
//				freopen("CON", "r", stdin);
//				return i;//��¼�ɹ� �򷵻������뱾�е�id 
//			}
//			else {
//				fflush(fp);
//				freopen("CON", "r", stdin);
//				return 0;//���ҵ��û������������ 
//			}
//		}
//	}
//	fflush(fp);
//	freopen("CON", "r", stdin);
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
				if(t > 0) {
					functionChoose(t);//ע��ʱ���� 
					return;
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
void GymRes::completeInfomation(int userId) {
	puts("������Ϣ");
	Sleep(1000);
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
