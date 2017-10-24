#ifndef __TIMEREPORTS_H_INCLUDED__
#define __TIMEREPORTS_H_INCLUDED__
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "miscActions.h"
#include "employeeRecords.h"
#include "departments.h"

using namespace std;

class timeReports{
	private:
		ofstream trOutFile;
		ifstream trInFile;
		
		employeeRecords eRecords;
		departments dRecords;
		
		
//		string timeRepID, employeeID, reportStatus, totalWorkHours, disapproval, adjustments, adjustmentTimeLog;
	public:
		void viewNoTimeReports();
		void viewWithTimeReports();
		void enterTimeReport();
		void employeeTimeReports();
		void displayTimeReport();
		void adjustTimeReport();
		void deleteAdjustment();
		void viewSubmittedReports();
		void disapproveReport();
		
		void autoGenerateTimeReports(); //must be run during start of program and hiring of an employee, finds days automatically with no time reports		
				
		bool doesReportExists(string, string, string, string); // checks if a specific time report of individual exists
		void updateTimeReportDB(string, string);
		string getValueFromEntry(string element, string entry); //gets specific value of a database element within a database entry		
		bool searchTimeReportDB(string, string, string *, bool); //assigns string to *focus where query was found
		int getLastReportID(string);
};

#endif
