#include "tests.h"
#include "controller.h"
#include <assert.h>


void testRepository() {
    Repository repo;
    repo.addMovie("Titanic", "Drama", 1997, 100, "https://www.imdb.com/title/tt0120338/");
    repo.addMovie("Inception", "Action", 2010, 150, "https://www.imdb.com/title/tt1375666/");
    repo.addMovie("The Shawshank Redemption", "Drama", 1994, 142, "https://www.imdb.com/title/tt0111161/");

   // Test getMovies
    assert(repo.getMovies().size() == 3);

    // Test getMovie
    assert(repo.getMovie("Titanic").getTitle() == "Titanic");

    // Test deleteMovie
    repo.deleteMovie("Titanic");
    assert(repo.getMovies().size() == 2);
}

void testController() {
    Controller controller;
    controller.addMovie("Titanic", "Drama", 1997, 100, "https://www.imdb.com/title/tt0120338/");
    controller.addMovie("Inception", "Action", 2010, 150, "https://www.imdb.com/title/tt1375666/");

    // Test deleteMovie
    controller.deleteMovie("Titanic");
    assert(controller.getMovies().size() == 1);
    assert(controller.getMovies()[0].getTitle() == "Inception");

    //// Test updateMovie
    controller.updateMovie("Inception", "Scooby Doo", "Drama", 1997, 100, "https://www.imdb.com/title/tt0120338/");
    assert(controller.getMovies()[0].getTitle() == "Scooby Doo");
    assert(controller.getMovie("Scooby Doo").getTitle() == "Scooby Doo");
//
//    // Test likeMovie
//    controller.likeMovie("Scooby Doo");
//    assert(controller.getMovie("Scooby Doo").getLikes() == 101);
//
//    // Test getMoviesByGenre
//    assert(controller.getMoviesByGenre("Drama").size() == 1);
}

void testDomain() {
    Movie m("Titanic", "Drama", 1997, 100, "https://www.imdb.com/title/tt0120338/");
    Movie m2("Buzz House The Movie", "Horror", 2024, 1000, "https://www.imdb.com/title/tt0120338/");

    // Test getters
    assert(m.getTitle() == "Titanic");
    assert(m.getGenre() == "Drama");
    assert(m.getYear() == 1997);
    assert(m.getLikes() == 100);
    assert(m.getTrailer() == "https://www.imdb.com/title/tt0120338/");

    // Test operator==
    assert(m == m);
    assert(!(m == m2));

    // Test setters
    m.setGenre("Action");
    assert(m.getGenre() == "Action");
    m.setLikes(200);
    assert(m.getLikes() == 200);
    m.setTrailer("https://www.imdb.com/title/tt0120338/");
    assert(m.getTrailer() == "https://www.imdb.com/title/tt0120338/");
    m.setTitle("Inception");
    assert(m.getTitle() == "Inception");
    m.setYear(2010);
    assert(m.getYear() == 2010);
}

void testAll() {
	try {
		testRepository();
		testController();
		testDomain();
	}
    catch (exception& e) {}
}