#ifndef __MISCACTIONS_H_INCLUDED__
#define __MISCACTIONS_H_INCLUDED__
#include "users.h"
#include <string>
#include <sstream>
#include <iostream>
class users;
using namespace std;

class miscActions {
	private:
		char task;
		char perform,report;
		ofstream userOutFile;
		ifstream userInFile;
		users *u;
	public:
		float askFloatInput(int); //
		int askIntInput(int); //
		stringstream clearSStream(stringstream);
		string trimOuterSpaces(string);
		void Menu(void);
		void managerSubMenu(void);
		void recruiterSubMenu(void);
		void personnelSubMenu(void);
		void adminSubMenu(void);
		void loadingBar(void);
		void viewReports(void);
		string hidePass(void);
		void managerView();
	
};



#endif
