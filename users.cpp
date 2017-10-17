#include "users.h"

// login users, verifies if account exist, and verifies if password is matched
void users::loginUser() {
	string input, currentUser; //currentUser is line containing elements of current user

	system("cls");
	cout << "Please enter your user ID: ";
	cin >>  input;
	
	
	
	if (searchUserDB(input, "$id#", &currentUser, false)) {
//		cout << "test1";
		userID = input;
		
		password = getValueFromEntry("$pw#", currentUser);
		
		cout << "Please enter your password: ";
		cin >> input;
		if (input == password) {
			cout << endl << "Login successful!";
			
			firstName = getValueFromEntry("$fn#", currentUser);
			lastName = getValueFromEntry("$ln#", currentUser);
			middleName = getValueFromEntry("$mn#", currentUser);
			userLevel = getValueFromEntry("$ul#", currentUser);
			cout << endl << "Welcome " + lastName + ", " + firstName + " " + middleName + "!";
			
		} else {
			cout << endl << "Error: Incorrect password.";
		}
		
	} else {
		cout << "Error: Unable to login. No user with that ID found.";
	}
	
	cout << endl;
	system("pause");
}

void users::changePassword() {
	string temp, confirm;
	
	system("cls");

	cout << endl << "Please enter your current password: ";
	cin >> temp;
	if (temp == password) {
		cout << endl << "Please enter your new password: ";
		cin >> temp;
		cout << endl << "Please re-enter your new password to confirm: ";
		cin >> confirm;
		if (temp == confirm) {
			cout << endl << "Password has been changed.";
			password = confirm;
//			temp = "$id#"+userID+"$id#$pw#"+password+"$pw#$ln#"+lastName+"$ln#$fn#"+firstName+"$fn#$mn#"+middleName+"$mn#$ul#"+userLevel+"$ul#";
//			cout << endl << temp;
			updateUserDB(userID, "$id#"+userID+"$id#$pw#"+password+"$pw#$ln#"+lastName+"$ln#$fn#"+firstName+"$fn#$mn#"+middleName+"$mn#$ul#"+userLevel+"$ul#");
		} else {
			cout << endl << "Error: Passwords do not match.";
		}		
	} else {
		cout << endl << "Error: Incorrrect password.";
	}
	
	cout << endl;
	system("pause");
}

void users::registerUser() {
	string newID, newLName, newFName, newMName, newUL, newPW, temp;
	int posStart, posEnd, id, aN, mN, rN, pN, lI;
	stringstream sline, sAN, sMN, sRN, sPN, sLI;
	bool repeat;
	char s;

	system("cls");
	
//	lastEntry = getLastUserEntry();
//	cout << lastEntry;
//	cout << "weee";
	userInFile.open("database/users.txt");
	userOutFile.open("temp.txt");
	
	repeat = true;
	if (userInFile.is_open() && userOutFile.is_open()){
		while (getline(userInFile, temp)) {
			if (repeat) {
				sline << getValueFromEntry("$aN#", temp);
				sline >> aN;
				sline.str(string());
				sline.clear();
				sline << getValueFromEntry("$mN#", temp);
				sline >> mN;
				sline.str(string());
				sline.clear();
				sline << getValueFromEntry("$rN#", temp);
				sline >> rN;
				sline.str(string());
				sline.clear();
				sline << getValueFromEntry("$pN#", temp);
				sline >> pN;
				sline.str(string());
				sline.clear();
				sline << getValueFromEntry("$lI#", temp);
				sline >> lI;
				sline.str(string());
				sline.clear();
//				cout << aN << " " << mN << " " << rN << " " << pN;
				
				cout << endl << "Please enter new user's Last Name:" << endl;
				cin >> newLName;
				
				cout << endl << "Please enter new user's First Name:" << endl;
				cin >> newFName;
				
				cout << endl << "Please enter new user's Middle Name:" << endl;
				cin >> newMName;
				
				while (repeat) {
					cout << endl << "What is the new user's level? " << endl;
					cout << endl << "Options: (A) - Admin, (M) - HR Manager, (R) - Recruiter, (P) - HR Personnel" << endl;
					cout << endl << "Select a letter: ";
					cin >> s;
			
					switch(s) {
						case 'A': case 'a':
							newUL = "admin";
							aN++;
							repeat = false;
							break;
						case 'M': case 'm':
							newUL = "manager";
							mN++;
							repeat = false;
							break;	
						case 'R': case 'r':
							newUL = "recruiter";
							rN++;
							repeat = false;
							break;
						case 'P': case 'p':
							newUL = "personnel";
							pN++;
							repeat = false;
							break;	
						default:
							cout << "Error: Invalid selection. Please try again." << endl;
							cin.clear();
							cin.ignore(10000,'\n');
							break;
					}
				}
				
				cout << "Please enter the new user's default password: ";
				cin >> newPW;
				
				//lastEntry = getLastUserEntry();
				lI++;
				sline.str(string());
				sline.clear();
				sline << lI;
				sline >> newID;
				while (newID.length() < 6) {
					newID.insert(0, "0");
				}
//				cout << newID;
			}
			
			
			temp += "\n";
			userOutFile << temp;
		}
		
		userOutFile << "$id#"+newID+"$id#$pw#"+newPW+"$pw#$ln#"+newLName+"$ln#$fn#"+newFName+"$fn#$mn#"+newMName+"$mn#$ul#"+newUL+"$ul#";
		
		userInFile.close();
		userOutFile.close();
		
		ifstream fileIn("temp.txt");
		ofstream fileOut("database/users.txt");
		
		repeat = true;
		if (fileIn.is_open() && fileOut.is_open()) {
			while (getline(fileIn, temp)) {
				if (repeat) {
					sAN << aN;
					sMN << mN;
					sRN << rN;
					sPN << pN;
					sLI << lI;
					fileOut << "$aN#"+sAN.str()+"$aN#$mN#"+sMN.str()+"$mN#$rN#"+sRN.str()+"$rN#$pN#"+sPN.str()+"$pN#$lI#"+sLI.str()+"$lI#\n";
					repeat = false;
				} else {
					temp += "\n";
					fileOut << temp;
				}
				
			}
			fileIn.close();
			fileOut.close();	
		} else {
			cout << endl << "Error: Unable to update Users database."; 
		}
	remove("temp.txt");	
	} else {
		cout << endl << "Error: Unable to open Users database."; 
	}
	
}

void users::deleteUser() {
	string id, found, level, temp, orig, currentUser;  //found is entry of user to be deleted
	int posStart, posEnd, aN, mN, rN, pN, lI;
	stringstream sline, sAN, sMN, sRN, sPN, sLI;
	bool repeat, proceedDelete;
	
	cout << endl << "Enter the user ID number of the account you wish to delete: ";
	cin >> id;
	searchUserDB(userID, "$id#", &currentUser, false);
	
	if (searchUserDB(id, "$id#", &found, false)) {
		proceedDelete = true;
		
//		cout << "search found";
		
		userInFile.open("database/users.txt");
		userOutFile.open("temp.txt");
		
		repeat = true;
		
		if (userInFile.is_open() && userOutFile.is_open()){
			while (getline(userInFile, temp)) {
				//retrieve user population
				if (repeat) {
					repeat = false;
					sline << getValueFromEntry("$aN#", temp);
					sline >> aN;
					sline.str(string());
					sline.clear();
					sline << getValueFromEntry("$mN#", temp);
					sline >> mN;
					sline.str(string());
					sline.clear();
					sline << getValueFromEntry("$rN#", temp);
					sline >> rN;
					sline.str(string());
					sline.clear();
					sline << getValueFromEntry("$pN#", temp);
					sline >> pN;
					sline.str(string());
					sline.clear();
					sline << getValueFromEntry("$lI#", temp);
					sline >> lI; 
//					cout << "li is " << lI;
					sline.str(string());
					sline.clear();
				}
				
				//cout << endl << "aN: " << aN;
				//cout << endl << "user level: " << getValueFromEntry("$ul#", temp);
				
				// UT4 - unable to delete own account
				if (id == getValueFromEntry("$id#", currentUser)) {
					cout << endl << "Error: You cannot delete your own account.";
					proceedDelete = false;
					break;
				// UT5 - at least two admins 	
				} else if ((getValueFromEntry("$ul#", found) == "admin") && aN <= 2) {
					cout << endl << "Error: You cannot delete the last two admins (including yourself).";
					proceedDelete = false;
					break;
				}   
								
				//proceed with deletions, start by putting into temp text file
				orig = temp;
				posStart = temp.find("$id#") + 4;
				posEnd = temp.find("$id#", posStart);
				if (!(id == temp.substr(posStart, posEnd - posStart))) { //skip entry with matching user ID, to be skipped when updating database
					orig += "\n";
					userOutFile << orig;
				} 				
			}
			
			//UT 6 and 7
			//make new functions confirmDelete, confirmDeleteLastofLevel, ask to enter admin ID and password
			
			
			userInFile.close();
			userOutFile.close();
			
			if (proceedDelete) {
//				cout << endl << "proceeding with deletion!";
				//put back contents to main database file, but without the deleted entry
				ifstream fileIn("temp.txt");
				ofstream fileOut("database/users.txt");
				
				//update user popluation
				level = getValueFromEntry("$ul#", found);
				if (level == "admin") {
					aN--;
				} else if (level == "manager") {
					mN--;
				} else if (level == "recruiter") {
					rN--;
				} else {
					pN--;
				}
				
				//add rest of the remaining database entries
				repeat = true;
				if (fileIn.is_open() && fileOut.is_open()) {
					while (getline(fileIn, temp)) {
						if (repeat) {
							sAN << aN;
							sMN << mN;
							sRN << rN;
							sPN << pN;
							sLI << lI;
							fileOut << "$aN#"+sAN.str()+"$aN#$mN#"+sMN.str()+"$mN#$rN#"+sRN.str()+"$rN#$pN#"+sPN.str()+"$pN#$lI#"+sLI.str()+"$lI#\n";
							repeat = false;
						} else {
							temp += "\n";
							fileOut << temp;
						}
						
					}
					
					fileIn.close();
					fileOut.close();	
				} else {
					cout << endl << "Error: Unable to update Users database."; 
				}				
			}
			
			
			
		remove("temp.txt");	
		} else {
			cout << endl << "Error: Unable to open Users database."; 
		}

	} else {
		cout << endl << "Error: No user exists with that ID.";
	}
}


//mode true = load and display to command prompt; false = just load
void users::viewDeductions(bool mode) { 
	string line;
	stringstream sline;
	int posStart, posEnd;
	
	userInFile.open("database/deductions.txt");
	if (userInFile.is_open()) {
		getline(userInFile,line);
		
		posStart = line.find("$pg#") + 4;
		posEnd = line.find("$pg#", posStart);
		sline << line.substr(posStart, posEnd - posStart);
		sline >> pagibig;
		if (mode) cout << endl << "Pag-Ibig: \t less " << pagibig * 100 << "%";		
		sline.ignore(10000,'\n');
		sline.clear();		

		posStart = line.find("$ph#") + 4;
		posEnd = line.find("$ph#", posStart);
		sline << line.substr(posStart, posEnd - posStart);
		sline >> philhealth;
		if (mode) cout << endl << "PhilHealth: \t less " << philhealth * 100 << "%";			
		sline.ignore(10000,'\n');
		sline.clear();
		
		posStart = line.find("$ss#") + 4;
		posEnd = line.find("$ss#", posStart);
		sline << line.substr(posStart, posEnd - posStart);
		sline >> sss;
		if (mode) cout << endl << "SSS: \t\t less " << sss * 100 << "%";
		sline.ignore(10000,'\n');
		sline.clear();
		
		posStart = line.find("$tx#") + 4;
		posEnd = line.find("$tx#", posStart);
		sline << line.substr(posStart, posEnd - posStart);
		sline >> tax;
		if (mode) cout << endl << "Tax: \t\t less " << tax * 100 << "%";
		sline.ignore(10000,'\n');
		sline.clear();

		userInFile.close();
	}
  	else cout << "Error: Unable to open Deductions database.";
  	
	cout << endl;
	system("pause");	
}


void users::changeDeductions() {
	string out; 
	ostringstream buff1, buff2, buff3, buff4;
	
	system("cls");
	
	cout << endl << "Note: Deductions are deducted from the base salary as percentages.";
	cout << endl << "Please enter the new values in decimal form. For example, enter 0.125 for a 12.5% deduction.";
	
	cout << endl << endl << "Enter the Pag-Ibig contribution deduction. " << endl;
	pagibig = mActions.askFloatInput(1);
	buff1 << pagibig;
	
	cout << endl << "Enter the PhilHealth contribution deduction. " << endl;
	philhealth = mActions.askFloatInput(1);
	buff2 << philhealth;
	
	cout << endl <<  "Enter the SSS contribution deduction. " << endl;
	sss = mActions.askFloatInput(1);
	buff3 << sss;
	
	cout << endl << "Enter the tax contribution deduction. " << endl;
	tax = mActions.askFloatInput(1);
	buff4 << tax;
	
	userOutFile.open("database/deductions.txt");
	
	if (userOutFile.is_open()){
		out = "$pg#" + buff1.str() + "$pg#$ph#" + buff2.str() + "$ph#$ss#" + buff3.str() + "$ss#$tx#" + buff4.str() + "$tx#";
		userOutFile << out; 
		userOutFile.close();
		
		cout << endl << "Here are the new values for each deduction: ";
		viewDeductions(true);
	} else {
		cout << endl << "Error: Unable to open Deductions database."; 
	}
	
	
	
}

//just indicates if query is matched or not
bool users::searchUserDB(string query, string type) {
	string line, found;
	int posStart, posEnd;

	
	userInFile.open("database/users.txt");
	if (userInFile.is_open()) {
		while ( getline (userInFile,line) ) {
			
//			cout << endl << line;
			posStart = line.find("$"+type+"#") + 4;
			posEnd = line.find("$"+type+"#", posStart);
			found = line.substr(posStart, posEnd - posStart);
//			cout << endl << found;
//			cout << endl << line.substr(posStart, posEnd - posStart);
			if (query == found) {
				userInFile.close();
				//cout << endl << focus;
				return true;
			}			
		}

		 userInFile.close();
	}
  	else cout << "Error: Unable to open Users database."; 
  	
  	
	return false;
}

//search and gets the whole line where query matching with an element was found
//keepSearch if true, searches whole database, false only first found
bool users::searchUserDB(string query, string element, string *focus, bool keepSearching) {
	string line, found;
	int ctr;

	ctr = 0;
	userInFile.open("database/users.txt");
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
  	else cout << "Error: Unable to open Users database."; 

	return false;
}

// updates line of specified db element ID, replaces whole line with newInfo
void users::updateUserDB(string id, string newInfo) {
	string temp, orig;
	int posStart, posEnd;
	
	userInFile.open("database/users.txt");
	userOutFile.open("temp.txt");
	
	if (userInFile.is_open() && userOutFile.is_open()){
		while (getline(userInFile, temp)) {
			orig = temp;
			posStart = temp.find("$id#") + 4;
			posEnd = temp.find("$id#", posStart);
			if (id == temp.substr(posStart, posEnd - posStart)) {
				orig = newInfo;
			}
			orig += "\n";
			userOutFile << orig;
		}
		
		userInFile.close();
		userOutFile.close();
		
		ifstream fileIn("temp.txt");
		ofstream fileOut("database/users.txt");
		
		if (fileIn.is_open() && fileOut.is_open()) {
			while (getline(fileIn, temp)) {
				temp += "\n";
				fileOut << temp;
			}
			
			fileIn.close();
			fileOut.close();	
		} else {
			cout << endl << "Error: Unable to update Users database."; 
		}
	remove("temp.txt");	
	} else {
		cout << endl << "Error: Unable to open Users database."; 
	}
	
	
}

string users::getLastUserEntry() {
	string line, last; 
	
	userInFile.open("database/users.txt");
	
	if (userInFile.is_open()) {
		while ( getline (userInFile,line) ) {
			if (line.at(0) == '$') {
				last = line;
			}		
		}
		
		
		 userInFile.close();
	}
  	else cout << "Error: Unable to open Users database."; 

	return last;
}

string users::getValueFromEntry(string element, string entry) {
//	cout << "entered! element is " << element << " entry is " << entry;
	int posStart, posEnd;
	
//	cout << element;
	
	posStart = entry.find(element) + 4;
	posEnd = entry.find(element, posStart);
	return entry.substr(posStart, posEnd - posStart);
//	cout <<"exited";
}

string users::getUserLevel(){
	return userLevel;
}

//int users::getUserLevel1(string ul){
//	string temp, orig;
//	int posStart, posEnd;
//	
//	userInFile.open("database/users.txt");
//	
//	if (userInFile.is_open() && userOutFile.is_open()){
//		while (getline(userInFile, temp)) {
//			orig = temp;
//			posStart = temp.find("$ul#") + 4;
//			posEnd = temp.find("$ul#", posStart);
//			if (ul == temp.substr(posStart, posEnd - posStart)) {
//				userInFile>>userLevel1;
//			}
//			orig += "\n";
//			
//		}
//		userInFile.close();
//	return userLevel1;
//}
//}


