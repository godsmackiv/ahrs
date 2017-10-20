#ifndef __BENEFITS_H_INCLUDED__
#define __BENEFITS_H_INCLUDED__
#include <iostream>
#include <fstream>

using namespace std;
class benefits{
	private:
		int benefitCode,amount;
		string name,createDate;
		ifstream benInFile;
		ofstream benOutFile;
	public:
		bool searchBenefit(string, string);
		bool createNewBenefit();
		bool deleteBenefit();
		bool updateBenefit();
		bool editBenefit(string, string, string);
		bool rewriteBenefitRecord();
};

#endif
