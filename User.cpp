#include "User.h"
using namespace std;

//User::User() {
//	Sno.clear();
//	college.clear();
//	ID.clear();
//	userName.clear();
//	Pno.clear();
//}

User::User(string _Sno, int _userType, string _college, string _ID, string _userName, string _Pno) {
//	puts("User Set");
	Sno = _Sno;
	userType = _userType;
	college = _college;
	ID = _ID;
	userName = _userName;
	Pno = _Pno;
//	puts("User Set Done");
}

//void User::Set(string _Sno, int _userType, string _college, string _ID, string _userName, string _Pno) {
//	puts("User Set");
//	Sno = _Sno;
//	userType = _userType;
//	college = _college;
//	ID = _ID;
//	userName = _userName;
//	Pno = _Pno;
//	puts("User Set Done");
//}
void User::Input() {
	cin >> Sno >> userType >> college >> ID >> userName >> Pno;
}

string User::getSno() {
	return Sno;
}

int User::getUserType() {
	return userType;
}

string User::getCollege() {
	return college;
}

string User::getID() {
	return ID;
}

string User::getUserName() {
	return userName;
}

string User::getPno() {
	return Pno;
}
