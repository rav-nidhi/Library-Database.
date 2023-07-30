//function definitions of library item

#include <iostream>
using namespace std;
#include "libraryitem.h"

LibraryItem::LibraryItem(int libID, double libCost, string status, int length, string title) {
	id = libID;
	cost = libCost;
	stat = status;
	period = length;
	t = title;
}

void LibraryItem::SetID(int libID) {id = libID;}
void LibraryItem::SetCost(double libCost) {cost = libCost;}
void LibraryItem::SetStatus(string status) {stat = status;}
void LibraryItem::SetPeriod(int length) {period = length;}
void LibraryItem::SetTitle(string title) {t=title;}

int LibraryItem::GetID() {return id;}
double LibraryItem::GetCost() {return cost;}
string LibraryItem::GetStatus() {return stat;}
int LibraryItem::GetPeriod() {return period;}
string LibraryItem::GetTitle() {return t;}

/*ostream& operator<<(ostream& st, LibraryItem& it) {
	it.rawprint();
	return st;
}*/
