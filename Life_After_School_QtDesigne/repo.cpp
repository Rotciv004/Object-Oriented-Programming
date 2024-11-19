#include "repo.h"

using namespace std;
//create repo
Repo::Repo(){
	this->events = std::vector<Event>();
	this->file = "events.txt";
}
//create repo 
Repo::Repo(std::string file)
{
	this->file = move(file);
	this->takeFromFile_Repo();
}
// destroy repo
Repo::~Repo() {}
//add event 
void Repo::addEvent_Repo(const Event& event)
{
	if (find(this->events.begin(), this->events.end(), event) != this->events.end())
		throw EventInListException();

	this->events.push_back(event);
}
// remove an event by position
void Repo::removeEvent_Repo(int position)
{
	this->events.erase(this->events.begin() + position);
}
// update event by position and a new event
void Repo::updateEvent_Repo(int position, const Event& event)
{
	this->events[position] = event;
}
// get events list
std::vector<Event> Repo::getEvents_Repo() const
{
	return this->events;
}
// get event by position
Event Repo::getEvent_byPosition_Repo(int position) const
{
	if (position < 0 || position >= this->events.size())
		throw EventNotFoundException();

	return this->events[position];
}
// get size of the repo
int Repo::getSize_Repo() const
{
	return this->events.size();
}
// increase the number of people
void Repo::increasePeople_Repo(int position)
{
	Event event = this->getEvent_byPosition_Repo(position);

	event.setPeoples(1);

	this->updateEvent_Repo(position, event);
}
//decrease the number of peoples
void Repo::decreasePeople_Repo(int position)
{
	Event event = this->getEvent_byPosition_Repo(position);

	event.setPeoples(0);

	this->updateEvent_Repo(position, event);
}


void Repo::saveToFile_Repo()
{
	std::ofstream file(this->file);
	for (const auto& event : this->events)
	{
		file << event;
	}

	file.close();
}

void Repo::takeFromFile_Repo()
{
	std::ifstream file(this->file);
	Event event;

	while (file >> event)
		this->events.push_back(event);

	file.close();
}

void EventValidator::validateEvent(const Event& event)
{
	int currentYear = 2024, currentMonth = 4, currentDay = 6, currentHour = 10, currentMinute = 30;
	std::string errors;

	if (event.getTitle().size() <3)
		errors += "Title must have at least 3 characters!\n";

	if (event.getDescription().size() < 3)
		errors += "Description must have at least 3 characters!\n";

	const std::regex pattern("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");

	if (!std::regex_match(event.getLink(), pattern))
		errors+= "Link is invalid!\n";

	if (event.getYear() < currentYear ||
		(event.getYear() == currentYear && event.getMonth() < currentMonth) ||
		(event.getYear() == currentYear && event.getMonth() == currentMonth && event.getDay() < currentDay) ||
		(event.getYear() == currentYear && event.getMonth() == currentMonth && event.getDay() == currentDay && event.getHour() < currentHour) ||
		(event.getYear() == currentYear && event.getMonth() == currentMonth && event.getDay() == currentDay && event.getHour() == currentHour && event.getMinute() < currentMinute))
		errors += "Invalid date!\n";

	if (errors.size() > 0)
		throw InvalidHTTPException();
}