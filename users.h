#ifndef __USERS_H_INCLUDED__
#define __USERS_H_INCLUDED__

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class users {
	private:
		string userID, lastName, firstName, middleName, userLevel, password;
		float pagibig, philhealth, sss, tax;
		ofstream userOutFile;
		ifstream userInFile;
	
	public:
		string getUserID(void);
		string getLastName(void);
		string getFirstName(void);
		string getMiddleName(void);
		string getUserLevel(void);
		string getPassword(void);
		
		void setUserID(string);
		void setLastName(string);
		void setFirstName(string);
		void setMiddleName(string);
		void setUserLevel(string);
		void setPassword(string);
		
		void loginUser(); //
		void changePassword(); //
		void registerUser();
		void deleteUser();
		void loadDeductions(); //
		void viewDeductions(); //
		void changeDeductions(); 
		bool searchUserDB(string, string); // basic
		bool searchUserDB(string, string, string *); //assigns string to *focus where query was found
//		bool searchUserDB(string, string, string); //search query within third arg string
 		//bool assignUserInfo();
		void updateUserDB(string, string);
};

#endif
