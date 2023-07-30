//main file for menu options

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;
#include "libraryitem.h"
#include "book.h"
#include "audiocd.h"
#include "dvd.h"
#include "patron.h"
#include "loan.h"
#include "libraryitems.h"
#include "patrons.h"
#include "loans.h"

int main() {
	Patrons pat;	//all patrons
	LibraryItems lib;		//all books
	Loans lo;		//all loans
	
	ofstream fout;	//output stream
	ifstream fin;	//input stream
	
	//temp variables for input
	int count = 0;
	int read = 0;	//determines if savefile exists
	int obj;	//type of obj from input
	
	int lID;	//load id, library id, patron id
	int libID;
	int pID;
	string strDT;
	int year, month, day, hour, min;
	string istat;	//item status, loan status
	string lstat;
	int recheck;
	string a;	//author/artist
	string title;
	string cat;		//category/genre
	long int isbn;
	double cost;
	string name;
	double balance;
	int itemsOut;
	
	fin.open("save.txt");	//open save file for input
	if(fin.fail()) {	//create file if opening fails
		fout.open("save.txt");
		fout.close();
		read--;
	}
	
	if(read != -1) {	//only run if save file already existed
		fin >> obj;
		while(obj != 9) {	//read save file data into program until end
			switch (obj) {	//create 1 of 3 objects based on obj input
				case 1:	//patron
					fin >> pID;
					fin.ignore();
					getline(fin, name);
					fin >> balance >> itemsOut;
					pat.patronList.push_back(Patron(name, pID, balance, itemsOut));
					break;
					
				case 2:	//loan
					fin >> lID >> libID >> pID;
					fin >> year >> month >> day >> hour >> min;
					fin.ignore();
					fin >> lstat; 
					fin >> recheck;
					lo.loanList.push_back(Loan(lID, libID, pID, year, month, day, hour, min, lstat, recheck));
					break;
			};
			fin >> obj;
		}
		lib.Load();
	}
	fin.close();		//close input file
	
	int menu1;	//menu 1 choice
	int menu2;	//menu 2 choice
	//load menu for user
	while(menu1 != 10) {
		cout << "MENU:" << endl;
		cout << "1 - New Loan, Patron, or Item" << endl;
		cout << "2 - Edit Loan, Patron, or Item" << endl;
		cout << "3 - Delete Loan, Patron, or Item" << endl;
		cout << "4 - Find Loan, Patron or Item" << endl;
		cout << "5 - Report a Item as Lost" << endl;
		cout << "6 - Pay a Patron's Fines" << endl;
		cout << "7 - Update a Loan Status" << endl;
		cout << "8 - Recheck a Loan" << endl;
		cout << "9 - Print Information (select for more details)" << endl;
		cout << "10 - Quit" << endl;
		cout << "Enter a number between 1 and 10: ";
		cin >> menu1;
		while((menu1 < 1) || (menu1 > 10)) {
			cout << "Number must be between 1 and 9: ";
			cin >> menu1;
		}
		
		switch (menu1) {
			case 1: //new object
				cout << endl << "New Object Menu: " << endl;
				cout << "1 - New Loan (Check Out Item)" << endl;
				cout << "2 - New Patron" << endl;
				cout << "3 - New Item" << endl;
				cout << "4 - Return to Main Menu" << endl;
				cout << "Enter a number between 1 and 4: ";
				cin >> menu2;
				while((menu2 < 1) || (menu2 > 4)) {
					cout << "Number must be between 1 and 4: ";
					cin >> menu2;
				}
				
				switch (menu2) {
					case 1: 
						lo.CheckOut(lib, pat);
						break;
					
					case 2:
						pat.AddPatron();
						break;
						
					case 3:
						lib.AddItem();
						break;
					
					case 4:
						break;
				};
				break;
			
			case 2:	//edit object
				cout << endl << "Edit Object Menu: " << endl;
				cout << "1 - Edit Loan" << endl;
				cout << "2 - Edit Patron" << endl;
				cout << "3 - Edit Item" << endl;
				cout << "4 - Return to Main Menu" << endl;
				cout << "Enter a number between 1 and 4: ";
				cin >> menu2;
				while((menu2 < 1) || (menu2 > 4)) {
					cout << "Number must be between 1 and 4: ";
					cin >> menu2;
				}
				
				switch (menu2) {
					case 1: 
						lo.EditLoan(lib, pat);
						break;
					
					case 2:
						pat.EditPatron();
						break;
						
					case 3:
						lib.EditItem();
						break;
						
					case 4:
						break;
				};
				break;
			
			case 3: //delete object
				cout << endl << "Delete Object Menu: " << endl;
				cout << "1 - Delete Loan (Check In Item)" << endl;
				cout << "2 - Delete Patron" << endl;
				cout << "3 - Delete Item" << endl;
				cout << "4 - Return to Main Menu" << endl;
				cout << "Enter a number between 1 and 4: ";
				cin >> menu2;
				while((menu2 < 1) || (menu2 > 4)) {
					cout << "Number must be between 1 and 4: ";
					cin >> menu2;
				}
				
				switch (menu2) {
					case 1: 
						lo.CheckIn(lib, pat);
						break;
					
					case 2:
						pat.DelPatron();
						break;
						
					case 3:
						lib.DelItem();
						break;
						
					case 4:
						break;
					
				};
				break;
			
			case 4:	//find object
				cout << endl << "Find Object Menu: " << endl;
				cout << "1 - Find Loan" << endl;
				cout << "2 - Find Patron" << endl;
				cout << "3 - Find Item" << endl;
				cout << "4 - Return to Main Menu" << endl;
				cout << "Enter a number between 1 and 4: ";
				cin >> menu2;
				while((menu2 < 1) || (menu2 > 4)) {
					cout << "Number must be between 1 and 4: ";
					cin >> menu2;
				}
				
				switch (menu2) {
					case 1: 
						lo.FindLoan();
						break;
					
					case 2:
						pat.FindPatron();
						break;
						
					case 3:
						lib.FindItem();
						break;
						
					case 4:
						break;	
				};
				break;
			
			case 5:	//report lost
				lo.Report(lib, pat);
				break;
				
			case 6:	//pay fines
				pat.PayFines();
				break;
				
			case 7:	//update loan status
				lo.UpdateStatus(pat);
				break;
			
			case 8:
				lo.ReCheck(lib, pat);
				break;
			
			case 9:	//print functions
				cout << endl << "Print Options:" << endl;
				cout << "1 - Print List of Items" << endl;
				cout << "2 - Print List of Patrons" << endl;
				cout << "3 - Print Item Details" << endl;
				cout << "4 - Print Patron Details" << endl;
				cout << "5 - Print all Overdue Loans" << endl;
				cout << "6 - Print all Items Checked Out by a Patron" << endl;
				cout << "7 - Return to Main Menu" << endl;
				cout << "Enter a number between 1 and 7: ";
				cin >> menu2;
				while((menu2 < 1) || (menu2 > 7)) {
					cout << "Number must be between 1 and 7: ";
					cin >> menu2;
				}
				
				switch (menu2) {
					case 1:
						lib.PrintAll();
						break;
					
					case 2:
						pat.PrintAll();
						break;
					
					case 3:
						lib.PrintDetails();
						break;
						
					case 4:
						pat.PrintDetails();
						break;
					
					case 5:
						lo.PrintOverdue(pat);
						break;
						
					case 6:
						lo.PrintPatron(lib, pat);
						break;
						
					case 7:
						break;
				};
				break;
				
			case 10:	//quit
				break;
		};
	}
	
	fout.open("save.txt");	//open save file for output
	if(fout.fail()) {
		cout << "File open failed." << endl;
		exit(EXIT_FAILURE);
	}
	
	read = 0;
	
	for(int i=0; i<pat.patronList.size(); i++) {	//save all patrons to save file
		fout << "1" << endl;
		fout << pat.patronList[i].GetID() << endl;
		fout << pat.patronList[i].GetName() << endl;
		fout << pat.patronList[i].GetBal() << endl;
		fout << pat.patronList[i].GetItems() << endl;
	}
	
	for(int i=0; i<lo.loanList.size(); i++) {
		fout << "2" << endl;
		fout << lo.loanList[i].GetID() << endl;
		fout << lo.loanList[i].GetItemID() << endl;
		fout << lo.loanList[i].GetPatronID() << endl;
		fout << lo.loanList[i].GetYear() << endl;
		fout << lo.loanList[i].GetMonth() << endl;
		fout << lo.loanList[i].GetDay() << endl;
		fout << lo.loanList[i].GetHour() << endl;
		fout << lo.loanList[i].GetMin() << endl;
		fout << lo.loanList[i].GetStatus() << endl;
		fout << lo.loanList[i].GetRecheck() << endl;
	}
	
	if((pat.patronList.size() > 0) || (lib.itemList.size() > 0) || (lo.loanList.size() > 0)) {		//only if save data exists
		fout << "9" << endl;	//marks end of save file for later input
	}
	
	//empty vectors
	pat.patronList.clear();
	lo.loanList.clear();
	fout.close();	//close outstream
	
	return 0;
}
