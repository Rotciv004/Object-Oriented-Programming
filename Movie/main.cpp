#include "Movies2.h"
#include "repository.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/qmessagebox.h>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QIcon icon("icon.png");
	a.setWindowIcon(icon);
	a.setApplicationName("Movies Manager"); 
	Repository repo("movies.txt");
	Controller ctrl(repo);
	Movies2 w{ nullptr, ctrl };
	w.show();
	return a.exec();

}
