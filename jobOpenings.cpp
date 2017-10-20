#include "jobOpenings.h"
#include <sstream>

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

bool jobOpenings::createNewJobOpening(){
	string line;
//	
//	cout<<"Position: ";
//	getline(cin,position);
//	if(searchJobOpening(position,"jpo")){
//		cout<<"jobOpening position already exists"<<endl;
//		return 0;
//	}
//	
//	joInFile.open("database/jobOpenings.txt");
//	if (joInFile.is_open()) {
//		string line, found;
//		int posStart=0, posEnd=0;
//		while(getline(joInFile,line)){
//			posStart = line.find("$jid#") + 5;
//			posEnd = line.find("$jid#", posStart);
//			found = line.substr(posStart, posEnd - posStart);
//		}
//		stringstream strID(found);
//		strID >>jobOpeningID;
//		jobOpeningID++;
//		joInFile.close();
//	}
//  	else cout << "Error: Unable to open JobOpenings database."; 
//  	
//	cout<<"Location: ";
//	getline(cin,location);
//	
//	
//	joOutFile.open("database/jobOpenings.txt",ios_base::app);
//	joOutFile<<"$jid#"<<setw(6)<<setfill('0')<<jobOpeningID<<"$jid#";
//	joOutFile<<"$jpo#"<<position<<"$jpo#"<<endl;
//	joOutFile.close();
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
