#include "User.h"
using namespace std;

User::User() {
	
}

void User::Input() {
	cin >> Sno >> type >> college >> ID >> name >> Pno;
}

User::name_t User::getName() {
	return name;
}
