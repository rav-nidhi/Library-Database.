//class defintion for patrons

#ifndef PATRONS_H
#define PATRONS_H

#include <string>
#include <vector>
using namespace std;
#include "patron.h"

class Patrons {
	public:
		void AddPatron();
		void EditPatron();
		void DelPatron();
		int FindPatron();
		void PrintAll();
		void PrintDetails();
		void PayFines();
		vector<Patron> patronList;
};

#endif
