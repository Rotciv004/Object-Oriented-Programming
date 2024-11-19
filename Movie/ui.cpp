#include <iostream>
#include "controller.h"
#include "tests.h"
#include <crtdbg.h>
#include <cstdlib>

using namespace std;
class UI {
	public:
	void printing_mode_menu() {
		cout << "Modes: " << endl;
		cout << " 1.Administrator mode" << endl;
		cout << " 2.User mode" << endl;
		cout << " 0.Exit" << endl;
		cout << "Enter option: ";
	}

	void printing_administrator_menu() {
		cout << endl << "Options : " << endl;
		cout << " 1. Add a new movie" << endl;
		cout << " 2. Delete a movie" << endl;
		cout << " 3. Update information of a movie" << endl;
		cout << " 4. Display all movies" << endl;
		cout << " 0. Return" << endl;
		cout << "Enter option: ";
	}

	void printing_user_menu() {
		cout << endl << "Options : " << endl;
		cout << " 1. Search by genre" << endl;
		cout << " 2. Display watchlist" << endl;
		cout << " 3. Delete from watchlist" << endl;
		cout << " 4. Open the watchlist file" << endl;
		cout << " 0. Return" << endl;
		cout << "Enter option: ";
	}

	void printing_watchlist_menu() {
		cout << endl << " 1. Add to watchlist" << endl;
		cout << " 2. Continue " << endl;
		cout << " 0. Return" << endl;
		cout << "Enter option: ";
	}

	void displayMovies(vector<Movie> movies) {
		cout << endl;
		for (int i = 0; i < movies.size(); i++) {
			Movie m = movies[i];
			cout << m.getTitle() << " - " << m.getGenre() << " - " << m.getYear() << " - " << m.getLikes() << " - " << m.getTrailer() << endl;
		}
	}

	void addMovie(Controller& controller) {
		string title, genre, trailer;
		int year, likes;
		cout << "Enter title: ";
		cin.ignore();
		getline(cin, title);
		cout << "Enter genre: ";
		getline(cin, genre);
		cout << "Enter year: ";
		cin >> year;
		cout << "Enter likes: ";
		cin >> likes;
		cout << "Enter trailer: ";
		cin.ignore();
		getline(cin, trailer);
		controller.addMovie(title, genre, year, likes, trailer);
		cout<< "Movie added successfully!";
	};
	void deleteMovie(Controller& controller) {
		string title;
		cout << "Enter title to be deleted : ";
		cin.ignore();
		getline(cin, title);
		controller.deleteMovie(title);
		cout<<"Movie deleted successfully!";

	};
	void updateMovie(Controller& controller) {
		string title, newTitle, newGenre, newTrailer;
		int newYear, newLikes;
		cout << "Enter title to be updated : ";
		cin.ignore();
		getline(cin, title);
		cout << "Enter new title: ";
		getline(cin, newTitle);
		cout << "Enter new genre: ";
		getline(cin, newGenre);
		cout << "Enter new year: ";
		cin >> newYear;
		cout << "Enter new likes: ";
		cin >> newLikes;
		cout << "Enter new trailer: ";
		cin.ignore();
		getline(cin, newTrailer);
		controller.updateMovie(title, newTitle, newGenre, newYear, newLikes, newTrailer);
		cout<<"Movie updated successfully!";
	};

	void administratorMode(Controller& controller) {
		int option;
		while (true) {
			try {
				printing_administrator_menu();
				cin >> option;
				switch (option) {
				case 1:
					addMovie(controller);
					break;
				case 2:
					deleteMovie(controller);
					break;
				case 3:
					updateMovie(controller);
					break;
				case 4:
					displayMovies(controller.getMovies());
					break;
				case 0:
					return;
				default:
					cout << "Invalid option" << endl;
				}
			}
			catch (exception& e) {
				cout <<endl << e.what() << endl;
			}
		}
	}

	void searchByGenre(Controller& controller, vector<Movie>& watchlist) {
		string genre;
		cout<<"Enter genre: ";
		cin.ignore();
		getline(cin, genre);
		vector<Movie> movies = controller.getMoviesByGenre(genre);
		if (genre == "") {
			displayMoviesForWatchlist(controller, controller.getMovies(), watchlist);
		}
		else {
			displayMoviesForWatchlist(controller, movies, watchlist);
		}			
	}

	void displayMoviesForWatchlist(Controller& controller, vector<Movie> movies, vector<Movie>& watchlist) {
		for (int i = 0; i < movies.size(); i++) {
			cout << i + 1 << ". " << movies[i].getTitle() << " - " << movies[i].getGenre() << " - " << movies[i].getYear() << " - " << movies[i].getLikes() << " - " << movies[i].getTrailer() << endl;
			openTrailer(movies[i].getTrailer());
			string option;
			cout << "Do you want to add this movie to your watchlist? (yes/no): " << endl;
			cin >> option;
			if (option == "yes") {
				watchlist.push_back(movies[i]);
				cout << "Movie added to watchlist!" << endl;
				cout << "If you want to continue watching trailers, enter next. If you want to return to the menu, enter exit: " << endl;
				cin >> option;
				if (option == "exit") {
					return;
				}
			}
			else if (option == "no") {
				cout << "If you didn't like the trailer, you can watch the next movie trailer in the list. Enter next to continue, or exit to return to the menu: " << endl;
				cin >> option;
				if (option == "exit") {
					return;
				}
				else if (option == "next") {
					continue;
				}
				else {
					cout << "Invalid option!" << endl;
				}
			}
			else {
				cout << "Invalid option!" << endl;
			}
		}
		cout << "You have reached the end of the list." << endl;
		cout << "You can input another genre to search for more movies!" << endl;
		searchByGenre(controller, watchlist);
	}

	void openTrailer(string trailer) {
		string command = "start " + trailer;
		system(command.c_str());
	}

	void deleteFromWatchlist(Controller& controller, vector<Movie>& watchlist) {
		displayMovies(watchlist);
		cout<<"Enter the title of the movie you want to delete from the watchlist: ";
		string title;
		cin.ignore();
		getline(cin, title);
		for (int i = 0; i < watchlist.size(); i++) {
			if (watchlist[i].getTitle() == title) {
				watchlist.erase(watchlist.begin() + i);
				cout << "Movie deleted from watchlist!" << endl;
				break;
			}
			if (i == watchlist.size() - 1) {
				cout << "Movie not found in watchlist!" << endl;
				return;
			}
		}
		cout<<"Do you enjoyed the movie? If so, don't forget to like it, by just entering yes. If you didn't like it, enter no: ";
		string option;
		cin >> option;
		if (option == "yes") {
			likedTrailer(controller, title);
		}
		else if (option != "no") {
			cout << "Invalid option!" << endl;
		}
	}

	static void likedTrailer(Controller& controller, string title) {
		controller.likeMovie(title);
		cout << "Thank you for your feedback! The movie " << title << " has been liked!" << endl;

	}



	void userMode(Controller& controller, vector<Movie>& watchlist) {
		int option;
		while (true) {
			printing_user_menu();
			cin >> option;
			switch (option) {
				case 1:
					searchByGenre(controller, watchlist);
					break;
				case 2:
					displayMovies(watchlist);
					break;
				case 3:
					deleteFromWatchlist(controller, watchlist);
					break;
				case 4:
					controller.openWatchlistFile(watchlist);
					break;
				case 0:
					return;
				default:
					cout << "Invalid option" << endl;
			}
		}
	}
};

int main() {
	testAll();
	int option;
	Controller controller;
	UI ui;
	vector<Movie> watchlist;
	try {
		controller.readFromFile();
	}
	catch (exception& e) {}
	string format, fileName;
	cout << "Enter the format of the file you want to save ( csv / html ): ";
	cin >> format;
	controller.setFileFormat(format);
	while (true) {
		ui.printing_mode_menu();
		cin >> option;
		switch (option) {
		case 1:
			ui.administratorMode(controller);
			break;
		case 2:
			ui.userMode(controller, watchlist);
			break;
		case 0:
			cout << "Enter the name of the file you want to save the movies to: ";
			cin >> fileName;
			controller.saveToFile(fileName);
			return 0;
		default:
			cout << "Invalid option" << endl;
		}
	}
	return 0;
}