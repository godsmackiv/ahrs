#ifndef __LOCATIONS_H_INCLUDED__
#define __LOCATIONS_H_INCLUDED__
#include <iostream>
#include <fstream>

using namespace std;
class locations{
	private:
		int locationID;
		string code, name;
		
		ifstream locInFile;
		ofstream locOutFile;				
	public:
		bool searchLocation(string,string);
		bool createNewLocation();
		bool deleteLocation();
		bool updateLocation();
		bool editLocation(string,string,string);
		bool rewriteLocationRecord();
};

#endif
