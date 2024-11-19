#pragma once
#include "repository.h"
using namespace std;

class Controller 
{
	private:
		Repository repo;
		string format;

	public:	
		Controller();
		Controller(const Repository& repo);
		void addMovie(string title, string genre, int year, int likes, string trailer);
		void deleteMovie(string title);
		void updateMovie(string title, string newTitle, string newGenre, int newYear, int newLikes, string newTrailer);
		void likeMovie(string title);
		void readFromFile();
		void saveToFile(string fileName);
		void setFileFormat(string format);
		string getFileFormat();
		void openWatchlistFile(vector<Movie>& watchlist);
		Movie getMovie(string title);
		vector<Movie> getMovies();
		vector<Movie> getMoviesByGenre(string genre);
};