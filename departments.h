#ifndef __DEPARTMENTS_H_INCLUDED__
#define __DEPARTMENTS_H_INCLUDED__
#include <iostream>
#include <fstream>

using namespace std;
class departments{
	private:
		int departmentID;
		string code, name;
		
						
	public:
		ifstream deptInFile;
		ofstream deptOutFile;
		
		bool searchDepartment(string,string);
		bool createNewDepartment();
		bool deleteDepartment();
		bool updateDepartment();
		bool editDepartment(string,string,string);
		bool rewriteDepartmentRecord();
};

#endif
