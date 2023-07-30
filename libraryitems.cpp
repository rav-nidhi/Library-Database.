//function definitions of library items (with a vector of library item object pointers)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <typeinfo>
using namespace std;
#include "libraryitems.h"
#include "libraryitem.h"
#include "book.h"
#include "audiocd.h"
#include "dvd.h"


LibraryItems::LibraryItems() {		//when program begins (constructor)
	Load();
}

LibraryItems::~LibraryItems() {		//when program ends (destructor)
	Store();
	CleanUp();
}

void LibraryItems::Load() {		//load data from savefile
	ifstream fin;
	int id;
	double cost;
	string stat;
	int period;		//loan period
	string a;	//artist/author
	string title;
	long int isbn;
	string cat;		//category/genre
	int year, month, day;	//release date
	int tracks;		//number of tracks
	int hour, min;		//run time
	string studio;
	int type;	//book, cd, or dvd
	
	fin.open("libraryitems.txt");	//open file with data of all items
	if(fin.fail()) {	//check if opening fails
		ofstream fout;
		fout.open("libraryitems.txt");		//create file
		fout.close();
	}
	else {
		fin >> type;	//receive type of item
		while(type != 9) {
			switch(type) {
				case 1:		//book
					fin >> id;
					fin >> cost;
					fin.ignore();
					getline(fin, stat);
					fin >> period;
					fin.ignore();
					getline(fin, a);
					getline(fin, title);
					fin >> isbn;
					fin.ignore();
					getline(fin, cat);
					itemList.push_back(new Book(id, cost, stat, period, a, title, isbn, cat));
					
					break;
				
				case 2:		//cd			
					fin >> id;
					fin >> cost;
					fin.ignore();
					getline(fin, stat);
					fin >> period;
					fin.ignore();
					getline(fin, a);
					getline(fin, title);
					fin >> tracks;
					fin >> year;
					fin >> month;
					fin >> day;
					fin.ignore();
					getline(fin, cat);
					itemList.push_back(new AudioCD(id, cost, stat, period, a, title, tracks, year, month, day, cat));
					
					break;
					
				case 3:		//dvd
					fin >> id;
					fin >> cost;
					fin.ignore();
					getline(fin, stat);
					fin >> period;
					fin.ignore();
					getline(fin, title);
					getline(fin, cat);
					fin >> hour >> min;
					fin.ignore();
					getline(fin, studio);
					fin >> year >> month >> day;
					itemList.push_back(new DVD(id, cost, stat, period, title, cat, hour, min, studio, year, month, day));
					
					break;
			};
			fin >> type;
		}
		fin.close();
	}
}

void LibraryItems::AddItem() {
	int id;
	double cost;
	string status;
	int period;		//loan period
	string a;	//artist/author
	string title;
	long int isbn;
	string cat;		//category/genre
	int year, month, day;	//release date
	int tracks;		//number of tracks
	int hour, min;		//run time
	string studio;
	int type;	//book, cd, or dvd
	
	bool dupeID = true;
    while (dupeID) {	//prompt for id
        cout << "Enter a 6-digit id for new item: ";
        cin >> id;
        while ((id < 100000) || (id > 999999)) {
            cout << "Please enter a valid ID: ";
            cin >> id;
        }
		
		if(itemList.size() == 0) {
            dupeID = false;
			break;
        }
		
		for (int i = 0; i < itemList.size(); i++) {
            if(itemList[i]->GetID() == id)
            {
                cout << "This item id is already being used." << endl;
				dupeID = true;
                break;
            }
			else {
                dupeID = false;
            }
        }
    }
	
	cout << "Enter price of item: ";
	cin >> cost;
	
	cout << "Enter status of item (In, Out, or Lost): ";
	cin >> status;
	while(status != "In" && status != "Out" && status != "Lost") {
		cout << "Please enter a valid status with proper capitaliation." << endl;
		cout << "Options are In, Out, or Lost: ";
		cin >> status;
	}
	
	cout << "Enter maximum loan period: ";
	cin >> period;
	
	cout << "Item Type: " << endl;
	cout << "1 - Book" << endl;
	cout << "2 - Audio CD" << endl;
	cout << "3 - DVD" << endl;
	cout << "Enter choice: ";
	cin >> type;
	while(type < 1 || type > 3) {
		cout << "Options are 1, 2, or 3: ";
		cin >> type;
	}
	
	bool dupeISBN = true;
	bool dupeFound = false;
	LibraryItem* add;
	switch(type) {
		case 1:		//new book
			//prompt for isbn
			cout << "Enter a 13-digit ISBN for new book: ";
			cin >> isbn;
			while ((isbn < 1000000000000) || (isbn > 9999999999999)) {
				cout << "Please enter a valid ISBN: ";
				cin >> isbn;
			}
			
			cin.ignore();
			cout << "Enter title of new book: ";	//prompt for title
			getline(cin, title);
			cout << "Enter author of new book: ";	//prompt for author
			getline(cin, a);
			cout << "Enter book category: ";
			getline(cin, cat);
			
			add = new Book(id, cost, status, period, a, title, isbn, cat);
			break;
		
		case 2:		//new Audio CD
			cin.ignore();
			cout << "Enter title of new audio CD: ";	//prompt for title
			getline(cin, title);
			cout << "Enter artist of new audio CD: ";	//prompt for author
			getline(cin, a);
			cout << "Enter audio genre: ";
			getline(cin, cat);
			cout << "Enter number of tracks on CD: ";
			cin >> tracks;
			
			cout << "Enter year of release: ";
			cin >> year;
			while(year > 2023) {
				cout << "Invalid year. Only enter years that have occured: ";
				cin >> year;
			}
			
			cout << "Enter month of release (1 to 12): ";
			cin >> month;
			while(month < 1 || month > 12) {
				cout << "Invalid month. Must be between 1 and 12: ";
				cin >> month;
			}
			cout << "Enter day of release (1 to 31): ";
			cin >> day;
			while(day < 1 || day > 31) {
				cout << "Invalid date. Must be between 1 and 31: ";
				cin >> day;
			}
			
			add = new AudioCD(id, cost, status, period, a, title, tracks, year, month, day, cat);
			break;
			
		case 3:		//new dvd
			cin.ignore();
			cout << "Enter title of new DVD: ";	//prompt for title
			getline(cin, title);
			cout << "Enter DVD category: ";
			getline(cin, cat);
			cout << "Enter DVD studio: ";
			getline(cin, studio);
			
			cout << "Enter DVD run time (hours, then minutes): ";
			cin >> hour >> min;
			while(min < 1 || min > 59) {
				cout << "Invalid minute input. Must be between 1 and 59: ";
				cin >> min;
			}
			while(hour < 0) {
				cout << "Invalid hour input. Cannot be less than 0: ";
				cin >> hour;
			}
			
			cin.ignore();
			cout << "Enter year of release: ";
			cin >> year;
			while(year > 2023) {
				cout << "Invalid year. Only enter years that have occured: ";
				cin >> year;
			}
			cout << "Enter month of release (1 to 12): ";
			cin >> month;
			while(month < 1 || month > 12) {
				cout << "Invalid month. Must be between 1 and 12: ";
				cin >> month;
			}
			cout << "Enter day of release (1 to 31): ";
			cin >> day;
			while(day < 1 || day > 31) {
				cout << "Invalid date. Must be between 1 and 31: ";
				cin >> day;
			}
			
			add = new DVD(id, cost, status, period, title, cat, hour, min, studio, year, month, day);
			break;
	};
	itemList.push_back(add);
}

void LibraryItems::DelItem() {
	int pos = FindItem();		//Search item list vector for matching object using Find Item Method
	cout << itemList[pos]->GetTitle() << " has been successfully removed from the database." << endl;
	itemList.erase(itemList.begin() + pos);	//erase object from vector
}

void LibraryItems::EditItem() {
	int choice, typeChoice, dateChoice;
	int found = FindItem();		//Search item list vector for matching object using Find Item Method
	if(found == -1) {
		return;
	}

	cout << "What would you like to edit?: " << endl;	//prompt user for info to change
    cout << "1 - ID" << endl;
    cout << "2 - Cost" << endl;
    cout << "3 - Status" << endl;
    cout << "4 - Loan Period" << endl;
	cout << "5 - Book-specific Data" << endl;
	cout << "6 - Audio CD-specific Data" << endl;
	cout << "7 - DVD-specific Data" << endl;
	cout << "Enter choice: ";
    cin >> choice;
    while ((choice < 1) || (choice > 7)) {
        cout << "Please enter a valid option: ";
        cin >> choice;
    }

    bool dupe = true;
    int newID;
	double newCost;
	string newStatus;
	int newPeriod;		//loan period
	string newA;	//artist/author
	string newTitle;
	long int newISBN;
	string newCat;		//category/genre
	int newYear, newMonth, newDay;	//release date
	int newTracks;		//number of tracks
	int newHour, newMin;		//run time
	string newStudio;

    switch (choice) {
        case 1:
            while (dupe) {
                cout << "Enter a new 6-digit item id: ";
                cin >> newID;
				while ((newID < 100000) || (newID > 999999)) {
                    cout << "Please enter a valid ID: ";
                    cin >> newID;
                }
                
				for (int i = 0; i < itemList.size(); i++) {
                    if (itemList[i]->GetID() != newID) {
                        dupe = false;
                    }
                    else if(itemList[i]->GetID() == newID)
                    {
						dupe = true;
                        cout << "This item id is already in use." << endl;
                        break;
                    }
                }
            }
            itemList[found]->SetID(newID);	//Match object values to new values
            break;
        case 2:
            cout << "Enter a new cost for item: ";
            cin >> newCost;
            itemList[found]->SetCost(newCost);	//Match object values to new values
            break;
			
		case 3:
            cout << "Enter a new item status (In, Out, or Lost): ";
			cin >> newStatus;
			while(newStatus != "In" && newStatus != "Out" && newStatus != "Lost") {
				cout << "Please enter a valid status with proper capitaliation." << endl;
				cout << "Options are In, Out, or Lost: ";
				cin >> newStatus;
			}
            itemList[found]->SetTitle(newTitle);	//Match object values to new values
            break;
			
        case 4:
            cout << "Enter a new loan period: ";
			cin >> newPeriod;
			itemList[found]->SetPeriod(newPeriod);
            break;
			
        case 5: {
            cout << "What book information would you like to edit?" << endl;
			cout << "1 - Title" << endl;
			cout << "2 - Author" << endl;
			cout << "3 - ISBN" << endl;
			cout << "4 - Category" << endl;
			cout << "5 - Return to Previous Menu" << endl;
			cout << "Enter choice: ";
			cin >> typeChoice;
			while(typeChoice < 1 || typeChoice > 5) {
				cout << "Invalid input. Choice must be between 1 and 5: ";
				cin >> typeChoice;
			}
			
			Book *temp = dynamic_cast<Book*>(itemList[found]);
			
			switch(typeChoice) {
				case 1:
					cout << "Enter a new book title: ";
					cin.ignore();
					getline(cin, newTitle);
					temp->SetTitle(newTitle);		//Match object values to new values
					break;
					
				case 2:
					cout << "Enter a new book author: ";
					cin.ignore();
					getline(cin, newA);
					temp->SetAuthor(newA);	//Match object values to new values
					break;
					
				case 3:
					cout << "Enter a new book ISBN: ";
					cin >> newISBN;
					
					if ((newISBN < 1000000000000) || (newISBN > 9999999999999)) {
						cout << "Please enter a valid 13-digit ISBN: ";
						cin >> newISBN;
					}
					temp->SetIsbn(newISBN);	//Match object values to new values
					break;
				
				case 4:
					cout << "Enter a new book category: ";
					cin.ignore();
					getline(cin, newCat);
					temp->SetCat(newCat);
					break;
				
				case 5:
					break;
			};
			break;
		}
		case 6: {
            cout << "What audio CD information would you like to edit?" << endl;
			cout << "1 - Title" << endl;
			cout << "2 - Artist" << endl;
			cout << "3 - Number of Tracks" << endl;
			cout << "4 - Release Date" << endl;
			cout << "5 - Genre" << endl;
			cout << "6 - Return to Previous Menu" << endl;
			cout << "Enter choice: ";
			cin >> typeChoice;
			while(typeChoice < 1 || typeChoice > 6) {
				cout << "Invalid input. Choice must be between 1 and 6: ";
				cin >> typeChoice;
			}
            
			AudioCD *temp = dynamic_cast<AudioCD*>(itemList[found]);
			
			switch(typeChoice) {
				case 1:
					cout << "Enter a new CD title: ";
					cin.ignore();
					getline(cin, newTitle);
					temp->SetTitle(newTitle);		//Match object values to new values
					break;
				
				case 2:
					cout << "Enter a new CD artist: ";
					cin.ignore();
					getline(cin, newA);
					temp->SetArtist(newA);	//Match object values to new values
					break;
				
				case 3:
					cout << "Enter new number of tracks on CD: ";
					cin >> newTracks;
					temp->SetTracks(newTracks);
					break;
				
				case 4:
					cout << "Which do you want to edit?" << endl;
					cout << "1 - Year" << endl;
					cout << "2 - Month" << endl;
					cout << "3 - Day" << endl;
					cout << "4 - Return to Previous Menu" << endl;
					cout << "Enter choice: ";
					cin >> dateChoice;
					while(dateChoice < 1 || dateChoice > 4) {
						cout << "Invalid input. Number must be between 1 and 4: ";
						cin >> dateChoice;
					}
					
					switch(dateChoice) {
						case 1:
							cout << "Enter new release year: ";
							cin >> newYear;
							temp->SetDate(newYear, temp->GetMonth(), temp->GetDay());
							break;
							
						case 2:
							cout << "Enter new release month (1 to 12): ";
							cin >> newMonth;
							temp->SetDate(temp->GetYear(), newMonth, temp->GetDay());
							break;
						
						case 3:
							cout << "Enter new release day (1 to 31): ";
							cin >> newDay;
							temp->SetDate(temp->GetYear(), temp->GetMonth(), newDay);
							break;
						
						case 4:
							break;
					};
					break;
				
				case 5:
					cout << "Enter a new audio genre: ";
					cin.ignore();
					getline(cin, newCat);
					temp->SetGenre(newCat);
					break;
				
				case 6:	
					break;
			};
			break;
		}
		case 7: {
			cout << "What DVD information would you like to edit?" << endl;
			cout << "1 - Title" << endl;
			cout << "2 - Category" << endl;
			cout << "3 - Studio" << endl;
			cout << "4 - Release Date" << endl;
			cout << "5 - Run Time" << endl;
			cout << "6 - Return to Previous Menu" << endl;
			cout << "Enter choice: ";
			cin >> typeChoice;
			while(typeChoice < 1 || typeChoice > 6) {
				cout << "Invalid input. Choice must be between 1 and 6: ";
				cin >> typeChoice;
			}
			
			DVD *temp = dynamic_cast<DVD*>(itemList[found]);
			
			switch(typeChoice) {
				case 1:
					cout << "Enter a new CD title: ";
					cin.ignore();
					getline(cin, newTitle);
					temp->SetTitle(newTitle);		//Match object values to new values
					break;
				
				case 2:
					cout << "Enter a new DVD category: ";
					cin.ignore();
					getline(cin, newCat);
					temp->SetCat(newCat);
					break;
					
				case 3:
					cout << "Enter a new studio: ";
					cin.ignore();
					getline(cin, newStudio);
					temp->SetStudio(newStudio);
					break;
				
				case 4:
					cout << "Which do you want to edit?" << endl;
					cout << "1 - Year" << endl;
					cout << "2 - Month" << endl;
					cout << "3 - Day" << endl;
					cout << "4 - Return to Previous Menu" << endl;
					cout << "Enter choice: ";
					cin >> dateChoice;
					while(dateChoice < 1 || dateChoice > 4) {
						cout << "Invalid input. Number must be between 1 and 4: ";
						cin >> dateChoice;
					}
					
					switch(dateChoice) {
						case 1:
							cout << "Enter new release year: ";
							cin >> newYear;
							temp->SetDate(newYear, temp->GetMonth(), temp->GetDay());
							break;
							
						case 2:
							cout << "Enter new release month (1 to 12): ";
							cin >> newMonth;
							temp->SetDate(temp->GetYear(), newMonth, temp->GetDay());
							break;
						
						case 3:
							cout << "Enter new release day (1 to 31): ";
							cin >> newDay;
							temp->SetDate(temp->GetYear(), temp->GetMonth(), newDay);
							break;
						
						case 4:
							break;
					};
					break;
				case 5:
					cout << "Which do you want to edit?" << endl;
					cout << "1 - Hour" << endl;
					cout << "2 - Minute" << endl;
					cout << "3 - Return to Previous Menu" << endl;
					cout << "Enter choice: ";
					cin >> dateChoice;
					while(dateChoice < 1 || dateChoice > 3) {
						cout << "Invalid input. Number must be between 1 and 3: ";
						cin >> dateChoice;
					}
					
					switch(dateChoice) {
						case 1:
							cout << "Enter new release hour: ";
							cin >> newHour;
							temp->SetTime(newHour, temp->GetMin());
							break;
							
						case 2:
							cout << "Enter new release minute (1 to 59): ";
							cin >> newMin;
							temp->SetTime(temp->GetHour(), newMin);
							break;
						
						case 3:
							break;
					};
					break;
				case 6:
					break;
			};
			break;
		}
    };
    cout << endl;
}

int LibraryItems::FindItem() {
	int findID;
    int found = -1;
    
	if(itemList.size() == 0) {
		cout << "No items found in database." << endl << endl;
	}
	else {
		while (found == -1) {	//repeat until id match is found
			cout << "Enter the id number of the item to find: ";	//prompt for id
			cin >> findID;
			while ((findID < 100000) || (findID > 999999)) {
				cout << "Please enter a valid 6-digit ID: ";
				cin >> findID;
			}
			
			for (int i = 0; i < itemList.size(); i++) {
				if (itemList[i]->GetID() == findID) {	//if match, return position in vector
					found = i;
					break;
				}
			}
			if (found == -1) {	//if no match, return that book does not exist
				cout << "No items with that ID found." << endl;
			}
		}
	}
	
	cout << "Item Found: " << itemList[found]->GetTitle() << endl;
	return found;
}

void LibraryItems::PrintAll() {		//output all item data
	if(itemList.size() == 0) {
		cout << "No items found in database." << endl << endl;
	}
	else {
		for(auto it : itemList) {
			if(typeid(*it) == typeid (Book)) {
				dynamic_cast<Book*>(it)->Print();
			}
			else if(typeid(*it) == typeid(AudioCD)) {
				dynamic_cast<AudioCD*>(it)->Print();
			}
			else if(typeid(*it) == typeid(DVD)) {
				dynamic_cast<DVD*>(it)->Print();
			}
		}
	}
}

void LibraryItems::PrintDetails() {		//output data for one item
	int i = FindItem();		//Search item list vector for matching object using Find item Method
	cout << "Item Details: " << endl;	//print data values of object
	if(typeid(*itemList[i]) == typeid (Book)) {
		dynamic_cast<Book*>(itemList[i])->Print();
	}
	else if(typeid(*itemList[i]) == typeid(AudioCD)) {
		dynamic_cast<AudioCD*>(itemList[i])->Print();
	}
	else if(typeid(*itemList[i]) == typeid(DVD)) {
		dynamic_cast<DVD*>(itemList[i])->Print();
	}
}

void LibraryItems::Store() {	//store data in a savefile
	ofstream fout;
	fout.open("libraryitems.txt", ofstream::out | ofstream::trunc);;	//file for output
	if(fout.fail()) {	//check if file was opened correctly
		cout << "Item output file could not open" << endl;
		return;
	}
	
    for(auto it : itemList) {		//use iterator to sort through vector
		if(typeid(*it) == typeid(Book)) {
			fout << "1" << endl;
		}
		else if (typeid(*it) == typeid(AudioCD)) {
            fout << "2" << endl;
        }
        else if (typeid(*it) == typeid(DVD)) {
            fout << "3" << endl;
        }
		
		//output common data
		fout << it->GetID() << endl;
        fout << it->GetCost() << endl;
        fout << it->GetStatus() << endl;
        fout << it->GetPeriod() << endl;
		
		if (typeid(*it) == typeid(Book)) {		//book data
            Book* book = dynamic_cast<Book*>(it);
            fout << book->GetAuthor() << endl;
            fout << book->GetTitle() << endl;
            fout << book->GetIsbn() << endl;
            fout << book->GetCat() << endl;
		}
		else if(typeid(*it) == typeid(AudioCD)) {	//audio cd data
            AudioCD* cd = dynamic_cast<AudioCD*>(it);
            fout << cd->GetArtist() << endl;
            fout << cd->GetTitle() << endl;
            fout << cd->GetTracks() << endl;
            fout << cd->GetYear() << endl;
            fout << cd->GetMonth() << endl;
            fout << cd->GetDay() << endl;
            fout << cd->GetGenre() << endl;
		}
		else if(typeid(*it) == typeid(DVD)) {	//dvd data
			DVD* dvd = dynamic_cast<DVD*>(it);
            fout << dvd->GetTitle() << endl;
            fout << dvd->GetCat() << endl;
            fout << dvd->GetHour() << endl;
            fout << dvd->GetMin() << endl;
            fout << dvd->GetStudio() << endl;
            fout << dvd->GetYear() << endl;
            fout << dvd->GetMonth() << endl;
            fout << dvd->GetDay() << endl;
        }   
    }
	fout << "9" << endl;	//mark end of data
	fout.close();
}

void LibraryItems::CleanUp() {		//deallocation and erase vector
	for(auto it=itemList.begin(); it != itemList.end(); it++) {		//Use iterator to sort through vector
		delete *it;		//deallocate
	}
	itemList.clear();	//clear vector
}
