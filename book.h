//class defintion for book

#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;
#include "libraryitem.h"

class Book : public LibraryItem {
	public:
		Book(int id, double cost, string stat, int length, string author, string title, long int bookIsbn, string category);
		void SetAuthor(string author);
		void SetIsbn(long int bookIsbn);
		void SetCat(string category);
		
		string GetAuthor() const;
		long int GetIsbn() const;
		string GetCat() const;
		void Print();
		
	private:
		string a;
		long int isbn;
		string cat;
};

#endif
