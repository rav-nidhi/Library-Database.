//class defintion for libraryitems

#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <vector>
using namespace std;
#include "libraryitem.h"

class LibraryItems {
	public:
		LibraryItems();
		~LibraryItems();
		
		void Load();
		void Store();
		void AddItem();
		void DelItem();
		void EditItem();
		int FindItem();
		void PrintAll();
		void PrintDetails();
		void CleanUp();
		
		vector<LibraryItem*> itemList;		//points to book, cd, or dvd
};

#endif
