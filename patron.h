//class defintion for patron

#ifndef PATRON_H
#define PATRON_H

#include <string>
using namespace std;

class Patron {
	public:
		Patron(string name, int id, double balance, int items);
		void SetID(int id);
		void SetName(string name);
		void SetBal(double balance);
		void SetItems(int items);
		
		int GetID() const;
		string GetName() const;
		double GetBal() const;
		int GetItems() const;
		
	private:
		string n;
		int patronID;
		double bal;
		int itemsOut;
};

#endif
