#ifndef __JOBOPENINGS_H_INCLUDED__
#define __JOBOPENINGS_H_INCLUDED__
#include <iostream>
#include <fstream>

#include "departments.h"
#include "locations.h"
#include "employeeRecords.h"
#include "jobPositions.h"

class employeeRecords;
class departments;
class locations;

using namespace std;
class jobOpenings{
	private:
		int jobOpeningID;
		string position, jobDepartment, jobLocation, requirements, applicants, availability;
		
		ifstream joInFile;
		ofstream joOutFile;	
		
		departments dept;	
		locations loc;	
		employeeRecords er;	
		jobPositions jPos;
	public:
		bool searchJobOpening(string,string);
		bool jobExists(string);
		bool createNewJobOpening();
		bool deleteJobOpening();
		bool updateJobOpening();
		bool editJobOpening(string,string,string);
		bool rewriteJobOpeningRecord();
		bool assignApplicant();
		bool hireApplicant();
		bool applicantTransaction(int);
		void addRequirements();
		void addApplicants();
		bool isAlreadyApplied(string,string);
		string retrieveInfo(string,string);
};

#endif
