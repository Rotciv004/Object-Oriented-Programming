#include "repository.h"

using namespace std;


Repository::Repository()
{
	this->file = "movies.txt";
};

Repository :: Repository(string fileName) 
{
	this->file = move(fileName);
	this->readFromFile();
};

/// <summary>
/// adds a movie to the repository
/// </summary>
/// <param name="title"> - string, the title of the movie</param>
/// <param name="genre"> - string, the genre of the movie</param>
/// <param name="year"> - int, the year of release of the movie</param>
/// <param name="likes"> - int, the number of likes of the movie</param>
/// <param name="trailer> - string, the link to the trailer of the movie</param>
void Repository::addMovie(const string& title, const string& genre, int year, int likes, const string& trailer)
{
	Movie movieToAdd = Movie(title, genre, year, likes, trailer);
	if (find(moviesRepo.begin(), moviesRepo.end(), movieToAdd) != moviesRepo.end())
		throw MovieInListException();

	MovieValidator::validator(movieToAdd);

	this->moviesRepo.push_back(movieToAdd);
};

void Repository::updateMovie(const string& title, const string& newTitle, const string& newGenre, int newYear, int newLikes, const string& newTrailer)
{


	for (auto& movie : moviesRepo)
	{
		if (movie.getTitle() == title)
		{
			MovieValidator::validator(Movie(newTitle, newGenre, newYear, newLikes, newTrailer));
			movie.setTitle(newTitle);
			movie.setGenre(newGenre);
			movie.setYear(newYear);
			movie.setLikes(newLikes);
			movie.setTrailer(newTrailer);
		}
	}
	throw MovieNotFoundException();
};

/// <summary>
///  deletes a movie from the repository
/// </summary>
/// <param name="title"> - string, the title of the movie</param>
void Repository::deleteMovie(const string& title)
{
	auto it = remove_if(moviesRepo.begin(), moviesRepo.end(), [title](const Movie& movie) {
		return movie.getTitle() == title;
		});

	if (it == moviesRepo.end())
	{
		throw MovieNotFoundException();
	}

	moviesRepo.erase(it, moviesRepo.end());
};


void Repository::feedback(string title)
{
	for_each(moviesRepo.begin(), moviesRepo.end(), [&](Movie& movie) {
		if (movie.getTitle() == title)
		{
			movie.setLikes(movie.getLikes() + 1);
		}
		});

	throw MovieNotFoundException();
};

/// <summary>
/// get a movie from the repository
/// </summary>
/// <param name="title"> - string, the title of the movie</param>
/// <returns> - the movie with the given title</returns>
Movie Repository :: getMovie(const string& title)
{
	auto it = find_if(moviesRepo.begin(), moviesRepo.end(), [title](const Movie& movie) { return movie.getTitle() == title; });
	if (it == moviesRepo.end())
	{
		throw MovieNotFoundException();
	}
	return *it;
};

/// <summary>
/// get all the movies from the repository
/// </summary>
/// <returns> - all the movies from the repository</returns>
vector<Movie> Repository :: getMovies()
{
	return this->moviesRepo;
};
/// <summary>
/// get the length of the repository
/// </summary>
/// <returns> - the length of the repository</returns>
int Repository :: getLength()
{
	return this->moviesRepo.size();
};

void Repository::readFromFile()
{
	ifstream file(this->file);
	Movie movie;
	while (file >> movie)
		this->moviesRepo.push_back(movie);
	file.close();
};

void Repository::writeToFile()
{
	ofstream file(this->file);
	for (const auto& movie : this->moviesRepo)
	{
		file << movie;
	}
	file.close();
};

void MovieValidator::validator(const Movie& movie)
{
	string errors;
	if (movie.getTitle().size() < 3)
		errors += "The title must have at least 3 characters!\n";
	if (movie.getGenre().size() < 3)
		errors += "The genre must have at least 3 characters!\n";
	if (movie.getYear() < 1900)
		errors += "The year must be greater than 1900!\n";
	if (movie.getLikes() < 0)
		errors += "The number of likes must be greater than 0!\n";
	if (movie.getTrailer().find("http") != 0)
		errors += "The link must start with http!\n";
	if (errors.size() > 0)
		throw InvalidMovieException();

};


