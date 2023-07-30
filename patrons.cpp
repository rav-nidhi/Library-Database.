//function definitions of patrons (including a vector of patron objects)

#include <iostream>
#include <iomanip>
using namespace std;
#include "patron.h"
#include "patrons.h"

void Patrons::AddPatron() {
	int id, out;
	string name;
	double balance;
	
	bool dupeID = true;
    while (dupeID) {	//prompt user for id
        cout << "Enter a 6-digit id for new patron: ";
        cin >> id;
        while ((id < 100000) || (id > 999999)) {
            cout << "Please enter a valid ID: ";
            cin >> id;
        }
        if(patronList.size() == 0)
        {
            dupeID = false;
        }
        for (int i = 0; i < patronList.size(); i++) {
            if(patronList[i].GetID() == id)
            {
                cout << "This patron id is already being used." << endl;
				dupeID = true;
                break;
            }
			
			else {
                dupeID = false;
            }
        }
    }

    cin.ignore();
    cout << "Enter name of new patron: ";	//prompt user for name
    getline(cin, name);

    cout << "Enter fine balance of new patron: ";	//prompt user for fine balance
    cin >> balance;
	
	cout << "Enter number of items checked out by new patron: ";	//prompt user for items out
	cin >> out;
	while(out > 6) {
		cout << "Number of items checked out can't be more than 6." << endl;
		cout << "Enter number of items checked out by new patron: ";
		cin >> out;
	}

    Patron pat(name, id, balance, out);	//create new patron object
    patronList.push_back(pat);	//add object to vector of patrons
    cout << endl;
}

void Patrons::EditPatron() {
    int choice;
	int found = FindPatron();	//Search patron list vector for matching patron object using Find Patron method
	if(found != -1) {
		cout << "What would you like to edit?: " << endl;	//prompt user for info to change
		cout << "1 - ID" << endl;
		cout << "2 - Name" << endl;
		cout << "3 - Fine Balance" << endl;
		cout << "4 - Items Out" << endl;
		cin >> choice;
		if ((choice < 1) || (choice > 4)) {
			cout << "Please enter a valid option: ";
			cin >> choice;
		}

		bool dupe = true;
		int newID;
		string newName;
		double newBal;
		int newItems;

		switch (choice) {
			case 1:
				while (dupe) {
					cout << "Enter a new 6-digit patron id: ";	//prompt for new info
					cin >> newID;
					while ((newID < 100000) || (newID > 999999)) {
						cout << "Please enter a valid ID: ";
						cin >> newID;
					}
					for (int i = 0; i < patronList.size(); i++) {
						if (patronList[i].GetID() != newID) {
							dupe = false;
						}
						else if(patronList[i].GetID() == newID)
						{
							dupe = true;
							cout << "This patron id is already in use." << endl;
							break;
						}
					}
				}
				patronList[found].SetID(newID);	//match object values to new values
				break;
			case 2:
				cout << "Enter a new name for patron: ";	//prompt for new info
				cin.ignore();
				getline(cin, newName);
				patronList[found].SetName(newName);	//match object values to new values
				break;
			case 3:
				cout << "Enter a new fine balance for patron: ";	//prompt for new info
				cin >> newBal;
				patronList[found].SetBal(newBal);	//match object values to new values
				break;
			case 4:
				cout << "Enter a new number of items checked out by patron: ";	//prompt for new info
				cin >> newItems;
				if ((newItems < 0) || (newItems > 6)) {
					cout << "Number of items checked out must be between 0 and 6: ";
					cin >> newItems;
				}
				patronList[found].SetItems(newItems);	//match object values to new values
				break;
		}
	}
    cout << endl;
}

void Patrons::DelPatron() {
	int i = FindPatron();	//Search patron list vector for matching patron object using Find Patron method
	if(i != -1) {
		cout << patronList[i].GetName() << " has been successfully removed from the database." << endl;
		patronList.erase(patronList.begin() + i);	//erase object from vector
	}
}

int Patrons::FindPatron() {
	int findID;
    int found = -1;
    
	while (found == -1) {	//repeat until match is found
        cout << "Enter the id number of the patron: ";	//Prompt user for patron ID
        cin >> findID;
        while ((findID < 100000) || (findID > 999999)) {
            cout << "Please enter a valid 6-digit ID: ";
            cin >> findID;
		}
        for (int i = 0; i < patronList.size(); i++) {
            if (patronList[i].GetID() == findID) { //if ID matches, return position in vector
                found = i;
				break;
            }
        }
        if (found == -1) {	//if no ids match, return that patron does not exist
            cout << "No patrons with that ID found." << endl;
		}
    }
	
	cout << "Patron Found: " << patronList[found].GetName() << endl;
	return found;
}

void Patrons::PrintAll() {
	if(patronList.size() == 0) {
		cout << "ERROR: 0 Patrons Registered." << endl;
	}
	else {
		cout << "List of all patrons:" << endl << endl;
		for(int i = 0; i < patronList.size(); i++)	//For each object of Patron List vector
		{	//print patron info
			cout << "Patron ID: " << patronList[i].GetID() << endl;
			cout << "Name: " << patronList[i].GetName() << endl;
			cout << "Fine Balance: $" << fixed << setprecision(2) << patronList[i].GetBal() << endl;
			cout << "Items Checked Out: " << patronList[i].GetItems() << endl;
			cout << endl << endl;
		}
	}
}

void Patrons::PrintDetails() {
    int i = FindPatron();	//Search patron list vector for matching patron object using Find Patron method
    cout << "Details for Patron:" << endl << endl;	//Print all patron info
    cout << "Patron ID: " << patronList[i].GetID() << endl;
	cout << "Name: " << patronList[i].GetName() << endl;
	cout << "Fine Balance: $" << fixed << setprecision(2) << patronList[i].GetBal() << endl;
	cout << "Items Checked Out: " << patronList[i].GetItems() << endl;
	cout << endl;
}

void Patrons::PayFines() {	
	double pay;	//amount paid
	int i = FindPatron();	//Search patron list vector for matching patron object using Find Patron Method
	cout << "Patron's Balance is $" << fixed << setprecision(2) << patronList[i].GetBal() << "." << endl;	//print fine balance
	cout << "How much would you like to pay? ";		//prompt for amount paid
	cin >> pay;
	patronList[i].SetBal(patronList[i].GetBal()-pay);
	cout << "Patron's Balance is now $" << fixed << setprecision(2) << patronList[i].GetBal() << "." << endl;	//print new balance
}
