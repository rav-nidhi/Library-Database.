//function definitions of patron

#include <iostream>
using namespace std;
#include "patron.h"

Patron::Patron(string name, int id, double balance, int items) {
	n = name;
	patronID = id;
	bal = balance;
	itemsOut = items;
}

void Patron::SetID(int id) {patronID = id;}
void Patron::SetName(string name) {n = name;}
void Patron::SetBal(double balance) {bal = balance;}
void Patron::SetItems(int items) {itemsOut = items;}

int Patron::GetID() const {return patronID;}
string Patron::GetName() const {return n;}
double Patron::GetBal() const {return bal;}
int Patron::GetItems() const {return itemsOut;}
