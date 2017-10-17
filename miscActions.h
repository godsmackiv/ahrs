#ifndef __MISCACTIONS_H_INCLUDED__
#define __MISCACTIONS_H_INCLUDED__

#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

class miscActions {
	private:
	
	public:
		float askFloatInput(int); //
		int askIntInput(int); //
		stringstream clearSStream(stringstream);
		string trimOuterSpaces(string);
		void displayLoadingBar();
		

	
	
};



#endif
