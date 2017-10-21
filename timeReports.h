#ifndef __TIMEREPORTS_H_INCLUDED__
#define __TIMEREPORTS_H_INCLUDED__
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "miscActions.h"
#include "employeeRecords.h"


using namespace std;

class timeReports{
	private:
		ofstream userOutFile;
		ifstream userInFile;
		miscActions mActions;
		employeeRecords eRecords;
		
		string timeRepID, employeeID, reportStatus, totalWorkHours, disapproval, adjustments, adjustmentTimeLog;
	public:
		void viewNoTimeReports();
		void enterTimeReport();
		void employeeTimeReports();
		void approveTimeReport();
		void adjustTimeReport();
		void deleteAdjustment();
		void viewSubmittedReports();
		void disapproveReport();
		
		void autoGenerateTimeReports(); //must be run during start of program, finds days automatically with no time reports		
				
		bool doesReportExists(string, string, string, string); // checks if a specific time report of individual exists
		void updateTimeReportDB(string, string);
		string getValueFromEntry(string element, string entry); //gets specific value of a database element within a database entry		
		bool searchTimeReportDB(string, string, string *, bool); //assigns string to *focus where query was found
		int getLastReportID(string);
};

#endif
