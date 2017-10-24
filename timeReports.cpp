#include "timeReports.h"

void timeReports::viewNoTimeReports() {
	miscActions mActions;
	stringstream sline;
	string temp;
	string *noReportEmployees;
	int lastEmployeeID, lastAddedPos;
	bool isAdded;
//	int ctr;
	
	system("cls");
	cout << endl << "Here are the list of employees without (or with missing) time reports:";
	
	trInFile.open("database/timeReports.txt");
	trInFile.clear();
	
	lastEmployeeID = eRecords.getNumberOfEmployees();
	getline(trInFile, temp);
	trInFile.clear();
	noReportEmployees = new string[lastEmployeeID];
	
	lastAddedPos = 0;
	if (trInFile.is_open()) {
		while(getline(trInFile, temp)) {
			trInFile.clear();
			
			if (getValueFromEntry("$trs#", temp) == "No Report") {
				temp = getValueFromEntry("$tei#", temp);
//				cout << endl << temp;
				
				isAdded = false;
				for(int i = 0; i < lastEmployeeID - 1; i++) {
					if (noReportEmployees[i] == temp) {
						isAdded = true;
						break;
					}
				}
				if (!isAdded) {
//					cout << "adding";
					noReportEmployees[lastAddedPos] = temp;
		//				cout << noReportEmployees[lastAddedPos];
					lastAddedPos++;			
				}
			}
			

		}
		
		cout << endl << "\tEmployee ID\tEmployee Name";
		cout << endl << "\t___________\t_____________";
		for (int i = 0; i < lastEmployeeID; i++) {
			if (noReportEmployees[i] != "") {
//				cout << "hey";
				cout << endl << "\t" << noReportEmployees[i] << "\t\t";
				cout << eRecords.getEmployeeInfo(noReportEmployees[i], "ena");
			}
		}
		trInFile.close();
	} else {
		cout << endl << "Error (viewNoTimeReports): Unable to open Time Reports database.";
	}
	
	delete[] noReportEmployees;
}

void timeReports::viewWithTimeReports() {
	miscActions mActions;
	stringstream sline;
	string temp;
	string *noReportEmployees;
	int lastEmployeeID, lastAddedPos;
	bool isAdded;
//	int ctr;
	
	system("cls");
	cout << endl << "Here are the list of employees with partial/complete time reports:";
	
	trInFile.open("database/timeReports.txt");
	trInFile.clear();
	
	lastEmployeeID = eRecords.getNumberOfEmployees();
	getline(trInFile, temp);
	trInFile.clear();
	noReportEmployees = new string[lastEmployeeID];
	
	lastAddedPos = 0;
	if (trInFile.is_open()) {
		while(getline(trInFile, temp)) {
			trInFile.clear();
			
			if (getValueFromEntry("$trs#", temp) == "No Report") {
				temp = getValueFromEntry("$tei#", temp);
//				cout << endl << temp;
				
				isAdded = false;
				for(int i = 0; i < lastEmployeeID - 1; i++) {
					if (noReportEmployees[i] == temp) {
						isAdded = true;
						break;
					}
				}
				if (!isAdded) {
//					cout << "adding";
					noReportEmployees[lastAddedPos] = temp;
		//				cout << noReportEmployees[lastAddedPos];
					lastAddedPos++;			
				}
			}
			

		}
		
		cout << endl << "\tEmployee ID\tEmployee Name";
		cout << endl << "\t___________\t_____________";
		for (int i = 0; i < lastEmployeeID; i++) {
			if (noReportEmployees[i] != "") {
//				cout << "hey";
				cout << endl << "\t" << noReportEmployees[i] << "\t\t";
				cout << eRecords.getEmployeeInfo(noReportEmployees[i], "ena");
			}
		}
		trInFile.close();
	} else {
		cout << endl << "Error (viewNoTimeReports): Unable to open Time Reports database.";
	}
	
	delete[] noReportEmployees;
}


void timeReports::autoGenerateTimeReports() {
	miscActions mActions;
	int lI, nYears, nMonths, nDays, mYears, mMonths, mDays, cutoffPeriod, lastCutoff;
	string sYears, sMonths, sDays, temp, currentEmployeeID, sCutoffPeriod;
	stringstream sline;
	
    lI = eRecords.getNumberOfEmployees();
	trOutFile.open("temp/tempReports.txt");
	trOutFile.close();
	trOutFile.open("temp/newReports.txt");
	trOutFile.close();
	
	//first loop: search per employee
	for (int i = 1; i <= lI; i++) {
		currentEmployeeID = mActions.intToString(i);

		while (currentEmployeeID.length() < 6) {
			currentEmployeeID.insert(0, "0");
		}
		
		//get starting date from employee database
		if (eRecords.getEmployeeInfo(currentEmployeeID.c_str(), "ees") != "Applicant") {
			sYears = eRecords.getEmployeeInfo(currentEmployeeID.c_str(), "esd");
			if (sYears.size() > 0) {
				sDays = sYears.substr(4, 2);
				sMonths = sYears.substr(0, 3);
				sYears = sYears.substr(7, 4);	
			}

			//STARTING DATE in int form
			nYears = mActions.stringToInt(sYears);
			nMonths = mActions.convertToIMonth(sMonths);	
			nDays = mActions.stringToInt(sDays);
			
			//CURRENT DATE in int form
			mYears = mActions.stringToInt(mActions.getDateTime(false, true).substr(8,4));
			mMonths = mActions.convertToIMonth(mActions.getDateTime(false, true).substr(0,3));
			mDays = mActions.stringToInt(mActions.getDateTime(false, true).substr(4,2));

			
			if (nDays < 16) {
				cutoffPeriod = 1;
			} else {
				cutoffPeriod = 2;
			}
			
			if (mDays < 16) {
				lastCutoff = 1;
			} else {
				lastCutoff = 2;
			}
			
			while (nYears <= mYears) {
				
				sYears = mActions.intToString(nYears);
				while (nMonths <= 12) {
					
					while (cutoffPeriod <= 2) {
						sCutoffPeriod = mActions.intToString(cutoffPeriod);
						sMonths = mActions.convertToSMonth(nMonths);
						doesReportExists(currentEmployeeID, sYears, sMonths, sCutoffPeriod);						

						if (nYears == mYears && nMonths == mMonths && cutoffPeriod == lastCutoff) {
							break;
						}
						cutoffPeriod++;	
					}
					
					if (nYears == mYears && nMonths == mMonths && cutoffPeriod == lastCutoff) {
						break;
					}
					nMonths++;
					cutoffPeriod = 1;
				}
				nMonths = 1;
				nYears++;
			}	
		}	
	}
	
//	system("pause");
	
	if (getLastReportID("database/timeReports.txt") > getLastReportID("temp/newReports.txt")) {
		lI = getLastReportID("database/timeReports.txt");
	} else {
		lI = getLastReportID("temp/newReports.txt");
	}
	
	ifstream tempIn("temp/newReports.txt");
	trInFile.open("database/timeReports.txt");
	trOutFile.open("temp.txt");
	
	if (tempIn.is_open() && trInFile.is_open() && trOutFile.is_open()) {
		getline(trInFile, temp); //ignore old lI
		getline(tempIn, temp);  //ignore old LI
//		cout << "new LI is: " << temp;
		temp = "$lI#" + mActions.intToString(lI) + "$lI#\n";
//		temp += "\n";
		trOutFile << temp; //record new lI
		
		//get existing time reports
		while(getline(trInFile, temp)) {
			temp += "\n";
			trOutFile << temp;
		}
		
		//get newly generated time reports
		while(getline(tempIn, temp)) {
			temp += "\n";
			trOutFile << temp;
		}
	} else { 
		cout << endl << "Error 1 (autoGen): Unable to open file. ";
		
	}
	
	tempIn.close();
	trInFile.close();
	trOutFile.close();
	
	trInFile.open("temp.txt");
	trOutFile.open("database/timeReports.txt");
	
	if (trInFile.is_open() && trOutFile.is_open()) {
		while(getline(trInFile, temp)) {
			temp += "\n";
			trOutFile << temp;
		}
	} else { 
		cout << endl << "Error 2 (autoGen): Unable to open file.";
	}
	
	trInFile.close();
	trOutFile.close();
	
	remove("temp/tempReports.txt");
	remove("temp/newReports.txt");
	
}

int timeReports::getLastReportID(string fileName) {
	miscActions mActions;
	string line;
	int num, posStart, posEnd;
	
//	cout << endl << "filename is " << fileName; 
	
	num = 0; posStart = 0; posEnd = 0;
	
	trInFile.open(fileName.c_str());
	
	if (trInFile.is_open()) {
		getline(trInFile, line);
		posStart = line.find("$lI#") + 4;
		posEnd = line.find("$lI#", posStart);
		if (line.size() > 0) {
			line = line.substr(posStart, posEnd - posStart);
		}
		num = mActions.stringToInt(line);
//		cout << "entered here";
//		cout << "num is " << num <<".";
		trInFile.close();
	} else {
		cout << "Error (getLastReportID): Unable to open file: " << fileName;		
	}
	
	return num;
		
}

//if report doesn't exist, add it
bool timeReports::doesReportExists(string empID, string workYear, string workMonth, string cutOff) {
	miscActions mActions;
//	cout << endl << empID << " " << workYear << " " << workMonth << " " << workDay;
	string line, found, orig, nextID, temp;
	int posStart, posEnd, lastID;
	bool query1, query2, query3, query4, doIt, isFirstLine;
	ofstream tempOut;
	ifstream tempIn;
	

//	cout << getLastReportID("database/timeReports.txt");
//	cout << getLastReportID("temp/newReports.txt");
	if (getLastReportID("database/timeReports.txt") > getLastReportID("temp/newReports.txt")) {
		lastID = getLastReportID("database/timeReports.txt");
//		cout << "lastID from timeReports " << lastID;
	} else {
		lastID = getLastReportID("temp/newReports.txt");
//		cout << "lastID taken from newReports: " << lastID;
	}
	trInFile.open("database/timeReports.txt");
	trInFile.clear();
	
	doIt = true;
	if (trInFile.is_open()) {
		while (getline(trInFile, line)) {
			trInFile.clear();
			
			query1 = false; query2 = false; query3 = false; query4 = false;
			
			posStart = line.find("$tei#") + 5;
			posEnd = line.find("$tei#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			
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
			
			posStart = line.find("$tco#") + 5;
			posEnd = line.find("$tco#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			
//			cout << endl << "found: " << found << ", cutOff: " << cutOff;
			if (found == cutOff) {
				query4 = true;
			}
			
//			cout << endl << query1 << query2 << query3 << query4;
			if (query1 && query2 && query3 && query4) {
				doIt = false; //time report found
			}
			
		}
		
		lastID++;
		nextID = mActions.intToString(lastID);

		while (nextID.length() < 6) {
			nextID.insert(0, "0");
		}
		
		if (doIt) {
//			cout << "entered doIt";
			tempIn.open("temp/newReports.txt");
			tempOut.open("temp/tempReports.txt");
			
			if (tempIn.is_open() && tempOut.is_open()) {
				tempOut << "$lI#" + mActions.intToString(lastID) + "$lI#\n";
				getline(tempIn, temp);
				tempIn.clear();
				while(getline(tempIn, temp)) {
					temp += "\n";
					tempOut << temp;
//					cout << endl << "putting to tempreports: " << temp; 
					tempIn.clear();
				}
//				cout << endl;
//				system("pause");
				tempOut << "$tid#"+nextID+"$tid#$tei#"+empID+"$tei#$twy#"+workYear+"$twy#$twm#"+workMonth+"$twm#$tco#"+cutOff+"$tco#$twh#$twh#$trs#No Report$trs#$trd#$trd#$tal#$tal#$ttd#$ttd#\n";
			} else { 
				cout << endl << "Error 2 (doesReportExists): Unable to open file. " << tempIn.is_open() << tempOut.is_open();
			}
			
			tempIn.close();
			tempOut.close();
			
//			system("pause");
			
			tempIn.open("temp/tempReports.txt");
			tempOut.open("temp/newReports.txt");
			
			if (tempIn.is_open() && tempOut.is_open()) {
				while(getline(tempIn, temp)) {
					temp += "\n";
					tempOut << temp;
					tempIn.clear();
				}
			} else { 
				cout << endl << "Error 3 (doesReportExists): Unable to open file.";
			}
			
			tempIn.close();
			tempOut.close();
		
//			trOutFile << "$tid#"+nextID+"$tid#$tei#"+empID+"$tei#$twy#"+workYear+"$twy#$twm#"+workMonth+"$twm#$twd#"+workDay+"$twd#$twh#$twh#$trs#No Report$trs#$trd#$trd#$tal#$tal#$ttd#$ttd#\n";
		}
		
		
		
		
		trInFile.close();
		trOutFile.close();
		
	} else {
		cout << endl << "Error 1 (doesReportExists): Unable to open file.";
	}
	
		
	

	
	return false;
}

void timeReports::enterTimeReport() {
	miscActions mActions;
	string newEmployeeID, newMonth, newYear, temp, line, found, newInfo;
	int cutoffSelection, iDays, iHours;
	bool repeat, query1, query2, query3, query4, toUpdate, gotUpdated;

	system("cls");		
	

	repeat = true;
	while (repeat) {
		cout << endl << "Please enter the employee ID: ";
		getline(cin, newEmployeeID);
//		cout << eRecords.searchEmployee(newEmployeeID, "eid");
		if (eRecords.searchEmployee(newEmployeeID, "eid")) {
			if (eRecords.getEmployeeInfo(newEmployeeID, "ees") == "Applicant") {
				cout << "Error: You can't create time reports for applicants." << endl;			
			} else {
				repeat = false;
			}
			
		} else {
			cout << "Error: No employee exists with that ID." << endl;
			cout << "Note: Make sure you don't enter any spaces." << endl;
//			system("pause");
		}
	}
	
	
	cout << endl << "Please indicate the year of work (ex: 2017): ";
	getline(cin, newYear);
	
	cout << endl << "Please indicate the month of work (ex: Jan): ";
	getline(cin, newMonth);
	
	do {
		cout << endl << "Please select a cutoff period.";
		cout << endl << " [1] 1st to 15th day";
		cout << endl << " [2] 16th to 29th/30th/31st day (whichever applicable)";
		cout << endl << "Selection: ";
		getline(cin, temp);
		cutoffSelection = mActions.stringToInt(temp);
//		sline << temp;
//		sline >> cutoffSelection;
		if (cutoffSelection == 1 || cutoffSelection == 2) {
			break;
		} else {
			cout << "Error: Invalid selection. Please try again." << endl;
		}
//		sline.str(string());
//		sline.clear();
	} while (!(cutoffSelection == 1 || cutoffSelection == 2));
	
	ifstream src("database/timeReports.txt", ios::binary);
	ofstream dst("temp/tempReports.txt", ios::binary);
	
	dst << src.rdbuf();
	
	dst.close();
	src.close();
//	system("pause");
	src.clear();
	src.open("temp/tempReports.txt");
		
	if (src.is_open()) {
		src.clear();
		getline(src, line);
		src.clear();
		while (getline(src, line)) {
//			cout << endl << line;
			toUpdate = false; query1 = false; query2 = false; query3 = false, query4 = false;
//			cout << "last is " << last; 
			
			if (getValueFromEntry("$trs", line) == "No Report") {
				found = getValueFromEntry("$tei#", line);		
				if (found == newEmployeeID) {
					query1 = true;
				}
				
				found = getValueFromEntry("$twy#", line);		
				if (found == newYear) {
					query2 = true;
				}
	
				found = getValueFromEntry("$twm#", line);		
				if (found == newMonth) {
					query3 = true;
				}
	
				found = getValueFromEntry("$tco#", line);
				if (found == mActions.intToString(cutoffSelection)) {
					query4 = true;
				}
			
				
				if (query1 && query2 && query3 && query4) {
					toUpdate = true;
					
					newInfo = "$tid#"+getValueFromEntry("$tid#", line)+"$tid#";
					newInfo += "$tei#"+newEmployeeID+"$tei#";
					newInfo += "$twy#"+newYear+"$twy#";
					newInfo += "$twm#"+newMonth+"$twm#";
					
					iHours = 0;
					iDays = mActions.numberOfDaysInMonth(mActions.convertToIMonth(newMonth), mActions.stringToInt(newYear));
					
//					cout << "number of days in " << newMonth << " " << newYear << " is " << iDays;
					
					if (cutoffSelection == 1) {
						for (int i = 1; i <= 15; i++) {
							repeat = true;
							do {
								cout << endl << "Please enter the total hours the worker logged for ";
								cout << newMonth << " " << i << ", " << newYear << ": ";
								getline(cin, temp);						
								if (mActions.stringToInt(temp) >= 0 && mActions.stringToInt(temp) <= 24) {
									repeat = false;
									iHours += mActions.stringToInt(temp);
								} else {
									cout << "Error: You can only enter from 0 to 24 hours per work day." << endl;
								}	
							} while (repeat);
						}
					} else {
						for (int i = 16; i <= iDays; i++) {
							repeat = true;
							do {
								cout << endl << "Please enter the total hours the worker logged for ";
								cout << newMonth << " " << i << ", " << newYear << ": ";
								getline(cin, temp);						
								if (mActions.stringToInt(temp) >= 0 && mActions.stringToInt(temp) <= 24) {
									repeat = false;
									iHours += mActions.stringToInt(temp);
								} else {
									cout << "Error: You can only enter from 0 to 24 hours per work day." << endl;
								}	
							} while (repeat);
						}
					}
					
				}

				
			}		

			src.clear();
			
			newInfo += "$tco#"+mActions.intToString(cutoffSelection)+"$tco#";
			newInfo += "$twh#"+mActions.intToString(iHours)+"$twh#";
			newInfo += "$trs#Submitted$trs#";
			newInfo += "$trd#"+getValueFromEntry("$trd#", line)+"$trd#";
			newInfo += "$tal#"+getValueFromEntry("$tal#", line)+"$tal#";
			newInfo += "$ttd#"+getValueFromEntry("$ttd#", line)+"$ttd#";	
			
			if (toUpdate) {
				updateTimeReportDB(getValueFromEntry("$tid#", line), newInfo);
				gotUpdated = true;
			} 
		}
		
		if (!gotUpdated) {
			cout << endl << "Error: Sorry. There are no lacking/missing/needed time reports";
			cout << endl << "for the cutoff period you specified. Or you may have entered";
			cout << endl << "wrong information. Please try again.";
		}
		
		
		src.close();
		
	} else {
		cout << endl << "Error 1 (enterTimeReport): Unable to open file.";
	}

	
	remove("temp/tempReports.txt");
}

void timeReports::employeeTimeReports() {
	miscActions mActions;
	string currentEmployeeID, sYears, sMonths, sDays, line;
	bool repeat, proceed;
	
	//ask for specific employee
	repeat = true;
	while (repeat) {
		cout << endl << "Please enter the employee ID: ";
		getline(cin, currentEmployeeID);
		if (eRecords.searchEmployee(currentEmployeeID, "eid")) {
			if (eRecords.getEmployeeInfo(currentEmployeeID, "ees") == "Applicant") {
				cout << "Error (employeeTimeReports): This employee is an applicant," << endl;
				cout << "and therefore does not have time reports." << endl;
				cout << "Please try again." << endl;				
			} else {
				repeat = false;
				proceed = true;
			}
			
		} else {
			cout << "Error (employeeTimeReports): No employee exists with that ID." << endl;
			cout << "Note: Make sure you don't enter any spaces." << endl;
			cout << "Please try again." << endl;
		}
	}
	
	trInFile.open("database/timeReports.txt");
	trInFile.clear();
	//start reading database for non applicant
	if (proceed && trInFile.is_open()) {
		cout << endl << "Time Report Summary for " << currentEmployeeID << " ";
		cout << eRecords.getEmployeeInfo(currentEmployeeID, "ena") << endl;
		cout << endl << "\tDate\t\tCutoff Period\tReport Status\tTotal Work Hours\tReason of Disapproval (if applicable)";
		
		getline(trInFile, line);
		trInFile.clear();
		while(getline(trInFile, line)) {
			if (getValueFromEntry("$tei#", line) == currentEmployeeID) {
				cout << endl << "\t" << getValueFromEntry("$twm#", line);
				cout << " " << getValueFromEntry("$twy#", line);
				cout << "\t" << getValueFromEntry("$tco#", line);
				cout << "\t\t" << getValueFromEntry("$trs#", line);
				if (getValueFromEntry("$trs#", line) != "No Report") {
					cout << "\t" << getValueFromEntry("$twh#", line);
					if (mActions.stringToInt(getValueFromEntry("$twh#", line)) > 1) {
						cout << " hours";	
					} else {
						cout << " hour";	
					}
				}
				cout << "\t" << getValueFromEntry("$trd", line);
			}
			
			trInFile.clear();
		}
	}
	
	
	
	
	trInFile.close();
	
	
}

void timeReports::displayTimeReport() {
	miscActions mActions;
	string sYear, sMonth, sPeriod, sDept, line, temp, found;
	int iYear, iMonth, iPeriod;
	bool repeat, query1, query2, query3, query4, isFound, headerDisplayed;

	repeat = true;
	cout << endl << "Please indicate the cutoff period (ex: Jun 2016, 1): ";
	getline(cin, temp);
	if (temp.length() >= 11) {
		
		sYear = temp.substr(4, 4);
		sMonth = temp.substr(0, 3);
		sPeriod = temp.substr(10, 1);
		
		iYear = mActions.stringToInt(sYear);
		iMonth = mActions.convertToIMonth(sMonth);
		iPeriod = mActions.stringToInt(sPeriod);
		
		cout << endl << "Please indicate the department code: ";
		getline(cin, sDept);
		
		trInFile.open("database/timeReports.txt");
		
		headerDisplayed = false;
		if (trInFile.is_open()) {
			getline(trInFile, line);
			trInFile.clear();
			
			while (getline(trInFile, line)) {
				trInFile.clear();
				
				query1 = false; query2 = false; query3 = false, query4 = false;
				
				if(getValueFromEntry("$trs#", line) != "No Report") {
					found = getValueFromEntry("$twy#", line);
					if (found == sYear) {
						query1 = true;
					}
					
					found = getValueFromEntry("$twm#", line);
					if (found == sMonth) {
						query2 = true;
					}
					
					found = getValueFromEntry("$tco#", line);
					if (found == sPeriod) {
						query3 = true;
					}
					
					found = getValueFromEntry("$tei#", line);
					found = eRecords.getEmployeeInfo(found, "ede");
					found = mActions.getDepartmentInfo(found, "dco");
					if (found == sDept) {
						query4 = true;
					}
					
					if (query1 && query2 && query3 && query4) {
						if(!headerDisplayed) {
							cout << endl << "List of " << sDept << " Employees for ";
							cout << sMonth << " " << sYear << " Cutoff Period " << sPeriod;
							
							cout << endl << endl << "Time Report ID\tEmployee ID\tName\t\t\tTotal Work Hours";
							cout << "\tReport Status\tDisapprove Reason (if any)";
							
							cout << endl << ""<< getValueFromEntry("$tid#", line);
							cout << "\t\t" << getValueFromEntry("$tei#", line);
							
							cout << "\t\t" << eRecords.getEmployeeInfo(getValueFromEntry("$tei#", line), "ena");
							cout << "\t" << getValueFromEntry("$twh#", line);
							cout << "\t\t\t" << getValueFromEntry("$trs#", line);
							cout << "\t" << getValueFromEntry("$trd#", line);
							
							
							headerDisplayed = true;
						}
						
					
					}
						
				}
			}
			
			
		}
		
		if(!headerDisplayed) {
			cout << endl << "Error: Sorry. There are no submitted time reports";
			cout << endl << "for the cutoff period and department you specified.";
			cout << endl << "Or you may have entered wrong information. Please try again.";		
		}
		
		trInFile.close();
		
	}
	
	
	
	
	
//	lastAddedPos = 0;
//	if (trInFile.is_open()) {
//		while(getline(trInFile, temp)) {
//			trInFile.clear();
//	
//			if (getValueFromEntry("$trs#", temp) == "Submitted") {
//				temp = getValueFromEntry("$tid#", temp);
//			}
//			
//			isAdded = false;
//			for(int i = 0; i < lastReportID - 1; i++) {
//				if (numSubmittedReports[i] == temp) {
//					isAdded = true;
//					break;
//				}
//			}
//			
//			if (!isAdded) {
//				numSubmittedReports[lastAddedPos] = temp;
//				lastAddedPos++;			
//			}	
//		}
//		
//		
//	}
//	
//	cout << endl << "Please enter an ID of the time report that you would like to approve/disapprove: ";
//
//	
//	delete[] numSubmittedReports;	
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
	miscActions mActions;
	string temp, orig;
	int posStart, posEnd, id;
	
	trInFile.open("database/timeReports.txt");
	trOutFile.open("temp.txt");
	
	if (trInFile.is_open() && trOutFile.is_open()){ 
		trInFile.clear();
		trOutFile.clear();
	
		while (getline(trInFile, temp)) {
			orig = temp;
			posStart = temp.find("$tid#") + 5;
			posEnd = temp.find("$tid#", posStart);
			if (reportID == temp.substr(posStart, posEnd - posStart)) {
				orig = newInfo;
			}
			orig += "\n";
			trOutFile << orig;
			trInFile.clear();
		}
		
		trInFile.close();
		trOutFile.close();
		
		ifstream fileIn("temp.txt");
		ofstream fileOut("database/timeReports.txt");
		
		if (fileIn.is_open() && fileOut.is_open()) {
			while (getline(fileIn, temp)) {
				temp += "\n";
				fileOut << temp;
				fileIn.clear();
			}
			
			fileIn.close();
			fileOut.close();	
		} else {
			cout << endl << "Error 1 (updateTimeReportDB): Unable to update Time Reports database."; 
		}
	remove("temp.txt");	
	} else {
		cout << endl << "Error 2 (updateTimeReportDB): Unable to open Time Reports database."; 
	}
	
	
}

string timeReports::getValueFromEntry(string element, string entry) { //gets specific value of a database element within a database entry
//	cout << endl << "Entering getValueFromEntry";
	
	int posStart, posEnd;
	
	
	posStart = entry.find(element) + 5;
	posEnd = entry.find(element, posStart);
	
	if (posEnd == -1) {
		cout << endl << "Error (getValueFromEntry): Unable to find element in entry.";
		cout << endl << "element: " << element << ", entry: " << entry << endl << endl;
		return "";
	} else {
		return entry.substr(posStart, posEnd - posStart);	
	}
}

bool timeReports::searchTimeReportDB(string query, string element, string *focus, bool keepSearching)  { //assigns string to *focus where query was found
	string line, found;
	int ctr;
	
	ctr = 0;
	trInFile.open("database/timeReports.txt");
	if (trInFile.is_open()) {
		if (keepSearching) 
			cout << endl << "Search results: ";	
		while ( getline (trInFile,line) ) {
			*focus = line;
//			cout << endl << line;
			found = getValueFromEntry(element, line);
//			cout << endl << found;
//			cout << endl << line.substr(posStart, posEnd - posStart);
			if (keepSearching) {
				if (query == found) {
					cout << endl << line; // edit this to be more user friendly
					ctr++;
				}
			} else {
				if (query == found) {
				trInFile.close();
				//cout << endl << focus;
				return true;
				}		
			}
		}
		if (!ctr) {
			if (keepSearching) {
				cout << endl << "No entries found!";
			} 
		}
		 trInFile.close();
	}
  	else cout << "Error (searchTimeReportDB): Unable to open Time Reports database."; 

	return false;
}



