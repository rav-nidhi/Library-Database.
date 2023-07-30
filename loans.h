//class defintion for loans

#ifndef LOANS_H
#define LOANS_H

#include <string>
#include <vector>
using namespace std;
#include "loan.h"
#include "libraryitems.h"
#include "patrons.h"

class Loans {
	public:
		void CheckIn(LibraryItems &lib, Patrons &pat);
		void CheckOut(LibraryItems &lib, Patrons &pat);
		void PrintOverdue(Patrons &pat);
		void PrintPatron(LibraryItems &lib, Patrons &pat);
		void UpdateStatus(Patrons &pat);
		void ReCheck(LibraryItems &lib, Patrons &pat);
		void EditLoan(LibraryItems &lib, Patrons &pat);
		int FindLoan();
		void Report(LibraryItems &lib, Patrons &pat);
		vector<Loan> loanList;
};

#endif
