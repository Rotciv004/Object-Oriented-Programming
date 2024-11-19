#include "Movies2.h"
#include <qmessagebox.h>

Movies2::Movies2(QWidget* parent, Controller ctrl)
	: QMainWindow(parent), ctrl{ ctrl }
{
	ui.setupUi(this);
	this->ctrl = ctrl;
	ctrl.readFromFile();
	this->populateList();
	this->connectSignalsAndSlots();

}

void Movies2::populateList()
{
	this->ui.movieList->clear();
	vector<Movie> movies = this->ctrl.getMovies();
	for (Movie& m : movies)
	{
		QString itemInList = QString::fromStdString(m.getTitle() + " - " + m.getGenre() + " - " + to_string(m.getYear()) + " - " + to_string(m.getLikes()) + " likes" + " - " + m.getTrailer());
		this->ui.movieList->addItem(itemInList);
	}
}


void Movies2::connectSignalsAndSlots()
{
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &Movies2::addMovie);
	QObject::connect(this->ui.deleteButton_ADMIN, &QPushButton::clicked, this, &Movies2::deleteMovie);
	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &Movies2::updateMovie);
	QObject::connect(this->ui.deleteButton_USER, &QPushButton::clicked, this, &Movies2::deleteMovieFromWatchlist);
	QObject::connect(this->ui.searchButton, &QPushButton::clicked, this, &Movies2::searchMovies);
	QObject::connect(this->ui.nextButton, &QPushButton::clicked, this, &Movies2::nextMovie);
	QObject::connect(this->ui.showFileButton, &QPushButton::clicked, this, [this]() {
		string format = this->ctrl.getFileFormat();
		if (format == "") {
			QMessageBox::critical(this, "Error", "Please enter a format!");
			return;
		}
		vector<Movie> watchlist;
		for (int i = 0; i < this->ui.watchlist->count(); i++)
		{
			string item = this->ui.watchlist->item(i)->text().toStdString();
			string title = item.substr(0, item.find(" - "));
			Movie m = this->ctrl.getMovie(title);
			watchlist.push_back(m);
		}
		this->openWatchlistFile(watchlist, format);
		});
	QObject::connect(this->ui.fileFormatButton, &QPushButton::clicked, this, [this]() {
		string format = this->ui.fileFormatLine->text().toStdString();
		if (format == "") {
			QMessageBox::critical(this, "Error", "Please enter a format!");
			return;
		}
		this->ctrl.setFileFormat(format);
		this->ui.fileFormatLine->clear();
		});
}

void Movies2::addMovie()
{
	string title = this->ui.titleLine->text().toStdString();
	string genre = this->ui.genreLine->text().toStdString();
	int year = this->ui.yearLine->text().toInt();
	int likes = this->ui.likesLine->text().toInt();
	string trailer = this->ui.trailerLine->text().toStdString();
	try {
	this->ctrl.addMovie(title, genre, year, likes, trailer);
	}
	catch (exception& e) {
		this->ui.titleLine->clear();
		this->ui.genreLine->clear();
		this->ui.yearLine->clear();
		this->ui.likesLine->clear();
		this->ui.trailerLine->clear();
		QMessageBox::critical(this, e.what(), e.what()); 
	}
	this->populateList();
	
	this->ui.titleLine->clear();
	this->ui.genreLine->clear();
	this->ui.yearLine->clear();
	this->ui.likesLine->clear();
	this->ui.trailerLine->clear();

}

void Movies2::deleteMovie()
{
	string title = this->ui.titleLine->text().toStdString();
	try
	{	
		this->ctrl.deleteMovie(title);
	}
	catch (exception& e) {
		this->ui.titleLine->clear();
		this->ui.genreLine->clear();
		this->ui.yearLine->clear();
		this->ui.likesLine->clear();
		this->ui.trailerLine->clear();
		QMessageBox::critical(this, e.what(), e.what());
	}
	this->populateList();
	this->ui.titleLine->clear();
	this->ui.genreLine->clear();
	this->ui.yearLine->clear();
	this->ui.likesLine->clear();
	this->ui.trailerLine->clear();

}

void Movies2::updateMovie()
{
	QWidget* window = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout;
	QLabel* label = new QLabel("Enter title of the movie you want to update: ");
	QLineEdit* line = new QLineEdit;
	QPushButton* button = new QPushButton("Enter");
	layout->addWidget(label);
	layout->addWidget(line);
	layout->addWidget(button);

	QObject::connect(button, &QPushButton::clicked, this, [this, window, line]() {
		string title = line->text().toStdString();
		window->close();
		QWidget* window2 = new QWidget;
		QHBoxLayout* layout2 = new QHBoxLayout;
		QLabel* label2 = new QLabel("Enter new title: ");
		QLineEdit* line2 = new QLineEdit;
		QLabel* label3 = new QLabel("Enter new genre: ");
		QLineEdit* line3 = new QLineEdit;
		QLabel* label4 = new QLabel("Enter new year: ");
		QLineEdit* line4 = new QLineEdit;
		QLabel* label5 = new QLabel("Enter new likes: ");
		QLineEdit* line5 = new QLineEdit;
		QLabel* label6 = new QLabel("Enter new trailer: ");
		QLineEdit* line6 = new QLineEdit;
		QPushButton* button2 = new QPushButton("Enter");
		layout2->addWidget(label2);
		layout2->addWidget(line2);
		layout2->addWidget(label3);
		layout2->addWidget(line3);
		layout2->addWidget(label4);
		layout2->addWidget(line4);
		layout2->addWidget(label5);
		layout2->addWidget(line5);
		layout2->addWidget(label6);
		layout2->addWidget(line6);
		layout2->addWidget(button2);
		window2->setLayout(layout2);
		window2->setPalette(QPalette("#000000", "#949494", "#ffffff", "#000000", "#f5f5f5", "#000000", "#ffffff"));
		window2->setWindowTitle("Update movie");
		window2->setFont(QFont("Tw Cen MT", 9));
		window2->show();

		QObject::connect(button2, &QPushButton::clicked, this, [this, window2, title, line2, line3, line4, line5, line6]() {
			string newTitle = line2->text().toStdString();
			string newGenre = line3->text().toStdString();
			int newYear = line4->text().toInt();
			int newLikes = line5->text().toInt();
			string newTrailer = line6->text().toStdString();
			window2->close();
			try {
				this->ctrl.updateMovie(title, newTitle, newGenre, newYear, newLikes, newTrailer);
			}
			catch (exception& e) {
				QMessageBox::critical(this, e.what(), e.what());
			}
			this->populateList();
			this->ui.titleLine->clear();
			this->ui.genreLine->clear();
			this->ui.yearLine->clear();
			this->ui.likesLine->clear();
			this->ui.trailerLine->clear();
			});
		}
	);
	window->setLayout(layout);
	window->setPalette(QPalette("#000000","#949494","#ffffff","#000000","#f5f5f5","#000000","#ffffff"));
	window->setWindowTitle("Update movie");
	window->setFont(QFont("Tw Cen MT", 9));
	window->show();
}

void Movies2::addMovieToWatchlist()
{
	string genre = this->ui.searchLine->text().toStdString();
	if (genre != "") {
		Movie m = this->ctrl.getMoviesByGenre(genre)[this->currentMovieIndex - 1];
		QString itemInList = QString::fromStdString(m.getTitle() + " - " + m.getGenre() + " - " + to_string(m.getYear()) + " - " + to_string(m.getLikes()) + " likes" + " - " + m.getTrailer());
		this->ui.watchlist->addItem(itemInList);
		return;
	}
	Movie m = this->ctrl.getMovies()[this->currentMovieIndex - 1];
	QString itemInList = QString::fromStdString(m.getTitle() + " - " + m.getGenre() + " - " + to_string(m.getYear()) + " - " + to_string(m.getLikes()) + " likes" + " - " + m.getTrailer());
	this->ui.watchlist->addItem(itemInList);
	return;
}

void Movies2::deleteMovieFromWatchlist()
{
	string title = this->ui.titleLine_User->text().toStdString();
	if (title == "") {
		QMessageBox::critical(this, "Error", "Please enter a title!");
		return;
	}

	for (int i = 0; i < this->ui.watchlist->count(); i++)
	{
		string item = this->ui.watchlist->item(i)->text().toStdString();
		if (item.find(title) != string::npos)
		{
			this->ui.watchlist->takeItem(i);
			QWidget* window = new QWidget;
			QHBoxLayout* layout = new QHBoxLayout;
			QLabel* label = new QLabel("Did you enjoyed the movie? You can leave a like by just pressing like button! ");
			QPushButton* button = new QPushButton("Like");
			QPushButton* button2 = new QPushButton("Exit");
			layout->addWidget(label);
			layout->addWidget(button);
			layout->addWidget(button2);
			window->setLayout(layout);
			window->setPalette(QPalette("#000000", "#949494", "#ffffff", "#000000", "#f5f5f5", "#000000", "#ffffff"));
			window->setWindowTitle("Feedback");
			window->setFont(QFont("Tw Cen MT", 9));
			window->show();
			QObject::connect(button, &QPushButton::clicked, this, [this,title, window]() {
				this->ctrl.likeMovie(title);
				this->populateList();
				window->close();
				window->deleteLater();
				});
			QObject::connect(button2, &QPushButton::clicked, this, [this, window]() {
				window->close();
				window->deleteLater();
				});
			return;
		}
	}
	this->ui.titleLine_User->clear();
	QMessageBox::critical(this, "Error", "Movie not found in watchlist!");
}

void Movies2::searchMovies()
{
	string genre = this->ui.searchLine->text().toStdString();
	if (genre == "") {
		this->ui.watchlist->clear();
		this->ui.currentMovie->clear();
		this->currentMovieIndex = 0;
		Movie m = this->ctrl.getMovies()[this->currentMovieIndex];
		QString itemInList = QString::fromStdString(m.getTitle() + " - " + m.getGenre() + " - " + to_string(m.getYear()) + " - " + to_string(m.getLikes()) + " likes" + " - " + m.getTrailer());
		QListWidgetItem* item = new QListWidgetItem(itemInList);
		this->ui.currentMovie->addItem(item);
		this->currentMovieIndex++;
		QWidget* window = new QWidget;
		QHBoxLayout* layout = new QHBoxLayout;
		QLabel* label = new QLabel("Do you want to add the movie to the watchlist ? ");
		QPushButton* button = new QPushButton("Yes");
		QPushButton* button2 = new QPushButton("No");
		layout->addWidget(label);
		layout->addWidget(button);
		layout->addWidget(button2);
		window->setLayout(layout);
		window->setPalette(QPalette("#000000", "#949494", "#ffffff", "#000000", "#f5f5f5", "#000000", "#ffffff"));
		window->setWindowTitle("Add movie to watchlist");
		window->setFont(QFont("Tw Cen MT", 9));
		window->show();
		this->openURL(m.getTrailer());
		QObject::connect(button, &QPushButton::clicked, this, [this, window]() {
			this->addMovieToWatchlist();
			window->close();
			window->deleteLater();
			});
		QObject::connect(button2, &QPushButton::clicked, this, [this, window]() {
			window->close();
			window->deleteLater();
			});

		return;
	}
	else {
		this->ui.currentMovie->clear();
		this->currentMovieIndex = 0;
		if (this->ctrl.getMoviesByGenre(genre).size() == 0)
		{
			QMessageBox::critical(this, "Error", "No movies with the given genre!");
			return;
		}
		Movie m = this->ctrl.getMoviesByGenre(genre)[this->currentMovieIndex];
		QString itemInList = QString::fromStdString(m.getTitle() + " - " + m.getGenre() + " - " + to_string(m.getYear()) + " - " + to_string(m.getLikes()) + " likes" + " - " + m.getTrailer());
		this->ui.currentMovie->addItem(itemInList);
		this->currentMovieIndex++;
		QWidget* window = new QWidget;
		QHBoxLayout* layout = new QHBoxLayout;
		QLabel* label = new QLabel("Do you want to add the movie to the watchlist ? ");
		QPushButton* button = new QPushButton("Yes");
		QPushButton* button2 = new QPushButton("No");
		layout->addWidget(label);
		layout->addWidget(button);
		layout->addWidget(button2);
		window->setLayout(layout);
		window->setPalette(QPalette("#000000", "#949494", "#ffffff", "#000000", "#f5f5f5", "#000000", "#ffffff"));
		window->setWindowTitle("Add movie to watchlist");
		window->setFont(QFont("Tw Cen MT", 9));
		window->show();
		this->openURL(m.getTrailer());
		QObject::connect(button, &QPushButton::clicked, this, [this, window]() {
			this->addMovieToWatchlist();
			window->close();
			window->deleteLater();
			});
		QObject::connect(button2, &QPushButton::clicked, this, [this, window]() {
			window->close();
			window->deleteLater();
			});
		return;
	}
}


void Movies2::nextMovie()
{
	string genre = this->ui.searchLine->text().toStdString();
	if (genre != "")
	{
		this->ui.currentMovie->clear();
		vector<Movie> movies = this->ctrl.getMoviesByGenre(genre);
		if (this->currentMovieIndex == movies.size())
			this->currentMovieIndex = 0;
		Movie m = movies[this->currentMovieIndex];
		QString itemInList = QString::fromStdString(m.getTitle() + " - " + m.getGenre() + " - " + to_string(m.getYear()) + " - " + to_string(m.getLikes()) + " likes" + " - " + m.getTrailer());
		QListWidgetItem* itemInListWidget = new QListWidgetItem(itemInList);
		itemInListWidget->setTextAlignment(Qt::AlignCenter);
		this->ui.currentMovie->addItem(itemInListWidget);
		this->currentMovieIndex++;
		QWidget* window = new QWidget;
		QHBoxLayout* layout = new QHBoxLayout;
		QLabel* label = new QLabel("Do you want to add the movie to the watchlist ? ");
		QPushButton* button = new QPushButton("Yes");
		QPushButton* button2 = new QPushButton("No");
		layout->addWidget(label);
		layout->addWidget(button);
		layout->addWidget(button2);
		window->setLayout(layout);
		window->setPalette(QPalette("#000000", "#949494", "#ffffff", "#000000", "#f5f5f5", "#000000", "#ffffff"));
		window->setWindowTitle("Add movie to watchlist");
		window->setFont(QFont("Tw Cen MT", 9));
		window->show();
		this->openURL(m.getTrailer());
		QObject::connect(button, &QPushButton::clicked, this, [this, window]() {
			this->addMovieToWatchlist();
			window->close();
			window->deleteLater();
			});
		QObject::connect(button2, &QPushButton::clicked, this, [this, window]() {
			window->close();
			window->deleteLater();
			});
		return;
	}
	this->ui.currentMovie->clear();
	if (this->currentMovieIndex == this->ctrl.getMovies().size())
		this->currentMovieIndex = 0;
	Movie m = this->ctrl.getMovies()[this->currentMovieIndex];
	QString itemInList = QString::fromStdString(m.getTitle() + " - " + m.getGenre() + " - " + to_string(m.getYear()) + " - " + to_string(m.getLikes()) + " likes" + " - " + m.getTrailer());
	QListWidgetItem* itemInListWidget = new QListWidgetItem(itemInList);
	itemInListWidget->setTextAlignment(Qt::AlignCenter);
	this->ui.currentMovie->addItem(itemInListWidget);
	this->currentMovieIndex++;
	QWidget* window = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout;
	QLabel* label = new QLabel("Do you want to add the movie to the watchlist ? ");
	QPushButton* button = new QPushButton("Yes");
	QPushButton* button2 = new QPushButton("No");
	layout->addWidget(label);
	layout->addWidget(button);
	layout->addWidget(button2);
	window->setLayout(layout);
	window->setPalette(QPalette("#000000", "#949494", "#ffffff", "#000000", "#f5f5f5", "#000000", "#ffffff"));
	window->setWindowTitle("Add movie to watchlist");
	window->setFont(QFont("Tw Cen MT", 9));
	window->show();
	this->openURL(m.getTrailer());
	QObject::connect(button, &QPushButton::clicked, this, [this, window]() {
		this->addMovieToWatchlist();
		window->close();
		window->deleteLater();
		});
	QObject::connect(button2, &QPushButton::clicked, this, [this, window]() {
		window->close(); 
		window->deleteLater();
		});
	return;
}

void Movies2::openWatchlistFile(vector<Movie>& watchlist, string format)
{
	if (format == "html")
	{
		this->ctrl.setFileFormat(format);
		this->ctrl.openWatchlistFile(watchlist);
		return;
	}
	if (format == "csv")
	{
		this->ctrl.setFileFormat(format);
		this->ctrl.openWatchlistFile(watchlist);
		return;
	}
	QMessageBox::critical(this, "Error", "Invalid format!");
}

void Movies2::openURL(string url)
{/*
	string command = "start " + url;
	system(command.c_str());*/
}

Movies2::~Movies2()
{}
