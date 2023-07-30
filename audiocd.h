/*
 * Name: Nidhi Ravala
 * EUID: nsr0065
 * Date: 18 April 2023
 * Course: CSCE 1040
 * Assignment: Homework 4
 */
 
//Program Description: Class defintion for audio cd

#ifndef CD_H
#define CD_H

#include <string>
using namespace std;
#include "libraryitem.h"

class AudioCD : public LibraryItem {
	public:
		AudioCD(int id, double cost, string stat, int period, string artist, string title, int numTracks, int year, int month, int day, string genre);
		
		void SetArtist(string artist);
		void SetTracks(int numTracks);
		void SetDate(int year, int month, int day);
		void SetGenre(string genre);
		void Print();
		
		string GetArtist();
		int GetTracks();
		int GetYear();
		int GetMonth();
		int GetDay();
		string GetGenre();
		
	private:
		string a;
		int tracks;
		int y, m, d;
		string g;
};

#endif