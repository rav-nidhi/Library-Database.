/*
 * Name: Nidhi Ravala
 * EUID: nsr0065
 * Date: 18 April 2023
 * Course: CSCE 1040
 * Assignment: Homework 4
 */
 
//Program Description: Function definitions of loan

#include <iostream>
using namespace std;
#include "loan.h"

Loan::Loan(int id, int libID, int pID, int year, int month, int day, int hour, int minute, string status, int recheck) {
	loanID = id;
	itemID = libID;
	patronID = pID;
	y = year;
	m = month;
	d = day;
	h = hour;
	min = minute;
	stat = status;
	rc = recheck;
}

void Loan::SetID(int id) {loanID = id;}
void Loan::SetItemID(int libID) {itemID = libID;}
void Loan::SetPatronID(int pID) {patronID = pID;}
void Loan::SetDate(int year, int month, int day) {
	y = year;
	m = month;
	d = day;
}
void Loan::SetTime(int hour, int minute) {
	h = hour;
	min = minute;
}
void Loan::SetStatus(string status) {stat = status;}
void Loan::SetRecheck(int recheck) {rc = recheck;}

int Loan::GetID() {return loanID;}
int Loan::GetItemID() {return itemID;}
int Loan::GetPatronID() {return patronID;}
int Loan::GetDay() {return d;}
int Loan::GetYear() {return y;}
int Loan::GetMonth() {return m;}
int Loan::GetHour() {return h;}
int Loan::GetMin() {return min;}
string Loan::GetStatus() {return stat;}
int Loan::GetRecheck() {return rc;}