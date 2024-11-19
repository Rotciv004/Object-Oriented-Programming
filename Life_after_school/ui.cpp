#include "ui.h"
#include <string>

Ui::Ui()
{
	this->service = Service();
}

Ui::~Ui() {}

int Ui::printFileFormatMenu_Ui()
{
	int command;

	std::cout << "Input the format do you want to save the file\n";
	std::cout << "1. CSV\n2. HTML\n\n";

	std::cout<<"Input a command -> ";
	std::cin >> command;
	std::cout << std::endl;

	return command;
}

int Ui::printUserMenu_Ui() {

	std::cout << "1. Add event\n";
	std::cout << "2. List your events\n";
	std::cout << "3. Delete event\n";
	std::cout << "0. EXIT\n\n";

	int command;

	std::cout << "Input a command -> ";
	std::cin >> command;
	std::cout << std::endl;

	return command;
}

int Ui::printAdminMenu_Ui() {

	std::cout << "1. Add events\n";
	std::cout << "2. Remove event\n";
	std::cout << "3. Update event\n";
	std::cout << "4. List events\n";
	std::cout << "0. EXIT\n\n";

	int command;

	std::cout << "Input a command -> ";
	std::cin >> command;
	std::cout << std::endl;

	return command;
}

int Ui::printFirstMenu_Ui() {

	std::cout << "1. Admin\n";
	std::cout << "2. User\n";
	std::cout << "0. EXIT\n\n";

	int command;

	std::cout << "Input a command -> ";
	std::cin >> command;
	std::cout << std::endl;

	return command;
}

void Ui::runApp_Ui() {

	this->service.takeFromFile_Services();

	while (true)
	{
		int command = this->printFirstMenu_Ui();

		if (command == 1)
		{
			while (true)
			{
				try {
					command = this->printAdminMenu_Ui();

					if (command == 1)
						this->addEventAdmin_Ui();
					else
						if (command == 2)
							this->removeEventAdmin_Ui();
						else
							if (command == 3)
								this->updateEventAdmin_Ui();
							else
								if (command == 4)
									this->listEventsAdmin_Ui();
								else
									if (command == 0)
									{
										std::cout << "You exit!\n\n";
										break;
									}
									else
										std::cout << "Invalide input!\n\n";
				}
				catch (std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}
			}
		}
		else
			if (command == 2)
			{
				while (true)
				{
					try {
						command = this->printUserMenu_Ui();

						if (command == 1)
							this->addEventsUser_Ui();
						else
							if (command == 2)
								this->listEventsUser_Ui();
							else
								if (command == 0)
								{
									std::cout << "You exit!\n\n";
									break;
								}
								else
									if (command == 3)
										this->deleteEventUser_Ui();
									else
										std::cout << "Invalide input!\n\n";
					}
					catch (std::exception& e)
					{
						std::cout << e.what() << std::endl;
					}
				}
			}
			else
				if (command == 0)
				{
					
					try {
						int form = this->printFileFormatMenu_Ui();

						if (form == 1)
							this->service.saveToFile_Services("csv");
						else
							if (form == 2)
								this->service.saveToFile_Services("html");
							else
								std::cout << "Invalide input!\n\n";
					}
					catch (exception e)
					{
						std::cout << e.what() << std::endl;
					}
					
				
					std::cout << "You exit!";
					break;
				}
				else
					std::cout << "Print invalide input!\n\n";

	}
}


void Ui::addEventAdmin_Ui() {
	std::string title, link, description;
	int day, month, year, hour, minute;

	std::cout << "Input a title from an event -> ";
	std::cin >> title;

	std::cout << "Input a link from an event -> ";
	std::cin >> link;

	std::cout << "Input a description from an event -> ";
	std::cin >> description;

	std::cout << "Input a day from an event -> ";
	std::cin >> day;

	std::cout << "Input a month from an event -> ";
	std::cin >> month;

	std::cout << "Input a year from an event -> ";
	std::cin >> year;

	std::cout << "Input a hour from an event -> ";
	std::cin >> hour;

	std::cout << "Input a minute from an event -> ";
	std::cin >> minute;

	this->service.addEvent_Services(Event(title, description, link, day, month, year, hour, minute, 0));
	std::cout<<"Event added succesfully!\n";
}

void Ui::removeEventAdmin_Ui() {

	int position;

	std::cout << "Input a position -> ";
	std::cin >> position;
	std::cout << std::endl;

	this->service.removeEvent_Services(position);
	std::cout << "Event was removed!\n";
}

void Ui::updateEventAdmin_Ui() {

	int position;

	std::string title, link, description;
	int day, month, year, hour, minute;

	std::cout << "Input a position -> ";
	std::cin >> position;
	std::cout << std::endl;

	std::cout << "Input a title from an event -> ";
	std::cin >> title;

	std::cout << "Input a link from an event -> ";
	std::cin >> link;

	std::cout << "Input a description from an event -> ";
	std::cin >> description;

	std::cout << "Input a day from an event -> ";
	std::cin >> day;

	std::cout << "Input a month from an event -> ";
	std::cin >> month;

	std::cout << "Input a year from an event -> ";
	std::cin >> year;

	std::cout << "Input a hour from an event -> ";
	std::cin >> hour;

	std::cout << "Input a minute from an event -> ";
	std::cin >> minute;

	this->service.updateEvent_Services(position, Event(title, description, link, day, month, year, hour, minute, 0));
	std::cout << "Event was updated!\n";
}

void Ui::listEventsAdmin_Ui() {
	for (int i = 0; i < this->service.getSize_Services(); ++i)
	{ 
		std::string afis = std::to_string(i) + ". " + this->service.getEvent_Services(i).toString();
		std::cout << afis;
	}
}


void Ui::addEventsUser_Ui() {

	int month;

	std::cout << "Input a month to see events or 0 to display all -> ";
	std::cin >> month;
	std::cout << std::endl;

	if (month < 0 or month > 12)
		std::cout << "Invalide month!\n\n";
	else
		if(month == 0)
		{
			for (int i = 0; i < this->service.getSize_Services(); ++i)
			{
				std::string op = std::string("start ").append(this->service.getEvent_Services(i).getLink());
				system(op.c_str());

				std::cout << this->service.getEvent_Services(i).toString();

				std::cout << "Input 1 to add or 0 to go to the next -> ";
				int command;
				std::cin >> command;
				std::cout << std::endl;

				if(command == 1)
					if (this->service.increasePeople_Services(i))
						std::cout << "Event was added!\n\n";
					else
						std::cout << "Event wasn't add!\n\n";
			}

			std::cout << "List is done\n\n";
		}
		else
		{
			for (int i = 0; i < this->service.getSize_Services(); ++i)
				if(this->service.getEvent_Services(i).getMonth() == month)
				{
					std::string op = std::string("start ").append(this->service.getEvent_Services(i).getLink());
					system(op.c_str());

					std::cout << this->service.getEvent_Services(i).toString();

					std::cout << "Input 1 to add or 0 to go to the next -> ";
					int command;
					std::cin >> command;
					std::cout << std::endl;

					if (command == 1)
						if (this->service.increasePeople_Services(i))
							std::cout << "Event was added!\n\n";
						else
							std::cout << "Event wasn't add!\n\n";
				}

			std::cout << "List is done\n\n";
		}
	
}

void Ui::listEventsUser_Ui() {

	int count = 0;

	for (int i = 0; i < this->service.getSize_Services(); ++i)
		if (this->service.getEvent_Services(i).getPeoples() == 1)
		{
			std::string print = std::to_string(count) + ". "+  this->service.getEvent_Services(i).toString();
			std::cout << print;
			++count;
		}
}

void Ui::deleteEventUser_Ui()
{
	for (int i = 0; i < this->service.getSize_Services(); ++i)
		if (this->service.getEvent_Services(i).getPeoples() == 1)
			std::cout << this->service.getEvent_Services(i).toString();

	std::string title;

	std::getline(std::cin, title);
	std::cout << "Input a title to delete an event -> ";
	std::getline(std::cin, title);
	std::cout << std::endl;

	for (int i = 0; i < this->service.getSize_Services(); ++i)
		if (this->service.getEvent_Services(i).getTitle() == title and this->service.getEvent_Services(i).getPeoples() == 1)
			if (this->service.decreasePeople_Services(i))
				std::cout << "Event was deleted!\n\n";
			else
				std::cout << "Event wasn't deleted!\n\n";
}

