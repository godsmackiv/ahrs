#ifndef __MISCACTIONS_H_INCLUDED__
#define __MISCACTIONS_H_INCLUDED__

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include "users.h"

class users;
using namespace std;

class miscActions {
	private:
		char task;
		char perform,report;
		ofstream userOutFile;
		ifstream userInFile;
		users *u;
			
	public:
		float askFloatInput(int); //
		int askIntInput(int); //
		stringstream clearSStream(stringstream);
		string trimOuterSpaces(string);
		void Menu(void);
		void managerSubMenu(void);
		void recruiterSubMenu(void);
		void personnelSubMenu(void);
		void adminSubMenu(void);
		void loadingBar(void);
		void viewReports(void);
		string hidePass(void);
	 	
		string getDateTime(bool timeOnly, bool dateOnly);
		int getYear();
		int convertToIMonth(string);
		string convertToSMonth(int);
		bool isLeapYear(int);
		int numberOfDaysInMonth(int, int);
		int whatIsDayOfDate(int, int, int);
		int stringToInt(string);
		string intToString(int);
				
};



#endif
