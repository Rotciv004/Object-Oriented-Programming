#pragma once
#include <string>
using namespace std; 

class Movie {
	private:
		string title;
		string genre;
		int year;
		int likes;
		string trailer;
	public:
		Movie();
		Movie(const string title, const string genre, const int year, const int likes, const string trailer);
		string getTitle() const;
		string getGenre() const;
		int getYear() const;
		int getLikes() const;
		string getTrailer() const;
		bool operator==(const Movie& movieToCompare);
		friend ostream& operator<<(ostream& os, const Movie& movie);
		friend istream& operator>>(istream& is, Movie& movie);
		void setLikes(int likes);
		void setTrailer(string trailer);
		void setTitle(string title);
		void setGenre(string genre);
		void setYear(int year);
};