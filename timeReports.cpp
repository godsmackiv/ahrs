#include "timeReports.h"

void timeReports::viewNoTimeReports() {
	stringstream sline;
	string temp;
	string *noReportEmployees;
	int lastEmployeeID, lastAddedPos;
	bool isAdded;
//	int ctr;
	
	system("cls");
	cout << endl << "Here are the list of employees without (or with missing) Time Reports: ";
	
	userInFile.open("database/timeReports.txt");
	userInFile.clear();
	
	lastEmployeeID = eRecords.getNumberOfEmployees();
	getline(userInFile, temp);
	userInFile.clear();
	noReportEmployees = new string[lastEmployeeID];
	
	lastAddedPos = 0;
	if (userInFile.is_open()) {
		while(getline(userInFile, temp)) {
			userInFile.clear();
			
			if (getValueFromEntry("$trs#", temp) == "No Report") {
				temp = getValueFromEntry("$tei#", temp);
//				cout << endl << temp;
			}
			
			isAdded = false;
			for(int i = 0; i < lastEmployeeID - 1; i++) {
				if (noReportEmployees[i] == temp) {
					isAdded = true;
					break;
				}
			}
			if (!isAdded) {
//				cout << "adding";
				noReportEmployees[lastAddedPos] = temp;
//				cout << noReportEmployees[lastAddedPos];
				lastAddedPos++;			
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
		userInFile.close();
	} else {
		cout << endl << "Error (viewNoTimeReports): Unable to open Time Reports database.";
	}
	
	delete[] noReportEmployees;
}

void timeReports::autoGenerateTimeReports() {
	int lI, nYears, nMonths, nDays, mYears, mMonths, mDays, cutoffPeriod, lastCutoff;
	string sYears, sMonths, sDays, temp, currentEmployeeID, sCutoffPeriod;
	stringstream sline;
	
    lI = eRecords.getNumberOfEmployees();
	userOutFile.open("temp/tempReports.txt");
	userOutFile.close();
	userOutFile.open("temp/newReports.txt");
	userOutFile.close();
	
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
	
	
	ifstream tempIn("temp/newReports.txt");
	userInFile.open("database/timeReports.txt");
	userOutFile.open("temp.txt");
	
	if (tempIn.is_open() && userInFile.is_open() && userOutFile.is_open()) {
		getline(userInFile, temp); //ignore old lI
		getline(tempIn, temp);  
//		cout << "new LI is: " << temp;
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
		num = mActions.stringToInt(line);
//		cout << "entered here";
//		cout << "num is " << num <<".";
		userInFile.close();
	} else {
		cout << "Error (getLastReportID): Unable to open file: " << fileName;		
	}
	
	return num;
		
}

//if report doesn't exist, add it
bool timeReports::doesReportExists(string empID, string workYear, string workMonth, string cutOff) {
	
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
	userInFile.open("database/timeReports.txt");
	userInFile.clear();
	
	doIt = true;
	if (userInFile.is_open()) {
		while (getline(userInFile, line)) {
			userInFile.clear();
			
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
				cout << endl;
				system("pause");
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
	string newEmployeeID, newMonth, newYear, temp, line, found, newInfo;
	int cutoffSelection, iDay, iHours;
	bool repeat, query1, query2, query3, toUpdate, gotUpdated;
	char s;
	stringstream sline, sLI;
	
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
			toUpdate = false; query1 = false; query2 = false; query3 = false;
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
	
				found = getValueFromEntry("$twd#", line);
				iDay = mActions.stringToInt(found);		
//				
//				sline << found;
//				sline >> iDay;
//				sline.str(string());
//				sline.clear();
				
				
				if (query1 && query2 && query3) {
//					cout << endl << "matched ID year and month";
					newInfo = "$tid#"+getValueFromEntry("$tid#", line)+"$tid#";
					newInfo += "$tei#"+newEmployeeID+"$tei#";
					newInfo += "$twy#"+newYear+"$twy#";
					newInfo += "$twm#"+newMonth+"$twm#";

					if (cutoffSelection == 1) {
						if (iDay <= 15) {
							repeat = true;
							do {
								cout << endl << "Please enter the total hours the worker logged for ";
								cout << newMonth << " " << found << ", " << newYear << ": ";
								getline(cin, temp);
								iHours = mActions.stringToInt(temp);
//								sline << temp;
//								sline >> iHours;
//								sline.str(string());
//								sline.clear();
								
								if (iHours >= 0 && iHours <= 24) {
									repeat = false;
									toUpdate = true;
								} else {
									cout << "Error: You can only enter from 0 to 24 hours per work day." << endl;
								}	
							} while (repeat);
						}
					} else {
						if (iDay >= 16) {
							repeat = true;
							do {
								cout << endl << "Please enter the total hours the worker logged for ";
								cout << newMonth << " " << found << ", " << newYear << ": ";
								getline(cin, temp);
								iHours = mActions.stringToInt(temp);
//								sline << temp;
//								sline >> iHours;
//								sline.str(string());
//								sline.clear();
								
								if (iHours >= 0 && iHours <= 24) {
									repeat = false;
									toUpdate = true;
								} else {
									cout << "Error: You can only enter from 0 to 24 hours per work day." << endl;
								}	
							} while (repeat);
						}
					}
				}

				
			}		

			src.clear();
			
			newInfo += "$twd#"+mActions.intToString(iDay)+"$twd#";
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
	
	userInFile.open("database/timeReports.txt");
	userInFile.clear();
	//start reading database for non applicant
	if (proceed && userInFile.is_open()) {
		cout << "Time Report Summary for: " << currentEmployeeID << " ";
		cout << eRecords.getEmployeeInfo(currentEmployeeID, "ena");
		cout << endl << "\tDate\t\tReport Status\tTotal Work Hours\tReason of Disapproval (if applicable)";
		
		getline(userInFile, line);
		userInFile.clear();
		while(getline(userInFile, line)) {
			if (getValueFromEntry("$tei#", line) == currentEmployeeID) {
				cout << endl << "\t" << getValueFromEntry("$twm", line);
				cout << " " << getValueFromEntry("$twd", line);
				cout << ", " << getValueFromEntry("$twy", line);
				cout << "\t" << getValueFromEntry("$trs", line);
				if (getValueFromEntry("$trs", line) != "No Report") {
					cout << "\t" << getValueFromEntry("$twh", line);
					if (mActions.stringToInt(getValueFromEntry("$twh", line)) > 1) {
						cout << " hours";	
					} else {
						cout << " hour";	
					}
				}
				cout << "\t" << getValueFromEntry("$trd", line);
			}
			
			userInFile.clear();
		}
	}
	
	
	
	
	userInFile.close();
	
	
	//per employee , must not be applicant
	//get starting date of employee
	//per 
	
	
	
	
	
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
	
	userInFile.open("database/timeReports.txt");
	userOutFile.open("temp.txt");
	
	if (userInFile.is_open() && userOutFile.is_open()){ 
		userInFile.clear();
		userOutFile.clear();
	
		while (getline(userInFile, temp)) {
			orig = temp;
			posStart = temp.find("$tid#") + 5;
			posEnd = temp.find("$tid#", posStart);
			if (reportID == temp.substr(posStart, posEnd - posStart)) {
				orig = newInfo;
			}
			orig += "\n";
			userOutFile << orig;
			userInFile.clear();
		}
		
		userInFile.close();
		userOutFile.close();
		
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
	userInFile.open("database/timeReports.txt");
	if (userInFile.is_open()) {
		if (keepSearching) 
			cout << endl << "Search results: ";	
		while ( getline (userInFile,line) ) {
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
				userInFile.close();
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
		 userInFile.close();
	}
  	else cout << "Error (searchTimeReportDB): Unable to open Time Reports database."; 

	return false;
}



