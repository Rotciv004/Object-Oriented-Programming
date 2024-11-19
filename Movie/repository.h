#pragma once 
#include "domain.h"
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class MovieNotFoundException : public exception {
public:
	const char* what() const noexcept override {
		return "Movie not found!";
	}
};

class MovieInListException : public exception {
public:
	const char* what() const noexcept override {
		return "Movie already exists!";
	}
};

class InvalidHTTPException : public exception {
public:
	const char* what() const noexcept override {
		return "Invalid HTTP!";
	}
};

class InvalidMovieException : public exception {
	const char* what() const noexcept override {
		return "Invalid movie!";
	}
};

class MovieValidator
{
public:
	static void validator(const Movie& m);
};

class FileWriter {
public:
	virtual void writeToFile(const vector<Movie>& movies, const string& fileName) = 0;
};

class CSVWriter : public FileWriter {
public:
	void writeToFile(const vector<Movie>& movies, const string& fileName) override {
		ofstream file(fileName + ".csv");
		for (const auto& movie : movies) {
			file << movie.getTitle() << "," << movie.getGenre() << "," << movie.getYear() << "," << movie.getLikes() << "," << movie.getTrailer() << endl;
		}
		file.close();
	};
};

class HTMLWriter : public FileWriter {
public:
	void writeToFile(const vector<Movie>& movies, const string& fileName) override {
		ofstream file(fileName + ".html");
		file << "<!DOCTYPE html><html><head<title>Movies</title></head<body><table border = '1'><tr><th>Title</th><th>Genre</th><th>Year</th><th>Likes</th><th>Trailer</th></tr>";
		for (const auto& movie : movies) {
			file << "<tr><td>" << movie.getTitle() << "</td><td>" << movie.getGenre() << "</td><td>" << movie.getYear() << "</td><td>" << movie.getLikes() << "</td><td><a href = '" << movie.getTrailer() << "'>Link</a></td></tr>";
		}
		file << "</table></body></html>";
		file.close();
	};
};

class Repository {
	private:
		vector<Movie> moviesRepo;
		string file;
	public:
		Repository();
		Repository(string file);
		void addMovie(const string& title, const string& genre, int year, int likes, const string& trailer);
		void deleteMovie(const string& title);
		void updateMovie(const string& title, const string& newTitle, const string& newGenre, int newYear, int newLikes, const string& newTrailer);
		void feedback(string title);
		void readFromFile();
		void writeToFile();
		Movie getMovie(const string& title);
		vector<Movie> getMovies();
		int getLength();
};