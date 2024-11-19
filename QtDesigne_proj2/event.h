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

using namespace std;

class Event {
private:
	string title, description, link;
	int day, month, year, hour, minutes, peoples;

public:

	Event(const string title = "", const string description = "", string link = "", int day = 0, int month = 0, int year = 0, int hour = 0, int minutes = 0, int peoples = 0): title(title), description(description), link(link), day(day), month(month), year(year), hour(hour), minutes(minutes), peoples(peoples) {}
	~Event() {}
};