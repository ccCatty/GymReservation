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

void GymRes::Init() {//���ļ��ж�ȡ��Ϣ 
//	puts("???");
	FILE *fp = freopen("UserInfo.txt", "r", stdin);
	scanf("%d", &userNum);//��һ��һ������userNum����ʾ�û����� 
	user = new User[userNum + 1];
	ll a, b, c, d;
	for(int i = 1; i <= userNum; ++i) {
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);//ÿ��ǰ�ĸ����ֱ�ʾ�û���������Ĺ�ϣ
		password[i] = make_pair(c, d);
		username[i] = make_pair(a, b);
		id[make_pair(a, b)] = i;
		user[i].Input();
	}
	fflush(fp);
	fp = freopen("CourtInfo.txt", "r", stdin);
	for(int i = 0; i < SPORTSNUM; ++i) {//����ÿ���˶��ĳ���
		scanf("%d", &courtNum[i]);//�����������˶����ص�����
		court[i] = new Court[courtNum[i]];
		for(int j = 0; j < courtNum[i]; ++j) {//����������ÿ�����ص���Ϣ
			court[i][j].setSports(i);
			court[i][j].setID(j);
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
					functionChoose(t); 
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

void GymRes::functionChoose(int userId) {
	while(1) {
		system("CLS");
		cout << "��ã�" << user[userId].getUserName() << "\n";
		if (user[userId].getUserType() == ADMINIS) {
			cout << "��������Ĳ�����" << endl;
			cout << "1.�鿴ԤԼ" << endl;
			cout << "2.����Ԥ��" << endl;
			cout << "3." << endl;
			cout << "4.ע����¼" << endl;
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
				cout << "��ӭ���´ι��٣�" << endl;
				system("pause");
				return;
			}
			else {
				cout << "��������ȷ��ѡ�" << endl;
				system("pause");
			}
		}
		else {
			cout << "��������Ĳ�����" << endl;
			cout << "1.ѡ��ԤԼ" << endl;
			cout << "2.�鿴ԤԼ" << endl;
			cout << "3.ȡ��ԤԼ" << endl;
			cout << "4.ע����¼" << endl;
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
				cout << "��ӭ���´ι��٣�" << endl;
				system("pause");
				return;
			}
			else {
				cout << "��������ȷ��ѡ�" << endl;
				system("pause");
			}
		}
		
	}
}

void GymRes::sportsChoose(int userId) {//ѡ���˶�������
	while(1) {
		system("CLS");
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
		system("CLS");
		cout << "ԤԼ" << sportsName[crt[0].getSports()] << "����\n";
		puts("��ѡ�񳡵�");
		for(int i = 0; i < num; ++i) {
			printf("%d-%d�ų���\n", i + 1, i + 1);
		}
		puts("0-����");
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
	//ѡ�����˶�����ͳ���, �������鿴�ó��ص�δ�������ԤԼ���
	while(1) {
		system("CLS");
		cout << "ԤԼ" << sportsName[crt.getSports()] << crt.getID() << "�ų���\n";
	    std::time_t now = std::time(NULL);
	    std::tm* localTime = std::localtime(&now);
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
				printf("%c - %d.%02d.%02d %02d:00-%02d:00 ԤԼ����:%2d/%2d\n", id2char(cnt), ts.getYear(), ts.getMonth(), ts.getDay(), ts.getHour(), ts.getHour() + 2, res[make_pair(ts, crt)].size(), crt.getCap());
				ts.addTwoHours();
			}
			ts.addOneDay();
		}//����һ��������ǵ����ԤԼʱ�λ�û��ʼ����ʹӵ��쿪ʼ��������ԤԼ��¼ 
		for(int i = 0; i < 2; ++i) {
			ts.setHour(8);
			while(ts.getHour() < 22) {
				p[++cnt] = ts;
				printf("%c - %d.%02d.%02d %02d:00-%02d:00 ԤԼ����:%2d/%2d\n", id2char(cnt), ts.getYear(), ts.getMonth(), ts.getDay(), ts.getHour(), ts.getHour() + 2, res[make_pair(ts, crt)].size(), crt.getCap());
				ts.addTwoHours();
			}
			ts.addOneDay();
		}
		char c = getch();
		int x = char2id(c);
		if(x >= 1 && x <= cnt) {
//			printf("ѡ����%c\n", id2char(x));
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
		puts("�ó���ԤԼ��������");
		Sleep(2000);
		return; 
	}
	while(1) {
		system("CLS");
		cout << "ԤԼ����: " << crt.getSports() << crt.getID() << "�ų���\n";
		printf("ԤԼʱ��: %d-%02d-%02d.%02d:00-%02d:00\n", tsg.getYear(), tsg.getMonth(), tsg.getDay(), tsg.getHour(), tsg.getHour() + 2);
		puts("ȷ��ԤԼ��?y/n");
		char c = getch();
		if(c == 'y' || c == 'Y') {
			res[make_pair(tsg, crt)].push_back(usrId);
			puts("ԤԼ�ɹ�");
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
		puts("ע�����û�");
		if(urn == "") {
			puts("�������û���");
			cin.clear();
			cin >> urn;
			if(id[stringHash(urn)]) {
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
