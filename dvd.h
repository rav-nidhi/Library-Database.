/*
 * Name: Nidhi Ravala
 * EUID: nsr0065
 * Date: 18 April 2023
 * Course: CSCE 1040
 * Assignment: Homework 4
 */
 
//Program Description: Class defintion for dvd

#ifndef DVD_H
#define DVD_H

#include <string>
using namespace std;
#include "libraryitem.h"

class DVD : public LibraryItem {
	public:
		DVD(int id, double cost, string stat, int period, string title, string category, int hour, int minute, string studio, int year, int month, int day);
		
		void SetCat(string category);
		void SetTime(int hour, int minute);
		void SetStudio(string studio);
		void SetDate(int year, int month, int day);
		void Print();
		
		string GetCat();
		int GetHour();
		int GetMin();
		string GetStudio();
		int GetYear();
		int GetMonth();
		int GetDay();
		
	private:
		string cat;
		int h, min;
		string stu;
		int y, m, d;
};

#endif