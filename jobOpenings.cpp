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
	
	char req='y';
	cout<<"Requirements: ";
	while(req=='y'){
		getline(cin,requirements);
		cout<<"Add Another Requirement? (y/n) ";
		cin>>req;
		tolower(req);
	}
	cin.ignore();
//	
//	char app='y';
//	cout<<"Add applicants?";
//	
//	
	
	joOutFile.open("database/jobOpenings.txt",ios_base::app);
	
	joOutFile.close();
	return 1;	
}

bool jobOpenings::deleteJobOpening(){
	
}

bool jobOpenings::updateJobOpening(){
	
}

bool jobOpenings::editJobOpening(string,string,string){
	
}

bool jobOpenings::rewriteJobOpeningRecord(){
	
}
