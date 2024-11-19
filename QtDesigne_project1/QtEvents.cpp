#include "QtEvents.h"
#include <QBoxLayout>
#include <qlabel.h>
#include <iostream>

GUI::GUI(Service& services) : services{ services }
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

	// ADMIN

	QHBoxLayout* adminLayout = new QHBoxLayout{ this->adminTab };
	this->eventListWidget = new QListWidget{};
	adminLayout->addWidget(this->eventListWidget);

	QGridLayout* adminRightLayout = new QGridLayout{};

	QLabel* nameLabel = new QLabel{ "Title" };
	this->titleEdit = new QLineEdit{};

	QLabel* descriptionLabel = new QLabel{ "Description" };
	this->descriptionEdit = new QLineEdit{};

	QLabel* linkLabel = new QLabel{ "Link" };
	this->linkEdit = new QLineEdit{};

	QLabel* dayLabel = new QLabel{ "Day" };
	this->dayEdit = new QLineEdit{};

	QLabel* monthLabel = new QLabel{ "Month" };
	this->monthEdit = new QLineEdit{};

	QLabel* yearLabel = new QLabel{ "Year" };
	this->yearEdit = new QLineEdit{};

	QLabel* minuteLabel = new QLabel{ "Minute" };
	this->minuteEdit = new QLineEdit{};

	QLabel* hourLabel = new QLabel{ "Hour" };
	this->hourEdit = new QLineEdit{};

	QLabel* peopleLabel = new QLabel{ "People" };
	this->peopleEdit = new QLineEdit{};

	adminRightLayout->addWidget(nameLabel, 0, 0);
	adminRightLayout->addWidget(this->titleEdit, 0, 1);

	adminRightLayout->addWidget(descriptionLabel, 1, 0);
	adminRightLayout->addWidget(this->descriptionEdit, 1, 1);

	adminRightLayout->addWidget(linkLabel, 2, 0);
	adminRightLayout->addWidget(this->linkEdit, 2, 1);

	adminRightLayout->addWidget(minuteLabel, 3, 0);
	adminRightLayout->addWidget(this->minuteEdit, 3, 1);

	adminRightLayout->addWidget(monthLabel, 4, 0);
	adminRightLayout->addWidget(this->monthEdit, 4, 1);

	adminRightLayout->addWidget(yearLabel, 5, 0);
	adminRightLayout->addWidget(this->yearEdit, 5, 1);

	adminRightLayout->addWidget(minuteLabel, 6, 0);
	adminRightLayout->addWidget(this->minuteEdit, 6, 1);

	adminRightLayout->addWidget(hourLabel, 7, 0);
	adminRightLayout->addWidget(this->hourEdit, 7, 1);

	adminRightLayout->addWidget(peopleLabel, 8, 0);
	adminRightLayout->addWidget(this->peopleEdit, 8, 1);

	this->addButton_admin = new QPushButton{ "Add" };
	this->deleteButton_admin = new QPushButton{ "Delete" };
	this->updateButton_admin = new QPushButton{ "Update" };

	adminRightLayout->addWidget(this->addButton_admin, 9, 0);
	adminRightLayout->addWidget(this->deleteButton_admin, 9, 1);
	adminRightLayout->addWidget(this->updateButton_admin, 9, 2);

	adminLayout->addLayout(adminRightLayout);



	// USER

	QVBoxLayout* userLayout = new QVBoxLayout{ this->userTab };

	this->eventListWidget_user = new QListWidget{};
	this->selectedEvents = new QListWidget{};

	QHBoxLayout* userButtonsLayout = new QHBoxLayout{};

	this->addButton_user = new QPushButton{ "Add event" };
	this->viewSelected_events = new QPushButton{ "View selected events" };

	this->month_user = new QLineEdit{};
	this->month_user->setPlaceholderText("Month");
	this->filterByMonth = new QPushButton{ "Filter by month" };

	userButtonsLayout->addWidget(this->addButton_user);
	userButtonsLayout->addWidget(this->viewSelected_events);
	userButtonsLayout->addWidget(this->month_user);
	userButtonsLayout->addWidget(this->filterByMonth);

	userLayout->addLayout(userButtonsLayout);
	

}


void GUI::populateList()
{
	this->eventListWidget->clear();

	for (auto& m : this->services.getEvents_Services())
	{
		this->eventListWidget->addItem(QString::fromStdString(m.getTitle() + " - " + m.getDescription() + " - " + m.getLink() + " - " + std::to_string(m.getDay()) + " - " + std::to_string(m.getMonth()) + " - " + std::to_string(m.getYear()) + " - " + std::to_string(m.getHour()) + " - " + std::to_string(m.getMinute()) + " - " + std::to_string(m.getPeoples())));
	}
}
