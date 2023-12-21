#include "GymRes.h"
using namespace std;

GymRes::GymRes() {
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

void GymRes::Init() {//从文件中读取信息 
//	puts("???");
	FILE *fp = freopen("UserInfo.txt", "r", stdin);
	scanf("%d", &userNum);//第一行一个整数userNum，表示用户数量 
	user = new User[userNum + 1];
	ll a, b, c, d;
	for(int i = 1; i <= userNum; ++i) {
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);//每行前四个数字表示用户名和密码的哈希
		password[i] = make_pair(c, d);
		username[i] = make_pair(a, b);
		id[make_pair(a, b)] = i;
		user[i].Input();
	}
	fflush(fp);
	fp = freopen("CourtInfo.txt", "r", stdin);
	for(int i = 0; i < SPORTSNUM; ++i) {//对于每种运动的场地
		scanf("%d", &courtNum[i]);//先输入这种运动场地的数量
		court[i] = new Court[courtNum[i]];
		for(int j = 0; j < courtNum[i]; ++j) {//再依次输入每个场地的信息
			court[i][j].setSports(i);
			court[i][j].setID(j);
			if(i == SWIMMING) {
				int cap;
				scanf("%d", &cap);
				court[i][j].setCap(cap);
			}//对于游泳馆,需要额外输入场地的容量
			else {
				court[i][j].setCap(1);
			}
		}
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
			return t;//密码正确，返回其id 
		}
		else {
			return 0;//密码错误 
		}
	}
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
					functionChoose(t); 
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

void GymRes::functionChoose(int userId) {
	while(1) {
		system("CLS");
		cout << "你好，" << user[userId].getUserName() << "\n";
		if (user[userId].getUserType() == ADMINIS) {
			cout << "请输入你的操作：" << endl;
			cout << "1.查看预约" << endl;
			cout << "2.收入预估" << endl;
			cout << "3." << endl;
			cout << "4.注销登录" << endl;
			int select = 0;
			cin >> select;
			if (select == 1)
			{
				
			}
			else if (select == 2)
			{

			}
			else if (select == 3)
			{

			}
			else if (select == 4)
			{
				system("cls");
				cout << "欢迎您下次光临！" << endl;
				system("pause");
				return;
			}
			else {
				cout << "请输入正确的选项！" << endl;
				system("pause");
			}
		}
		else {
			cout << "请输入你的操作：" << endl;
			cout << "1.选择预约" << endl;
			cout << "2.查看预约" << endl;
			cout << "3.取消预约" << endl;
			cout << "4.注销登录" << endl;
			int select = 0;
			cin >> select;
			if (select == 1)
			{
				sportsChoose(userId);
			}
			else if (select == 2)
			{

			}
			else if (select == 3)
			{

			}
			else if (select == 4)
			{
				system("cls");
				cout << "欢迎您下次光临！" << endl;
				system("pause");
				return;
			}
			else {
				cout << "请输入正确的选项！" << endl;
				system("pause");
			}
		}
		
	}
}

void GymRes::sportsChoose(int userId) {//选择运动的种类
	while(1) {
		system("CLS");
		puts("预约场地\n请选择运动");
		for(int i = 0; i < SPORTSNUM; ++i) {
			cout << i + 1 << "-" << sportsName[i] << "\n";
		}
		puts("0-返回");
		char c = getch();
		if(c >= '1' && c <= '5') {
			courtChoose(userId, court[c - '1'], courtNum[c - '1']);
		}
		if(c == '0') {
			return;
		}
		Sleep(200);
		while(_kbhit()) {
			getch();
		}
	}
}

void GymRes::courtChoose(int userId, Court* crt, int num) {
//参数是一类运动的所有场地和场地数量, 要求显示每个场地,并有选择功能
	while(1) {
		system("CLS");
		cout << "预约" << sportsName[crt[0].getSports()] << "场地\n";
		puts("请选择场地");
		for(int i = 0; i < num; ++i) {
			printf("%d-%d号场地\n", i + 1, i + 1);
		}
		puts("0-返回");
		char c = getch();
		if(c >= '1' && c <= '0' + num) {
			timeChoose(userId, crt[c - '1']);
		}
		if(c == '0') {
			return;
		}
		Sleep(200);
		while(_kbhit()) {
			getch();
		}
	}
}

void GymRes::timeChoose(int userId, Court crt) {
	//选好了运动种类和场地, 接下来查看该场地的未来两天的预约情况
	while(1) {
		system("CLS");
		cout << "预约" << sportsName[crt.getSports()] << crt.getID() << "号场地\n";
	    std::time_t now = std::time(NULL);
	    std::tm* localTime = std::localtime(&now);
	    int year = localTime->tm_year + 1900;
	    int month = localTime->tm_mon;
	    int day = localTime->tm_mday;
	    int hour = localTime->tm_hour;
	    int cnt = 0;
	    hour = hour >> 1 << 1;//所在时间段的起始时间 
	    TimeSeg ts(year, month, day, hour);
	    TimeSeg *p = new TimeSeg[30];
	    if(ts.getHour() >= 22) {//现在的时间已经错过了当天的所有预约时间段
	    	ts.addOneDay();//则从第二天开始输出两天的预约记录 
		}
		else if(ts.getHour() >= 8) {//正在当天的可预约时段内
			while(ts.getHour() < 22) {
				p[++cnt] = ts;
				printf("%c - %d.%02d.%02d %02d:00-%02d:00 预约人数:%2d/%2d\n", id2char(cnt), ts.getYear(), ts.getMonth(), ts.getDay(), ts.getHour(), ts.getHour() + 2, res[make_pair(ts, crt)].size(), crt.getCap());
				ts.addTwoHours();
			}
			ts.addOneDay();
		}//还有一种情况就是当天的预约时段还没开始，则就从当天开始输出两天的预约记录 
		for(int i = 0; i < 2; ++i) {
			ts.setHour(8);
			while(ts.getHour() < 22) {
				p[++cnt] = ts;
				printf("%c - %d.%02d.%02d %02d:00-%02d:00 预约人数:%2d/%2d\n", id2char(cnt), ts.getYear(), ts.getMonth(), ts.getDay(), ts.getHour(), ts.getHour() + 2, res[make_pair(ts, crt)].size(), crt.getCap());
				ts.addTwoHours();
			}
			ts.addOneDay();
		}
		char c = getch();
		int x = char2id(c);
		if(x >= 1 && x <= cnt) {
//			printf("选择了%c\n", id2char(x));
			doRes(userId, p[x], crt);
//			Sleep(1000);
		}
		Sleep(1000);
		while(_kbhit()) {
			getch();
		}
	}
}

void GymRes::doRes(int usrId, TimeSeg tsg, Court crt) {
	system("CLS");
	if(res[make_pair(tsg, crt)].size() >= crt.getCap()) {
		puts("该场次预约人数已满");
		Sleep(2000);
		return; 
	}
	while(1) {
		system("CLS");
		cout << "预约场地: " << crt.getSports() << crt.getID() << "号场地\n";
		printf("预约时间: %d-%02d-%02d.%02d:00-%02d:00\n", tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
		puts("确认预约吗?y/n");
		char c = getch();
		if(c == 'y' || c == 'Y') {
			res[make_pair(tsg, crt)].push_back(usrId);
			puts("预约成功");
			Sleep(2000);
			return; 
		}
		if(c == 'n' || c == 'N') {
			return;
		}
	}
}
void GymRes::Register() {
	string urn = "", pwd1 = "", pwd2 = "";
	string Sno = "", college = "", ID = "", userName = "", Pno = "";
	int userType = -1;
	bool done1 = 0, done2 = 0;
	while(1) {
		system("CLS");
		puts("注册新用户");
		if(urn == "") {
			puts("请输入用户名");
			cin.clear();
			cin >> urn;
			if(id[stringHash(urn)]) {
				puts("用户名已被注册, 请重新输入");
				urn = ""; 
				Sleep(1800); 
			}
//			cout << "" << username << "\n";
//			puts("!!!");
			goto ifEnd;
		}
		else {
			cout << "用户名: " << urn << "\n"; 
		} 
		if(!done1) {
			puts("请输入密码");
			char c = getch();
			if(c != '\r') {
				pwd1 += c;
			}
			else {
				done1 = 1;
			}
//			goto ifEnd;
			continue;
		}
//		cout << "pwd1 = " << pwd1 << "\n";
		if(!done2) {
			puts("请确认密码");
			char c = getch();
			if(c != '\r') {
				pwd2 += c;
			}
			else {
				done2 = 1;
			}
//			goto ifEnd;
			continue;
		}
//		cout << "pwd2 = " << pwd2 << "\n";
		if(pwd1 != pwd2) {
			puts("两次密码不一致");
			pwd1 = pwd2 = "";
			done1 = done2 = 0;
			Sleep(800);
			goto ifEnd;
		}
		if(userType == -1) {
			cout << "请选择用户类型\n";
			for(int i = 0; i < 3; ++i) {
				cout << i + 1 << "-" << userTypeName[i] << "\n";
			}
			puts("0-返回"); 
			char c = getch();
			if(c >= '1' && c <= '3') {
				userType = c - '1';
				goto ifEnd;
			}
			if(c == '0') {
				return;
			} 
		}
		else {
			cout << "用户类型:" << userTypeName[userType] << "\n";
			puts("请输入姓名");
			cin >> userName;
			puts("请输入身份证号");
			cin >> ID; 
			puts("请输入电话号码");
			cin>>Pno;
			if(userType==STUDENT||userType==FACULTY||userType==ADMINIS)
			{
				puts("请输入学院");
				cin>>college; 
			 }
			if(userType==STUDENT||userType==ADMINIS)
			{
				puts("请输入学号");
				cin>>Sno; 
			}
//			cout << username  << "\n" << pwd1 << "\n" << Sno << "\n" << userType << "\n" << college << "\n" << ID << "\n" << userName << "\n" << Pno << "\n";
//			system("pause");
			User newUser(Sno, userType, college, ID, userName, Pno);
			User *t = new User[userNum + 2];
			for(int i = 1; i <= userNum; ++i) {
				t[i] = user[i];
			}
			delete[] user;
			t[++userNum] = newUser;
			user = t;
			pair<ll, ll> urnHash = stringHash(urn), pwdHash = stringHash(pwd1);
			password[userNum] = pwdHash;
			username[userNum] = urnHash;
			id[urnHash] = userNum;
			ofstream outputFile("UserInfo.txt");
			assert(outputFile.is_open());
			outputFile << userNum << "\n";
			for(int i = 1; i <= userNum; ++i) {
				outputFile << username[i].first << " " << username[i].second << " " << password[i].first << " " << password[i].second << " ";
				outputFile << user[i].getSno() <<" "<< user[i].getUserType() <<" "<< user[i].getCollege() <<" "<< user[i].getID() <<" "<< user[i].getUserName() <<" "<< user[i].getPno() << "\n";
			}
			puts("注册成功, 将返回首页");
			Sleep(1000);
			return; 
		}
		ifEnd:
		Sleep(200);
		while(_kbhit()) {
			getch();
		}
	}
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
