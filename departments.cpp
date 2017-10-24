#include "departments.h"
#include <iomanip>
#include <sstream>

bool departments::searchDepartment(string query,string type){
	string line, found;
	int posStart=0, posEnd=0;
	
	deptInFile.open("database/departments.txt");
	if(deptInFile.is_open()){
		while(getline(deptInFile,line)){
			posStart = line.find("$"+type+"#") + 5;
			posEnd = line.find("$"+type+"#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			if (query == found) {
				deptInFile.close();
				return true;
			}
		}
		deptInFile.close();
	}
	return false;
}

bool departments::createNewDepartment(){
	string line, found;
	
	cout<<"Name: ";
	getline(cin,name);
	if(searchDepartment(name,"dna")){
		cout<<"department name already exists"<<endl;
		return 0;
	}
	
	deptInFile.open("database/departments.txt");
	if (deptInFile.is_open()) {
		getline(deptInFile,line);
		found=line.substr(4,6);
		stringstream strID(found);
		strID >>departmentID;
		departmentID++;
		deptInFile.close();
	}
  	else cout << "Error: Unable to open Departments database."; 
  	
	cout<<"Code: ";
	getline(cin,code);
	
	deptOutFile.open("database/tempDepartments.txt");
	deptOutFile<<"$lI#"<<setw(6)<<setfill('0')<<departmentID<<"$lI#"<<endl;
	deptOutFile.close();
	if(!editDepartment(" "," "," ")) return 0;

	deptOutFile.open("database/departments.txt",ios_base::app);
	deptOutFile<<"$did#"<<setw(6)<<setfill('0')<<departmentID<<"$did#";
	deptOutFile<<"$dco#"<<code<<"$dco#";
	deptOutFile<<"$dna#"<<name<<"$dna#"<<endl;
	deptOutFile.close();
	return 1;
}

bool departments::deleteDepartment(){
	cout<<"Enter department ID to delete: ";
	cin>>departmentID;
	string result;
	stringstream convert;
	convert<<setw(6)<<setfill('0')<<departmentID;
	result=convert.str();
	
	if(!searchDepartment(result,"did")){
		cout<<"Department ID doesn't exist";
		return 0;
	}
	else{
		string line, found;
		int posStart=0, posEnd=0;
		char choice;
		
		cout<<"Are you sure you want to delete this department?(y/n) ";
		cin>>choice;
		if(choice=='y'){
			deptInFile.open("database/departments.txt");
			deptOutFile.open("database/tempDepartments.txt");
			if(deptInFile.is_open()){
				while(getline(deptInFile,line)){
					posStart=line.find("$did#")+5;
					posEnd=line.find("$did#",posStart);
					found=line.substr(posStart,posEnd-posStart);
					if(result!=found){
						deptOutFile<<line<<endl;
					}
				}
				deptOutFile.close();
				deptInFile.close();
				if(rewriteDepartmentRecord()) return 1;
				else return 0;
			}
			else cout<<"Error: Unable to open departments database. ";
			return false;
		}
		return false;
	}
}

bool departments::updateDepartment(){
	cout<<"Enter Department ID to update: ";
	cin>>departmentID;
	
	string Result;//string which will contain the result
	stringstream convert; // stringstream used for the conversion
	convert<<setw(6)<<setfill('0')<<departmentID;//add the value of Number to the characters in the stream
	Result = convert.str();//set Result to the content of the stream

	if(!searchDepartment(Result,"did")){
		cout<<"Department ID doesn't exist";
		return 0;
	}
	else{
		cout<<"select info to edit"<<endl;
		cout<<"[1] Name"<<endl;
		cout<<"[2] Code"<<endl;
		cout<<endl<<"edit choice: ";
		int choice=0;
		cin>>choice;
		while(choice<1&&choice>2){
			cin>>choice;
		}
		string newInfo,type;
		cout<<"Enter new data: ";
		cin.ignore();
		getline(cin,newInfo);
		switch(choice){
			case 1:if(!searchDepartment(newInfo,"dna")) type="dna";
				else{
					cout<<"Department name already exists!";
					return 0;
				}
				break;
			case 2: type="dco";
				break;
		}
	deptOutFile.open("database/tempDepartments.txt");
	deptOutFile<<"$lI#"<<setw(6)<<setfill('0')<<departmentID<<"$lI#"<<endl;
	deptOutFile.close();
	if(editDepartment(Result,newInfo,type)) return 1;
	else return 0;
	}
}

bool departments::editDepartment(string departmentID, string newInfo, string type){
	deptInFile.open("database/departments.txt");
	deptOutFile.open("database/tempDepartments.txt",ios_base::app);
	string newLine,line,found,temp;
	int posStart=0,posEnd=0,editStart=0,editEnd=0;
	if (deptInFile.is_open()) {
		getline(deptInFile,line);
		while ( getline (deptInFile,line) ) {
			posStart = line.find("$did#") + 5;
			posEnd = line.find("$did#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			editStart=line.find("$"+type+"#")+5;
			editEnd=line.find("$"+type+"#", editStart);
			if (departmentID != found) {
				deptOutFile<<line<<endl;
			}
			else{
				temp=line.substr(0,editStart);
				deptOutFile<<temp;
				deptOutFile<<newInfo;
				temp=line.substr(editEnd,line.size());
				deptOutFile<<temp;
				deptOutFile<<endl;
			}	
		}
		deptOutFile.close();
		deptInFile.close();
		if(rewriteDepartmentRecord()) return 1;
		else return 0;
	}
  	else cout << "Error: Unable to open Departments database."; 
}

bool departments::rewriteDepartmentRecord(){
	string line;
	deptInFile.open("database/tempDepartments.txt");
	deptOutFile.open("database/departments.txt");
	if(deptInFile.is_open()){
		while(getline(deptInFile,line)){
			deptOutFile<<line<<endl;
		}
		deptOutFile.close();
		deptInFile.close();
		remove("database/tempDepartments.txt");
		return 1;
	}
	else cout<<"Error: Unable to open Departments database.";
	return 0;
}

int departments::getLastDeptID() {
	string line;
	int num, posStart, posEnd;
	
//	cout << endl << "filename is " << fileName; 
	
	num = 0; posStart = 0; posEnd = 0;
	
	deptInFile.open("database/departments.txt");
	
	if (deptInFile.is_open()) {
		getline(deptInFile, line);
		posStart = line.find("$lI#") + 4;
		posEnd = line.find("$lI#", posStart);
		if (line.size() > 0) {
			line = line.substr(posStart, posEnd - posStart);
		}
		num = mActions.stringToInt(line);
//		cout << "entered here";
//		cout << "num is " << num <<".";
		deptInFile.close();
	} else {
		cout << "Error (getLastDeptID): Unable to open file.";		
	}
	
	return num;
		
}


string departments::getDepartmentInfo(string ID, string type) {
	string found, temp;
	int posStart, posEnd;

	deptInFile.open("database/departments.txt");
	if (deptInFile.is_open()) {
		
		deptInFile.clear();
		while (getline(deptInFile, temp, '\n')) {

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
			deptInFile.clear();
		}
		 deptInFile.close();
	}
  	else cout << "Error: Unable to open Employees database."; 
	
	return temp;
}













