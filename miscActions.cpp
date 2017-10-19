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
			cout<<"\t\t\t\t=\t[2] Print Open Job Positions                         ="<<endl;
			cout<<"\t\t\t\t=\t[3] Display List of Candidates                       ="<<endl;
			cout<<"\t\t\t\t=\t[4] Print List of Candidates                         ="<<endl;
			cout<<"\t\t\t\t=\t[5] View Pay Roll Information of Employee            ="<<endl;
			cout<<"\t\t\t\t=\t[6] Print Pay Slip of Employee                       ="<<endl;
			cout<<"\t\t\t\t=\t[7] View Pay Roll Information of All Employee        ="<<endl;
			cout<<"\t\t\t\t=\t[8] Print Pay Slip of All Employee                   ="<<endl;
			cout<<"\t\t\t\t=\t[9] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[10] Print Current Benefit Enrollment                ="<<endl;
			cout<<"\t\t\t\t=\t[11] View Current Benefit Enrollment of an Employee  ="<<endl;
			cout<<"\t\t\t\t=\t[12] Print Current Benefit Enrollment of an Employee ="<<endl;
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
			cout<<"\t\t\t\t=\t[2] Print Open Job Positions                         ="<<endl;
			cout<<"\t\t\t\t=\t[3] Display List of Candidates                       ="<<endl;
			cout<<"\t\t\t\t=\t[4] Print List of Candidates                         ="<<endl;
			cout<<"\t\t\t\t=\t[5] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[6] Print Current Benefit Enrollment                ="<<endl;
			cout<<"\t\t\t\t=\t[7] View Current Benefit Enrollment of an Employee  ="<<endl;
			cout<<"\t\t\t\t=\t[8] Print Current Benefit Enrollment of an Employee ="<<endl;
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
			cout<<"\t\t\t\t=\t[2] Print Open Job Positions                         ="<<endl;
			cout<<"\t\t\t\t=\t[3] Display List of Candidates                       ="<<endl;
			cout<<"\t\t\t\t=\t[4] Print List of Candidates                         ="<<endl;
			cout<<"\t\t\t\t=\t[5] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[6] Print Current Benefit Enrollment                 ="<<endl;
			cout<<"\t\t\t\t=\t[7] View Current Benefit Enrollment of an Employee   ="<<endl;
			cout<<"\t\t\t\t=\t[8] Print Current Benefit Enrollment of an Employee  ="<<endl;
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
			cout<<"\t\t\t\t=\t[2] Print Open Job Positions                         ="<<endl;
			cout<<"\t\t\t\t=\t[3] Display List of Candidates                       ="<<endl;
			cout<<"\t\t\t\t=\t[4] Print List of Candidates                         ="<<endl;
			cout<<"\t\t\t\t=\t[5] View Current Benefit Enrollment                  ="<<endl;
			cout<<"\t\t\t\t=\t[6] Print Current Benefit Enrollment                 ="<<endl;
			cout<<"\t\t\t\t=\t[7] View Current Benefit Enrollment of an Employee   ="<<endl;
			cout<<"\t\t\t\t=\t[8] Print Current Benefit Enrollment of an Employee  ="<<endl;
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
void miscActions::loadingBar(void){
	char a=177;
	cout<<"\n\t\t\t\t\t\t Loading. . . .\n";
	cout<<"\t\t\t\t\t\t ";
	for(int i=0;i<=20;i++){
		cout<<a;
		Sleep(40);
	}

}
