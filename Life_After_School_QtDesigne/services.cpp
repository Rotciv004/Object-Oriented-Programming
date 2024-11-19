#include "services.h"

Service::Service()
{
	this->repo = Repo();
}

Service::~Service() {}

void Service::addEvent_Services(const Event& event) 
{
	EventValidator::validateEvent(event);
	this->repo.addEvent_Repo(event);
}

void Service::removeEvent_Services(int position) 
{
	if (position<0 || position >=this->getSize_Services())
		throw EventNotFoundException();

	this->repo.removeEvent_Repo(position);
}

void Service::updateEvent_Services(int position, Event event)
{
	if (position < 0 || position >= this->getSize_Services())
		throw EventNotFoundException();

	EventValidator::validateEvent(event);

	this->repo.updateEvent_Repo(position, event);
}

bool Service::increasePeople_Services(int position)
{
	if (position >= 0 and position < this->getSize_Services())
	{
		this->repo.increasePeople_Repo(position);
		return true;
	}
	else
		return false;
}

std::vector<Event> Service::getEvents_Services() const
{
	return this->repo.getEvents_Repo();
}

Event Service::getEvent_Services(int position) const
{
	return this->repo.getEvent_byPosition_Repo(position);
}

int Service::getSize_Services() const
{
	return this->repo.getSize_Repo();
}

bool Service::decreasePeople_Services(int position)
{
	if (position >= 0 and position < this->getSize_Services())
	{
		this->repo.decreasePeople_Repo(position);
		return true;
	}
	else
		return false;
}

// print in a csv file or html
void Service::saveToFile_Services(string fileName)
{
	std::vector<Event> events = this->getEvents_Services();
	std::vector<Event> user_events;

	for (const auto& event : events)
		if (event.getPeoples() == 1)
			user_events.push_back(event);
	


	if (fileName == "csv") {
		FileWrite* writer = new CSVWriter();
		writer->writeToFile(user_events, fileName);
	}
	else
		if (fileName == "html")
		{
			FileWrite* writer = new HTMLWriter();
			writer->writeToFile(user_events, fileName);
		}
		else
			throw exception("Invalide format");

}
void Service::takeFromFile_Services()
{
	this->repo.takeFromFile_Repo();
}

void Service::setFileFormat(string format)
{
	this->format = format;
}

void Service::openEventListFile(vector<Event>& events)
{
	if (this->format == "csv")
	{
		CSVWriter writer;
		writer.writeToFile(events, "events");
		system("start events.csv");
	}
	else
		if (this->format == "html")
		{
			HTMLWriter writer;
			writer.writeToFile(events, "events");
			system("start events.html");
		}
}