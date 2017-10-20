#include "jobOpenings.h"
#include <iomanip>
#include <sstream>
#include <cctype>

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
		cout<<endl<<"edit choice: ";
		int choice=0;
		cin>>choice;
		while(choice<1&&choice>5){
			cin>>choice;
		}
		string newInfo,type;
		cout<<"Enter new data: ";
		cin.ignore();
		getline(cin,newInfo);
		switch(choice){
			case 1: if(!jPos.searchJobPosition(newInfo,"jpn")){
					cout<<"Position not found";
					return 0;
				}
				else type="jpo";
				break;
			case 2:  if(!dept.searchDepartment(newInfo,"dna")){
					cout<<"Department not found";
					return 0;
				}
				else type="jde";
				break;
			case 3: if(!loc.searchLocation(newInfo,"lna")){
					cout<<"Location not found";
					return 0;
				}
				else type="jlo";
				break;
			case 4: addRequirements();
				type="req";
				break;
			case 5: addApplicants();
				type="jap";
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
			posStart = line.find("$eid#") + 5;
			posEnd = line.find("$eid#", posStart);
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
		cout<<"Applicant Number: ";
		cin>>applicantID;
		string Result;//string which will contain the result
		stringstream convert; // stringstream used for the conversion
		convert<<setw(6)<<setfill('0')<<applicantID;//add the value of Number to the characters in the stream
		Result = convert.str();//set Result to the content of the stream
		if(er.searchEmployee(Result,"eid")){
			if(er.searchEmployee("Applicant","ees")){
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
}
