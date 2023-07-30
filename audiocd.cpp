//function definitions of audio cd

#include <iostream>
using namespace std;
#include "audiocd.h"
#include "libraryitem.h"

AudioCD::AudioCD(int id, double cost, string stat, int length, string artist, string title, int numTracks, int year, int month, int day, string genre) : LibraryItem(id, cost, stat, length, title) {
	a = artist;
	tracks = numTracks;
	y = year;
	m = month;
	d = day;
	g = genre;
}

void AudioCD::SetArtist(string artist) {a = artist;}
void AudioCD::SetTracks(int numTracks) {tracks = numTracks;}
void AudioCD::SetDate(int year, int month, int day) {
	y = year;
	m = month;
	d = day;
}
void AudioCD::SetGenre(string genre) {g = genre;}

string AudioCD::GetArtist() {return a;}
int AudioCD::GetTracks() {return tracks;}
int AudioCD::GetYear() {return y;}
int AudioCD::GetMonth() {return m;}
int AudioCD::GetDay() {return d;}
string AudioCD::GetGenre() {return g;}

void AudioCD::Print() {
	cout << "Item Type: Audio CD" << endl;
	cout << "ID: " << id << endl;
	cout << "Title: " << t << endl;
	cout << "Artist: " << a << endl;
	cout << "Genre: " << g << endl;
	cout << "Number of Tracks: " << tracks << endl;
	cout << "Release Date: " << m << "/" << d << "/" << y << endl;
	cout << "Status: " << stat << endl;
	cout << "Loan Period: " << period << endl;
	cout << endl;
}
