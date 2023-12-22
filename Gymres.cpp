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

void GymRes::Init() {//���ļ��ж�ȡ��Ϣ 
//	puts("???");
	FILE *fp = freopen("UserInfo.txt", "r", stdin);
	scanf("%d", &userNum);//��һ��һ������userNum����ʾ�û����� 
	user = new User[userNum + 1];
	ll a, b, c, d;
	for(int i = 1; i <= userNum; ++i) {
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);//ÿ��ǰ�ĸ����ֱ�ʾ�û���������Ĺ�ϣ
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
	for(int i = 0; i < SPORTSNUM; ++i) {//����ÿ���˶��ĳ���
		scanf("%d", &courtNum[i]);//�����������˶����ص�����
		court[i] = new Court[courtNum[i]];
		for(int j = 0; j < courtNum[i]; ++j) {//����������ÿ�����ص���Ϣ
			court[i][j].setSports(i);
			court[i][j].setID(j);
			court[i][j].setCourtId(++cnt);
			idToCourt[cnt] = &court[i][j];
			if(i == SWIMMING) {
				int cap;
				scanf("%d", &cap);
				court[i][j].setCap(cap);
			}//������Ӿ��,��Ҫ�������볡�ص�����
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
	
	
	
//	��������δ�����ע�ͺ����������ɹ���Ա���˺����� 
//	pair<ll, ll> a = stringHash("Administrator"), b = stringHash("123456");
//	freopen("CipherBook.txt", "w", stdout);
//	puts("1");
//	printf("%lld %lld %lld %lld\n", a.first, a.second, b.first, b.second);
//	return;

	Init();
    while(1) {
//    	Pause();
        cout << "\033c";
        printf("��ӭ����������ԤԼϵͳ\n1 - ��¼\n2 - ע��\n3 - �˳�");
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
			return t;//������ȷ��������id 
		}
		else {
			return 0;//������� 
		}
	}
	return -1;//�û��������� 
}

void GymRes::Login() {
    string username, password;
    int wrongTime;
	while(1) {
		fflush(stdout);
		cout << "\033c";
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
//				Pause();
				int t = checkPassword(username, password);
				if(t > 0) {
					functionChoose(t); 
					return;
				}
				else {
					if(++wrongTime == 3){
						puts("��������ﵽ����");
						Pause("�����������"); 
						return;
					}
					if(t == 0)
						puts("�������");
					else {
						puts("�û���������");
						Pause("�����������"); 
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
		cout << "��ã�" << user[userId].getUserName() << "\n";
		if (user[userId].getUserType() == ADMINIS) {
			cout << "��������Ĳ�����" << endl;
			cout << "1 - �鿴ԤԼ��¼" << endl;
			cout << "2 - ����Ԥ��" << endl;
			cout << "3 - ע����¼" << endl;
			char select = getch();
			if (select == '1') {
				showRes(userId);
			}
			else if (select == '2') {
				
			}
			else if (select == '3') {
				cout << "\033c";
				cout << "��ӭ���´ι��٣�" << endl;
				Pause("��������˳�"); 
				return;
			}
		}
		else {
			cout << "��������Ĳ�����" << endl;
			cout << "1 - ����ԤԼ" << endl;
			cout << "2 - �鿴ԤԼ��¼" << endl;
			cout << "3 - ע����¼" << endl;
			char select = getch();
			if (select == '1') {
				sportsChoose(userId);
			}
			else if (select == '2') {
				showRes(userId);
			}
			else if (select == '3') {
				cout << "\033c";
				cout << "��ӭ���´ι��٣�" << endl;
				Pause("��������˳�"); 
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
					printf("%c - ԤԼʱ��: %d-%02d-%02d.%02d:00-%02d:00\n", idToChar(cnt), tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
					cout << "    ԤԼ����: " << sportsName[crt->getSports()] << crt->getID() + 1 << "�ų���\n";
					cout << "    ԤԼ�û�id: ";
					for(int i = 0; i < num; ++i) {
						cout << it->second[i] << " ";
					}
					puts("");
				}
			}
			puts("0 - ����\n���¶�Ӧ���ּ���ȡ��ԤԼ");
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
					printf("%c - ԤԼʱ��: %d-%02d-%02d.%02d:00-%02d:00\n", idToChar(cnt), tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
					cout << "    ԤԼ����: " << sportsName[crt->getSports()] << crt->getID() + 1 << "�ų���\n";
				}
			}
			puts("0 - ����\n���¶�Ӧ���ּ���ȡ��ԤԼ");
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
			cout << "����ȡ��: " << crt->getSports() << " " << crt->getID() + 1 << "�ų���";
			printf("%d-%02d-%02d.%02d:00-%02d:00ʱ��ε�ԤԼ\n", tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
			puts("��ѡ��Ҫȡ�����û�id\n");
			for(int i = 0; i < num; ++i) {
				printf("%c - %d\n", idToChar(i + 1), it->second[i]);
			}
			puts("0 - ȡ��"); 
			char c = getch();
			int x = charToId(c);
			if(!x) {
				return;
			}
			if(x >= 1 && x <= num) {
				it->second.erase(it->second.begin() + x - 1);
				writeResInfo();
				puts("ȡ���ɹ�");
				Pause("�����������");
				return; 
			}
		}
	}
	else {
		while(1) {
			cout << "\033c";
			cout << "����ȡ��: " << crt->getSports() << " " << crt->getID() + 1 << "�ų���";
			printf("%d-%02d-%02d.%02d:00-%02d:00ʱ��ε�ԤԼ\n", tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
			puts("�Ƿ�ȷ��ȡ��ԤԼ? y/n\n");
			char c = getch();
			if(c == 'y' || c == 'Y') {
				it->second.erase(find(it->second.begin(), it->second.end(), userId));
				writeResInfo();
				puts("ȡ���ɹ�");
				Pause("�����������");
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
	printf("%d\n", res.size());//ԤԼ��¼�ļ��ĵ�һ�б�ʾԤԼ������ 
	for(map<pair<TimeSeg, int>, vector<int> >::iterator i = res.begin(); i != res.end(); i++) {
		//����ÿ��ԤԼ����һ�б�ʾʱ��εĿ�ʼʱ�� ԤԼ���ص��˶������id
		tsg = (i->first).first;
		crt = idToCourt[(i->first).second];
		printf("%d %2d %2d %2d %d\n", tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), crt->getCourtId());
		int n = i->second.size();
		printf("%d ", n);//�����б�ʾ���ʱ��ԤԼ������ص����� 
		for(int j = 0; j < n; ++j) {
			printf("%d ", i->second[j]);//Ȼ������ʱ��ԤԼ���ʱ��������˵�id 
		}
		puts(""); 
	}
	fflush(fp);
	freopen("CON", "w", stdout);
}

void GymRes::sportsChoose(int userId) {//ѡ���˶�������
	while(1) {
		cout << "\033c";
		puts("ԤԼ����\n��ѡ���˶�");
		for(int i = 0; i < SPORTSNUM; ++i) {
			cout << i + 1 << "-" << sportsName[i] << "\n";
		}
		puts("0-����");
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
//������һ���˶������г��غͳ�������, Ҫ����ʾÿ������,����ѡ����
	while(1) {
		cout << "\033c";
		cout << "ԤԼ" << sportsName[crt[0].getSports()] << "����\n";
		puts("��ѡ�񳡵�");
		for(int i = 0; i < num; ++i) {
			printf("%d-%d�ų���\n", i + 1, i + 1);
		}
		puts("0-����");
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
	//ѡ�����˶�����ͳ���, �������鿴�ó��ص�δ�������ԤԼ���
	while(1) {
		cout << "\033c";
		fflush(stdout);
		cout << "ԤԼ" << sportsName[idToCourt[crtId]->getSports()] << idToCourt[crtId]->getID() + 1 << "�ų���\n";
	    time_t now = std::time(NULL);
	    tm* localTime = std::localtime(&now);
	    int year = localTime->tm_year + 1900;
	    int month = localTime->tm_mon;
	    int day = localTime->tm_mday;
	    int hour = localTime->tm_hour;
	    int cnt = 0;
	    hour = hour >> 1 << 1;//����ʱ��ε���ʼʱ�� 
	    TimeSeg ts(year, month, day, hour);
	    TimeSeg *p = new TimeSeg[30];
	    if(ts.getHour() >= 22) {//���ڵ�ʱ���Ѿ�����˵��������ԤԼʱ���
	    	ts.addOneDay();//��ӵڶ��쿪ʼ��������ԤԼ��¼ 
		}
		else if(ts.getHour() >= 8) {//���ڵ���Ŀ�ԤԼʱ����
			while(ts.getHour() < 22) {
				p[++cnt] = ts;
				printf("%c - %d.%02d.%02d %02d:00-%02d:00 ԤԼ����:%2d/%2d\n", idToChar(cnt), ts.getYear(), ts.getMonth(), ts.getDay(), ts.getHour(), ts.getHour() + 2, res[make_pair(ts, crtId)].size(), idToCourt[crtId]->getCap());
				ts.addTwoHours();
			}
			ts.addOneDay();
		}//����һ��������ǵ����ԤԼʱ�λ�û��ʼ����ʹӵ��쿪ʼ��������ԤԼ��¼ 
		for(int i = 0; i < 2; ++i) {
			ts.setHour(8);
			while(ts.getHour() < 22) {
				p[++cnt] = ts;
				printf("%c - %d.%02d.%02d %02d:00-%02d:00 ԤԼ����:%2d/%2d\n", idToChar(cnt), ts.getYear(), ts.getMonth(), ts.getDay(), ts.getHour(), ts.getHour() + 2, res[make_pair(ts, crtId)].size(), idToCourt[crtId]->getCap());
				ts.addTwoHours();
			}
			ts.addOneDay();
		}
		puts("0 - ����");
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
		puts("�ó���ԤԼ��������");
		Sleep(2000);
		return; 
	}
	while(1) {
		cout << "\033c";
		cout << "ԤԼ����: " << sportsName[idToCourt[crtId]->getSports()] << idToCourt[crtId]->getID()+ 1 << "�ų���\n";
		printf("ԤԼʱ��: %d-%02d-%02d.%02d:00-%02d:00\n", tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
		puts("ȷ��ԤԼ��?y/n");
		char c = getch();
		if(c == 'y' || c == 'Y') {
			res[make_pair(tsg, crtId)].push_back(usrId);//�����ԤԼ��¼��res�� 
			writeResInfo();
			puts("ԤԼ�ɹ�");
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
		puts("ע�����û�");
		if(urn == "") {
			puts("�������û���");
			cin.clear();
			cin >> urn;
			if(usernameToId[stringHash(urn)]) {
				puts("�û����ѱ�ע��, ����������");
				urn = ""; 
				Sleep(1800); 
			}
//			cout << "" << username << "\n";
//			puts("!!!");
			goto ifEnd;
		}
		else {
			cout << "�û���: " << urn << "\n"; 
		} 
		if(!done1) {
			puts("����������");
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
			puts("��ȷ������");
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
			puts("�������벻һ��");
			pwd1 = pwd2 = "";
			done1 = done2 = 0;
			Sleep(800);
			goto ifEnd;
		}
		if(userType == -1) {
			cout << "��ѡ���û�����\n";
			for(int i = 0; i < 3; ++i) {
				cout << i + 1 << "-" << userTypeName[i] << "\n";
			}
			puts("0-����"); 
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
			cout << "�û�����:" << userTypeName[userType] << "\n";
			puts("����������");
			cin >> userName;
			puts("���������֤��");
			cin >> ID; 
			puts("������绰����");
			cin>>Pno;
			if(userType==STUDENT||userType==FACULTY||userType==ADMINIS)
			{
				puts("������ѧԺ");
				cin>>college; 
			 }
			if(userType==STUDENT||userType==ADMINIS)
			{
				puts("������ѧ��");
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
			puts("ע��ɹ�, ��������ҳ");
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
