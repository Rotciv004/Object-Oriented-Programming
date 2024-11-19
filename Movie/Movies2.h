#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Movies2.h"
#include "controller.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <QHBoxLayout>
#include <qlabel.h>
#include <QtWebEngineWidgets/qwebengineview.h>
#include <iostream>
#include "controller.h"

class Movies2 : public QMainWindow
{
    Q_OBJECT

public:
	Movies2(QWidget* parent = nullptr, Controller ctrl = Controller());
	void populateList();
	void connectSignalsAndSlots();
	void addMovie();
	void deleteMovie();
	void updateMovie();
	void addMovieToWatchlist();
	void deleteMovieFromWatchlist();
	void searchMovies();
	void nextMovie();
	void openURL(string url);
	void openWatchlistFile(vector<Movie>& watchlist, string format);
    ~Movies2();

private:
    Ui::Movies2Class ui;
	Controller ctrl;
	int currentMovieIndex = 0;

};
