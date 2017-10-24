#ifndef __DEPARTMENTS_H_INCLUDED__
#define __DEPARTMENTS_H_INCLUDED__
#include <iostream>
#include <fstream>
#include "miscActions.h"

using namespace std;
class departments{
	private:
		int departmentID;
		string code, name;
		
		ifstream deptInFile;
		ofstream deptOutFile;
		
		miscActions mActions;
						
	public:
		bool searchDepartment(string,string);
		bool createNewDepartment();
		bool deleteDepartment();
		bool updateDepartment();
		bool editDepartment(string,string,string);
		bool rewriteDepartmentRecord();
		int getLastDeptID();
		string getDepartmentInfo(string, string);
};

#endif
