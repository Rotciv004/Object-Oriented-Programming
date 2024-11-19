#pragma once

#include <QtWidgets/QMainWindow>
#include "controller.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtabwidget.h>

class GUI : public QMainWindow
{
	Q_OBJECT
public:
	GUI(Controller& ctrl);

    void buildGUI();
    void populateList();

private:
    Controller& ctrl;

    QTabWidget* tabWidget;
    QWidget* adminTab;
    QWidget* userTab;

    // Admin Mode Widgets
    QListWidget* movieListWidget;
    QLineEdit* titleEdit;
    QLineEdit* genreEdit;
    QLineEdit* yearEdit;
    QLineEdit* likesEdit;
    QLineEdit* trailerEdit;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;

    // User Mode Widgets
    QListWidget* watchListWidget;
    QLineEdit* filterGenreEdit;
    QPushButton* openButton;
    QPushButton* viewWatchListButton;
    QPushButton* filterButton;


};