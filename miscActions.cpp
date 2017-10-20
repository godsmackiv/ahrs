#include "miscActions.h"
#include <windows.h>
#include <conio.h>
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
					break;
				}
				case 'V':{
					cout<<"\t\t\t\t\t================= View =================="<<endl;
					cout<<"\t\t\t\t\t=\t[1] View Department\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[2] View Location\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[3] View Job Position\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[4] View Benefits\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[5] View Employee\t\t="<<endl;
					cout<<"\t\t\t\t\t========================================="<<endl;
					cout<<"\t\t\t\t\tEnter input: ";
					cin>>perform;
					managerView();
					break;
				}
				case 'U':{
					cout<<"\t\t\t\t\t================ Update ================="<<endl;
					cout<<"\t\t\t\t\t=\t[1] Update Department\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[2] Update Location\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[3] Update Job Position\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[4] Update Benefits\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[5] Update Employee\t\t="<<endl;
					cout<<"\t\t\t\t\t========================================="<<endl;
					cout<<"\t\t\t\t\tEnter input: ";
					cin>>perform;	
					break;
				}
				case 'D':{
					cout<<"\t\t\t\t\t================ Delete ================="<<endl;
					cout<<"\t\t\t\t\t=\t[1] Delete Department\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[2] Delete Location\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[3] Delete Job Position\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[4] Delete Benefits\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[5] Delete Employee\t\t="<<endl;
					cout<<"\t\t\t\t\t========================================="<<endl;
					cout<<"\t\t\t\t\tEnter input: ";
					cin>>perform;
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
			cin>>input;
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
					cout<<"\t\t\t\t\t=\t[1] Create Job Opening\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[2] View Job Opening\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[3] Edit Job Opening\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[4] Delete Job Opening\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[5] Assign Applicant\t\t="<<endl;
					cout<<"\t\t\t\t\t=\t[6] Hire Employee\t\t="<<endl;
					cout<<"\t\t\t\t\t========================================="<<endl;
					cout<<"\t\t\t\t\tEnter input: ";
					cin>>perform;
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
					break;
				}
				case 'P':{
					cout<<"\t\t\t\t\t================= Salary ================="<<endl;
					cout<<"\t\t\t\t\t= [1] View Employee Salary ="<<endl;
					cout<<"\t\t\t\t\t= [2] View Employee Info\t\t  ="<<endl;
					cout<<"\t\t\t\t\t= [3] Compute Salary\t  ="<<endl;
					cout<<"\t\t\t\t\t==========================================="<<endl;
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
			cout<<"\t\t\t\t=\t[1] View Open Job Positions                          ="<<endl;
			cout<<"\t\t\t\t=\t[2] View List of Candidates                       ="<<endl;
			cout<<"\t\t\t\t=\t[3] View Pay Roll Information of Employee            ="<<endl;
			cout<<"\t\t\t\t=\t[4] View Pay Roll Information of All Employee        ="<<endl;
			cout<<"\t\t\t\t=\t[5] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[6] View Current Benefit Enrollment of an Employee  ="<<endl;
			cout<<"\t\t\t\t=============================================================="<<endl;
			cout<<"\t\t\t\tEnter input: ";
			cin>>report;
			viewReports();
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

void miscActions::managerView(){
	string line, found,temp;
	int posStart=0, posEnd=0;
	switch(perform){
		case '1':{
			system("cls");
			cout<<"\t\t\t\t\t View Department\n\n";
			userInFile.open("database/departments.txt");
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
		case '2':{
			system("cls");
			cout<<"\t\t\t\t\t View Location\n\n";
			userInFile.open("database/locations.txt");
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
		case '3':{
			system("cls");
			cout<<"\t\t\t\t\t View Job Position\n\n";
			userInFile.open("database/job positions.txt");
			if (userInFile.is_open()) {
					while ( getline (userInFile,line) ) {
					
							posStart = line.find("$jid#") + 5;
							posEnd = line.find("$jid#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Job Position ID: "<<found<<endl;	
							posStart = line.find("$jpn#") + 5;
							posEnd = line.find("$jpn#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Job: "<<found<<endl<<endl;		
						}
						system("pause");
					userInFile.close();
					}
					else{
						cout << "Error: Unable to open job position database."; 
				
					}
			break;
		}
		case '4':{
			system("cls");
			cout<<"\t\t\t\t\t View Benefits\n\n";
			userInFile.open("database/benefits.txt");
			if (userInFile.is_open()) {
					while ( getline (userInFile,line) ) {
					
							posStart = line.find("$bid#") + 5;
							posEnd = line.find("$bid#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Benefit ID: "<<found<<endl;	
							posStart = line.find("$bna#") + 5;
							posEnd = line.find("$bna#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Benefit: "<<found<<endl<<endl;		
						}
						system("pause");
					userInFile.close();
					}
					else{
						cout << "Error: Unable to open benefit database."; 
				
					}
			break;
		}
		case '5':{
			system("cls");
			cout<<"\t\t\t\t\t View Employee\n\n";
			userInFile.open("database/employees.txt");
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
								cout<<"\t\t\t\t Start Date: "<<found<<endl;
							posStart = line.find("$ees#") + 5;
							posEnd = line.find("$ees#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Employment Status: "<<found<<endl;	
							posStart = line.find("$eat#") + 5;
							posEnd = line.find("$eat#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Educational Attainment: "<<found<<endl;
								posStart = line.find("$ebs#") + 5;
							posEnd = line.find("$ebs#", posStart);
							found = line.substr(posStart, posEnd - posStart);
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
	cout<<"\t\t\t\t\t=========================================="<<endl;
	cout<<"\t\t\t\t\tEnter letter of choice: ";
	cin>>task;
}

void miscActions::recruiterSubMenu(void){
	char input;
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
			cin>>input;
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
			
			break;
		}
		
		case 'R':{
			cout<<"\t\t\t\t============================ Report =========================="<<endl;
			cout<<"\t\t\t\t=\t[1] View Open Job Positions                          ="<<endl;
			cout<<"\t\t\t\t=\t[2] View List of Candidates                       ="<<endl;
			cout<<"\t\t\t\t=\t[3] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[4] View Current Benefit Enrollment of an Employee  ="<<endl;
			cout<<"\t\t\t\t=============================================================="<<endl;
			cout<<"\t\t\t\tEnter input: ";
			cin>>input;
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
			cin>>input;
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
			cout<<"\t\t\t\t=\t[1] View Open Job Positions                          ="<<endl;
			cout<<"\t\t\t\t=\t[2] View List of Candidates                       ="<<endl;
			cout<<"\t\t\t\t=\t[3] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[4] View Current Benefit Enrollment of an Employee   ="<<endl;
			cout<<"\t\t\t\t=============================================================="<<endl;
			cout<<"\t\t\t\tEnter input: ";
			cin>>input;
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
			cout<<"\t\t\t\t\t= [A] View List of Applicants for a Job Order ="<<endl;
			cout<<"\t\t\t\t\t= [S] View Summary of Benefits                ="<<endl;
			cout<<"\t\t\t\t\t= [B] View Benefits of an Employee            ="<<endl;
			cout<<"\t\t\t\t\t= [S] Search                                  ="<<endl;
			cout<<"\t\t\t\t\t==============================================="<<endl;
			cout<<"\t\t\t\t\tEnter input: ";
			cin>>input;
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
			cout<<"\t\t\t\t=\t[1] View Open Job Positions                          ="<<endl;
			cout<<"\t\t\t\t=\t[2] View List of Candidates                       ="<<endl;
			cout<<"\t\t\t\t=\t[3] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[4] View Current Benefit Enrollment of an Employee   ="<<endl;
			cout<<"\t\t\t\t=============================================================="<<endl;
			cout<<"\t\t\t\tEnter input: ";
			cin>>input;
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

void miscActions::viewReports(){
	string line, found,temp;
	char ch;
	int posStart=0, posEnd=0;
		switch(report){
			case '1':{
				system("cls");
				cout<<"\t\t\t\t\t All Available Job Opening\n\n";
				userInFile.open("database/job openings.txt");
				if (userInFile.is_open()) {
					while ( getline (userInFile,line) ) {
						posStart = line.find("$av#") + 4;
						posEnd = line.find("$av#", posStart);
						found = line.substr(posStart, posEnd - posStart);
							if(found=="Open"){
							posStart = line.find("$jn#") + 4;
							posEnd = line.find("$jn#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t\t Job #: "<<found<<endl;	
							posStart = line.find("$po#") + 4;
							posEnd = line.find("$po#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Job Position: "<<found<<endl;
							posStart = line.find("$de#") + 4;
							posEnd = line.find("$de#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Department #: "<<found<<endl;		
							posStart = line.find("$lo#") + 4;
							posEnd = line.find("$lo#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Location #: "<<found<<endl;
							posStart = line.find("$jr#") + 4;
							posEnd = line.find("$jr#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Job Requirements: "<<found<<endl;
							posStart = line.find("$aa#") + 4;
							posEnd = line.find("$aa#", posStart);
							found = line.substr(posStart, posEnd - posStart);
								cout<<"\t\t\t\t Aspiring Applicants: "<<found<<endl<<endl;
							}
							else{
								break;
							}
						}
					userInFile.close();
					}
					else{
						cout << "Error: Unable to open job openings database."; 
				
					}
					cout<<"\t\t\t\t\t Do you want a hard copy of this list? (y/n): ";
					cin>>ch;
					system("cls");
					loadingBar();
					cout<<"\n\n\t\t\t\t\t\t Print Successful!"<<endl;
					int Start=0, End=0;
					userInFile.open("Database/job openings.txt");
					userOutFile.open("Database/print job openings.txt");
					if(ch=='y'||ch=='Y'){
						userOutFile<<"All Available Job Opening"<<endl<<endl;
						if(userInFile.is_open()){
							while(getline(userInFile,temp)){
							//	cout<<temp<<endl;
							//	system("pause");
							//	userOutFile<<temp<<endl;
							Start = temp.find("$av#") + 4;
							End = temp.find("$av#", Start);
							found = temp.substr(Start, End - Start);
//							userOutFile<<"Job #: "<<found<<endl;
							if(found=="Open"){
								Start = temp.find("$jn#") + 4;
								End = temp.find("$jn#", Start);
								found = temp.substr(Start, End - Start);
								userOutFile<<"Job #: "<<found<<endl;
								Start = temp.find("$po#") + 4;
								End = temp.find("$po#", Start);
								found = temp.substr(Start, End - Start);
								userOutFile<<"Job Position: "<<found<<endl;
								Start = temp.find("$de#") + 4;
								End = temp.find("$de#", Start);
								found = temp.substr(Start, End - Start);
								userOutFile<<"Department: "<<found<<endl;
								Start = temp.find("$lo#") + 4;
								End = temp.find("$lo#", Start);
								found = temp.substr(Start, End - Start);
								userOutFile<<"Location: "<<found<<endl;
								Start = temp.find("$jr#") + 4;
								End = temp.find("$jr#", Start);
								found = temp.substr(Start, End - Start);
								
								userOutFile<<"Job Requirement: "<<found<<endl;
								Start = temp.find("$aa#") + 4;
								End = temp.find("$aa#", Start);
								found = temp.substr(Start, End - Start);
								userOutFile<<"Aspiring Applicants: "<<found<<endl<<endl;
//								Start = temp.find("$av#") + 4;
//								End = temp.find("$av#", Start);
//								found = temp.substr(Start, End - Start);
//								if(found=="Open"||found=="Close"){
//									userOutFile<<cin.ignore();
//								}
							}
							else{
								break;
							}
							
							}
							userInFile.close();
							userOutFile.close();
						}
						else{
							cout << "Error: Unable to print job openings."; 
						}	
				}
				break;
			}
		default:{
			break;
		}
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
		Sleep(40);
	}

}
