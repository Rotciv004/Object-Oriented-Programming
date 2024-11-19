#pragma once
#include <string>
#include <iostream>
#include <regex>
#include <sstream>
#include <initializer_list>
#include <ctime>
#include <cassert>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <algorithm>

class Event
{
	std::string title, description, link;
	int day, month, year, hour, minute, peoples;

public:
	Event(const std::string& title = "", const std::string& description = "", const std::string& link = "", int day = 0, int month = 0, int year = 0, int hour = 0, int minute = 0, int peoples = 0);
	~Event();
	Event(const Event& event);

	Event& operator=(const Event& event);
	bool operator==(const Event& event) const;

	std::string getTitle() const;
	std::string getDescription() const;
	std::string getLink() const;
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	int getHour() const;
	int getMinute() const;
	int getPeoples() const;

	void setTitle(const std::string& title);
	void setDescription(const std::string& description);
	void setDateTime(int day, int month, int year, int hour, int minute);
	void setLink(const std::string& link);
	void setPeoples(int peoples);

	std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, const Event& event);
	friend std::istream& operator>>(std::istream& is, Event& event);

};
