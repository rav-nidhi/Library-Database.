/*
 * Name: Nidhi Ravala
 * EUID: nsr0065
 * Date: 18 April 2023
 * Course: CSCE 1040
 * Assignment: Homework 4
 */
 
//Program Description: Class defintion for library item

#ifndef LIBITEM_H
#define LIBITEM_H

#include <string>
#include <iomanip>
using namespace std;

class LibraryItem {
	public:
		LibraryItem(int libID, double libCost, string status, int length, string title);
		virtual ~LibraryItem() = default;
		
		void SetID(int libID);
		void SetCost(double libCost);
		void SetStatus(string status);
		void SetPeriod(int length);
		void SetTitle(string title);
		
		int GetID();
		double GetCost();
		string GetStatus();
		int GetPeriod();
		string GetTitle();
		
		virtual void Print() = 0;
		//friend ostream& operator<< (ostream& st, LibraryItem& it);
		
	protected:
		int id;
		double cost;
		string stat;
		int period;
		string t;
	
};

#endif