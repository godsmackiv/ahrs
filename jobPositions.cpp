#include "jobPositions.h"
#include <iomanip>
#include <sstream>

bool jobPositions::searchJobPosition(string query,string type){
	string line, found;
	int posStart=0, posEnd=0;
	
	jpInFile.open("database/jobPositions.txt");
	if(jpInFile.is_open()){
		while(getline(jpInFile,line)){
			posStart = line.find("$"+type+"#") + 5;
			posEnd = line.find("$"+type+"#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			if (query == found) {
				jpInFile.close();
				return true;
			}
		}
		jpInFile.close();
	}
	return false;
}

bool jobPositions::createNewJobPosition(){
	string line,found;
	
	cout<<"Name: ";
	getline(cin,name);
	if(searchJobPosition(name,"jpn")){
		cout<<"jobPosition name already exists"<<endl;
		return 0;
	}
	
	jpInFile.open("database/jobPositions.txt");
	if (jpInFile.is_open()) {
		getline(jpInFile,line);
		found=line.substr(4,6);
		stringstream strID(found);
		strID >>jobPositionID;
		jobPositionID++;
		jpInFile.close();
	}
  	else cout << "Error: Unable to open JobPositions database."; 
  	
	cout<<"Code: ";
	getline(cin,code);
	
	jpOutFile.open("database/tempJobPositions.txt");
	jpOutFile<<"$lI#"<<setw(6)<<setfill('0')<<jobPositionID<<"$lI#"<<endl;
	jpOutFile.close();
	if(!editJobPosition(" "," "," ")) return 0;
	
	jpOutFile.open("database/jobPositions.txt",ios_base::app);
	jpOutFile<<"$jid#"<<setw(6)<<setfill('0')<<jobPositionID<<"$jid#";
	jpOutFile<<"$jpc#"<<code<<"$jpc#";
	jpOutFile<<"$jpn#"<<name<<"$jpn#"<<endl;
	jpOutFile.close();
	return 1;
}

bool jobPositions::deleteJobPosition(){
	cout<<"Enter jobPosition ID to delete: ";
	cin>>jobPositionID;
	string result;
	stringstream convert;
	convert<<setw(6)<<setfill('0')<<jobPositionID;
	result=convert.str();
	
	if(!searchJobPosition(result,"jid")){
		cout<<"JobPosition ID doesn't exist";
		return 0;
	}
	else{
		string line, found;
		int posStart=0, posEnd=0;
		char choice;
		
		cout<<"Are you sure you want to delete this jobPosition?(y/n) ";
		cin>>choice;
		if(choice=='y'){
			jpInFile.open("database/jobPositions.txt");
			jpOutFile.open("database/tempJobPositions.txt");
			if(jpInFile.is_open()){
				while(getline(jpInFile,line)){
					posStart=line.find("$jid#")+5;
					posEnd=line.find("$jid#",posStart);
					found=line.substr(posStart,posEnd-posStart);
					if(result!=found){
						jpOutFile<<line<<endl;
					}
				}
				jpOutFile.close();
				jpInFile.close();
				if(rewriteJobPositionRecord()) return 1;
				else return 0;
			}
			else cout<<"Error: Unable to open jobPositions database. ";
			return false;
		}
		return false;
	}
}

bool jobPositions::updateJobPosition(){
	cout<<"Enter JobPosition ID to update: ";
	cin>>jobPositionID;
	
	string Result;//string which will contain the result
	stringstream convert; // stringstream used for the conversion
	convert<<setw(6)<<setfill('0')<<jobPositionID;//add the value of Number to the characters in the stream
	Result = convert.str();//set Result to the content of the stream

	if(!searchJobPosition(Result,"jid")){
		cout<<"JobPosition ID doesn't exist";
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
			case 1:if(!searchJobPosition(newInfo,"jpn")) type="jpn";
				else{
					cout<<"JobPosition name already exists!";
					return 0;
				}
				break;
			case 2: type="jpc";
				break;
		}
		jpOutFile.open("database/tempJobPositions.txt");
		jpOutFile<<"$lI#"<<setw(6)<<setfill('0')<<jobPositionID<<"$lI#"<<endl;
		jpOutFile.close();
		if(editJobPosition(Result,newInfo,type)) return 1;
		else return 0;
	}
}

bool jobPositions::editJobPosition(string jobPositionID, string newInfo, string type){
	jpInFile.open("database/jobPositions.txt");
	jpOutFile.open("database/tempJobPositions.txt",ios_base::app);
	string newLine,line,found,temp;
	int posStart=0,posEnd=0,editStart=0,editEnd=0;
	if (jpInFile.is_open()) {
		getline(jpInFile,line);
		while ( getline (jpInFile,line) ) {
			posStart = line.find("$jid#") + 5;
			posEnd = line.find("$jid#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			editStart=line.find("$"+type+"#")+5;
			editEnd=line.find("$"+type+"#", editStart);
			if (jobPositionID != found) {
				jpOutFile<<line<<endl;
			}
			else{
				temp=line.substr(0,editStart);
				jpOutFile<<temp;
				jpOutFile<<newInfo;
				temp=line.substr(editEnd,line.size());
				jpOutFile<<temp;
				jpOutFile<<endl;
			}	
		}
		jpOutFile.close();
		jpInFile.close();
		if(rewriteJobPositionRecord()) return 1;
		else return 0;
	}
  	else cout << "Error: Unable to open JobPositions database."; 
}

bool jobPositions::rewriteJobPositionRecord(){
	string line;
	jpInFile.open("database/tempJobPositions.txt");
	jpOutFile.open("database/jobPositions.txt");
	if(jpInFile.is_open()){
		while(getline(jpInFile,line)){
			jpOutFile<<line<<endl;
		}
		jpOutFile.close();
		jpInFile.close();
		remove("database/tempJobPositions.txt");
		return 1;
	}
	else cout<<"Error: Unable to open JobPositions database.";
	return 0;
}


















