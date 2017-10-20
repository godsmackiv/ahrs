#include "employeeRecords.h"
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

bool employeeRecords::searchEmployee(string query,string type){
	string line, found;
	int posStart=0, posEnd=0;

	erInFile.open("database/employees.txt");
	if (erInFile.is_open()) {
		getline(erInFile,line);
		while ( getline (erInFile,line) ) {
			posStart = line.find("$"+type+"#") + 5;
			posEnd = line.find("$"+type+"#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			if (query == found) {
				erInFile.close();
				return true;
			}			
		}
		 erInFile.close();
	}
  	else cout << "Error: Unable to open Employee database."; 
  	
	return false;
}

bool employeeRecords::createNewEmployee(){
	string line, found;
		
	cout<<"Name: ";
	getline(cin,name);
	if(searchEmployee(name,"ena")){
		cout<<"employee name already exists"<<endl;
		return 0;
	} 
	
	cout<<"Age: ";
	cin>>age;
	if(age<18){
		cout<<"Employee must be at least 18 years old.";
		return 0;
	}
	
	erInFile.open("database/employees.txt");
	if (erInFile.is_open()) {
		getline(erInFile,line);
		found=line.substr(4,6);
		stringstream strID(found);
		strID >>employeeID;
		employeeID++;
		erInFile.close();
	}
  	else cout << "Error: Unable to open Employees database."; 
	
	cout<<"Address: ";
	cin.ignore();
	getline(cin,address);
	cout<<"Contact Number: ";
	getline(cin,contactNumber);
	cout<<"E-mail Address: ";
	getline(cin,emailAddress);
	cout<<"Birthday: ";
	getline(cin,birthday);
	cout<<"Sex: ";
	getline(cin,sex);
	cout<<"Father's Name: ";
	getline(cin,fathersName);
	cout<<"Father's Occupation: ";
	getline(cin,fathersOccupation);
	cout<<"Mother's Name: ";
	getline(cin,mothersName);
	cout<<"Mother's Occupation: ";
	getline(cin,mothersOccupation);
	cout<<"Marital Status: ";
	getline(cin,maritalStatus);
	
	startDate="\t";
	
	employmentStatus="Applicant";
	
	cout<<"Educational Attainment: ";
	getline(cin,educationalAttainment);
	cout<<"Name of School: ";
	getline(cin,schoolName);
	cout<<"School Address: ";
	getline(cin,schoolAddress);
	
	cout<<"Year Graduated: ";
	cin>>yearGraduated;
	
	baseSalary=0;
	
	position="\t";
	
//	erOutFile.open("database/tempEmployees.txt");
//	erOutFile<<"$lI#"<<setw(6)<<setfill('0')<<employeeID<<"$lI#"<<endl;
//	erOutFile.close();
//	if(!editEmployee(" "," "," ")) return 0;
	
	erOutFile.open("database/employees.txt",ios_base::app);	
	erOutFile<<"$eid#"<<setw(6)<<setfill('0')<<employeeID<<"$eid#";
	erOutFile<<"$ena#"<<name<<"$ena#";
	erOutFile<<"$ead#"<<address<<"$ead#";
	erOutFile<<"$ecn#"<<contactNumber<<"$ecn#";
	erOutFile<<"$eag#"<<age<<"$eag#";
	erOutFile<<"$eea#"<<emailAddress<<"$eea#";
	erOutFile<<"$ebd#"<<birthday<<"$ebd#";
	erOutFile<<"$esx#"<<sex<<"$esx#";
	erOutFile<<"$efn#"<<fathersName<<"$efn#";
	erOutFile<<"$efo#"<<fathersOccupation<<"$efo#";
	erOutFile<<"$emn#"<<mothersName<<"$emn#";
	erOutFile<<"$emo#"<<mothersOccupation<<"$emo#";
	erOutFile<<"$ems#"<<maritalStatus<<"$ems#";
	erOutFile<<"$esd#"<<startDate<<"$esd#";
	erOutFile<<"$ees#"<<employmentStatus<<"$ees#";
	erOutFile<<"$eat#"<<educationalAttainment<<"$eat#";
	erOutFile<<"$esn#"<<schoolName<<"$esn#";
	erOutFile<<"$esa#"<<schoolAddress<<"$esa#";
	erOutFile<<"$eyg#"<<yearGraduated<<"$eyg#";
	erOutFile<<"$ebs#"<<baseSalary<<"$ebs#";
	erOutFile<<"$ejp#"<<position<<"$ejp#"<<endl;
	
	erOutFile.close();
	return 1;
}

bool employeeRecords::deleteEmployee(){
	cout<<"Enter employee ID to delete: ";
	cin>>employeeID;
	
string Result;//string which will contain the result
stringstream convert; // stringstream used for the conversion
convert<<setw(6)<<setfill('0')<<employeeID;//add the value of Number to the characters in the stream
Result = convert.str();//set Result to the content of the stream

	if(!searchEmployee(Result,"eid")){
		cout<<"Employee ID doesn't exist";
		return 0;
	}
	else{
		string line, found;
		int posStart=0, posEnd=0;
		char choice;
		
		cout<<"Are you sure you want to delete this employee?(y/n)";
		cin>>choice;
		if(choice=='y'){
			erInFile.open("database/employees.txt");
			erOutFile.open("database/tempEmployees.txt");
			if (erInFile.is_open()) {
				while ( getline (erInFile,line) ) {
					posStart = line.find("$eid#") + 5;
					posEnd = line.find("$eid#", posStart);
					found = line.substr(posStart, posEnd - posStart);
					if (Result != found) {
						erOutFile<<line<<endl;
					}			
				}
				erOutFile.close();
				erInFile.close();
				if(rewriteEmployeeRecord()) return 1;
				else return 0;
			}
		  	else cout << "Error: Unable to open Employee database."; 
		  	
			return false;
		}
		return false;
	}
}

bool employeeRecords::updateEmployee(){
	cout<<"Enter employee ID to update: ";
	cin>>employeeID;
	
string Result;//string which will contain the result
stringstream convert; // stringstream used for the conversion
convert<<setw(6)<<setfill('0')<<employeeID;//add the value of Number to the characters in the stream
Result = convert.str();//set Result to the content of the stream

	if(!searchEmployee(Result,"eid")){
		cout<<"Employee ID doesn't exist";
		return 0;
	}
	else{
		
		cout<<"select info to edit"<<endl;
		cout<<"[1]  Name"<<endl;
		cout<<"[2]  Address"<<endl;
		cout<<"[3]  Contact Number"<<endl;
		cout<<"[4]  Age"<<endl;
		cout<<"[5]  E-mail Address"<<endl;
		cout<<"[6]  Birhtday"<<endl;
		cout<<"[7]  Sex"<<endl;
		cout<<"[8]  Father's Name"<<endl;
		cout<<"[9]  Father's Occupation"<<endl;
		cout<<"[10] Mothers's Name"<<endl;
		cout<<"[11] Mothers's Occupation"<<endl;
		cout<<"[12] Marital Status"<<endl;
		cout<<"[13] Educational Attainment"<<endl;
		cout<<"[14] Name of School"<<endl;
		cout<<"[15] School Address"<<endl;
		cout<<"[16] Year Graduated"<<endl;
		cout<<endl<<"Edit choice: ";
		int choice=0;
		cin>>choice;
		while(choice<1&&choice>16){
			cin>>choice;
		}
		string newInfo,type;
		cout<<"Enter new data: ";
		cin.ignore();
		getline(cin,newInfo);
		const char *cnewInfo = newInfo.c_str();
		switch(choice){
			case 1: if(!searchEmployee(newInfo,"ena"))type="ena";
					else{
						cout<<"Employee name already exists!";
						return 0;
					}
				break;
			case 2: type="ead";
				break;
			case 3: type="ecn";
				break;
			case 4: age=atoi(cnewInfo);
					if(age>=18)type="eag";
					else{
						cout<<"Must be at least 18 years old";
						return 0;
					}
				break;
			case 5: type="eea";
				break;
			case 6: type="ebd";
				break;
			case 7: type="esx";
				break;
			case 8: type="efn";
				break;
			case 9: type="efo";
				break;
			case 10: type="emn";
				break;
			case 11: type="emo";
				break;
			case 12: type="ems";
				break;
			case 13: type="eat";
				break;
			case 14: type="esn";
				break;
			case 15: type="esa";
				break;
			case 16: type="eyg";
				break;
		}
//	erOutFile.open("database/tempEmployees.txt");
//	erOutFile<<"$lI#"<<setw(6)<<setfill('0')<<employeeID<<"$lI#"<<endl;
//	erOutFile.close();
	if(editEmployee(Result,newInfo,type)) return 1;
	else return 0;
	  	
	}
}

bool employeeRecords::editEmployee(string employeeID,string newInfo,string type){
	erInFile.open("database/employees.txt");
	erOutFile.open("database/tempEmployees.txt",ios_base::app);
	string newLine,line,found,temp;
	int posStart=0,posEnd=0,editStart=0,editEnd=0;
	if (erInFile.is_open()) {
		getline(erInFile,line);
		while ( getline (erInFile,line) ) {
			posStart = line.find("$eid#") + 5;
			posEnd = line.find("$eid#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			editStart=line.find("$"+type+"#")+5;
			editEnd=line.find("$"+type+"#",editStart);
			if (employeeID != found) {
				erOutFile<<line<<endl;
			}
			else{
				temp=line.substr(0,editStart);
				erOutFile<<temp;
				erOutFile<<newInfo;
				temp=line.substr(editEnd,line.size());
				erOutFile<<temp;
				erOutFile<<endl;
			}	
		}
		erOutFile.close();
		erInFile.close();
		if(rewriteEmployeeRecord()) return 1;
		else return 0;
	}
  	else cout << "Error: Unable to open Employee database."; 
}

bool employeeRecords::rewriteEmployeeRecord(){
	string line;
	erInFile.open("database/tempEmployees.txt");
	erOutFile.open("database/employees.txt");
	if (erInFile.is_open()) {
		while ( getline (erInFile,line) ) {
			erOutFile<<line<<endl;
		}
		erOutFile.close();
		erInFile.close();
		remove("database/tempEmployees.txt");
		return 1;
	}
  	else cout << "Error: Unable to open Employee database."; 
  	return 0;
}

bool employeeRecords::isApplicant(string employeeID){
	string line, found;
	int posStart=0, posEnd=0;

	erInFile.open("database/employees.txt");
	if (erInFile.is_open()) {
		getline(erInFile,line);
		while ( getline (erInFile,line) ) {
			posStart = line.find("$eid#") + 5;
			posEnd = line.find("$eid#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			if (employeeID == found) {
				posStart=line.find("$ees#")+5;
				posEnd=line.find("$ees#",posStart);
				found=line.substr(posStart,posEnd-posStart);
				if(found=="Applicant"){
					erInFile.close();
					return true;
				}
			}			
		}
		 erInFile.close();
	}
  	else cout << "Error: Unable to open Employee database."; 
  	
	return false;	
}
