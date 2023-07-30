//class defintion for loan

#ifndef LOAN_H
#define LOAN_H

#include <string>
using namespace std;
#include "book.h"
#include "patron.h"

class Loan {
	public:
		Loan(int id, int libID, int pID, int year, int month, int day, int hour, int minute, string status, int recheck);
		void SetID(int id);
		void SetItemID(int libID);
		void SetPatronID(int pID);
		void SetDate(int year, int month, int day);
		void SetTime(int hour, int minute);
		void SetStatus(string status);
		void SetRecheck(int recheck);
		
		int GetID();
		int GetItemID();
		int GetPatronID();
		int GetDay();
		int GetYear();
		int GetMonth();
		int GetHour();
		int GetMin();
		string GetStatus();
		int GetRecheck();
		
	private:
		int loanID;
		int itemID;
		int patronID;
		int y;
		int m;
		int d;
		int h;
		int min;
		string stat;
		int rc;
};

#endif
