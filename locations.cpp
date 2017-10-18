#include "locations.h"
#include <iomanip>
#include <sstream>

bool locations::searchLocation(string query,string type){
	string line, found;
	int posStart=0, posEnd=0;
	
	locInFile.open("database/locations.txt");
	if(locInFile.is_open()){
		while(getline(locInFile,line)){
			posStart = line.find("$"+type+"#") + 5;
			posEnd = line.find("$"+type+"#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			if (query == found) {
				locInFile.close();
				return true;
			}
		}
		locInFile.close();
	}
	return false;
}

bool locations::createNewLocation(){
	string line;
	
	cout<<"Name: ";
	getline(cin,name);
	if(searchLocation(name,"lna")){
		cout<<"location name already exists"<<endl;
		return 0;
	}
	
	locInFile.open("database/locations.txt");
	if (locInFile.is_open()) {
		string line, found;
		int posStart=0, posEnd=0;
		while(getline(locInFile,line)){
			posStart = line.find("$lid#") + 5;
			posEnd = line.find("$lid#", posStart);
			found = line.substr(posStart, posEnd - posStart);
		}
		stringstream strID(found);
		strID >>locationID;
		locationID++;
		locInFile.close();
	}
  	else cout << "Error: Unable to open Locations database."; 
  	
	cout<<"Code: ";
	getline(cin,code);
	
	locOutFile.open("database/locations.txt",ios_base::app);
	locOutFile<<"$lid#"<<setw(6)<<setfill('0')<<locationID<<"$lid#";
	locOutFile<<"$lco#"<<code<<"$lco#";
	locOutFile<<"$lna#"<<name<<"$lna#"<<endl;
	locOutFile.close();
	return 1;
}

bool locations::deleteLocation(){
	cout<<"Enter location ID to delete: ";
	cin>>locationID;
	string result;
	stringstream convert;
	convert<<setw(6)<<setfill('0')<<locationID;
	result=convert.str();
	
	if(!searchLocation(result,"lid")){
		cout<<"Location ID doesn't exist";
		return 0;
	}
	else{
		string line, found;
		int posStart=0, posEnd=0;
		char choice;
		
		cout<<"Are you sure you want to delete this location?(y/n) ";
		cin>>choice;
		if(choice=='y'){
			locInFile.open("database/locations.txt");
			locOutFile.open("database/tempLocations.txt");
			if(locInFile.is_open()){
				while(getline(locInFile,line)){
					posStart=line.find("$lid#")+5;
					posEnd=line.find("$lid#",posStart);
					found=line.substr(posStart,posEnd-posStart);
					if(result!=found){
						locOutFile<<line<<endl;
					}
				}
				locOutFile.close();
				locInFile.close();
				if(rewriteLocationRecord()) return 1;
				else return 0;
			}
			else cout<<"Error: Unable to open locations database. ";
			return false;
		}
		return false;
	}
}

bool locations::updateLocation(){
	cout<<"Enter Location ID to update: ";
	cin>>locationID;
	
	string Result;//string which will contain the result
	stringstream convert; // stringstream used for the conversion
	convert<<setw(6)<<setfill('0')<<locationID;//add the value of Number to the characters in the stream
	Result = convert.str();//set Result to the content of the stream

	if(!searchLocation(Result,"lid")){
		cout<<"Location ID doesn't exist";
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
			case 1:if(!searchLocation(newInfo,"lna")) type="lna";
				else{
					cout<<"Location name already exists!";
					return 0;
				}
				break;
			case 2: type="lco";
				break;
		}
		if(editLocation(Result,newInfo,type)) return 1;
		else return 0;
	}
}

bool locations::editLocation(string locationID, string newInfo, string type){
	locInFile.open("database/locations.txt");
	locOutFile.open("database/tempLocations.txt");
	string newLine,line,found,temp;
	int posStart=0,posEnd=0,editStart=0,editEnd=0;
	if (locInFile.is_open()) {
		while ( getline (locInFile,line) ) {
			posStart = line.find("$lid#") + 5;
			posEnd = line.find("$lid#", posStart);
			found = line.substr(posStart, posEnd - posStart);
			editStart=line.find("$"+type+"#")+5;
			editEnd=line.find("$"+type+"#", editStart);
			if (locationID != found) {
				locOutFile<<line<<endl;
			}
			else{
				temp=line.substr(0,editStart);
				locOutFile<<temp;
				locOutFile<<newInfo;
				temp=line.substr(editEnd,line.size());
				locOutFile<<temp;
				locOutFile<<endl;
			}	
		}
		locOutFile.close();
		locInFile.close();
		if(rewriteLocationRecord()) return 1;
		else return 0;
	}
  	else cout << "Error: Unable to open Locations database."; 
}

bool locations::rewriteLocationRecord(){
	string line;
	locInFile.open("database/tempLocations.txt");
	locOutFile.open("database/locations.txt");
	if(locInFile.is_open()){
		while(getline(locInFile,line)){
			locOutFile<<line<<endl;
		}
		locOutFile.close();
		locInFile.close();
		remove("database/tempLocations.txt");
		return 1;
	}
	else cout<<"Error: Unable to open Locations database.";
	return 0;
}


















