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
	bool is_leap_year;
//	bool bYears, bMonths, bDays;
//	bool isApplicant;
	
    lI = eRecords.getNumberOfEmployees();
	userOutFile.open("temp/tempReports.txt");
	userOutFile.close();
	userOutFile.open("temp/newReports.txt");
	userOutFile.close();
	
	//first loop: search per employee
	for (int i = 1; i <= lI; i++) {
//		cout << lI;
		sline << i;
		sline >> currentEmployeeID;
		sline.str(string());
		sline.clear();

		while (currentEmployeeID.length() < 6) {
			currentEmployeeID.insert(0, "0");
		}
		
//		cout << eRecords.getEmployeeInfo(currentEmployeeID.c_str(), "ees");
		if (eRecords.getEmployeeInfo(currentEmployeeID.c_str(), "ees") != "Applicant") {
//			cout << "entered here";
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
			nMonths = mActions.convertToIMonth(sMonths);
			stringstream tDays(sDays);
			tDays >> nDays;
			
			stringstream a(mActions.getDateTime(false, true).substr(8,4));
			a >> mYears;
			mMonths = mActions.convertToIMonth(mActions.getDateTime(false, true).substr(0,3));
			stringstream c(mActions.getDateTime(false, true).substr(4,2));			
			c >> mDays;
			
			//n starting date, m date today
//			cout << endl << "nMonths " << nMonths << " " << nDays << " " << nYears << endl;
//			cout << endl << "mMonths " << mMonths << " " << mDays << " " << mYears << endl;
			
			stringstream days;
			stringstream years;
			
			
			while (nYears <= mYears) {
				years.str(string());
				years.clear();
				years << nYears;
				years >> sYears;
				while (nMonths <= 12) {
					while (nDays <= mActions.numberOfDaysInMonth(nMonths, nYears)) {
						days.str(string());
						days.clear();
						days << nDays;
						days >> sDays;
						sMonths = mActions.convertToSMonth(nMonths);
						
//						cout << mActions.whatIsDayOfDate(nYears, nMonths, nDays)<< " ";
						if (mActions.whatIsDayOfDate(nYears, nMonths, nDays) > 0 && mActions.whatIsDayOfDate(nYears, nMonths, nDays) < 6) {
							doesReportExists(currentEmployeeID, sYears, sMonths, sDays);
							cout << "got here";
						}

						if (nYears == mYears && nMonths == mMonths && nDays == mDays) {
							break;
						}
						nDays++;	
					}
					if (nYears == mYears && nMonths == mMonths && nDays == mDays) {
						break;
					}
					nMonths++;
					nDays = 1;
				}
				nMonths = 1;
				nYears++;
			}	
		}	
	}
	
	
	
	ifstream tempIn("temp/newReports.txt");
	userInFile.open("database/timeReports.txt");
	userOutFile.open("temp.txt");
	
	if (tempIn.is_open() && userInFile.is_open() && userOutFile.is_open()) {
		getline(userInFile, temp); //ignore old lI
		getline(tempIn, temp); 
		temp += "\n";
		userOutFile << temp; //record new lI
		
		//get existing time reports
		while(getline(userInFile, temp)) {
			temp += "\n";
			userOutFile << temp;
		}
		
		//get newly generated time reports
		while(getline(tempIn, temp)) {
			temp += "\n";
			userOutFile << temp;
		}
	} else { 
		cout << endl << "Error 1 (autoGen): Unable to open file. ";
		
	}
	
	tempIn.close();
	userInFile.close();
	userOutFile.close();
	
	userInFile.open("temp.txt");
	userOutFile.open("database/timeReports.txt");
	
	if (userInFile.is_open() && userOutFile.is_open()) {
		while(getline(userInFile, temp)) {
			temp += "\n";
			userOutFile << temp;
		}
	} else { 
		cout << endl << "Error 2 (autoGen): Unable to open file.";
	}
	
	userInFile.close();
	userOutFile.close();
	
	remove("temp/tempReports.txt");
	remove("temp/newReports.txt");
	
}

int timeReports::getLastReportID(string fileName) {
	string line;
	int num, posStart, posEnd;
	
//	cout << endl << "filename is " << fileName; 
	
	num = 0; posStart = 0; posEnd = 0;
	
	userInFile.open(fileName.c_str());
	
	if (userInFile.is_open()) {
		getline(userInFile, line);
		posStart = line.find("$lI#") + 4;
		posEnd = line.find("$lI#", posStart);
		if (line.size() > 0) {
			line = line.substr(posStart, posEnd - posStart);
		}
		stringstream s(line);
		s >> num;
//		cout << "entered here";
//		cout << "num is " << num <<".";
		userInFile.close();
	} else {
		cout << "Error (getLastReportID): Unable to open file: " << fileName;		
	}
	
	return num;
		
}

//if report doesn't exist, add it
bool timeReports::doesReportExists(string empID, string workYear, string workMonth, string workDay) {
//	cout << endl << empID << " " << workYear << " " << workMonth << " " << workDay;
	string line, found, orig, nextID, temp;
	int posStart, posEnd, lastID;
	bool query1, query2, query3, query4, doIt;
	ofstream tempOut;
	ifstream tempIn;
	

//	cout << getLastReportID("database/timeReports.txt");
//	cout << getLastReportID("temp/newReports.txt");
	if (getLastReportID("database/timeReports.txt") > getLastReportID("temp/newReports.txt")) {
		lastID = getLastReportID("database/timeReports.txt");
//		cout << "lastID from timeReports";
	} else {
		lastID = getLastReportID("temp/newReports.txt");
//		cout << "lastID from newReports";
	}
	userInFile.open("database/timeReports.txt");
	doIt = true;
	if (userInFile.is_open()) {
		while (getline(userInFile, line)) {
			query1 = false; query2 = false; query3 = false; query4 = false;
//			cout << "last is " << last; 
			
			posStart = line.find("$tei#") + 5;
			posEnd = line.find("$tei#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			
//			cout << "found: " << found << " employeeID: " << empID << " ";
			if (found == empID) {
				query1 = true;
			}
			
			posStart = line.find("$twy#") + 5;
			posEnd = line.find("$twy#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			
			if (found == workYear) {
				query2 = true;
			}
			
			posStart = line.find("$twm#") + 5;
			posEnd = line.find("$twm#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			
			if (found == workMonth) {
				query3 = true;
			}
			
			posStart = line.find("$twd#") + 5;
			posEnd = line.find("$twd#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			
			if (found == workDay) {
				query4 = true;
			}
			
//			cout << endl << line;
//			cout << endl << empID << " " << workYear << " " << workMonth << " " << workDay;
//			cout << endl << query1 << query2 << query3 << query4 << endl;
			if (query1 && query2 && query3 && query4) {
				doIt = false; //time report found
			}
//			cout << "doIt: " << doIt << endl;

		}
		
		lastID++;
		stringstream sline;
		sline << lastID;
		sline >> nextID;
		while (nextID.length() < 6) {
			nextID.insert(0, "0");
		}
//		cout << "nextID is " << nextID; 
		
		if (doIt) {
			tempIn.open("temp/newReports.txt");
			tempOut.open("temp/tempReports.txt");
			
			if (tempIn.is_open() && tempOut.is_open()) {
				tempOut << "$lI#" + sline.str() + "$lI#\n";
				getline(tempIn, temp);
				while(getline(tempIn, temp)) {
					temp += "\n";
					tempOut << temp;
				}
				tempOut << "$tid#"+nextID+"$tid#$tei#"+empID+"$tei#$twy#"+workYear+"$twy#$twm#"+workMonth+"$twm#$twd#"+workDay+"$twd#$twh#$twh#$trs#No Report$trs#$trd#$trd#$tal#$tal#$ttd#$ttd#\n";
			} else { 
				cout << endl << "Error 2 (doesReportExists): Unable to open file. " << tempIn.is_open() << tempOut.is_open();
				
			}
			
			tempIn.close();
			tempOut.close();
			
			tempIn.open("temp/tempReports.txt");
			tempOut.open("temp/newReports.txt");
			
			if (tempIn.is_open() && tempOut.is_open()) {
				while(getline(tempIn, temp)) {
					temp += "\n";
					tempOut << temp;
				}
			} else { 
				cout << endl << "Error 3 (doesReportExists): Unable to open file.";
			}
			
			tempIn.close();
			tempOut.close();
		
//			userOutFile << "$tid#"+nextID+"$tid#$tei#"+empID+"$tei#$twy#"+workYear+"$twy#$twm#"+workMonth+"$twm#$twd#"+workDay+"$twd#$twh#$twh#$trs#No Report$trs#$trd#$trd#$tal#$tal#$ttd#$ttd#\n";
		}
		
		
		
		
		userInFile.close();
		userOutFile.close();
		
	} else {
		cout << endl << "Error 1 (doesReportExists): Unable to open file.";
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



