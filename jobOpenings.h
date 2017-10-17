#ifndef __JOBOPENINGS_H_INCLUDED__
#define __JOBOPENINGS_H_INCLUDED__

#include <fstream>

#include "miscActions.h"

using namespace std;

class jobOpenings {
	private:
		string jobOID, position, department, location, requirements, applicants, availability;
		ofstream userOutFile;
		ifstream userInFile;
		miscActions mActions;
		
	public:
		string getJobOID(void);
		string getPosition(void);
		string getDepartment(void);
		string getLocation(void);
		string getRequirements(void);
		string getApplicants(void);
		string getAvailability(void);
		
		void setJobOID(string);
		void setPosition(string);
		void setDepartment(string);
		void setLocation(string);
		void setRequirements(string);
		void setApplicants(string);
		void setAvailability(string);
		
		void createJobOpening();
		void editJobOpening();
		void viewJobOpening();
		void deleteJobOpening();
		void assignApplicants();
		void hireEmployee();
		void viewJobOrderApplicants();
		void printOpenJobOpenings();
};

#endif
