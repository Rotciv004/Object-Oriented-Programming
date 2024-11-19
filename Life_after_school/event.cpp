#include "event.h"
//create Event
Event::Event(const std::string& title, const std::string& description, const std::string& link, int day, int month, int year, int hour, int minute, int peoples) : title{ title }, description{ description }, link{ link }, day{ day }, month{ month }, year{ year }, hour{ hour }, minute{ minute }, peoples{ peoples } {};
//destroyEvent
Event::~Event() {}
//create Event
Event::Event(const Event& event)
{
	this->title = event.title;
	this->description = event.description;
	this->link = event.link;
	this->day = event.day;
	this->month = event.month;
	this->year = event.year;
	this->hour = event.hour;
	this->minute = event.minute;
	this->peoples = event.peoples;
}
// define an operator to atribute some values
Event& Event::operator=(const Event& event)
{
	if (this == &event)
		return *this;

	this->title = event.title;
	this->description = event.description;
	this->link = event.link;
	this->day = event.day;
	this->month = event.month;
	this->year = event.year;
	this->hour = event.hour;
	this->minute = event.minute;
	this->peoples = event.peoples;

	return *this;
}
// define an operator to compare two values
bool Event::operator==(const Event& event) const
{
	return this->title == event.title;
}
// get title
std::string Event::getTitle() const
{
	return this->title;
}
//get description
std::string Event::getDescription() const
{
	return this->description;
}
//get link
std::string Event::getLink() const
{
	return this->link;
}
//get day
int Event::getDay() const
{
	return this->day;
}
//get month
int Event::getMonth() const
{
	return this->month;
}
//get year
int Event::getYear() const
{
	return this->year;
}
//get hour
int Event::getHour() const
{
	return this->hour;
}
//get minute
int Event::getMinute() const
{
	return this->minute;
}
// get peoples
int Event::getPeoples() const
{
	return this->peoples;
}
// set title
void Event::setTitle(const std::string& title)
{
	this->title = title;
}

void Event::setDescription(const std::string& description)
{
	this->description = description;
}

void Event::setDateTime(int day, int month, int year, int hour, int minute)
{
	this->day = day;
	this->month = month;
	this->year = year;
	this->hour = hour;
	this->minute = minute;
}

void Event::setLink(const std::string& link)
{
	this->link = link;
}

void Event::setPeoples(int peoples)
{
	this->peoples = peoples;
}

std::string Event::toString() const
{
	return this->title + " " + this->description + " " + this->link + " " + std::to_string(this->day) + "." + std::to_string(this->month) + "." + std::to_string(this->year) + " " + std::to_string(this->hour) + ":" + std::to_string(this->minute) + " " + std::to_string(this->peoples) +"\n";
}

std::ostream& operator<<(std::ostream & os, const Event & event)
{
	os << event.getTitle() << "," << event.getDescription() << "," << event.getDay() << "," << event.getMonth() << "," << event.getYear() << "," << event.getMinute() << "," << event.getHour()<< "," <<event.getPeoples() << "," << event.getLink() << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Event& event)
{
	std::string title, description, link, day, month, year, minute, hour, peoples,line;
	std::getline(is,line);

	if (line.empty())
		return is;

	std::stringstream stream(line);

	std::getline(stream, title, ',');
	event.title = title;

	std::getline(stream, description, ',');
	event.description = description;

	std::getline(stream, day, ',');
	event.day = stoi(day);

	std::getline(stream, month, ',');
	event.month = stoi(month);

	std::getline(stream, year, ',');
	event.year = stoi(year);

	std::getline(stream, minute, ',');
	event.minute = stoi(minute);

	std::getline(stream, hour, ',');
	event.hour = stoi(hour);

	std::getline(stream, peoples, ',');
	event.peoples = stoi(peoples);

	std::getline(stream, link, ',');
	event.link = link;

	return is;

}
