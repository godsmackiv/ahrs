#include <iostream>
#include <string>
#include "users.h"
#include "miscActions.h"

using namespace std;

int main(int argc, char** argv) {
	users usersDB;
	string testString; 
	gino test
	float f;
	miscActions m;
	
//	usersDB.test();
//	cout << usersDB.searchUserDB("000001", "id");
//	cout << usersDB.searchUserDB("qwertyui", "pw", &testString);
//	
//	cout << endl << testString;
//	f = m.askFloatInput(1);
//	cout << f;
//	usersDB.loginUser();
////	cout << "done logging test";
////	system("pause");
//	 
//	usersDB.viewDeductions(false);
//	usersDB.changePassword();
//	usersDB.changeDeductions();

//	testString = usersDB.getLastUserEntry();
//	cout << "the last line is: " << testString;
	usersDB.registerUser();

//	usersDB.updateUserDB("000003", "$id#000003$id#$pw#12345678$pw#$ln#Alvarez$ln#$fn#Ralph Louis$fn#$mn#Arizobal$mn#$ul#admin$ul#");
	
	return 0;
}
