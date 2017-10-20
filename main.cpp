#include <iostream>
#include <string>
#include "users.h"
#include "miscActions.h"

using namespace std;

int main(int argc, char** argv) {
	system("color 2f");
	system("color 0a");
	users usersDB;
	string testString; 
	int q;
	float f;
	miscActions m;
	
	usersDB.loginUser();
	while(1){
		if(usersDB.getUserLevel()=="manager"){
			system("cls");
			m.Menu();
			system("cls");
			m.loadingBar();
			system("cls");
			m.managerSubMenu();
		}
		else if(usersDB.getUserLevel()=="recruiter"){
			system("cls");
			m.Menu();
			system("cls");
			m.loadingBar();
			system("cls");
			m.recruiterSubMenu();
		}
		else if(usersDB.getUserLevel()=="personnel"){
			system("cls");
			m.Menu();
			system("cls");
			m.loadingBar();
			system("cls");
			m.personnelSubMenu();
		}
		else if(usersDB.getUserLevel()=="admin"){
			system("cls");
			m.Menu();
			system("cls");
			m.loadingBar();
			system("cls");
			m.adminSubMenu();
		}
	}




	
//	usersDB.loginUser();
//	usersDB.loginUser();
//	if(usersDB.getUserLevel()=="manager"){
//		 cout<<"manager";
//	}
//	else if(usersDB.getUserLevel()=="admin"){
//		cout<<"admin";
//	}

//	usersDB.searchUserDB("gaytos", "$ln#", &testString, true);
	usersDB.deleteUser();
//	usersDB.test();
//	cout << usersDB.searchUserDB("000001", "id");
//	cout << usersDB.searchUserDB("qwertyui", "pw", &testString);
//	
//	cout << endl << testString;
//	f = m.askFloatInput(1);
//	cout << f;
	
////	cout << "done logging test";
////	system("pause");
//	 
//	usersDB.viewDeductions(false);
//	usersDB.changePassword();
//	usersDB.changeDeductions();

//	testString = usersDB.getLastUserEntry();
//	cout << "the last line is: " << testString;
//	usersDB.registerUser();

//	usersDB.updateUserDB("000003", "$id#000003$id#$pw#12345678$pw#$ln#Alvarez$ln#$fn#Ralph Louis$fn#$mn#Arizobal$mn#$ul#admin$ul#");
	
	return 0;
}
