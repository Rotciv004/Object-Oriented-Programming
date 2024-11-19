
#pragma once
#include "services.h"

class Ui
{
private:
	Service service;

public:

	Ui();
	~Ui();

	int printUserMenu_Ui();
	int printAdminMenu_Ui();
	int printFirstMenu_Ui();
	int printFileFormatMenu_Ui();

	void runApp_Ui();

	void addEventAdmin_Ui();
	void removeEventAdmin_Ui();
	void updateEventAdmin_Ui();
	void listEventsAdmin_Ui();
	
	void addEventsUser_Ui();
	void listEventsUser_Ui();

	void deleteEventUser_Ui();
};
