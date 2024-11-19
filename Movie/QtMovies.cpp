#include "QtMovies.h"
#include <QHBoxLayout>
#include <qlabel.h>
#include <iostream>


GUI::GUI(Controller& ctrl) : ctrl{ ctrl }

{

    this->buildGUI();
    this->populateList();

}

void GUI::buildGUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout{ this };

    this->tabWidget = new QTabWidget{ this };
    this->adminTab = new QWidget{};
    this->userTab = new QWidget{};

    this->tabWidget->addTab(this->adminTab, "Admin Mode");
    this->tabWidget->addTab(this->userTab, "User Mode");

    mainLayout->addWidget(this->tabWidget);

    // Admin Mode
    QHBoxLayout* adminLayout = new QHBoxLayout{ this->adminTab };

    this->movieListWidget = new QListWidget{};
    adminLayout->addWidget(movieListWidget);

    QGridLayout* adminRightLayout = new QGridLayout{};

    QLabel* nameLabel = new QLabel{ "Title" };
    this->titleEdit = new QLineEdit{};
    QLabel* genreLabel = new QLabel{ "Genre" };
    this->genreEdit = new QLineEdit{};
    QLabel* yearLabel = new QLabel{ "Year" };
    this->yearEdit = new QLineEdit{};
    QLabel* likesLabel = new QLabel{ "Likes" };
    this->likesEdit = new QLineEdit{};
    QLabel* trailerLabel = new QLabel{ "Trailer" };
    this->trailerEdit = new QLineEdit{};

    adminRightLayout->addWidget(nameLabel, 0, 0);
    adminRightLayout->addWidget(this->titleEdit, 0, 1);
    adminRightLayout->addWidget(genreLabel, 1, 0);
    adminRightLayout->addWidget(this->genreEdit, 1, 1);
    adminRightLayout->addWidget(yearLabel, 2, 0);
    adminRightLayout->addWidget(this->yearEdit, 2, 1);
    adminRightLayout->addWidget(likesLabel, 3, 0);
    adminRightLayout->addWidget(this->likesEdit, 3, 1);
    adminRightLayout->addWidget(trailerLabel, 4, 0);
    adminRightLayout->addWidget(this->trailerEdit, 4, 1);

    this->addButton = new QPushButton{ "Add" };
    this->deleteButton = new QPushButton{ "Delete" };
    this->updateButton = new QPushButton{ "Update" };

    adminRightLayout->addWidget(this->addButton, 5, 0);
    adminRightLayout->addWidget(this->deleteButton, 5, 1);
    adminRightLayout->addWidget(this->updateButton, 5, 2);

    adminLayout->addLayout(adminRightLayout);

    // User Mode
    QVBoxLayout* userLayout = new QVBoxLayout{ this->userTab };

    this->watchListWidget = new QListWidget{};
    userLayout->addWidget(this->watchListWidget);
    
    QHBoxLayout* userButtonsLayout = new QHBoxLayout{};
    this->openButton = new QPushButton{ "Open" };
    this->viewWatchListButton = new QPushButton{ "View Watchlist" };
    this->filterGenreEdit = new QLineEdit{};
    this->filterGenreEdit->setPlaceholderText("Genre");
    this->filterButton = new QPushButton{ "Filter by Genre" };

    userButtonsLayout->addWidget(this->openButton);
    userButtonsLayout->addWidget(this->viewWatchListButton);
    userButtonsLayout->addWidget(this->filterGenreEdit);
    userButtonsLayout->addWidget(this->filterButton);

    userLayout->addLayout(userButtonsLayout);
}

void GUI::populateList()
{
    this->movieListWidget->clear();

    for (auto& m : this->ctrl.getMovies())
    {
        this->movieListWidget->addItem(QString::fromStdString(m.getTitle() + " - " + m.getGenre() + " - " + std::to_string(m.getYear()) + " - " + std::to_string(m.getLikes()) + " - " + m.getTrailer()));
    }
}
