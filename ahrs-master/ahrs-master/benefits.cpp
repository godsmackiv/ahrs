#include "benefits.h"
#include <iomanip>
#include <sstream>
#include <ctime>

bool benefits::searchBenefit(string query, string type){
	string line, found;
	int posStart=0, posEnd=0;
	
	benInFile.open("database/benefits.txt");
	if(benInFile.is_open()){
		while(getline(benInFile,line)){
			posStart=line.find("$"+type+"#")+5;
			posEnd=line.find("$"+type+"#",posStart);
			found=line.substr(posStart,posEnd-posStart);
			if(query==found){
				benInFile.close();
				return 1;
			}
		}
		benInFile.close();
	}
	return 0;
}

bool benefits::createNewBenefit(){
	string line;
	
	
	cout<<"Name: ";
	getline(cin,name);
	if(searchBenefit(name,"bna")){
		cout<<"benefit name already exists"<<endl;
		return 0;
	}
	
	benInFile.open("database/benefits.txt");
	if (benInFile.is_open()) {
		string line, found;
		int posStart=0, posEnd=0;
		while(getline(benInFile,line)){
			posStart = line.find("$bco#") + 5;
			posEnd = line.find("$bco#", posStart);
			found = line.substr(posStart, posEnd - posStart);
		}
		stringstream strID(found);
		strID >>benefitCode;
		benefitCode++;
		benInFile.close();
	}
  	else cout << "Error: Unable to open Benefits database."; 
  	
	cout<<"Amount: ";
	cin>>amount;
	char dtnow[20];
	time_t now=time(0);
	tm tstruct;
	tstruct = *localtime(&now);
	strftime(dtnow, sizeof(dtnow), "%B %d, %Y", &tstruct);
	createDate=dtnow;
	benOutFile.open("database/benefits.txt",ios_base::app);	
	benOutFile<<"$bco#"<<setw(3)<<setfill('0')<<benefitCode<<"$bco#";
	benOutFile<<"$bna#"<<name<<"$bna#";
	benOutFile<<"$bam#"<<amount<<"$bam#";
	benOutFile<<"$bcd#"<<createDate<<"$bcd#"<<endl;	
	benOutFile.close();
	return 1;
}

bool benefits::deleteBenefit(){
	cout<<"Enter benefit ID to delete: ";
	cin>>benefitCode;
	string result;
	stringstream convert;
	convert<<setw(3)<<setfill('0')<<benefitCode;
	result=convert.str();
	
	if(!searchBenefit(result,"bco")){
		cout<<"Benefit ID doesn't exist";
		return 0;
	}
	else{
		string line, found;
		int posStart=0, posEnd=0;
		char choice;
		
		cout<<"Are you sure you want to delete this benefit?(y/n) ";
		cin>>choice;
		if(choice=='y'){
			benInFile.open("database/benefits.txt");
			benOutFile.open("database/tempBenefits.txt");
			if(benInFile.is_open()){
				while(getline(benInFile,line)){
					posStart=line.find("$bco#")+5;
					posEnd=line.find("$bco#",posStart);
					found=line.substr(posStart,posEnd-posStart);
					if(result!=found){
						benOutFile<<line<<endl;
					}
				}
				benOutFile.close();
				benInFile.close();
				if(rewriteBenefitRecord()) return 1;
				else return 0;
			}
			else cout<<"Error: Unable to open benefits database. ";
			return false;
		}
		return false;
	}
}

bool benefits::updateBenefit(){
	cout<<"Enter Benefit ID to update: ";
	cin>>benefitCode;
	
	string Result;//string which will contain the result
	stringstream convert; // stringstream used for the conversion
	convert<<setw(3)<<setfill('0')<<benefitCode;//add the value of Number to the characters in the stream
	Result = convert.str();//set Result to the content of the stream

	if(!searchBenefit(Result,"bco")){
		cout<<"Benefit ID doesn't exist";
		return 0;
	}
	else{
		cout<<"select info to edit"<<endl;
		cout<<"[1] Name"<<endl;
		cout<<"[2] Amount"<<endl;
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
			case 1:if(!searchBenefit(newInfo,"bna")) type="bna";
				else{
					cout<<"Benefit name already exists!";
					return 0;
				}
				break;
			case 2: type="bam";
				break;
		}
		if(editBenefit(Result,newInfo,type)) return 1;
		else return 0;
	}
}

bool benefits::editBenefit(string benefitCode, string newInfo, string type){
	benInFile.open("database/benefits.txt");
	benOutFile.open("database/tempBenefits.txt");
	string newLine,line,found,temp;
	int posStart=0,posEnd=0,editStart=0,editEnd=0;
	if (benInFile.is_open()) {
		while ( getline (benInFile,line) ) {
			posStart = line.find("$bco#") + 5;
			posEnd = line.find("$bco#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			editStart=line.find("$"+type+"#")+5;
			editEnd=line.find("$"+type+"#", editStart);
			if (benefitCode != found) {
				benOutFile<<line<<endl;
			}
			else{
				temp=line.substr(0,editStart);
				benOutFile<<temp;
				benOutFile<<newInfo;
				temp=line.substr(editEnd,line.size());
				benOutFile<<temp;
				benOutFile<<endl;
			}	
		}
		benOutFile.close();
		benInFile.close();
		if(rewriteBenefitRecord()) return 1;
		else return 0;
	}
  	else cout << "Error: Unable to open Benefits database."; 
}

bool benefits::rewriteBenefitRecord(){
	string line;
	benInFile.open("database/tempBenefits.txt");
	benOutFile.open("database/benefits.txt");
	if(benInFile.is_open()){
		while(getline(benInFile,line)){
			benOutFile<<line<<endl;
		}
		benOutFile.close();
		benInFile.close();
		remove("database/tempBenefits.txt");
		return 1;
	}
	else cout<<"Error: Unable to open Benefits database.";
	return 0;
}
