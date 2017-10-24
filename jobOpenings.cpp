#include "jobOpenings.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include <ctime>

bool jobOpenings::searchJobOpening(string query, string type){
	string line, found;
	int posStart=0, posEnd=0;
	
	joInFile.open("database/jobOpenings.txt");
	if(joInFile.is_open()){
		while(getline(joInFile,line)){
			posStart = line.find("$"+type+"#") + 5;
			posEnd = line.find("$"+type+"#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			if (query == found) {
				joInFile.close();
				return true;
			}
		}
		joInFile.close();
	}
	return false;
}

bool jobOpenings::jobExists(string query){
	string line, found;
	int posStart=0, posEnd=0;
	
	joInFile.open("database/jobOpenings.txt");
	if(joInFile.is_open()){
		while(getline(joInFile,line)){
			posStart = line.find("$jpo#") + 5;
			posEnd = line.find("$req#");
			found = line.substr(posStart,posEnd-posStart);
			if (query == found) {
				joInFile.close();
				return true;
			}
		}
		joInFile.close();
	}
	return false;
} 

bool jobOpenings::createNewJobOpening(){
	string line, found;
	
	cout<<"Position: ";
	getline(cin,position);
	if(!jPos.searchJobPosition(position,"jpn")){
		cout<<"Job Position not found";
		return 0;
	}
	
	joInFile.open("database/jobOpenings.txt");
	if (joInFile.is_open()) {
		getline(joInFile,line);
		found=line.substr(4,6);
		stringstream strID(found);
		strID >>jobOpeningID;
		jobOpeningID++;
		joInFile.close();
	}
  	else cout << "Error: Unable to open JobOpenings database."; 
  	
	cout<<"Location: ";
	getline(cin,jobLocation);
	if(!loc.searchLocation(jobLocation,"lna")){
		cout<<"location not found";
		return 0;
	}
	
	cout<<"Department: ";
	getline(cin,jobDepartment);
	if(!dept.searchDepartment(jobDepartment,"dna")){
		cout<<"department not found";
		return 0;
	}
	
	string job=position+"$jpo#$jde#"+jobDepartment+"$jde#$jlo#"+jobLocation+"$jlo#";	
	if(jobExists(job)){
		cout<<"Job opening already exists";
		return 0;
	}
	
	addRequirements();	
	addApplicants();	
	availability="Open";
	
	joOutFile.open("database/tempJobOpenings.txt");
	joOutFile<<"$lI#"<<setw(6)<<setfill('0')<<jobOpeningID<<"$lI#"<<endl;
	joOutFile.close();
	if(!editJobOpening(" "," "," ")) return 0;
		
	joOutFile.open("database/jobOpenings.txt",ios_base::app);
	joOutFile<<"$jid#"<<setw(6)<<setfill('0')<<jobOpeningID<<"$jid#";
	joOutFile<<"$jpo#"<<position<<"$jpo#";
	joOutFile<<"$jde#"<<jobDepartment<<"$jde#";
	joOutFile<<"$jlo#"<<jobLocation<<"$jlo#";
	joOutFile<<"$req#"<<requirements<<"$req#";
	joOutFile<<"$jap#"<<applicants<<"$jap#";
	joOutFile<<"$jav#"<<availability<<"$jav#"<<endl;
	joOutFile.close();
	return 1;	
}

bool jobOpenings::deleteJobOpening(){
	cout<<"Enter jobOpening ID to delete: ";
	cin>>jobOpeningID;
	
	string Result;//string which will contain the result
	stringstream convert; // stringstream used for the conversion
	convert<<setw(6)<<setfill('0')<<jobOpeningID;//add the value of Number to the characters in the stream
	Result = convert.str();//set Result to the content of the stream

	if(!searchJobOpening(Result,"jid")){
		cout<<"JobOpening ID doesn't exist";
		return 0;
	}
	else{
		string line, found;
		int posStart=0, posEnd=0;
		char choice;
		
		cout<<"Are you sure you want to delete this jobOpening?(y/n)";
		cin>>choice;
		if(choice=='y'){
			joInFile.open("database/jobOpenings.txt");
			joOutFile.open("database/tempJobOpenings.txt");
			if (joInFile.is_open()) {
				while ( getline (joInFile,line) ) {
					posStart = line.find("$jid#") + 5;
					posEnd = line.find("$jid#", posStart);
					found = line.substr(posStart, posEnd - posStart);
					if (Result != found) {
						joOutFile<<line<<endl;
					}			
				}
				joOutFile.close();
				joInFile.close();
				if(rewriteJobOpeningRecord()) return 1;
				else return 0;
			}
		  	else cout << "Error: Unable to open JobOpening database."; 
		  	
			return false;
		}
		return false;
	}
}

bool jobOpenings::updateJobOpening(){
	cout<<"Enter JobOpening ID to update: ";
	cin>>jobOpeningID;
	
	string Result;//string which will contain the result
	stringstream convert; // stringstream used for the conversion
	convert<<setw(6)<<setfill('0')<<jobOpeningID;//add the value of Number to the characters in the stream
	Result = convert.str();//set Result to the content of the stream

	if(!searchJobOpening(Result,"jid")){
		cout<<"JobOpening ID doesn't exist";
		return 0;
	}
	else{
		cout<<"select info to edit"<<endl;
		cout<<"[1] Position"<<endl;
		cout<<"[2] Department"<<endl;
		cout<<"[3] Location"<<endl;
		cout<<"[4] Requirements"<<endl;
		cout<<"[5] Applicants"<<endl;
		cout<<"[6] Availability"<<endl;
		cout<<endl<<"edit choice: ";
		int choice=0;
		cin>>choice;
		while(choice<1&&choice>5){
			cin>>choice;
		}
		string newInfo,type;
		switch(choice){
			case 1: cout<<"Enter new data: ";
					cin.ignore();
					getline(cin,newInfo);
					if(!jPos.searchJobPosition(newInfo,"jpn")){
						cout<<"Position not found";
						return 0;
					}
				else type="jpo";
				break;
			case 2: cout<<"Enter new data: ";
					cin.ignore();
					getline(cin,newInfo);
					if(!dept.searchDepartment(newInfo,"dna")){
						cout<<"Department not found";
						return 0;
					}
				else type="jde";
				break;
			case 3: cout<<"Enter new data: ";
					cin.ignore();
					getline(cin,newInfo);
					if(!loc.searchLocation(newInfo,"lna")){
						cout<<"Location not found";
						return 0;
					}
				else type="jlo";
				break;
			case 4: addRequirements();
				newInfo=requirements;
				type="req";
				break;
			case 5: addApplicants();
				newInfo=applicants;
				type="jap";
				break;
			case 6: cout<<"[1] Open\n[2] Close \nChoice: ";
					int choice=0;
				cin>>choice;
				switch(choice){
					case 1: newInfo="Open";
						break;
					case 2: newInfo="Close";
						break;
					default: cout<<endl<<"update failed"<<endl;
						system("pause");
						return 0;
						break;
				}
				type="jav";
				break;
		}
		joOutFile.open("database/tempJobOpenings.txt");
		joOutFile<<"$lI#"<<setw(6)<<setfill('0')<<jobOpeningID<<"$lI#"<<endl;
		joOutFile.close();
		if(editJobOpening(Result,newInfo,type)) return 1;
		else return 0;
	}
}

bool jobOpenings::editJobOpening(string id, string newInfo, string type){
	joInFile.open("database/jobOpenings.txt");
	joOutFile.open("database/tempJobOpenings.txt",ios_base::app);
	string newLine,line,found,temp;
	int posStart=0,posEnd=0,editStart=0,editEnd=0;
	if (joInFile.is_open()) {
		getline(joInFile,line);
		while ( getline (joInFile,line) ) {
			posStart = line.find("$jid#") + 5;
			posEnd = line.find("$jid#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			editStart=line.find("$"+type+"#")+5;
			editEnd=line.find("$"+type+"#",editStart);
			if (id != found) {
				joOutFile<<line<<endl;
			}
			else{
				temp=line.substr(0,editStart);
				joOutFile<<temp;
				joOutFile<<newInfo;
				temp=line.substr(editEnd,line.size());
				joOutFile<<temp;
				joOutFile<<endl;
			}	
		}
		joOutFile.close();
		joInFile.close();
		if(rewriteJobOpeningRecord()) return 1;
		else return 0;
	}
  	else cout << "Error: Unable to open Users database."; 	
}

bool jobOpenings::rewriteJobOpeningRecord(){
	string line;
	joInFile.open("database/tempJobOpenings.txt");
	joOutFile.open("database/jobOpenings.txt");
	if (joInFile.is_open()) {
		while ( getline (joInFile,line) ) {
			joOutFile<<line<<endl;
		}
		joOutFile.close();
		joInFile.close();
		remove("database/tempJobOpenings.txt");
		return 1;
	}
  	else cout << "Error: Unable to open Users database."; 
  	return 0;
}

bool jobOpenings::assignApplicant(){
	return applicantTransaction(1);
}

void jobOpenings::addRequirements(){
	string line;
	char req='y';
	int reqCount=1;
	cout<<"Requirements: ";
	while(req=='y'){
		getline(cin,line);
		if(reqCount==1){
			requirements=line;
		}
		else{
			requirements=requirements+"%%"+line;
		}
		cout<<"Add Another Requirement? (y/n) ";
		cin>>req;
		cin.ignore();
		tolower(req);
		reqCount++;
		cout<<"\t";
	}
}

void jobOpenings::addApplicants(){
	char app='y';
	int appCount=1;
	int applicantID;
	cout<<"\nAdd applicant? (y/n) ";
	cin>>app;
	while(app=='y'){
		cout<<"Applicant ID: ";
		cin>>applicantID;
		string Result;//string which will contain the result
		stringstream convert; // stringstream used for the conversion
		convert<<setw(6)<<setfill('0')<<applicantID;//add the value of Number to the characters in the stream
		Result = convert.str();//set Result to the content of the stream
		if(er.searchEmployee(Result,"eid")){
			if(er.isApplicant(Result)){
				if(appCount==1){
					applicants=Result;
				}
				else{
					applicants=applicants+"%%"+Result;
				}
			}
		}
		else{
			cout<<endl<<"Applicant not found."<<endl;
		}
		cout<<"Add another applicant? (y/n) ";
		cin>>app;
		appCount++;
	}
	if(applicants.size()<1){
		applicants="\t";
	}
}

string jobOpenings::retrieveInfo(string jobOpeningID, string type){
	joInFile.open("database/jobOpenings.txt");
	int posStart=0,posEnd=0;
	string line,found;
	if(joInFile.is_open()){
		while(getline(joInFile,line)){
			posStart = line.find("$jid#") + 5;
			posEnd = line.find("$jid#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			if (jobOpeningID == found) {
				posStart=line.find("$"+type+"#")+5;
				posEnd=line.find("$"+type+"#",posStart);
				found = line.substr(posStart, posEnd - posStart);
				joInFile.close();
				return found;
			}
		}
		joInFile.close();
	}	
}

bool jobOpenings::isAlreadyApplied(string allApplicants, string newApplicant){
	int posStart=0,posEnd=6;
	string found;
	while(posStart<allApplicants.size()){
		found=allApplicants.substr(posStart,posEnd);
		if(found==newApplicant){
			return 1;
		}
		else {
			posStart+=8;
		}
	}
	return 0;
}

bool jobOpenings::hireApplicant(){
	return applicantTransaction(2);
}

bool jobOpenings::applicantTransaction(int transactType){
	string Result;//string which will contain the result
	stringstream convert,convert1; // stringstream used for the conversion
	int applicantID;
	string strJobOpeningID;
	cout<<"Enter Job Opening ID: ";
	cin>>jobOpeningID;
	convert<<setw(6)<<setfill('0')<<jobOpeningID;//add the value of Number to the characters in the stream
	strJobOpeningID = convert.str();//set Result to the content of the stream
	if(searchJobOpening(strJobOpeningID,"jid")){
		cout<<"Enter Applicant ID: ";
		cin>>applicantID;
		convert1<<setw(6)<<setfill('0')<<applicantID;//add the value of Number to the characters in the stream
		Result = convert1.str();//set Result to the content of the stream
		if(er.searchEmployee(Result,"eid")){
			if(er.isApplicant(Result)){
				if(transactType==1){
					if(!isAlreadyApplied(retrieveInfo(strJobOpeningID,"jap"),Result)){
						joInFile.open("database/jobOpenings.txt");
						joOutFile.open("database/tempJobOpenings.txt");
						string line;
						getline(joInFile,line);
						joOutFile<<line<<endl;
						joOutFile.close();
						joInFile.close();
						if(searchJobOpening("\t","jap")){
							if(editJobOpening(strJobOpeningID,Result,"jap")) return 1;
							else{
								cout<<"error";
								return 0;
							}
						}
						else{
							if(editJobOpening(strJobOpeningID,retrieveInfo(strJobOpeningID,"jap")+"%%"+Result,"jap")) return 1;
							else{
								cout<<"error";
								return 0;
							}
						}
					}
					else{
						cout<<"Applicant already applied for this job opening";
						return 0;
					}
				}
				if(transactType==2){
					if(isAlreadyApplied(retrieveInfo(strJobOpeningID,"jap"),Result)){
						string allApplicants=retrieveInfo(strJobOpeningID,"jap");
						if(allApplicants!=Result){
							int posStart=0,posEnd=6;
							string found;
							applicants.clear();
							while(posStart<allApplicants.size()){
								found=allApplicants.substr(posStart,posEnd);
								if(found!=Result){
									if(applicants.size()==0) applicants=found;
									else applicants=applicants+"%%"+found;
								}
								posStart+=8;
							}
						}
						else applicants="\t";
						joOutFile.open("database/tempJobOpenings.txt");
						joInFile.open("database/jobOpenings.txt");
						string line;
						getline(joInFile,line);
						joOutFile<<line<<endl;
						joInFile.close();
						joOutFile.close();
						if(editJobOpening(strJobOpeningID,applicants,"jap")){
							string line;
							er.erOutFile.open("database/tempEmployees.txt");
							er.erInFile.open("database/employees.txt");
							getline(er.erInFile,line);
							er.erOutFile<<line<<endl;
							er.erInFile.close();
							er.erOutFile.close();
							er.editEmployee(Result,"Probation","ees");
							er.erOutFile.open("database/tempEmployees.txt");
							er.erOutFile<<line<<endl;
							er.erOutFile.close();
							er.editEmployee(Result,retrieveInfo(strJobOpeningID,"jpo"),"ejp");
							er.erOutFile.open("database/tempEmployees.txt");
							er.erOutFile<<line<<endl;
							er.erOutFile.close();
							er.editEmployee(Result,"30000","ebs");
							er.erOutFile.open("database/tempEmployees.txt");
							er.erOutFile<<line<<endl;
							er.erOutFile.close();
							time_t now=time(0);
							char dtnow[30];
							tm tstruct;
							tstruct = *localtime(&now);
							strftime(dtnow, sizeof(dtnow), "%B %d, %Y", &tstruct);
							string startDate=dtnow;
							er.editEmployee(Result,startDate,"esd");
							return 1;
						}
					}
					else{
						cout<<"Applicant not applied for this job opening";
						return 0;
					}
				}
			}
			else{
				cout<<"Employee not an Applicant";
				return 0;
			}
		}
		else{
			cout<<"Applicant not found";
			return 0;
		}
	}
	else{
		cout<<"Job Opening not Found";
		return 0;
	}
}
