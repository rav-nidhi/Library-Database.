//function definitions of book

#include <iostream>
using namespace std;
#include "book.h"
#include "libraryitem.h"

Book::Book(int id, double cost, string stat, int length, string author, string title, long int bookIsbn, string category) : LibraryItem(id, cost, stat, length, title) {
	a = author;
	isbn = bookIsbn;
	cat = category;
}

void Book::SetAuthor(string author) {a = author;}
void Book::SetIsbn(long int bookIsbn) {isbn = bookIsbn;}
void Book::SetCat(string category) {cat = category;}

string Book::GetAuthor() const {return a;}
long int Book::GetIsbn() const {return isbn;}
string Book::GetCat() const {return cat;}

void Book::Print() {
	cout << "Item Type: Book" << endl;
	cout << "ID: " << id << endl;
	cout << "ISBN: " << isbn << endl;
	cout << "Title: " << t << endl;
	cout << "Author: " << a << endl;
	cout << "Category: " << cat << endl;
	cout << "Cost: $" << fixed << setprecision(2) << cost << endl;	//FIXME: add set precision
	cout << "Status: " << stat << endl;
	cout << "Loan Period: " << period << endl;
	cout << endl;
}
