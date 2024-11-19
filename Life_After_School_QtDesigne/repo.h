#pragma once
#include "event.h"

using namespace std;

class EventNotFoundException : public exception {
public:
const char* what() const noexcept override {
		return "Event not found!";
	}
};

class EventInListException : public exception {
public:
const char* what() const noexcept override {
		return "Event already in list!";
	}
};

class InvalidHTTPException : public exception {
public:
	const char* what() const noexcept override {
		return "Invalid HTTP !";
	}
};

class EventValidator
{
public:
	static void validateEvent(const Event& event);
};

class FileWrite {
public:
	virtual void writeToFile(const std::vector<Event>& events, const string& fileName) = 0;
};

class CSVWriter : public FileWrite {
public:
	void writeToFile(const std::vector<Event>& events, const string& fileName) override {
		ofstream file(fileName + ".csv");

		for (const auto& event : events) {
			file << event.getTitle() << "," << event.getDescription() <<"," << event.getDay() << "," << event.getMonth() << "," << event.getYear() << "," << event.getHour() << "," << event.getMinute() << "," << event.getPeoples() <<"," << event.getLink() << "\n";
		}
		file.close();
	};
};

class HTMLWriter : public FileWrite {
public:
	void writeToFile(const vector<Event>& events, const string& fileName) override {
		ofstream file(fileName + ".html");

		file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Events</title>\n</head>\n<body>\n<table border=\"1\">\n<tr>\n<th>Title</th>\n<th>Description</th>\n<th>Link</th>\n<th>Day</th>\n<th>Month</th>\n<th>Year</th>\n<th>Hour</th>\n<th>Minute</th>\n<th>People</th>\n</tr>\n";

		for (const auto& event : events) {
			file << "<tr>\n<td>" << event.getTitle() << "</td>\n<td>" << event.getDescription() << "</td>\n<td>" << event.getDay() << "</td>\n<td>" << event.getMonth() << "</td>\n<td>" << event.getYear() << "</td>\n<td>" << event.getHour() << "</td>\n<td>" << event.getMinute() << "</td>\n<td>" << event.getPeoples() << "</td>\n<td>" << event.getLink() << "</td>\n</tr>\n";
		}

		file << "</table>\n</body>\n</html>";
		file.close();
	};
};

class Repo
{
private:
	std::vector<Event> events;
	std::string file;

public:
	Repo();
	Repo(std::string file);
	~Repo();

	void addEvent_Repo(const Event& event);
	void removeEvent_Repo(int position);
	void updateEvent_Repo(int position, const Event& event);
	void increasePeople_Repo(int position);
	void decreasePeople_Repo(int position);

	int getSize_Repo() const;

	std::vector<Event> getEvents_Repo() const;
	Event getEvent_byPosition_Repo(int position) const;

	void saveToFile_Repo();
	void takeFromFile_Repo();

};
