#include "domain.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

Movie :: Movie() {
	title = "";
	genre = "";
	year = 0;
	likes = 0;
	trailer = "";
};

Movie :: Movie(const string title, const string genre, const int year, const int likes, const string trailer) {
	this->title = title;
	this->genre = genre;
	this->year = year;
	this->likes = likes;
	this->trailer = trailer;
};


/// getters 
string Movie :: getTitle() const {
	return title;
};

string Movie :: getGenre() const {
	return genre;
};

int Movie :: getYear() const{
	return year;
};

int Movie :: getLikes() const {
	return likes;
};

string Movie :: getTrailer() const {
	return trailer;
};

bool Movie :: operator==(const Movie &m) {
	if (title == m.title &&  trailer == m.trailer )
		return true;
	return false;
};

ostream& operator<<(ostream& os, const Movie& movie) {
	os << movie.getTitle() << "," << movie.getGenre() << "," << movie.getYear() << "," << movie.getLikes() << "," << movie.getTrailer() << endl;
	return os;
}

istream& operator>>(istream& inp, Movie& movie) {
	string title, genre, trailer, line, year, likes;
	getline(inp, line);
	if (line.empty())
		return inp;
	stringstream stream(line);
	getline(stream, title, ',');
	movie.title = title;
	getline(stream, genre, ',');
	movie.genre = genre;
	getline(stream, year, ',');
	movie.year = stoi(year);
	getline(stream, likes, ',');
	movie.likes = stoi(likes);
	getline(stream, trailer, ',');
	movie.trailer = trailer;
	return inp;
}

/// Setters 
void Movie :: setTitle(string newTitle) {
	this->title = newTitle;
};

void Movie :: setGenre(string newGenre) {
	this->genre = newGenre;
};

void Movie :: setYear(int newYear) {
	this->year = newYear;
};

void Movie :: setLikes(int newLikes) {
	this->likes = newLikes;
};

void Movie :: setTrailer(string newTrailer) {
	this->trailer = newTrailer;
};
	