#include "GymRes.h"
using namespace std;

GymRes::GymRes() {
	idToPassword.clear();
	idToUsername.clear(); 
	usernameToId.clear();
	user = NULL;
	courtNum = new int[SPORTSNUM + 1];
	court = new Court *[SPORTSNUM + 1];
	for(int i = 0; i <= SPORTSNUM; ++i) {
		court[i] = NULL;
		courtNum[i] = 0;
	}
	idToCourt = NULL;
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
		idToPassword[i] = make_pair(c, d);
		idToUsername[i] = make_pair(a, b);
		usernameToId[make_pair(a, b)] = i;
		user[i].Input();
	}
	fflush(fp);
	fp = freopen("CourtInfo.txt", "r", stdin);
	int courtTotNum;
	scanf("%d", &courtTotNum);
	idToCourt = new Court*[courtTotNum + 1];
	int cnt = 0;
	for(int i = 0; i < SPORTSNUM; ++i) {//对于每种运动的场地
		scanf("%d", &courtNum[i]);//先输入这种运动场地的数量
		court[i] = new Court[courtNum[i]];
		for(int j = 0; j < courtNum[i]; ++j) {//再依次输入每个场地的信息
			court[i][j].setSports(i);
			court[i][j].setID(j);
			court[i][j].setCourtId(++cnt);
			idToCourt[cnt] = &court[i][j];
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
	fp = freopen("ResInfo.txt", "r", stdin);
	int resNum;
	scanf("%d", &resNum);
	int year, month, day, hour, courtId, num, x;
	for(int i = 1; i <= resNum; ++i) {
		scanf("%d %d %d %d %d %d", &year, &month, &day, &hour, &courtId, &num);
		pair<TimeSeg, int> p = make_pair(TimeSeg(year, month, day, hour), courtId);
		while(num--) {
			scanf("%d", &x);
			res[p].push_back(x);
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
//    	Pause();
        cout << "\033c";
        printf("欢迎来到体育馆预约系统\n1 - 登录\n2 - 注册\n3 - 退出");
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
	int t = usernameToId[unHash];
	if(t) {
		if(idToPassword[t] == pdHash) {
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
		fflush(stdout);
		cout << "\033c";
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
//				Pause();
				int t = checkPassword(username, password);
				if(t > 0) {
					functionChoose(t); 
					return;
				}
				else {
					if(++wrongTime == 3){
						puts("错误次数达到三次");
						Pause("按任意键返回"); 
						return;
					}
					if(t == 0)
						puts("密码错误");
					else {
						puts("用户名不存在");
						Pause("按任意键返回"); 
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
		cout << "\033c";
		cout << "你好，" << user[userId].getUserName() << "\n";
		if (user[userId].getUserType() == ADMINIS) {
			cout << "请输入你的操作：" << endl;
			cout << "1 - 查看预约记录" << endl;
			cout << "2 - 收入预估" << endl;
			cout << "3 - 注销登录" << endl;
			char select = getch();
			if (select == '1') {
				showRes(userId);
			}
			else if (select == '2') {
				
			}
			else if (select == '3') {
				cout << "\033c";
				cout << "欢迎您下次光临！" << endl;
				Pause("按任意键退出"); 
				return;
			}
		}
		else {
			cout << "请输入你的操作：" << endl;
			cout << "1 - 场地预约" << endl;
			cout << "2 - 查看预约记录" << endl;
			cout << "3 - 注销登录" << endl;
			char select = getch();
			if (select == '1') {
				sportsChoose(userId);
			}
			else if (select == '2') {
				showRes(userId);
			}
			else if (select == '3') {
				cout << "\033c";
				cout << "欢迎您下次光临！" << endl;
				Pause("按任意键退出"); 
				return;
			}
		}
		Sleep(200);
		while(_kbhit()) {
			getch();
		}
	}
}

void GymRes::showRes(int userId) {
	map<pair<TimeSeg, int>, vector<int> >::iterator it, rec[res.size() + 1];
	int cnt = 0;
	int num = 0;
	
	if(user[userId].getUserType() == ADMINIS) {
		while(1) {
			cout << "\033c";
			cnt = 0;
			for(it = res.begin(); it != res.end(); it++) {
				TimeSeg tsg = (it->first).first;
				Court *crt = idToCourt[(it->first).second];
				if(!(tsg < tsg.getCurrentSegment()) && (num = it->second.size())) {
					rec[++cnt] = it;
					printf("%c - 预约时间: %d-%02d-%02d.%02d:00-%02d:00\n", idToChar(cnt), tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
					cout << "    预约场地: " << sportsName[crt->getSports()] << crt->getID() + 1 << "号场地\n";
					cout << "    预约用户id: ";
					for(int i = 0; i < num; ++i) {
						cout << it->second[i] << " ";
					}
					puts("");
				}
			}
			puts("0 - 返回\n按下对应数字键以取消预约");
			char c = getch();
			int x = charToId(c);
			if(!x) {
				return;
			}
			if(x >= 1 && x <= cnt) {
				cancelRes(userId, rec[x]); 
			}
			Sleep(200);
			while(_kbhit()) {
				getch();
			}
		}
	}
	else {
		while(1) {
			cout << "\033c";
			cnt = 0;
			for(it = res.begin(); it != res.end(); it++) {
				TimeSeg tsg = (it->first).first;
				Court *crt = idToCourt[(it->first).second];
				if(!(tsg < tsg.getCurrentSegment()) && (num = it->second.size()) && find(it->second.begin(), it->second.end(), userId) != it->second.end()) {
					rec[++cnt] = it;
					printf("%c - 预约时间: %d-%02d-%02d.%02d:00-%02d:00\n", idToChar(cnt), tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
					cout << "    预约场地: " << sportsName[crt->getSports()] << crt->getID() + 1 << "号场地\n";
				}
			}
			puts("0 - 返回\n按下对应数字键以取消预约");
			char c = getch();
			int x = charToId(c);
			if(!x) {
				return;
			}
			if(x >= 1 && x <= cnt) {
				cancelRes(userId, rec[x]); 
			}
			Sleep(200);
			while(_kbhit()) {
				getch();
			}
		}
	}
}

void GymRes::cancelRes(int userId, map<pair<TimeSeg, int>, vector<int> >::iterator it) {
	TimeSeg tsg = (it->first).first;
	Court *crt = idToCourt[(it->first).second];
	int num = it->second.size();
	if(user[userId].getUserType() == ADMINIS) {
		while(1) {
			cout << "\033c";
			cout << "正在取消: " << crt->getSports() << " " << crt->getID() + 1 << "号场地";
			printf("%d-%02d-%02d.%02d:00-%02d:00时间段的预约\n", tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
			puts("请选择要取消的用户id\n");
			for(int i = 0; i < num; ++i) {
				printf("%c - %d\n", idToChar(i + 1), it->second[i]);
			}
			puts("0 - 取消"); 
			char c = getch();
			int x = charToId(c);
			if(!x) {
				return;
			}
			if(x >= 1 && x <= num) {
				it->second.erase(it->second.begin() + x - 1);
				writeResInfo();
				puts("取消成功");
				Pause("按任意键返回");
				return; 
			}
		}
	}
	else {
		while(1) {
			cout << "\033c";
			cout << "正在取消: " << crt->getSports() << " " << crt->getID() + 1 << "号场地";
			printf("%d-%02d-%02d.%02d:00-%02d:00时间段的预约\n", tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
			puts("是否确定取消预约? y/n\n");
			char c = getch();
			if(c == 'y' || c == 'Y') {
				it->second.erase(find(it->second.begin(), it->second.end(), userId));
				writeResInfo();
				puts("取消成功");
				Pause("按任意键返回");
				return; 
			}
			if(c == 'n' || c == 'N') {
				return;
			}
		}
	}
}

void GymRes::writeResInfo() {
	FILE* fp = freopen("ResInfo.txt", "w", stdout);
	TimeSeg tsg;
	Court *crt;
	printf("%d\n", res.size());//预约记录文件的第一行表示预约的数量 
	for(map<pair<TimeSeg, int>, vector<int> >::iterator i = res.begin(); i != res.end(); i++) {
		//对于每个预约，第一行表示时间段的开始时间 预约场地的运动种类和id
		tsg = (i->first).first;
		crt = idToCourt[(i->first).second];
		printf("%d %2d %2d %2d %d\n", tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), crt->getCourtId());
		int n = i->second.size();
		printf("%d ", n);//第三行表示这个时间预约这个场地的人数 
		for(int j = 0; j < n; ++j) {
			printf("%d ", i->second[j]);//然后接这个时间预约这个时间的所有人的id 
		}
		puts(""); 
	}
	fflush(fp);
	freopen("CON", "w", stdout);
}

void GymRes::sportsChoose(int userId) {//选择运动的种类
	while(1) {
		cout << "\033c";
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
		cout << "\033c";
		cout << "预约" << sportsName[crt[0].getSports()] << "场地\n";
		puts("请选择场地");
		for(int i = 0; i < num; ++i) {
			printf("%d-%d号场地\n", i + 1, i + 1);
		}
		puts("0-返回");
		char c = getch();
		if(c >= '1' && c <= '0' + num) {
			timeChoose(userId, crt[c - '1'].getCourtId());
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

void GymRes::timeChoose(int userId, int crtId) {
	//选好了运动种类和场地, 接下来查看该场地的未来两天的预约情况
	while(1) {
		cout << "\033c";
		fflush(stdout);
		cout << "预约" << sportsName[idToCourt[crtId]->getSports()] << idToCourt[crtId]->getID() + 1 << "号场地\n";
	    time_t now = std::time(NULL);
	    tm* localTime = std::localtime(&now);
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
				printf("%c - %d.%02d.%02d %02d:00-%02d:00 预约人数:%2d/%2d\n", idToChar(cnt), ts.getYear(), ts.getMonth(), ts.getDay(), ts.getHour(), ts.getHour() + 2, res[make_pair(ts, crtId)].size(), idToCourt[crtId]->getCap());
				ts.addTwoHours();
			}
			ts.addOneDay();
		}//还有一种情况就是当天的预约时段还没开始，则就从当天开始输出两天的预约记录 
		for(int i = 0; i < 2; ++i) {
			ts.setHour(8);
			while(ts.getHour() < 22) {
				p[++cnt] = ts;
				printf("%c - %d.%02d.%02d %02d:00-%02d:00 预约人数:%2d/%2d\n", idToChar(cnt), ts.getYear(), ts.getMonth(), ts.getDay(), ts.getHour(), ts.getHour() + 2, res[make_pair(ts, crtId)].size(), idToCourt[crtId]->getCap());
				ts.addTwoHours();
			}
			ts.addOneDay();
		}
		puts("0 - 返回");
		char c = getch();
		int x = charToId(c);
		if(!x) {
			return;
		}
		if(x >= 1 && x <= cnt) {
			doRes(userId, p[x], crtId);
		}
		Sleep(1000);
		while(_kbhit()) {
			getch();
		}
	}
}

void GymRes::doRes(int usrId, TimeSeg tsg, int crtId) {
		cout << "\033c";
	if(res[make_pair(tsg, crtId)].size() >= idToCourt[crtId]->getCap()) {
		puts("该场次预约人数已满");
		Sleep(2000);
		return; 
	}
	while(1) {
		cout << "\033c";
		cout << "预约场地: " << sportsName[idToCourt[crtId]->getSports()] << idToCourt[crtId]->getID()+ 1 << "号场地\n";
		printf("预约时间: %d-%02d-%02d.%02d:00-%02d:00\n", tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
		puts("确认预约吗?y/n");
		char c = getch();
		if(c == 'y' || c == 'Y') {
			res[make_pair(tsg, crtId)].push_back(usrId);//将这次预约记录在res中 
			writeResInfo();
			puts("预约成功");
			Sleep(2000);
			return;
		}
		if(c == 'n' || c == 'N') {
			return;
		}
		Sleep(200);
		while(_kbhit()) {
			getch();
		}
	}
}
void GymRes::Register() {
	string urn = "", pwd1 = "", pwd2 = "";
	string Sno = "", college = "", ID = "", userName = "", Pno = "";
	int userType = -1;
	bool done1 = 0, done2 = 0;
	while(1) {
		cout << "\033c";
		puts("注册新用户");
		if(urn == "") {
			puts("请输入用户名");
			cin.clear();
			cin >> urn;
			if(usernameToId[stringHash(urn)]) {
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
//			Pause();
			User newUser(Sno, userType, college, ID, userName, Pno);
			User *t = new User[userNum + 2];
			for(int i = 1; i <= userNum; ++i) {
				t[i] = user[i];
			}
			delete[] user;
			t[++userNum] = newUser;
			user = t;
			pair<ll, ll> urnHash = stringHash(urn), pwdHash = stringHash(pwd1);
			idToPassword[userNum] = pwdHash;
			idToUsername[userNum] = urnHash;
			usernameToId[urnHash] = userNum;
			ofstream outputFile("UserInfo.txt");
			assert(outputFile.is_open());
			outputFile << userNum << "\n";
			for(int i = 1; i <= userNum; ++i) {
				outputFile << idToUsername[i].first << " " << idToUsername[i].second << " " << idToPassword[i].first << " " << idToPassword[i].second << " ";
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
    	cout << "\033c";
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
