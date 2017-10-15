#include "users.h"

// login users, verifies if account exist, and verifies if password is matched
void users::loginUser() {
	string input, currentUser;
	int posStart, posEnd;
	
	system("cls");
	cout << "Please enter your user ID: ";
	cin >>  input;
	
	
	
	if (searchUserDB(input, "id", &currentUser)) {
//		cout << "test1";
		userID = input;
		
		posStart = currentUser.find("$pw#") + 4;
		posEnd = currentUser.find("$pw#", posStart);
		password = currentUser.substr(posStart, posEnd - posStart);
		
		cout << "Please enter your password: ";
		cin >> input;
		if (input == password) {
			cout << endl << "Login successful!";
			
			posStart = currentUser.find("$fn#") + 4;
			posEnd = currentUser.find("$fn#", posStart);
			firstName = currentUser.substr(posStart, posEnd - posStart);
	
			posStart = currentUser.find("$ln#") + 4;
			posEnd = currentUser.find("$ln#", posStart);
			lastName = currentUser.substr(posStart, posEnd - posStart);		
			
			posStart = currentUser.find("$mn#") + 4;
			posEnd = currentUser.find("$mn#", posStart);
			middleName = currentUser.substr(posStart, posEnd - posStart);
			
			posStart = currentUser.find("$ul#") + 4;
			posEnd = currentUser.find("$ul#", posStart);
			userLevel = currentUser.substr(posStart, posEnd - posStart);
			
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

void users::loadDeductions() {
	string line;
	stringstream sline;
	int posStart, posEnd;
	
	userInFile.open("database/deductions.txt");
	if (userInFile.is_open()) {
		getline(userInFile,line);
		posStart = line.find("$pg#") + 4;
		posEnd = line.find("$pg#", posStart);
		cout << endl << "pagibig string: " << line.substr(posStart, posEnd - posStart);
		sline << line.substr(posStart, posEnd - posStart);
//		cout << "test2";
		sline >> pagibig;
		sline.ignore(10000,'\n');
		sline.clear();
		
	//	sline.flush();		
		
		
		cout << "pagibig: " << pagibig;			

		posStart = line.find("$ph#") + 4;
		posEnd = line.find("$ph#", posStart);
		cout << endl << "philheath string: " << line.substr(posStart, posEnd - posStart);
		sline << line.substr(posStart, posEnd - posStart);
		sline >> philhealth;			
		sline.ignore(10000,'\n');
		sline.clear();
		
		posStart = line.find("$ss#") + 4;
		posEnd = line.find("$ss#", posStart);
		cout << endl << "sss string: " << line.substr(posStart, posEnd - posStart);
		sline << line.substr(posStart, posEnd - posStart);
		sline >> sss;			
		sline.ignore(10000,'\n');
		sline.clear();
		
		posStart = line.find("$tx#") + 4;
		posEnd = line.find("$tx#", posStart);
		cout << endl << "tax string: " << line.substr(posStart, posEnd - posStart);
		sline << line.substr(posStart, posEnd - posStart);
		sline >> tax;			
		sline.ignore(10000,'\n');
		sline.clear();

		userInFile.close();
	}
  	else cout << "Error: Unable to open Deductions database.";
  	
  	
	cout << endl << "Deductions: " << pagibig << " " << philhealth << " " << sss << " " << tax;
  	system("pause");
	
}

void users::viewDeductions() {
	string line;
	int posStart, posEnd;
	
	userInFile.open("database/deductions.txt");
	if (userInFile.is_open()) {
		cout << endl << "=== List of Deductions ===";
		
		getline(userInFile,line);
		posStart = line.find("$pg#") + 4;
		posEnd = line.find("$pg#", posStart);
		cout << endl << "Pag-Ibig: \t less " << line.substr(posStart, posEnd - posStart) << "%";
		
		getline(userInFile,line);
		posStart = line.find("$ph#") + 4;
		posEnd = line.find("$ph#", posStart);
		cout << endl << "PhilHealth: \t less " << line.substr(posStart, posEnd - posStart) << "%";
		
		getline(userInFile,line);
		posStart = line.find("$ss#") + 4;
		posEnd = line.find("$ss#", posStart);
		cout << endl << "SSS: \t\t less " << line.substr(posStart, posEnd - posStart) << "%";

		getline(userInFile,line);
		posStart = line.find("$tx#") + 4;
		posEnd = line.find("$tx#", posStart);
		cout << endl << "Tax: \t\t less " << line.substr(posStart, posEnd - posStart) << "%";

		userInFile.close();
	}
  	else cout << "Error: Unable to open Deductions database.";
  	
  	cout << endl;
	system("pause");
		
}

void users::changeDeductions() {
	
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

//search and gets the whole line where query was found
bool users::searchUserDB(string query, string type, string *focus) {
	string line, found;
	int posStart, posEnd;

	userInFile.open("database/users.txt");
	if (userInFile.is_open()) {
		while ( getline (userInFile,line) ) {
			*focus = line;
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

// updates line of specified id, replaces whole line with newInfo
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


