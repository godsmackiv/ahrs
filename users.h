#ifndef __USERS_H_INCLUDED__
#define __USERS_H_INCLUDED__

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "miscActions.h"

using namespace std;

class users {
	private:
		string userID, lastName, firstName, middleName, userLevel, password;
	//	int userLevel1;
		float pagibig, philhealth, sss, tax;
		ofstream userOutFile;
		ifstream userInFile;
		miscActions mActions;
	
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
		void registerUser(); //
		void deleteUser(); 
		void viewDeductions(bool); //
		void changeDeductions(); //
		bool searchUserDB(string, string); // basic; if found or not
		bool searchUserDB(string, string, string *, bool); //assigns string to *focus where query was found
//		bool searchUserDB(string, string, string); //search query within third arg string
 		//bool assignUserInfo();
		void updateUserDB(string, string); //
		string getLastUserEntry();
<<<<<<< HEAD
		string getValueFromEntry(string element, string entry); //gets specific value of a database element within a database entry
=======
		string getValueFromEntry(string, string); //gets specific value of a database element within a database entry
	//	int getUserLevel1(string);
>>>>>>> 0ecf5d9a136ec34182bde8c0617c652e30a0d876
};

#endif
