#ifndef __JOBOPENINGS_H_INCLUDED__
#define __JOBOPENINGS_H_INCLUDED__
#include <iostream>
#include <fstream>

using namespace std;
class jobOpenings{
	private:
		int jobOpeningID;
		string position, department, location, requirements, applicants;
		
		ifstream joInFile;
		ofstream joOutFile;				
	public:
		bool searchJobOpening(string,string);
		bool createNewJobOpening();
		bool deleteJobOpening();
		bool updateJobOpening();
		bool editJobOpening(string,string,string);
		bool rewriteJobOpeningRecord();
		bool assignApplicant();
};

#endif
