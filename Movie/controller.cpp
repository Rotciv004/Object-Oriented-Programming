#include "controller.h"
#include <exception>
#include <iterator>
using namespace std; 

Controller::Controller()
{
	this->repo = Repository();
}

Controller::Controller(const Repository& repo)
{
	this->repo = repo;
}

/// <summary>
/// Adds a movie to the repository.
/// </summary>
/// <param name="title"> - string, the title of the movie</param>
/// <param name="genre"> - string, the genre of the movie</param>
/// <param name="year"> - int, the year of release of the movie</param>
/// <param name="likes"> - int, the number of likes of the movie</param>
/// <param name="trailer> - string, the link to the trailer of the movie</param>
void Controller::addMovie(string title, string genre, int year, int likes, string trailer)
{
	const vector<Movie>& movies = repo.getMovies();
	if (any_of(movies.begin(), movies.end(), [&](const Movie& movie) {
		return movie.getTitle() == title;
		})) {
		throw exception("Movie already exists!");
	}
	repo.addMovie(title, genre, year, likes, trailer);
};

/// <summary>
/// Deletes a movie from the repository.
/// </summary>
/// <param name="title"> - string, the title of the movie</param>
void Controller::deleteMovie(string title)
{
	this->repo.deleteMovie(title);

}
/// <summary>
/// Updates a movie from the repository.
/// </summary>
/// <param name="title"> - string, the title of the movie</param>
/// <param name="newTitle"> - string, the new title of the movie</param>
/// <param name="newGenre"> - string, the new genre of the movie</param>
/// <param name="newYear"> - int, the new year of release of the movie</param>
/// <param name="newLikes"> - int, the new number of likes of the movie</param>
/// <param name="newTrailer"> - string, the new link to the trailer of the movie</param>
void Controller::updateMovie(string title, string newTitle, string newGenre, int newYear, int newLikes, string newTrailer)
{
	this->repo.updateMovie(title, newTitle, newGenre, newYear, newLikes, newTrailer);
};



/// <summary>
/// Adds a like to a movie.
/// </summary>
/// <param name="title"> Title of the movie</param>
void Controller::likeMovie(string title)
{
	const vector<Movie>& movies = repo.getMovies();
	auto it = find_if(movies.begin(), movies.end(), [&](const Movie& movie) {
		return movie.getTitle() == title;
		});

	if (it != movies.end()) {
		repo.feedback(title);
		return;
	}

	throw exception("Movie does not exist!");
};

/// <summary>
/// Getter for a movie from the repository.
/// </summary>
/// <param name="title"> - string, the title of the movie</param>
/// <returns> - Movie, the movie with the given title</returns>
Movie Controller::getMovie(string title)
{
	const vector<Movie>& movies = repo.getMovies();
	auto it = find_if(movies.begin(), movies.end(), [&](const Movie& movie) {
		return movie.getTitle() == title;
		});
	if (it != movies.end()) {
		return *it;
	}
	throw exception("Movie not found!");
};
/// <summary>
///  Gest all the movies from the repository.
/// </summary>
/// <returns> - DynamicVector<Movie>, all the movies from the repository</returns>
vector<Movie> Controller::getMovies()
{
	const vector<Movie>& movies = repo.getMovies();
	return movies;
};
/// <summary>
///	Gets the movies by genre.
/// </summary>
/// <param name="genre"> - string, the genre of the movies</param>
/// <returns> - DynamicVector<Movie>, the movies with the given genre</returns>
vector<Movie> Controller::getMoviesByGenre(string genre)
{
	const vector<Movie>& movies = repo.getMovies();
	vector<Movie> filteredMovies;
	copy_if(movies.begin(), movies.end(), back_inserter(filteredMovies), [genre](const Movie& movie) {
		return movie.getGenre() == genre;
		});
	return filteredMovies;
};

void Controller::setFileFormat(string format)
{
	this->format = format;
}

void Controller::openWatchlistFile(vector<Movie>& watchlist)
{
	if (this->format == "csv") {
		CSVWriter writer;
		writer.writeToFile(watchlist, "watchlist");
		system("start watchlist.csv");
	}
	else if (this->format == "html") {
		HTMLWriter writer;
		writer.writeToFile(watchlist, "watchlist");
		system("start watchlist.html");
	}
}

void Controller::readFromFile()
{
	this->repo.readFromFile();
}

void Controller::saveToFile(string fileName)
{
	if (this->format == "csv") {
		CSVWriter writer;
		writer.writeToFile(this->repo.getMovies(), fileName);
	}
	else if (this->format == "html") {
		HTMLWriter writer;
		writer.writeToFile(this->repo.getMovies(), fileName);
	}
	else {
		throw exception("Invalid format!");
	}
}