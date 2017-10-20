#include "timeReports.h"

void timeReports::viewNoTimeReports() {
	stringstream sline;
	
	
	
	
//	for (int i = 1; ) 
	//for each non-applicant employee
	//get worker's starting date
	//for each to cut off periods of each month of to current month, determine if there are missing time reports
	//
	
	
}

void timeReports::autoGenerateTimeReports() {
	int lI, nYears, nMonths, nDays, mYears, mMonths, mDays;
	string sYears, sMonths, sDays, temp, currentEmployeeID;
	stringstream sline;
//	bool bYears, bMonths, bDays;
//	bool isApplicant;
	
    lI = eRecords.getNumberOfEmployees();
	
	//first loop: search per employee
	for (int i = 0; i <= lI; i++) {
//		cout << lI;
		sline << i;
		sline >> currentEmployeeID;
		sline.str(string());
		sline.clear();

		while (currentEmployeeID.length() < 6) {
			currentEmployeeID.insert(0, "0");
		}
		
		if (eRecords.getEmployeeInfo(currentEmployeeID.c_str(), "ees") == "Applicant") {
			sYears = eRecords.getEmployeeInfo(currentEmployeeID.c_str(), "esd");
			if (sYears.size() > 0) {
				sDays = sYears.substr(4, 2);
				sMonths = sYears.substr(0, 3);
				sYears = sYears.substr(7, 4);	
			}
//			cout << endl << sMonths << " " << sDays << " " << sYears;
//			
			stringstream tYears(sYears);
			tYears >> nYears;
			nMonths = mActions.convertMonth(sMonths);
			stringstream tDays(sDays);
			tDays >> nDays;
			
			stringstream a(mActions.getDateTime(false, true).substr(8,4));
			a >> mYears;
			mMonths = mActions.convertMonth(mActions.getDateTime(false, true).substr(0,3));
			stringstream c(mActions.getDateTime(false, true).substr(5,2));			
			c >> mDays;

			cout << endl << nMonths << " " << nDays << " " << nYears << endl;
			
			for(int j = 0; j < mYears - nYears; j++) {
				for(int k = 0; k < 12; k++) {
					//if current year, should just be january to latest month, not all 12 months
							
					for(int l = 0; l < 22; l++) {
						//if current year and month, should just be day 1 to latest, not all 22 
						
					}
				}
			}
			
			
		}
		
		
	}
	
	

	 
	
}

bool timeReports::doesReportExists(string employeeID, string year, string month, string day ) {
	string line, found;
	int posStart, posEnd;
	bool query1, query2, query3, query4;
	
	
	userInFile.open("database/timeReports.txt");
	if (userInFile.is_open()) {
		while (getline(userInFile, line)) {
			posStart = line.find("$"+type+"#") + 4;
			posEnd = line.find("$"+type+"#", posStart);
			found = line.substr(posStart, posEnd - posStart);
		} 
	}
	
	
	return false;
}

void timeReports::enterTimeReport() {
	string newTimeRepID, newEmployeeID, newMonth, newYear, newWorkDate, newReportStatus, newTotalWorkHours;
	string newDisapproval, newAdjustments, newAdjustmentTimeLog, temp;
	int lI;
	bool repeat;
	char s;
	stringstream sline, sLI;
	
	system("cls");		
	
	userInFile.open("database/timeReports.txt");
	userOutFile.open("temp.txt");


	repeat = true;
	while (repeat) {
		cout << endl << "Please enter the employee ID: ";
		getline(cin, newEmployeeID);
//		cout << eRecords.searchEmployee(newEmployeeID, "eid");
		if (eRecords.searchEmployee(newEmployeeID, "eid")) {
			repeat = false;
		} else {
			cout << "Error: No employee exists with that ID." << endl;
			cout << "Note: Make sure you don't enter any spaces." << endl;
			system("pause");
		}
	}
	
	repeat = true;
	if (userInFile.is_open() && userOutFile.is_open()){
		while (getline(userInFile, temp)) {
			if (repeat) {
				sline << getValueFromEntry("$lI#", temp);
				sline >> lI;
				sline.str(string());
				sline.clear();	
				
				cout << endl << "Please indicate the year of work: ";
				getline(cin, newYear);
				
				cout << endl << "Please indicate the month of work: ";
				getline(cin, newMonth);
				
				cout << endl << "Please indicate the day of work (1-11 or 12-22): ";
				getline(cin, newWorkDate);
				
				cout << endl << "Input the hours that worker clocked in for that work day: ";
				getline(cin, newTotalWorkHours);
			
				lI++;
				sline.str(string());
				sline.clear();
				sline << lI;
				sline >> newTimeRepID;
				while (newTimeRepID.length() < 6) {
					newTimeRepID.insert(0, "0");
				}	
			}
			repeat = false;
			
			temp += "\n";
			userOutFile << temp;
		}
		
		userOutFile << "$tid#"+newTimeRepID+"$tid#$tei#"+newEmployeeID+"$tei#$twy#"+newYear+"$twy#$twm#"+newMonth+"$twm#$twd#"+newWorkDate+"$twd#$twh#"+newTotalWorkHours+"$twh#$trs#$trs#$trd#$trd#$tal#$tal#$ttd#$ttd#";
		
		userInFile.close();
		userOutFile.close();
		
		ifstream fileIn("temp.txt");
		ofstream fileOut("database/timeReports.txt");
		
		repeat = true;
		if (fileIn.is_open() && fileOut.is_open()) {
			while (getline(fileIn, temp)) {
				if (repeat) {
					sLI << lI;
					fileOut << "$lI#"+sLI.str()+"$lI#\n";
					repeat = false;
				} else {
					temp += "\n";
					fileOut << temp;
				}
				
			}
			fileIn.close();
			fileOut.close();	
		} else {
			cout << endl << "Error: Unable to update Time Reports database."; 
		}
	remove("temp.txt");	
	} else {
		cout << endl << "Error: Unable to open Time Reports database."; 
	}
}

void timeReports::employeeTimeReports() {
	
}

void timeReports::approveTimeReport() {
	
}

void timeReports::adjustTimeReport() {
	
}

void timeReports::deleteAdjustment() {
	
}

void timeReports::viewSubmittedReports() {
	
}

void timeReports::disapproveReport() {
	
}

void timeReports::updateTimeReportDB(string reportID, string newInfo) {
	
	string temp, orig;
	int posStart, posEnd, id;
	
	userInFile.open("database/time reports.txt");
	userOutFile.open("temp.txt");
	
	if (userInFile.is_open() && userOutFile.is_open()){
		while (getline(userInFile, temp)) {
			orig = temp;
			posStart = temp.find("$tid#") + 5;
			posEnd = temp.find("$tid#", posStart);
			if (reportID == temp.substr(posStart, posEnd - posStart)) {
				orig = newInfo;
			}
			orig += "\n";
			userOutFile << orig;
		}
		
		userInFile.close();
		userOutFile.close();
		
		ifstream fileIn("temp.txt");
		ofstream fileOut("database/time reports.txt");
		
		if (fileIn.is_open() && fileOut.is_open()) {
			while (getline(fileIn, temp)) {
				temp += "\n";
				fileOut << temp;
			}
			
			fileIn.close();
			fileOut.close();	
		} else {
			cout << endl << "Error: Unable to update Time Reports database."; 
		}
	remove("temp.txt");	
	} else {
		cout << endl << "Error: Unable to open Time Reports database."; 
	}
	
	
}

string timeReports::getValueFromEntry(string element, string entry) { //gets specific value of a database element within a database entry
	int posStart, posEnd;
	
	posStart = entry.find(element) + 5;
	posEnd = entry.find(element, posStart);
	
	if (posEnd == -1) {
		return "n/a";
	} else {
		return entry.substr(posStart, posEnd - posStart);	
	}
}

bool timeReports::searchTimeReportDB(string query, string, string *focus, bool keepSearching)  { //assigns string to *focus where query was found

}



