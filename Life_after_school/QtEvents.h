#pragma once

#include <QtWidgets/QMainWindow>
#include "services.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtabwidget.h>

class GUI : public QWidget
{
public:
	GUI(Service& services);

private:
	Service& services;
	
	QTabWidget* tabWidget;
	QWidget* adminTab;
	QWidget* userTab;

	// ADMIN

	QListWidget* eventListWidget;
	QLineEdit* titleEdit;
	QLineEdit* linkEdit;
	QLineEdit* descriptionEdit;
	QLineEdit* dayEdit;
	QLineEdit* monthEdit;
	QLineEdit* yearEdit;
	QLineEdit* minuteEdit;
	QLineEdit* hourEdit;
	QLineEdit* peopleEdit;

	QPushButton* addButton_admin;
	QPushButton* deleteButton_admin;
	QPushButton* updateButton_admin;

	// USER

	QListWidget* watchListWidget;






	void buildGUI();
	void populateList();
	

};