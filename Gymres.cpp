#include "GymRes.h"
using namespace std;


void GymRes::Init() {//从文件中读取信息 
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
	
	
	
//	将下面这段代码解除注释后运行以生成管理员的账号密码 
//	pair<ll, ll> a = stringHash("Administrator"), b = stringHash("123456");
//	freopen("CipherBook.txt", "w", stdout);
//	puts("1");
//	printf("%lld %lld %lld %lld\n", a.first, a.second, b.first, b.second);
//	return;


	Init();
    while(1) {
//    	system("pause");
        system("CLS");
        printf("欢迎来到体育馆预约系统\n1-登录\n2-注册\n3-退出");
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
//				return i;//登录成功 则返回在密码本中的id 
//			}
//			else {
//				fflush(fp);
//				freopen("CON", "r", stdin);
//				return 0;//查找到用户名，密码错误 
//			}
//		}
//	}
//	fflush(fp);
//	freopen("CON", "r", stdin);
	return -1;//用户名不存在 
}

void GymRes::Login() {
    string username, password;
    int wrongTime;
	while(1) {
		system("CLS");
    	puts("请输入用户名");
		if(username == "") {
			cin >> username;
		}
		else {
			cout << username << "\n请输入密码\n";
			char t = getch();
			if(t != '\r') {
				password += t;
			}
			else {
//				cout << password << "\n";
//				system("pause");
				int t = checkPassword(username, password);
				if(t > 0) {
					functionChoose(t);//注册时完善 
					return;
				}
				else {
					if(++wrongTime == 3){
						puts("错误次数达到三次");
						Sleep(2000);
						return;
					}
					if(t == 0)
						puts("密码错误");
					else {
						puts("用户名不存在"); 
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
	puts("完善信息");
	Sleep(1000);
}

void GymRes::typeChoose() {
	puts("选择运动");
//	system("pause");
	Sleep(1000);
}

void GymRes::Register() {
	puts("注册界面");
	Sleep(1000);
}
bool GymRes::Quit() {
	while(1) {
    	system("CLS");
    	puts("确认要退出吗？y/n");
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
