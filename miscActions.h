#ifndef __MISCACTIONS_H_INCLUDED__
#define __MISCACTIONS_H_INCLUDED__
#include "users.h"
#include "departments.h"
#include "locations.h"
#include "jobPositions.h"
#include "benefits.h"
#include "employeeRecords.h"
#include "jobOpenings.h"
#include "timeReports.h"
#include <string>
#include <sstream>
#include <iostream>
class users;
using namespace std;

class miscActions {
	private:
		char task;
		char perform,report;
		ofstream userOutFile;
		ifstream userInFile;
		
//		users *u;
		departments dept;
		locations loc;
		jobPositions jp;
		benefits ben;
		employeeRecords er;
		jobOpenings jo;
//		timeReports tr;
		
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
		void viewReports(char);
		string hidePass(void);
		void managerView(char);
		void viewEmployee();
		char getTask();
		string getDateTime(bool timeOnly, bool dateOnly);
		int getYear();
		int convertToIMonth(string);
		string convertToSMonth(int);
		bool isLeapYear(int);
		int numberOfDaysInMonth(int, int);
		int whatIsDayOfDate(int, int, int);
		int stringToInt(string);
		string intToString(int);
		int getLastDeptID();
		string getDepartmentInfo(string ID, string type);
		
		
};



#endif
