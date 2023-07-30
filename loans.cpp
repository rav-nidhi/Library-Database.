/*
 * Name: Nidhi Ravala
 * EUID: nsr0065
 * Date: 18 April 2023
 * Course: CSCE 1040
 * Assignment: Homework 4
 */
 
//Program Description: Function definitions of loans (with a vector of loan objects)

#include <iostream>
#include <iomanip>
#include <time.h>
#include <cmath>
using namespace std;
#include "loan.h"
#include "libraryitems.h"
#include "book.h"
#include "audiocd.h"
#include "dvd.h"
#include "patrons.h"
#include "loans.h"

void Loans::CheckIn(LibraryItems &lib, Patrons &pat) {	//delete loan
	int loc = FindLoan();		//Search loan list vector for matching loan object using Find Loan Method
	double fine = 0;
	
	if(loc != -1) {
		UpdateStatus(pat); //check if loan is overdue
	
		for(int i=0; i<lib.itemList.size(); i++) {	//search vector for book
			if(lib.itemList[i]->GetID() == loanList[loc].GetItemID()) {
				if(lib.itemList[i]->GetStatus() == "Out") {		//keep book status the same if lost or in repair
					lib.itemList[i]->SetStatus("In");	//update book status to in
				}
			}
		}
		
		for(int i=0; i<pat.patronList.size(); i++) {	//search vector for patron
			if(pat.patronList[i].GetID() == loanList[loc].GetPatronID()) {
				pat.patronList[i].SetItems(pat.patronList[i].GetItems() - 1);	//update patron's number of books out
				pat.patronList[i].SetBal(pat.patronList[i].GetBal() + fine);	//add fine to balance
			}
		}
		
		loanList.erase(loanList.begin() + loc);	//erase loan object from vector
		cout << "Loan successfully removed from database." << endl;
	}
}

void Loans::CheckOut(LibraryItems &lib, Patrons &pat) {	//add loan
	int lID, pID, libID;	//loan, patron, and item ids
	string stat; 
	int recheck;
	
	bool dupeID = true;		//variable to check if id is already being used
    while (dupeID) {
        cout << "Enter a 6-digit id for new loan: ";	//prompt for id
        cin >> lID;
        while ((lID < 100000) || (lID > 999999)) {	//check that id is 6 digits
            cout << "Please enter a valid ID: ";
            cin >> lID;
        }
        if(loanList.size() == 0)	//end loop if this is the first loan object
        {
            dupeID = false;
			break;
        }
        for (int i = 0; i < loanList.size(); i++) {		//search vector for loan
            if(loanList[i].GetID() == lID)	//if id is found, prompt for a new one
            {
                cout << "This loan id is already being used." << endl;
				dupeID = true;
                break;
            }
			else {
                dupeID = false;
            }
        }
    }
	
	bool out = true;	//variable to check if item is available
	int libLoc = -1;	//item location
	while(out) {
		cout << "Enter a 6-digit item id: ";	//prompt for item id
		cin >> libID;
		while (( libID < 100000) || ( libID > 999999)) {	//check that id is 6 digits
			cout << "Please enter a valid ID: ";
			cin >> libID;
		}
		for(int i=0; i<lib.itemList.size(); i++) {
			if(lib.itemList[i]->GetID() == libID) {
				libLoc = i;
				break;
			}
		}
		if(lib.itemList[libLoc]->GetStatus() == "Out") {	//check that item is available
			cout << "This item is unavailable." << endl;
			out = true;
		}
		else {
			out = false;
		}
	}
	
	int ploc;	//patron locatio in vector
	bool six = true;	//variable to check if patron has less than 6 books
	while(six) {
		cout << "Enter a 6-digit patron id: ";
		cin >> pID;
		while ((pID < 100000) || (pID > 999999)) {	//check that id is 6 digits
			cout << "Please enter a valid ID: ";
			cin >> pID;
		}
		
		for(int i=0; i<pat.patronList.size(); i++) {	//search vector for patron
			if(pat.patronList[i].GetID() == pID) {
				ploc = i;
			}
		}
		if(pat.patronList[ploc].GetItems() > 6) {	//if patron has 6 or more items, prompt for new id
			six = true;
			cout << "This patron cannot check out any more books." << endl;
		}
		else if(pat.patronList[ploc].GetItems() < 6){
			six = false;
		}
	}
	
	time_t rn = time(0);	//current date and time
	struct tm* newTime;
	int year, month, day, hour, minute;
	newTime = localtime(&rn);
	year = static_cast<int>(newTime->tm_year) + 1900;	//static cast to integers for storage
	month = static_cast<int>(newTime->tm_mon) + 1;
	day = static_cast<int>(newTime->tm_mday);
	day += lib.itemList[libLoc]->GetPeriod();
	hour = static_cast<int>(newTime->tm_hour);
	minute = static_cast<int>(newTime->tm_min);
	
	if(day > 31) {		//switch months if day crosses 31
		day -= 30;
		month++;
	}
	
	cout << "Enter loan's current status (Overdue or Normal): ";	//prompt for status
	cin >> stat;
	while(stat != "Overdue" && stat != "Normal") {	//check that status is valid
		cout << "Please enter a valid status with proper capitaliation." << endl;
		cout << "Options are Overdue or Normal: ";
		cin >> stat;
	}
	
	cout << "Enter number of rechecks: ";	//prompt for number of rechecks
	cin >> recheck;
	while(recheck < 0 || recheck > 1) {		//check that count is 1 or 0
		cout << "Invalid input. Patrons may have up to 1 recheck: ";
		cin >> recheck;
	}
	
	Loan lo(lID, libID, pID, year, month, day, hour, minute, stat, recheck);	//create new loan object using intialization constructor
	loanList.push_back(lo);		//add object to vector
	
	for(int i=0; i<lib.itemList.size(); i++) {	//search vector for book
		if(lib.itemList[i]->GetID() == libID) {
			lib.itemList[i]->SetStatus("Out");	//update book status to out
		}
	}
	
	for(int i=0; i<pat.patronList.size(); i++) {	//search vector for patron
		if(pat.patronList[i].GetID() == pID) {
			pat.patronList[i].SetItems(pat.patronList[i].GetItems() + 1);	//update patron's number of books out
		}
	}
}

void Loans::PrintOverdue(Patrons &pat) {
	bool overdue = false;	//variable to determine if there are overdue loans
	
	for(int i=0; i<loanList.size(); i++) {	//search loan vector
		if(loanList[i].GetStatus() == "Overdue") {
			overdue = true;
			break;
		}
	}
	
	if(overdue) {
		cout << "List of all overdue loans: " << endl << endl;
		for(int i=0; i<loanList.size(); i++) {	//search loan list vector for overdue loans
			if(loanList[i].GetStatus() == "Overdue") {	//for every overdue loan--
				cout << "Loan ID: " << loanList[i].GetID() << endl;
				cout << "Item ID: " << loanList[i].GetItemID() << endl << endl;
				for(int j=0; j<pat.patronList.size(); j++) {	//--search patron list and print patron information
					if(loanList[i].GetPatronID() == pat.patronList[j].GetID()) {
						cout << "Patron Information:" << endl;
						cout << "Patron ID: " << pat.patronList[i].GetID() << endl;
						cout << "Name: " << pat.patronList[i].GetName() << endl;
						cout << "Fine Balance: $" << fixed << setprecision(2) << pat.patronList[i].GetBal() << endl;
						cout << "Books Checked Out: " << pat.patronList[i].GetItems() << endl;
						cout << endl;
					}
				}
			}
		}
	}
	else {
		cout << "No overdue loans found." << endl;
	}
}

void Loans::PrintPatron(LibraryItems &lib, Patrons &pat) {
	int loc = pat.FindPatron();		//Search loan list vector for matching loan object using Find Loan Method
	int pID = pat.patronList[loc].GetID();
	int libID;
	cout << "Patron " << pat.patronList[loc].GetName() << " has " << pat.patronList[loc].GetItems() << " items checked out." << endl << endl;		//display number of books patron has
	if(pat.patronList[loc].GetItems() > 0) {
		cout << "List of Items and Statuses: " << endl;
		for(int i = 0; i<loanList.size(); i++) {	//search loan list vector for loans with matching patron ids
			if(pID == loanList[i].GetPatronID()) {
				libID = loanList[i].GetItemID();
			}
		}
		for(int j=0; j<pat.patronList[loc].GetItems(); j++) {		//for each item patron has
			if (lib.itemList[j]->GetID() == libID) {	//print book details
				if(typeid(*lib.itemList[j]) == typeid(Book)) {
					Book *temp = dynamic_cast<Book*>(lib.itemList[j]);
					cout << "Item type: Book" << endl;
					cout << "Title: " << temp->GetTitle() << endl;
					cout << "Author: " << temp->GetAuthor() << endl;
					cout << "ID: " << temp->GetID() << endl;
					cout << "Status: " << temp->GetStatus() << endl;
				}
				else if(typeid(*lib.itemList[j]) == typeid(AudioCD)) {		//print audio cd details
					AudioCD *temp = dynamic_cast<AudioCD*>(lib.itemList[j]);
					cout << "Item type: Audio CD" << endl;
					cout << "Title: " << temp->GetTitle() << endl;
					cout << "Author: " << temp->GetArtist() << endl;
					cout << "ID: " << temp->GetID() << endl;
					cout << "Status: " << temp->GetStatus() << endl;
				}
				else if(typeid(*lib.itemList[j]) == typeid(DVD)) {		//print dvd details
					DVD *temp = dynamic_cast<DVD*>(lib.itemList[j]);
					cout << "Item type: DVD" << endl;
					cout << "Title: " << temp->GetTitle() << endl;
					cout << "ID: " << temp->GetID() << endl;
					cout << "Status: " << temp->GetStatus() << endl;
				}
			}
			cout << endl;
		}
	}
}

void Loans::UpdateStatus(Patrons &pat) {
	int loc = FindLoan();	//use find loan to get location of loan in vector
	time_t rn = time(0);		//current time
	struct tm* currTime;
	int hourDiff, dayDiff;
	double fine = 0;
	int currYear, currMonth, currDay, currHour, currMin;
	int year, month, day, hour, min;
	currTime = localtime(&rn);
	currYear = static_cast<int>(currTime->tm_year) + 1900;	//static cast to integers for storage
	currMonth = static_cast<int>(currTime->tm_mon) + 1;
	currDay = static_cast<int>(currTime->tm_mday);
	currHour = static_cast<int>(currTime->tm_hour);
	currMin = static_cast<int>(currTime->tm_min);
	
	if(loc != -1) {
		year = loanList[loc].GetYear();	//get due date variables
		month = loanList[loc].GetMonth();
		day = loanList[loc].GetDay();
		hour = loanList[loc].GetHour();
		min = loanList[loc].GetMin();
		
		dayDiff = currDay - day;
		hourDiff = abs(currHour - hour);
		
		if(dayDiff > 0) {
			hourDiff += (dayDiff*24);	//convert to hours;
		}
		
		if(hourDiff >= 24) {	//if due date has passed, update status to overdue
			loanList[loc].SetStatus("Overdue");
			fine = (hourDiff/24) * 0.25;	//use patron id to add 25 cents to patron's balance for every 24 hours the book is overdue
		}
		else {
			loanList[loc].SetStatus("Normal");
		}
		
		cout << "Loan status is " << loanList[loc].GetStatus() << endl;
		for(int i=0; i<pat.patronList.size(); i++) {	//search vector for patron
			if(pat.patronList[i].GetID() == loanList[loc].GetPatronID()) {
				pat.patronList[i].SetBal(pat.patronList[i].GetBal() + fine);	//add fine to balance
				cout << "Patron has been fined $" << fine << "." << endl << endl;
			}
		}
	}
}

void Loans::ReCheck(LibraryItems &lib, Patrons &pat) {
	int loc = FindLoan();	//find loan location using find loan function
	int ploc;	//patron location in vector
	bool overdue = true;	//variable to check if patron has overdue books
	int i;
	
	time_t rn = time(0);	//current date and time
	struct tm* newTime;
	int year, month, day, hour, minute;
	int period;		//loan period
	
	for(i=0; i<pat.patronList.size(); i++) {	//find patron locaton in vector
		if(loanList[loc].GetPatronID() == pat.patronList[i].GetID()) {
			ploc = i;
		}
	}
	
	for(i = 0; i<loanList.size(); i++) {	//check if patron has overdue books besides the one they would like to recheck
		if((loanList[i].GetPatronID() == pat.patronList[ploc].GetID()) && (i != loc)) {
			if(loanList[i].GetStatus() == "Overdue") {
				overdue = true;
			}
			else {
				overdue = false;
			}
		}
		else {
			overdue = false;
		}
	}
	
	if(loanList[loc].GetRecheck() == 1) {	//only allow one recheck
		cout << "This loan has already been renewed once. This book cannot be rechecked again." << endl;
	}
	else if(pat.patronList[ploc].GetItems() > 6) {	//make sure patron doesn't have more than 6 books
		cout << "This patron has too many books checked out. They cannot recheck this book." << endl;
	}
	else if(pat.patronList[ploc].GetBal() > 0) {	//check for fines
		cout << "This patron has outstanding payments. They cannot recheck this book until they pay the fines." << endl;
	}
	else if(overdue) {	//check if patron has overdue books
		cout << "This patron has overdue books. They cannot recheck this book until the books are returned" << endl;
	}
	else {
		loanList[loc].SetRecheck(1);	//update recheck count
		
		for(int i=0; i<lib.itemList.size(); i++) {
			if(lib.itemList[i]->GetID() == loanList[loc].GetItemID()) {		//find loan period
				period = lib.itemList[i]->GetPeriod();
			}
		}
		
		//update due date and time
		newTime = localtime(&rn);
		year = static_cast<int>(newTime->tm_year) + 1900;	//static cast to integers for storage
		month = static_cast<int>(newTime->tm_mon) + 1;
		day = static_cast<int>(newTime->tm_mday) + period;
		hour = static_cast<int>(newTime->tm_hour);
		minute = static_cast<int>(newTime->tm_min);
		
		if(day > 31) {		//switch months if day crosses 31
			day -= 30;
			month++;
		}
		
		loanList[loc].SetDate(year, month, day);
		loanList[loc].SetTime(hour, minute);
		
		cout << "Loan successfully renewed." << endl;
		cout << "New Due Date and Time: " << month << "/" << day << "/" << year; 
		cout << " at " << hour << ":" << minute << "." << endl;
	}
}

void Loans::EditLoan(LibraryItems &lib, Patrons &pat) {
	int choice;
	int choice2;
	int found = FindLoan();	//Search loan list vector for matching loan object using Find Loan Method
	if(found != -1){
		cout << "What would you like to edit?: " << endl;	//prompt user for info to change
		cout << "1 - IDs" << endl;
		cout << "2 - Due Date and Time" << endl;
		cout << "3 - Status" << endl;
		cout << "4 - Times Rechecked" << endl;
		cout << "5 - Back to Main Menu" << endl;
		cin >> choice;
		if ((choice < 1) || (choice > 5)) {
			cout << "Please enter a valid option: ";
			cin >> choice;
		}

		bool dupe = true;
		int newlID, newlibID, newpID;		//loan, book, patron ids
		int month, day, year, hour, min;
		string newStatus;
		int newRC;

		switch (choice) {
			case 1:
				cout << "Which ID would you like to edit?" << endl;
				cout << "1 - Loan ID" << endl;
				cout << "2 - Item ID" << endl;
				cout << "3 - Patron ID" << endl;
				cout << "4 - Return to Previous Menu" << endl;
				cin >> choice2;
				while((choice2 < 1) || (choice2 > 4)) {
					cout << "Please enter a valid option: ";
					cin >> choice2;
				}
				
				switch(choice2) {
					case 1: 
						while(dupe) {
							cout << "Enter a new 6-digit loan id: ";
							cin >> newlID;
							while((newlID < 100000) || (newlID > 999999)) {
								cout << "Please enter a valid ID: ";
								cin >> newlID;
							}
							
							for (int i = 0; i < loanList.size(); i++) {
								if (loanList[i].GetID() != newlID) {
									dupe = false;
								}
								else {
									dupe = true;
									cout << "This loan id is already in use." << endl;
									break;
								}
							}
						}
						loanList[found].SetID(newlID);	//match object values to new values
						break;
					case 2:
						while (dupe) {
							cout << "Enter a new 6-digit item id: ";
							cin >> newlibID;
							while((newlibID < 100000) || (newlibID > 999999)) {
								cout << "Please enter a valid ID: ";
								cin >> newlibID;
							}
							
							for (int i = 0; i < lib.itemList.size(); i++) {
								if (lib.itemList[i]->GetID() != newlibID) {
									dupe = false;
								}
								else {
									dupe = true;
									cout << "This item id is already in use." << endl;
									break;
								}
							}
						}
						loanList[found].SetItemID(newlibID);	//match object values to new values
						break;
					case 3:
						while(dupe) {
						cout << "Enter a new 6-digit patron id: ";
						cin >> newpID;
						while((newpID < 100000) || (newpID > 999999)) {
							cout << "Please enter a valid ID: ";
							cin >> newpID;
						}
						
						for (int i = 0; i < pat.patronList.size(); i++) {
							if (pat.patronList[i].GetID() != newpID) {
								dupe = false;
							}
							else { 
								dupe = true;
								cout << "This loan id is already in use." << endl;
								break;
							}
						}
					}
					loanList[found].SetPatronID(newpID);	//match object values to new values
					break;
					case 4:
						break;
				};
				break;
				
			case 2:
				cout << "Which part of the Due Date and Time would you like to edit?" << endl;
				cout << "1 - Month" << endl;
				cout << "2 - Day" << endl;
				cout << "3 - Year" << endl;
				cout << "4 - Hour" << endl;
				cout << "5 - Minute" << endl;
				cout << "6 - Return to Previous Menu" << endl;
				cin >> choice2;
				while((choice2 < 1) || (choice2 > 6)) {
					cout << "Please enter a valid option: ";
					cin >> choice2;
				}
				
				switch(choice2) {
					case 1:		//new month
						cout << "Enter new month (1 to 12): ";
						cin >> month;
						while(month < 1 || month > 12) {
							cout << "Invalid month. Must be between 1 and 12: ";
							cin >> month;
						}
						loanList[found].SetDate(loanList[found].GetYear(), month, loanList[found].GetDay());
						break;
						
					case 2:
						cout << "Enter new day (1 to 31): ";
						cin >> day;
						while(day < 1 || day > 31) {
							cout << "Invalid date. Must be between 1 and 31: ";
							cin >> day;
						}
						loanList[found].SetDate(loanList[found].GetYear(), loanList[found].GetMonth(), day);
						break;
					
					case 3:
						cout << "Enter new year: ";
						cin >> year;
						while(year > 2023) {
							cout << "Invalid year. Only enter years that have occured: ";
							cin >> year;
						}
						loanList[found].SetDate(year, loanList[found].GetMonth(), loanList[found].GetDay());
						break;
					
					case 4:
						cout << "Enter new hour: ";
						cin >> hour;
						loanList[found].SetTime(hour, loanList[found].GetMin());
						break;
						
					case 5:
						cout << "Enter new minute (1 to 59): ";
						cin >> min;
						while(min < 1 || min > 59) {
							cout << "Invalid input. Must be between 1 and 59: ";
							cin >> min;
						}
						loanList[found].SetTime(loanList[found].GetHour(), min);
						break;
					
					case 6: 
						break;
				};
				break;
			
			case 3:
				cout << "Enter a new status: ";
				cin >> newStatus;
				while((newStatus != "Normal") && newStatus != "Overdue") {
					cout << "Please enter a valid status with proper capitaliation." << endl;
					cout << "Options are Overdue or Normal: ";
					cin >> newStatus;
				}
				loanList[found].SetStatus(newStatus);	//match object values to new values
				break;
			
			case 4:
				cout << "Enter new recheck count: ";
				cin >> newRC;
				while(newRC < 0 || newRC > 1) {		//check that count is 1 or 0
					cout << "Invalid input. Patrons may have up to 1 recheck: ";
					cin >> newRC;
				}
				loanList[found].SetRecheck(newRC);	//match object values to new values
				break;
			
			case 5:
				break;
		};
		cout << endl;
	}
}

int Loans::FindLoan() {
	int findID;
    int found = -1;
    
	while (found == -1) {	//repeat until match is found
        cout << "Enter the id number of the loan: ";	//prompt user for loan id
        cin >> findID;
        while ((findID < 100000) || (findID > 999999)) {
            cout << "Please enter a valid 6-digit ID: ";
            cin >> findID;
		}
        for (int i = 0; i < loanList.size(); i++) {	//search loan list for id
            if (loanList[i].GetID() == findID) {
                found = i;
				break;
            }
        }
        if (found == -1) {	//if no match is found
            cout << "No loans with that ID found." << endl;
		}
    }
	cout << "Loan Found. Book ID is " << loanList[found].GetItemID() << ", Patron ID is " << loanList[found].GetPatronID() << endl;
	return found;
}

void Loans::Report(LibraryItems &lib, Patrons &pat) {
	int loc = FindLoan();	//Use Find Loan method to find book ID and patron ID of lost book
	int libID = loanList[loc].GetItemID();
	int pID = loanList[loc].GetPatronID();
	double cost;
	
	if(loc != -1) {
		for(int i=0; i<lib.itemList.size(); i++) {	//find book
			if(libID == lib.itemList[i]->GetID()) {
				lib.itemList[i]->SetStatus("Lost");	//change book status to lost
				cost = lib.itemList[i]->GetCost();	//find cost of book
				cout << lib.itemList[i]->GetTitle() << " has been reported as lost." << endl;
				break;
			}
		}
		
		for(int i=0; i<pat.patronList.size(); i++) {	//find patron
			if(pID == pat.patronList[i].GetID()) {
				cost += pat.patronList[i].GetBal();		//include any prexisting fines
				pat.patronList[i].SetBal(cost);	//set fine balance of patron to cost of book + preexisting balance
				cout << pat.patronList[i].GetName() << " has been fined $" << cost << "." << endl;
				break;
			}
		}
	}
}
