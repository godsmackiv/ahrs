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
int miscActions::managerMenu(void){
	char task;
	cout<<"\t\t\t\t\t=========================================="<<endl;
	cout<<"\t\t\t\t\t=\t[F] File Maintenance\t\t ="<<endl;
	cout<<"\t\t\t\t\t=\t[T] Transactions\t\t ="<<endl;
	cout<<"\t\t\t\t\t=\t[I] Inquiry\t\t\t ="<<endl;
	cout<<"\t\t\t\t\t=\t[R] Report\t\t\t ="<<endl;
	cout<<"\t\t\t\t\t=\t[U] Utilities\t\t\t ="<<endl;
	cout<<"\t\t\t\t\t=========================================="<<endl;
	cout<<"\t\t\t\t\tEnter letter of choice: ";
	cin>>task;
	return task;
}

void miscActions::loadingBar(void){
	char a=177;
	cout<<"\n\t\t\t\t\t Loading. . . .\n";
	cout<<"\t\t\t\t\t ";
	for(int i=0;i<=20;i++){
		cout<<a;
		Sleep(90);
	}
	getch();
}
