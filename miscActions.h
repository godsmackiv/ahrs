#ifndef __MISCACTIONS_H_INCLUDED__
#define __MISCACTIONS_H_INCLUDED__

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class miscActions {
	private:
		char task;
		char perform;
	public:
		float askFloatInput(int); //
		int askIntInput(int); //
		stringstream clearSStream(stringstream);
		string trimOuterSpaces(string);
		void managerMenu(void);
		void managerSubMenu(void);
		void loadingBar(void);
	
	
};



#endif
