#ifndef __EMPLOYEERECORDS_H_INCLUDED__
#define __EMPLOYEERECORDS_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cctype>

using namespace std;
class employeeRecords{
	private:
		int employeeID, age; 																							//employee info(integers)
		string contactNumber, name, address, emailAddress, birthday, sex, maritalStatus, startDate, employmentStatus;	//employee info(strings)
		string fathersName, fathersOccupation, mothersName, mothersOccupation;											//parents info
		string educationalAttainment, schoolName, schoolAddress;														//educational attainment info(string)
		int yearGraduated,baseSalary;
		string position;
		
	public:		
		ifstream erInFile;
		ofstream erOutFile;		
				
		bool searchEmployee(string,string);
		bool createNewEmployee();
		bool deleteEmployee();
		bool updateEmployee();
		bool editEmployee(string,string,string);
		bool rewriteEmployeeRecord();
		bool isApplicant(string);
		int getNumberOfEmployees();
		string getEmployeeInfo(string, string); // requires ID is known
	
};

#endif
