#include "miscActions.h"
#include <windows.h>
#include <conio.h>
#include <iomanip>
float miscActions::askFloatInput(int mode) {
	float input;
	string str;
	bool repeat;
	//mode: 0 for default, 1 for values >= 0 only, 2 for values <= 0 only	
	//improve to capture mixed string like 123abc or presence of decimals	
	do {
		repeat = false;
		while (cout << "Input: " && !(cin >> str)) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Error: Invalid input! Please try again." << endl;			
		}
		istringstream ss(str);
		if (!(ss >> input)) {
				cout << "Error: Invalid input! Please try again." << endl;
				repeat = true;
		} else {
			if (mode == 1 && input < 0) {
					cout << "Error: Negative value not valid! Please try again." << endl;
					repeat = true;
			} else if (mode == 2 && input > 0) {
					cout << "Error: Positive value not valid! Please try again." << endl;
					repeat = true;
			}
		}
		cin.clear();
		cin.ignore(10000, '\n');
	} while (repeat);
	return input;
}

char miscActions::getTask(){
	return task;
}

int miscActions::askIntInput(int mode) {
	int input;
	string str;
	bool repeat;
	//mode: 0 for default, 1 for values >= 0 only, 2 for values <= 0 only	
	//improve to capture mixed string like 123abc or presence of decimals	
	do {
		repeat = false;
		while (cout << "Input: " && !(cin >> str)) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Error: Invalid input! Please try again." << endl;			
		}
		istringstream ss(str);
		if (!(ss >> input)) {
				cout << "Error: Invalid input! Please try again." << endl;
				repeat = true;
		} else {
			if (mode == 1 && input < 0) {
					cout << "Error: Negative value not valid! Please try again." << endl;
					repeat = true;
			} else if (mode == 2 && input > 0) {
					cout << "Error: Positive value not valid! Please try again." << endl;
					repeat = true;
			}
		}
		cin.clear();
		cin.ignore(10000, '\n');
	} while (repeat);
	return input;
}

//stringstream miscActions::clearSStream(stringstream argStream) {
//	stringstream temp; 
//	
//	temp << argStream;
//	temp.str(string());
//	temp.clear();
//	
//	return temp;
//}

void miscActions::managerSubMenu(void){
	int result=0;
	char input;
	switch(toupper(task))
	{
		case 'F':{
			cout<<"\t\t\t\t\t============ File Maintenance ==========="<<endl;
			cout<<"\t\t\t\t\t=\t\t[C] Create\t\t="<<endl;
			cout<<"\t\t\t\t\t=\t\t[V] View\t\t="<<endl;
			cout<<"\t\t\t\t\t=\t\t[U] Update\t\t="<<endl;
			cout<<"\t\t\t\t\t=\t\t[D] Delete\t\t="<<endl;
			cout<<"\t\t\t\t\t========================================="<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>input;
			switch(toupper(input))
			{
				case 'C':{
					cout<<"\t\t\t\t\t================ Create ================="<<endl;
					cout<<"\t\t\t\t\t=\t[1] Create Department\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[2] Create Location\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[3] Create Job Position\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[4] Create Benefits\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[5] Create Employee\t\t="<<endl;
					cout<<"\t\t\t\t\t========================================="<<endl;
					cout<<"\t\t\t\t\tEnter input: ";
					cin>>perform;
					cin.ignore();
					switch(perform){
						case '1': result=dept.createNewDepartment();
							break;
						case '2': result=loc.createNewLocation();
							break;
						case '3': result=jp.createNewJobPosition();
							break;
						case '4': result=ben.createNewBenefit();
							break;
						case '5': result=er.createNewEmployee();
							break;
					}
					if(result==1){
						cout<<endl<<endl<<"successfully created!"<<endl;
						system("pause");
					}
					else{
						cout<<endl<<endl<<"failed to proccess request!"<<endl;
						system("pause");
					}
					break;
				}
				case 'V':{
					cout<<"\t\t\t\t\t================= View =================="<<endl;
					cout<<"\t\t\t\t\t=\t[D] View Department\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[L] View Location\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[P] View Job Position\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[B] View Benefits\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[E] View Employee\t\t="<<endl;
					cout<<"\t\t\t\t\t========================================="<<endl;
					cout<<"\t\t\t\t\tEnter input: ";
					cin>>input;
					managerView(input);
					break;
				}
				case 'U':{
					cout<<"\t\t\t\t\t================ Update ================="<<endl;
					cout<<"\t\t\t\t\t=\t[D] Update Department\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[L] Update Location\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[P] Update Job Position\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[B] Update Benefits\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[E] Update Employee\t\t="<<endl;
					cout<<"\t\t\t\t\t========================================="<<endl;
					cout<<"\t\t\t\t\tEnter input: ";
					cin>>perform;	
					cin.ignore();
					switch(toupper(perform)){
						case 'D': result=dept.updateDepartment();
							break;
						case 'L': result=loc.updateLocation();
							break;
						case 'P': result=jp.updateJobPosition();
							break;
						case 'B': result=ben.updateBenefit();
							break;
						case 'E': result=er.updateEmployee();
							break;
					}
					if(result==1){
						cout<<endl<<endl<<"successfully updated!"<<endl;
						system("pause");
					}
					else{
						cout<<endl<<endl<<"failed to proccess request!"<<endl;
						system("pause");
					}
					break;
				}
				case 'D':{
					cout<<"\t\t\t\t\t================ Delete ================="<<endl;
					cout<<"\t\t\t\t\t=\t[D] Delete Department\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[L] Delete Location\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[P] Delete Job Position\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[B] Delete Benefits\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[E] Delete Employee\t\t="<<endl;
					cout<<"\t\t\t\t\t========================================="<<endl;
					cout<<"\t\t\t\t\tEnter input: ";
					cin>>perform;
					cin.ignore();
					switch(toupper(perform)){
						case 'D': result=dept.deleteDepartment();
							break;
						case 'L': result=loc.deleteLocation();
							break;
						case 'P': result=jp.deleteJobPosition();
							break;
						case 'B': result=ben.deleteBenefit();
							break;
						case 'E': result=er.deleteEmployee();
							break;
					}
					if(result==1){
						cout<<endl<<endl<<"successfully Deleted!"<<endl;
						system("pause");
					}
					else{
						cout<<endl<<endl<<"failed to proccess request!"<<endl;
						system("pause");
					}
					break;
				}
				default:{
					break;
				}
			}
			break;
		}
		case 'I':{
			cout<<"\t\t\t\t\t==================== Inquiry ======================"<<endl;
			cout<<"\t\t\t\t\t= [J] View Available Job Opening                  ="<<endl;
			cout<<"\t\t\t\t\t= [A] View List of Applicant                      ="<<endl;
			cout<<"\t\t\t\t\t= [L] View List of Pay Roll Information           ="<<endl;
			cout<<"\t\t\t\t\t= [P] View Pay Roll of Employee                   ="<<endl;
			cout<<"\t\t\t\t\t= [F] View Filtered Pay Slips                     ="<<endl;
			cout<<"\t\t\t\t\t= [C] View Current Benefit Enrollment             ="<<endl;
			cout<<"\t\t\t\t\t= [E] View Current Benefit Enrollment of Employee ="<<endl;
			cout<<"\t\t\t\t\t= [S] Search\t                                  ="<<endl;
			cout<<"\t\t\t\t\t==================================================="<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>report;
			viewReports('i');
			break;
		}
		case 'T':{
			cout<<"\t\t\t\t\t============= Transactions ==============="<<endl;
			cout<<"\t\t\t\t\t=\t[M] Manage Job Openings\t\t ="<<endl;
			cout<<"\t\t\t\t\t=\t[T] Time Reports\t\t ="<<endl;
			cout<<"\t\t\t\t\t=\t[P] Add Base Pay\t\t ="<<endl;
			cout<<"\t\t\t\t\t=\t[G] Generate Pay Slip\t\t ="<<endl;
			cout<<"\t\t\t\t\t=\t[B] Allot Benefits\t\t ="<<endl;
			cout<<"\t\t\t\t\t=========================================="<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>input;
			switch(toupper(input))
			{
				case 'M':{
					cout<<"\t\t\t\t\t========== Manage Job Openings =========="<<endl;
					cout<<"\t\t\t\t\t=\t[C] Create Job Opening\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[V] View Job Opening\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[E] Edit Job Opening\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[D] Delete Job Opening\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[A] Assign Applicant\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[H] Hire Employee\t\t="<<endl;
					cout<<"\t\t\t\t\t========================================="<<endl;
					cout<<"\t\t\t\t\tEnter input: ";
					cin>>perform;
					cin.ignore();
					switch(toupper(perform)){
						case 'C': result=jo.createNewJobOpening();
							break;
						case 'V': report='j';
								viewReports('t');
								result=-1;
							break;
						case 'E': result=jo.updateJobOpening();
							break;
						case 'D': result=jo.deleteJobOpening();
							break;
						case 'A': result=jo.assignApplicant();
							break;
						case 'H': result=jo.hireApplicant();
							break;
					}
					if(result==1){
						cout<<endl<<endl<<"Transaction Successful!"<<endl;
						system("pause");
					}
					else if(result==0){
						cout<<endl<<endl<<"failed to proccess request!"<<endl;
						system("pause");
					}
					break;
				}
				case 'T':{
					cout<<"\t\t\t\t\t============== Time Reports ==============="<<endl;
					cout<<"\t\t\t\t\t=\t[1] View Employee                 ="<<endl;
					cout<<"\t\t\t\t\t=\t[2] Approve Time Report           ="<<endl;
					cout<<"\t\t\t\t\t=\t[3] Time Report Adjustment        ="<<endl;
					cout<<"\t\t\t\t\t==========================================="<<endl;
					cout<<"\t\t\t\t\tEnter input: ";
					cin>>perform;
					cin.ignore();
					switch(toupper(perform)){
						case '1':{
							viewEmployee();
							break; 
						}
					}
					break;
				}
				case 'P':{
					cout<<"\t\t\t\t\t================= Salary ================="<<endl;
					cout<<"\t\t\t\t\t= [1] View Employee Salary               ="<<endl;
					cout<<"\t\t\t\t\t= [2] View Employee Info                 ="<<endl;
					cout<<"\t\t\t\t\t= [3] Compute Salary                     ="<<endl;
					cout<<"\t\t\t\t\t=========================================="<<endl;
					cout<<"\t\t\t\t\tEnter input: ";
					cin>>perform;	
					break;
				}
				case 'G':{
					
					break;
				}
				case 'B':{
					
					break;
				}
				default: {
					break;
				}
			break;
			}
			break;
		}
		
		case 'R':{
			cout<<"\t\t\t\t============================ Report =========================="<<endl;
			cout<<"\t\t\t\t=\t[J] View Open Job Positions                          ="<<endl;
			cout<<"\t\t\t\t=\t[A] View List of Candidates                          ="<<endl;
			cout<<"\t\t\t\t=\t[4] View Pay Roll Information of All Employee        ="<<endl;
			cout<<"\t\t\t\t=\t[5] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[6] View Current Benefit Enrollment of an Employee   ="<<endl;
			cout<<"\t\t\t\t=============================================================="<<endl;
			cout<<"\t\t\t\tEnter input: ";
			cin>>report;
			viewReports('r');
			break;
		}
		case 'U':{
			cout<<"\t\t\t\t\t=============== Utilities =================="<<endl;
			cout<<"\t\t\t\t\t= \t   [C] Change Password \t           ="<<endl;
			cout<<"\t\t\t\t\t= \t   [D] Delete User\t\t   ="<<endl;
			cout<<"\t\t\t\t\t============================================"<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>input;
			break;
		}
		default: {
			break;
		}
	}
}

void miscActions::viewEmployee(){
	string line, found,temp;
	int posStart=0, posEnd=0;
	system("cls");
			cout<<"\t\t\t\t\t View Employee\n\n";
			userInFile.open("database/employees.txt");
			getline(userInFile,line);
			if (userInFile.is_open()) {
					while ( getline (userInFile,line) ) {
					
							posStart = line.find("$eid#") + 5;
							posEnd = line.find("$eid#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t ID: "<<found<<endl;
							posStart = line.find("$ena#") + 5;
							posEnd = line.find("$ena#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Name: "<<found<<endl;
							posStart = line.find("$ead#") + 5;
							posEnd = line.find("$ead#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Address: "<<found<<endl;
							posStart = line.find("$ecn#") + 5;
							posEnd = line.find("$ecn#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Contact #: "<<found<<endl;
							posStart = line.find("$eag#") + 5;
							posEnd = line.find("$eag#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Age: "<<found<<endl;
							posStart = line.find("$eea#") + 5;
							posEnd = line.find("$eea#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Email Address: "<<found<<endl;
							posStart = line.find("$ebd#") + 5;
							posEnd = line.find("$ebd#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Birthday: "<<found<<endl;
							posStart = line.find("$esx#") + 5;
							posEnd = line.find("$esx#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Sex: "<<found<<endl;
							posStart = line.find("$efn#") + 5;
							posEnd = line.find("$efn#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Father's Name: "<<found<<endl;
							posStart = line.find("$efo#") + 5;
							posEnd = line.find("$efo#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Father's Occupation: "<<found<<endl;
							posStart = line.find("$emn#") + 5;
							posEnd = line.find("$emn#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Mother's Name: "<<found<<endl;
							posStart = line.find("$emo#") + 5;
							posEnd = line.find("$emo#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Mother's: "<<found<<endl;
							posStart = line.find("$ems#") + 5;
							posEnd = line.find("$ems#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Civil Status: "<<found<<endl;
							posStart = line.find("$esd#") + 5;
							posEnd = line.find("$esd#", posStart);
							found = line.substr(posStart, posEnd - posStart);
							if(found!="\t")
								cout<<"\t\t\t\t Start Date: "<<found<<endl;
							posStart = line.find("$ees#") + 5;
							posEnd = line.find("$ees#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Employment Status: "<<found<<endl;	
							posStart = line.find("$eat#") + 5;
							posEnd = line.find("$eat#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Educational Attainment: "<<found<<endl;
							posStart = line.find("$esn#") + 5;
							posEnd = line.find("$esn#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t School Name: "<<found<<endl;
							posStart = line.find("$esa#") + 5;
							posEnd = line.find("$esa#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t School Address: "<<found<<endl;
							posStart = line.find("$eyg#") + 5;
							posEnd = line.find("$eyg#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Year Graduated: "<<found<<endl;
							posStart = line.find("$ebs#") + 5;
							posEnd = line.find("$ebs#", posStart);
							found = line.substr(posStart, posEnd - posStart);
							if(found!="0")
								cout<<"\t\t\t\t Base Salary: "<<found<<".00 PHP"<<endl;
							else cout<<endl;
							posStart = line.find("$ejp#") + 5;
							posEnd = line.find("$ejp#", posStart);
							found = line.substr(posStart, posEnd - posStart);
							if(found!="\t")
								cout<<"\t\t\t\t Base Salary: "<<found<<".00 PHP"<<endl<<endl;			
						}
						system("pause");
					userInFile.close();
					}
					else{
						cout << "Error: Unable to open employee database."; 
				
					}
}

void miscActions::managerView(char perform){
	string line, found,temp;
	int posStart=0, posEnd=0;
	switch(toupper(perform)){
		case 'D':{
			system("cls");
			cout<<"\t\t\t\t\t View Department\n\n";
			userInFile.open("database/departments.txt");
			getline(userInFile,line);
			if (userInFile.is_open()) {
					while ( getline (userInFile,line) ) {
					
							posStart = line.find("$did#") + 5;
							posEnd = line.find("$did#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Department ID: "<<found<<endl;	
							posStart = line.find("$dco#") + 5;
							posEnd = line.find("$dco#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Department Code: "<<found<<endl;
							posStart = line.find("$dna#") + 5;
							posEnd = line.find("$dna#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Department Name: "<<found<<endl<<endl;		
						}
						system("pause");
					userInFile.close();
					}
					else{
						cout << "Error: Unable to open department database."; 
				
					}
			break;
		}
		case 'L':{
			system("cls");
			cout<<"\t\t\t\t\t View Location\n\n";
			userInFile.open("database/locations.txt");
			getline(userInFile,line);
			if (userInFile.is_open()) {
					while ( getline (userInFile,line) ) {
					
							posStart = line.find("$lid#") + 5;
							posEnd = line.find("$lid#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Location ID: "<<found<<endl;	
							posStart = line.find("$lco#") + 5;
							posEnd = line.find("$lco#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Location Code: "<<found<<endl;
							posStart = line.find("$lna#") + 5;
							posEnd = line.find("$lna#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Location Name: "<<found<<endl<<endl;		
						}
						system("pause");
					userInFile.close();
					}
					else{
						cout << "Error: Unable to open location database."; 
				
					}
			break;
		}
		case 'P':{
			system("cls");
			cout<<"\t\t\t\t\t View Job Position\n\n";
			userInFile.open("database/jobPositions.txt");
			getline(userInFile,line);
			if (userInFile.is_open()) {
					while ( getline (userInFile,line) ) {
					
							posStart = line.find("$jid#") + 5;
							posEnd = line.find("$jid#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Job Position ID: "<<found<<endl;
							posStart = line.find("$jpc#") + 5;
							posEnd = line.find("$jpc#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Job Position Code: "<<found<<endl;		
							posStart = line.find("$jpn#") + 5;
							posEnd = line.find("$jpn#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Job Position: "<<found<<endl<<endl;		
						}
						system("pause");
					userInFile.close();
					}
					else{
						cout << "Error: Unable to open job position database."; 
				
					}
			break;
		}
		case 'B':{
			system("cls");
			cout<<"\t\t\t\t\t View Benefits\n\n";
			userInFile.open("database/benefits.txt");
			getline(userInFile,line);
			if (userInFile.is_open()) {
					while ( getline (userInFile,line) ) {
					
							posStart = line.find("$bco#") + 5;
							posEnd = line.find("$bco#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Benefit ID: "<<found<<endl;	
							posStart = line.find("$bna#") + 5;
							posEnd = line.find("$bna#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Benefit Name: "<<found<<endl;		
							posStart = line.find("$bam#") + 5;
							posEnd = line.find("$bam#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Amount: "<<found<<".00 PHP"<<endl;		
							posStart = line.find("$bcd#") + 5;
							posEnd = line.find("$bcd#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Create Date: "<<found<<endl<<endl;	
						}
						system("pause");
					userInFile.close();
					}
					else{
						cout << "Error: Unable to open benefit database."; 
				
					}
			break;
		}
		case 'E':{
			system("cls");
			cout<<"\t\t\t\t\t View Employee\n\n";
			userInFile.open("database/employees.txt");
			getline(userInFile,line);
			if (userInFile.is_open()) {
					while ( getline (userInFile,line) ) {
					
							posStart = line.find("$eid#") + 5;
							posEnd = line.find("$eid#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t ID: "<<found<<endl;
							posStart = line.find("$ena#") + 5;
							posEnd = line.find("$ena#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Name: "<<found<<endl;
							posStart = line.find("$ead#") + 5;
							posEnd = line.find("$ead#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Address: "<<found<<endl;
							posStart = line.find("$ecn#") + 5;
							posEnd = line.find("$ecn#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Contact #: "<<found<<endl;
							posStart = line.find("$eag#") + 5;
							posEnd = line.find("$eag#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Age: "<<found<<endl;
							posStart = line.find("$eea#") + 5;
							posEnd = line.find("$eea#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Email Address: "<<found<<endl;
							posStart = line.find("$ebd#") + 5;
							posEnd = line.find("$ebd#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Birthday: "<<found<<endl;
							posStart = line.find("$esx#") + 5;
							posEnd = line.find("$esx#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Sex: "<<found<<endl;
							posStart = line.find("$efn#") + 5;
							posEnd = line.find("$efn#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Father's Name: "<<found<<endl;
							posStart = line.find("$efo#") + 5;
							posEnd = line.find("$efo#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Father's Occupation: "<<found<<endl;
							posStart = line.find("$emn#") + 5;
							posEnd = line.find("$emn#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Mother's Name: "<<found<<endl;
							posStart = line.find("$emo#") + 5;
							posEnd = line.find("$emo#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Mother's: "<<found<<endl;
							posStart = line.find("$ems#") + 5;
							posEnd = line.find("$ems#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Civil Status: "<<found<<endl;
							posStart = line.find("$esd#") + 5;
							posEnd = line.find("$esd#", posStart);
							found = line.substr(posStart, posEnd - posStart);
							if(found!="\t")
								cout<<"\t\t\t\t Start Date: "<<found<<endl;
							posStart = line.find("$ees#") + 5;
							posEnd = line.find("$ees#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Employment Status: "<<found<<endl;	
							posStart = line.find("$eat#") + 5;
							posEnd = line.find("$eat#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Educational Attainment: "<<found<<endl;
							posStart = line.find("$esn#") + 5;
							posEnd = line.find("$esn#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t School Name: "<<found<<endl;
							posStart = line.find("$esa#") + 5;
							posEnd = line.find("$esa#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t School Address: "<<found<<endl;
							posStart = line.find("$eyg#") + 5;
							posEnd = line.find("$eyg#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Year Graduated: "<<found<<endl;
							posStart = line.find("$ebs#") + 5;
							posEnd = line.find("$ebs#", posStart);
							found = line.substr(posStart, posEnd - posStart);
							if(found!="0")
								cout<<"\t\t\t\t Base Salary: "<<found<<".00 PHP"<<endl;
							else cout<<endl;
							posStart = line.find("$ejp#") + 5;
							posEnd = line.find("$ejp#", posStart);
							found = line.substr(posStart, posEnd - posStart);
							if(found!="\t")
								cout<<"\t\t\t\t Base Salary: "<<found<<".00 PHP"<<endl<<endl;			
						}
						system("pause");
					userInFile.close();
					}
					else{
						cout << "Error: Unable to open employee database."; 
				
					}
			break;
		}
	}
}

void miscActions::Menu(void){
	cout<<"\t\t\t\t\t=========================================="<<endl;
	cout<<"\t\t\t\t\t=\t[F] File Maintenance\t\t ="<<endl;
	cout<<"\t\t\t\t\t=\t[T] Transactions\t\t ="<<endl;
	cout<<"\t\t\t\t\t=\t[I] Inquiry\t\t\t ="<<endl;
	cout<<"\t\t\t\t\t=\t[R] Report\t\t\t ="<<endl;
	cout<<"\t\t\t\t\t=\t[U] Utilities\t\t\t ="<<endl;
	cout<<"\t\t\t\t\t=\t[E] Logout\t\t\t ="<<endl;
	cout<<"\t\t\t\t\t=========================================="<<endl;
	cout<<"\t\t\t\t\tEnter letter of choice: ";
//	cin.ignore();
	cin>>task;
}

void miscActions::recruiterSubMenu(void){
	char input,result=0;
	switch(toupper(task))
	{
		case 'F':{
			cout<<"\t\t\t\t\t============ File Maintenance ==========="<<endl;
			cout<<"\t\t\t\t\t= [C] Create Employee\t\t\t="<<endl;
			cout<<"\t\t\t\t\t= [U] Update Employee Data Records\t="<<endl;
			cout<<"\t\t\t\t\t= [D] Delete Employee Data Records\t="<<endl;
			cout<<"\t\t\t\t\t========================================="<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>input;
			cin.ignore();
			switch(toupper(input)){
				case 'C': if(er.createNewEmployee()){
						cout<<endl<<"Employee Creation Successful"<<endl;
					}
					break;
				case 'U': if(er.updateEmployee()){
						cout<<endl<<"Employee Update Successful"<<endl;
					}
					break;
				case 'D': if(er.deleteEmployee()){
						cout<<endl<<"Employee Deletion Successful"<<endl;
					}
					break;
			}
			cout<<endl;
			system("pause");
			break;
		}
		case 'I':{
			cout<<"\t\t\t\t\t================== Inquiry ===================="<<endl;
			cout<<"\t\t\t\t\t= [J] View List of Available Job Openings     ="<<endl;
			cout<<"\t\t\t\t\t= [A] View List of Applicants for a Job Order ="<<endl;
			cout<<"\t\t\t\t\t= [S] View Summary of Benefits                ="<<endl;
			cout<<"\t\t\t\t\t= [B] View Benefits of an Employee            ="<<endl;
			cout<<"\t\t\t\t\t= [S] Search\t                                  ="<<endl;
			cout<<"\t\t\t\t\t==============================================="<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>report;
			viewReports('i');
			break;
		}
		case 'T':{
			cout<<"\t\t\t\t\t============= Transactions ==============="<<endl;
			cout<<"\t\t\t\t\t=\t[C] Create Job Opening\t\t ="<<endl;
			cout<<"\t\t\t\t\t=\t[E] Edit Job Opening\t\t ="<<endl;
			cout<<"\t\t\t\t\t=\t[V] View Job Opening\t\t ="<<endl;
			cout<<"\t\t\t\t\t=\t[D] Delete Job Opening\t\t ="<<endl;
			cout<<"\t\t\t\t\t=\t[A] Assign Applicant\t\t ="<<endl;
			cout<<"\t\t\t\t\t=========================================="<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>input;
				cin.ignore();
				switch(toupper(input)){
					case 'C': result=jo.createNewJobOpening();
						break;
					case 'E': result=jo.updateJobOpening();
						break;
					case 'V': report='j';
							viewReports('t');
							result=-1;
						break;
					case 'D': result=jo.deleteJobOpening();
						break;
					case 'A': result=jo.assignApplicant();
						break;
				}
				if(result==1){
					cout<<endl<<endl<<"successfully updated!"<<endl;
					system("pause");
				}
				else if(result==0){
					cout<<endl<<endl<<"failed to proccess request!"<<endl;
					system("pause");
				}
			
			break;
		}
		
		case 'R':{
			cout<<"\t\t\t\t============================ Report =========================="<<endl;
			cout<<"\t\t\t\t=\t[J] View Open Job Positions                          ="<<endl;
			cout<<"\t\t\t\t=\t[A] View List of Candidates                          ="<<endl;
			cout<<"\t\t\t\t=\t[3] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[4] View Current Benefit Enrollment of an Employee   ="<<endl;
			cout<<"\t\t\t\t=============================================================="<<endl;
			cout<<"\t\t\t\tEnter input: ";
			cin>>report;
			viewReports('r');
			break;
		}
		case 'U':{
			cout<<"\t\t\t\t\t=============== Utilities =================="<<endl;
			cout<<"\t\t\t\t\t= \t   [C] Change Password \t           ="<<endl;
			cout<<"\t\t\t\t\t= \t   [D] Delete User\t\t   ="<<endl;
			cout<<"\t\t\t\t\t============================================"<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>input;
			break;
		}
		default: {
			break;
		}
}

}

void miscActions::personnelSubMenu(void){
	char input;
	switch(toupper(task))
	{
		case 'F':{
			fflush(stdin);
			cout<<"\t\t\t\tAccess Denied! User Level must be Manager or Recruiter.\n\t\t\t\t";
			system("pause");
			break;
		}
		case 'I':{
			cout<<"\t\t\t\t\t================== Inquiry ===================="<<endl;
			cout<<"\t\t\t\t\t= [J] View List of Available Job Openings     ="<<endl;
			cout<<"\t\t\t\t\t= [A] View List of Applicants for a Job Order ="<<endl;
			cout<<"\t\t\t\t\t= [S] View Summary of Benefits                ="<<endl;
			cout<<"\t\t\t\t\t= [B] View Benefits of an Employee            ="<<endl;
			cout<<"\t\t\t\t\t= [S] Search                                  ="<<endl;
			cout<<"\t\t\t\t\t==============================================="<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>report;
			viewReports('i');
			break;
		}
		case 'T':{
			cout<<"\t\t\t\t\t=============== Transactions ============="<<endl;
			cout<<"\t\t\t\t\t= [V] View List of Employee Time Reports ="<<endl;
			cout<<"\t\t\t\t\t= [T] View Time Report Status            ="<<endl;
			cout<<"\t\t\t\t\t= [R] Time Report Adjustments            ="<<endl;
			cout<<"\t\t\t\t\t= [D] Delete Time Report                 ="<<endl;
			cout<<"\t\t\t\t\t= [B] View All Benefits                  ="<<endl;
			cout<<"\t\t\t\t\t=========================================="<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>input;
			
			break;
		}
		
		case 'R':{
			cout<<"\t\t\t\t============================ Report =========================="<<endl;
			cout<<"\t\t\t\t=\t[J] View Open Job Positions                          ="<<endl;
			cout<<"\t\t\t\t=\t[A] View List of Candidates                          ="<<endl;
			cout<<"\t\t\t\t=\t[3] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[4] View Current Benefit Enrollment of an Employee   ="<<endl;
			cout<<"\t\t\t\t=============================================================="<<endl;
			cout<<"\t\t\t\tEnter input: ";
			cin>>report;
			viewReports('r');
			break;
		}
		case 'U':{
			cout<<"\t\t\t\t\t=============== Utilities =================="<<endl;
			cout<<"\t\t\t\t\t= \t   [C] Change Password             ="<<endl;
			cout<<"\t\t\t\t\t= \t   [D] Delete User                 ="<<endl;
			cout<<"\t\t\t\t\t============================================"<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>input;
			break;
		}
		default: {
			break;
		}
}

}
void miscActions::adminSubMenu(void){
	char input;
	switch(toupper(task))
	{
		case 'F':{
			fflush(stdin);
			cout<<"\t\t\t\tAccess Denied! User Level must be Manager, Recruiter or Personnel.\n\t\t\t\t";
			system("pause");
			break;
		}
		case 'I':{
			cout<<"\t\t\t\t\t================== Inquiry ===================="<<endl;
			cout<<"\t\t\t\t\t= [J] View List of Available Job Openings     ="<<endl;
			cout<<"\t\t\t\t\t= [S] View Summary of Benefits                ="<<endl;
			cout<<"\t\t\t\t\t= [B] View Benefits of an Employee            ="<<endl;
			cout<<"\t\t\t\t\t= [S] Search                                  ="<<endl;
			cout<<"\t\t\t\t\t==============================================="<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>report;
			viewReports('i');
			break;
		}
		case 'T':{
			fflush(stdin);
			cout<<"\t\t\t\tAccess Denied! User Level must be Manager, Recruiter or Personnel.\n\t\t\t\t";
			system("pause");
			break;
		}
		
		case 'R':{
			cout<<"\t\t\t\t============================ Report =========================="<<endl;
			cout<<"\t\t\t\t=\t[J] View Open Job Positions                          ="<<endl;
			cout<<"\t\t\t\t=\t[A] View List of Candidates                          ="<<endl;
			cout<<"\t\t\t\t=\t[2] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[3] View Current Benefit Enrollment of an Employee   ="<<endl;
			cout<<"\t\t\t\t=============================================================="<<endl;
			cout<<"\t\t\t\tEnter input: ";
			cin>>report;
			viewReports('r');
			break;
		}
		case 'U':{
			cout<<"\t\t\t\t\t=============== Utilities =================="<<endl;
			cout<<"\t\t\t\t\t= \t   [R] Register New User           ="<<endl;
			cout<<"\t\t\t\t\t= \t   [C] Change Password             ="<<endl;
			cout<<"\t\t\t\t\t= \t   [O] Override Code               ="<<endl;
			cout<<"\t\t\t\t\t= \t   [S] Delete Specific User        ="<<endl;
			cout<<"\t\t\t\t\t= \t   [D] Delete User                 ="<<endl;
			cout<<"\t\t\t\t\t= \t   [V] View Credentials            ="<<endl;
			cout<<"\t\t\t\t\t= \t   [U] Update Credentials          ="<<endl;
			cout<<"\t\t\t\t\t============================================"<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>input;
			
			break;
		}
		default: {
			break;
		}
}

}

void miscActions::viewReports(char type){
	string line, found,temp;
	string jobNumber;
	int Result;
	stringstream convert; // stringstream used for the conversion
	char ch;
	string found1=jo.retrieveInfo(jobNumber,"jap");
	string empID,foundID;
	int posStart1=0;
	int subStart=0, subEnd=0;
	int posStart=0, posEnd=0;
		switch(toupper(report)){
			case 'J':{
				system("cls");
				userInFile.open("database/jobOpenings.txt");
				userOutFile.open("database/tempJobOpenings.txt");
				cout<<"\t\t\t\t\t All Available Job Opening\n\n";
				userOutFile<<"\t\t\t\t\t All Available Job Opening\n\n";
				if (userInFile.is_open()) {
					getline(userInFile,line);
					while ( getline (userInFile,line) ) {
						posStart = line.find("$jav#") + 5;
						posEnd = line.find("$jav#", posStart);
						found = line.substr(posStart, posEnd - posStart);
							if(found=="Open"){
								posStart = line.find("$jid#") + 5;
								posEnd = line.find("$jid#", posStart);
									cout<<"\t\t\t\t\t Job #: "<<line.substr(posStart, posEnd - posStart)<<endl;	
									userOutFile<<"\t\t\t\t\t Job #: "<<line.substr(posStart, posEnd - posStart)<<endl;	
								posStart = line.find("$jpo#") + 5;
								posEnd = line.find("$jpo#", posStart);
									cout<<"\t\t\t\t Job Position: "<<line.substr(posStart, posEnd - posStart)<<endl;
									userOutFile<<"\t\t\t\t Job Position: "<<line.substr(posStart, posEnd - posStart)<<endl;
								posStart = line.find("$jde#") + 5;
								posEnd = line.find("$jde#", posStart);
									cout<<"\t\t\t\t Department #: "<<line.substr(posStart, posEnd - posStart)<<endl;
									userOutFile<<"\t\t\t\t Department #: "<<line.substr(posStart, posEnd - posStart)<<endl;	
								posStart = line.find("$jlo#") + 5;
								posEnd = line.find("$jlo#", posStart);
									cout<<"\t\t\t\t Location #: "<<line.substr(posStart, posEnd - posStart)<<endl;
									userOutFile<<"\t\t\t\t Location #: "<<line.substr(posStart, posEnd - posStart)<<endl;
								posStart = line.find("$req#") + 5;
								posEnd = line.find("$req#", posStart);
								found=line.substr(posStart, posEnd - posStart);
								for(int i=0;i<found.size();i++){
									if(found[i]=='%'){
										found[i]=',';
										i++;
										found[i]=' ';
									}
								}
									cout<<"\t\t\t\t Job Requirements: "<<found<<endl;
									userOutFile<<"\t\t\t\t Job Requirements: "<<found<<endl;
								posStart = line.find("$jap#") + 5;
								posEnd = line.find("$jap#", posStart);
								found=line.substr(posStart, posEnd - posStart);
								for(int i=0;i<found.size();i++){
									if(found[i]=='%'){
										found[i]=',';
										i++;
										found[i]=' ';
									}
								}
									cout<<"\t\t\t\t Aspiring Applicants: "<<found<<endl<<endl;
									userOutFile<<"\t\t\t\t Aspiring Applicants: "<<found<<endl<<endl;
							}
							else{
								break;
							}
						}
					userInFile.close();
					userOutFile.close();
					}
					else{
						cout << "Error: Unable to open job openings database."; 
				
					}
					cout<<endl<<endl;
					system("pause");
					if(toupper(type)=='R'){
						cout<<"\t\t\t\t\t Print Job Openings? (y/n) ";
						cin>>ch;
						if(toupper(ch)=='Y'){
							userInFile.open("database/tempJobOpenings.txt");
							userOutFile.open("Print/Job Openings.txt");
							while(getline(userInFile,line)){
								userOutFile<<line<<endl;
							}
							userInFile.close();
							userOutFile.close();
							cout<<endl<<"Job Openings Successfully Printed!"<<endl;
							system("pause");
						}
					}
					remove("database/tempJobOpenings.txt");
				break;
			}
		case 'A':	er.erOutFile.open("database/tempEmployees.txt");
					er.erOutFile<<"\n\n\t\t\t\t Aspiring Applicants "<<endl<<endl;
					er.erInFile.open("database/employees.txt");
					getline(er.erInFile,line);
					while(getline(er.erInFile,line)){
						subStart=line.find("$ees#")+5;
						subEnd=line.find("$ees#",subStart);
						foundID=line.substr(subStart,subEnd-subStart);
						if(foundID=="Applicant"){
							posStart = line.find("$eid#") + 5;
							posEnd = line.find("$eid#", posStart);
								er.erOutFile<<"\t\t\t\t ID: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$ena#") + 5;
							posEnd = line.find("$ena#", posStart);
								er.erOutFile<<"\t\t\t\t Name: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$ead#") + 5;
							posEnd = line.find("$ead#", posStart);
								er.erOutFile<<"\t\t\t\t Address: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$ecn#") + 5;
							posEnd = line.find("$ecn#", posStart);
								er.erOutFile<<"\t\t\t\t Contact #: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$eag#") + 5;
							posEnd = line.find("$eag#", posStart);
								er.erOutFile<<"\t\t\t\t Age: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$eea#") + 5;
							posEnd = line.find("$eea#", posStart);
								er.erOutFile<<"\t\t\t\t Email Address: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$ebd#") + 5;
							posEnd = line.find("$ebd#", posStart);
								er.erOutFile<<"\t\t\t\t Birthday: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$esx#") + 5;
							posEnd = line.find("$esx#", posStart);
								er.erOutFile<<"\t\t\t\t Sex: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$efn#") + 5;
							posEnd = line.find("$efn#", posStart);
								er.erOutFile<<"\t\t\t\t Father's Name: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$efo#") + 5;
							posEnd = line.find("$efo#", posStart);
								er.erOutFile<<"\t\t\t\t Father's Occupation: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$emn#") + 5;
							posEnd = line.find("$emn#", posStart);
								er.erOutFile<<"\t\t\t\t Mother's Name: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$emo#") + 5;
							posEnd = line.find("$emo#", posStart);
								er.erOutFile<<"\t\t\t\t Mother's: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$ems#") + 5;
							posEnd = line.find("$ems#", posStart);
								er.erOutFile<<"\t\t\t\t Civil Status: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$esd#") + 5;
							posEnd = line.find("$esd#", posStart);
							found = line.substr(posStart, posEnd - posStart);
							if(found!="\t")
								er.erOutFile<<"\t\t\t\t Start Date: "<<found<<endl;
							posStart = line.find("$ees#") + 5;
							posEnd = line.find("$ees#", posStart);
								er.erOutFile<<"\t\t\t\t Employment Status: "<<line.substr(posStart, posEnd - posStart)<<endl;	
							posStart = line.find("$eat#") + 5;
							posEnd = line.find("$eat#", posStart);
								er.erOutFile<<"\t\t\t\t Educational Attainment: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$esn#") + 5;
							posEnd = line.find("$esn#", posStart);
								er.erOutFile<<"\t\t\t\t School Name: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$esa#") + 5;
							posEnd = line.find("$esa#", posStart);
								er.erOutFile<<"\t\t\t\t School Address: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$eyg#") + 5;
							posEnd = line.find("$eyg#", posStart);
								er.erOutFile<<"\t\t\t\t Year Graduated: "<<line.substr(posStart, posEnd - posStart)<<endl;
							posStart = line.find("$ebs#") + 5;
							posEnd = line.find("$ebs#", posStart);
							found = line.substr(posStart, posEnd - posStart);
							if(found!="0")
								er.erOutFile<<"\t\t\t\t Base Salary: "<<found<<".00 PHP"<<endl;
							else er.erOutFile<<endl;
							posStart = line.find("$ejp#") + 5;
							posEnd = line.find("$ejp#", posStart);
							found = line.substr(posStart, posEnd - posStart);
							if(found!="\t")
								er.erOutFile<<"\t\t\t\t Base Salary: "<<found<<".00 PHP"<<endl<<endl;	
						}
					}
					er.erInFile.close();					
					er.erOutFile.close();
					er.erInFile.open("database/tempEmployees.txt");
					while(getline(er.erInFile,line)){
						cout<<line<<endl;
					}
					er.erInFile.close();
					system("pause");
					if(toupper(type)=='R'){
						cout<<endl<<"\t\t\t\t Print Applicant List? (y/n) ";
						char choice;
						cin>>choice;
						if(choice=='y'||choice=='Y'){
							er.erInFile.open("database/tempEmployees.txt");
							string filename="Print/List of Candidates.txt";
							const char *cstr = filename.c_str();
							er.erOutFile.open(cstr);
							while(getline(er.erInFile,line)){
								er.erOutFile<<line<<endl;
							}
							cout<<"Candidate List Successfuly Printed!!"<<endl;
							system("pause");
							er.erInFile.close();
							er.erOutFile.close();
						}
					}
					remove("database/tempEmployees.txt");
			break;
		default:
			break;
	}	
}
	


string miscActions::hidePass(void){
	START:
	char pass[32],a;
	int i;
//	cout<<"Enter Password: ";
	for(i=0;;){
		a=getch();
		if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9'))
        //check if a is numeric or alphabet
        {
            pass[i]=a;//stores a in pass
            ++i;
            cout<<"*";
        }
        if(a=='\b'&&i>=1)//if user typed backspace
        //i should be greater than 1.
        {
            cout<<"\b \b";//rub the character behind the cursor.
            --i;
        }
        if(a=='\r')//if enter is pressed
        {
            pass[i]='\0';//null means end of string.
            break;//break the loop
            
        }
		
	}
//	cout<<"\nYou entered : "<<pass;
	
	if(i<=3)
    {
        cout<<"\n\t\t\t\t\t Minimum 4 digits needed.\n\t\t\t\t\t Enter Again: ";
        getch();//It was not pausing :p
        goto START;
    }
    return pass;
}

void miscActions::loadingBar(void){
	char a=177;
	cout<<"\n\t\t\t\t\t\t Loading. . . .\n";
	cout<<"\t\t\t\t\t\t ";
	for(int i=0;i<=20;i++){
		cout<<a;
		Sleep(20);
	}
}

string miscActions::getDateTime(bool timeOnly, bool dateOnly) {
	time_t now;
	time(&now); //get current time
	string t;
	
	if (timeOnly && !dateOnly) {
		t = ctime(&now);
		t = t.substr(11, 5);
	} else if (!timeOnly && dateOnly) {
		t = ctime(&now);
		t = t.substr(4, 6) + ", " + t.substr(20, 4);
	} else if (!timeOnly && !dateOnly) {
		t = ctime(&now);
		t = t.substr(11, 5) + " " + t.substr(4, 6) + " " + t.substr(20, 4);
	} else {
		cout << endl << "Error: Invalid time and date mode.";
	}

	return t;
}

int miscActions::convertToIMonth(string sMonth) {
	int n = 0;
	
	if (sMonth == "Jan") {
		n = 1;
	} else if (sMonth == "Feb") {
		n = 2;
	} else if (sMonth == "Mar") {
		n = 3;
	} else if (sMonth == "Apr") {
		n = 4;
	} else if (sMonth == "May") {
		n = 5;
	} else if (sMonth == "Jun") {
		n = 6;
	} else if (sMonth == "Jul") {
		n = 7;
	} else if (sMonth == "Aug") {
		n = 8;
	} else if (sMonth == "Sep") {
		n = 9;
	} else if (sMonth == "Oct") {
		n = 10;
	} else if (sMonth == "Nov") {
		n = 11;
	} else if (sMonth == "Dec") {
		n = 12;
	} 
	return n;
}

string miscActions::convertToSMonth(int iMonth) {
	string n;
	
	if (iMonth == 1) {
		n = "Jan";
	} else if (iMonth == 2) {
		n = "Feb";
	} else if (iMonth == 3) {
		n = "Mar";
	} else if (iMonth == 4) {
		n = "Apr";
	} else if (iMonth == 5) {
		n = "May";
	} else if (iMonth == 6) {
		n = "Jun";
	} else if (iMonth == 7) {
		n = "Jul";
	} else if (iMonth == 8) {
		n = "Aug";
	} else if (iMonth == 9) {
		n = "Sep";
	} else if (iMonth == 10) {
		n = "Oct";
	} else if (iMonth == 11) {
		n = "Nov";
	} else if (iMonth == 12) {
		n = "Dec";
	} else {
		n = -1;
	}
	return n;
}

bool miscActions::isLeapYear(int argYear) {
	if (argYear % 400 == 0) {
		return true;
	} else if (argYear % 100 == 0) {
		return false;
	} else if (argYear % 4 == 0) {
		return true;
	} 
	return false;
}

int miscActions::numberOfDaysInMonth(int argMonth, int argYear) {
	if (argMonth == 1 || argMonth == 3 || argMonth == 5 || argMonth == 7 || argMonth == 8 || argMonth == 10 || argMonth == 12) {
		return 31;
	} else if (argMonth == 2) {
		if (isLeapYear(argYear)) {
			return 29;
		}
		return 28;
	} else if (argMonth == 4 || argMonth == 6 || argMonth == 9 || argMonth == 11 ) {
		return 30;
	} 
	cout << "Error: Unable to return correct number of days in month.";
	return 0;
}

int miscActions::whatIsDayOfDate(int argYear, int argMonth, int argDate) {
	tm timeStruct = {};
	timeStruct.tm_year = argYear - 1900;
	timeStruct.tm_mon = argMonth - 1;
	timeStruct.tm_mday = argDate;
	timeStruct.tm_hour = 12;    //  To avoid any doubts about summer time, etc.
	mktime( &timeStruct );
	return timeStruct.tm_wday;
}

int miscActions::stringToInt(string argString) {
	stringstream s;
	int i;
	
	s << argString;
	s >> i;
	
	return i;
}

string miscActions::intToString(int argInt) {
	stringstream s;
	string str;
	
	s << argInt;
	str = s.str();
	
	return str;
}

int miscActions::getLastDeptID() {
	string line;
	int num, posStart, posEnd;
	
//	cout << endl << "filename is " << fileName; 
	
	num = 0; posStart = 0; posEnd = 0;
	
	dept.deptInFile.open("database/departments.txt");
	
	if (dept.deptInFile.is_open()) {
		getline(dept.deptInFile, line);
		posStart = line.find("$lI#") + 4;
		posEnd = line.find("$lI#", posStart);
		if (line.size() > 0) {
			line = line.substr(posStart, posEnd - posStart);
		}
		num = stringToInt(line);
//		cout << "entered here";
//		cout << "num is " << num <<".";
		dept.deptInFile.close();
	} else {
		cout << "Error (getLastDeptID): Unable to open file.";		
	}
	
	return num;
		
}


string miscActions::getDepartmentInfo(string ID, string type) {
	string found, temp;
	int posStart, posEnd;

	dept.deptInFile.open("database/departments.txt");
	if (dept.deptInFile.is_open()) {
		
		dept.deptInFile.clear();
		while (getline(dept.deptInFile, temp, '\n')) {

			if (temp.size() > 0) {
				posStart = temp.find("$did#") + 5;
				posEnd = temp.find("$did#", posStart);
				found = temp.substr(posStart, posEnd - posStart);
				if (found == ID) {
					posStart = temp.find("$"+type+"#") + 5;
					posEnd = temp.find("$"+type+"#", posStart);
					temp = temp.substr(posStart, posEnd - posStart); 
					break;
				}
			} else {
				cout << "Error (getDepartmentInfo): Got a blank line from getline.";
			}
			dept.deptInFile.clear();
		}
		 dept.deptInFile.close();
	}
  	else cout << "Error: Unable to open Employees database."; 
	
	return temp;
}
