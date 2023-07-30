//function definitions of dvd

#include <iostream>
using namespace std;
#include "dvd.h"
#include "libraryitem.h"

DVD::DVD(int id, double cost, string stat, int length, string title, string category, int hour, int minute, string studio, int year, int month, int day) : LibraryItem(id, cost, stat, length, title) {
	cat = category;
	h = hour;
	min = minute;
	stu = studio;
	y = year;
	m = month;
	d = day;
}

void DVD::SetCat(string category) {cat = category;}
void DVD::SetTime(int hour, int minute) {
	h = hour;
	min = minute;
}
void DVD::SetStudio(string studio) {stu = studio;}
void DVD::SetDate(int year, int month, int day) {
	y = year;
	m = month;
	d = day;
}

string DVD::GetCat() {return cat;}
int DVD::GetHour() {return h;}
int DVD::GetMin() {return min;}
string DVD::GetStudio() {return stu;}
int DVD::GetYear() {return y;}
int DVD::GetMonth() {return m;}
int DVD::GetDay() {return d;}

void DVD::Print() {
	cout << "Item Type: DVD" << endl;
	cout << "ID: " << id << endl;
	cout << "Title: " << t << endl;
	cout << "Studio: " << stu << endl;
	cout << "Category: " << cat << endl;
	cout << "Release Date: " << m << "/" << d << "/" << y << endl;
	cout << "Run Time: " << h << "h " << min << "m" << endl;
	cout << "Status: " << stat << endl;
	cout << "Loan Period: " << period << endl;
	cout << endl;
}
