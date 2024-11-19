#pragma once
#include "repo.h"


class Service
{
private:

	Repo repo;
	string format;
public:

	Service();
	~Service();

	void addEvent_Services(const Event& event);
	void removeEvent_Services(int position);
	void updateEvent_Services(int position, Event event);

	bool increasePeople_Services(int position);
	bool decreasePeople_Services(int position);

	std::vector<Event> getEvents_Services() const;
	Event getEvent_Services(int position) const;

	int getSize_Services() const;

	void setFileFormat(string format);
	void openEventListFile(vector<Event>& events);

	void saveToFile_Services(string fileName);
	void takeFromFile_Services();


};
