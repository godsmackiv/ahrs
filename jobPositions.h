#ifndef __JOBPOSITIONS_H_INCLUDED__
#define __JOBPOSITIONS_H_INCLUDED__
#include <iostream>
#include <fstream>

using namespace std;
class jobPositions{
	private:
		int jobPositionID;
		string code, name;
		
		ifstream jpInFile;
		ofstream jpOutFile;				
	public:
		bool editJobPosition(string,string,string);
		bool searchJobPosition(string,string);
		bool createNewJobPosition();
		bool deleteJobPosition();
		bool updateJobPosition();
		bool rewriteJobPositionRecord();
};

#endif
