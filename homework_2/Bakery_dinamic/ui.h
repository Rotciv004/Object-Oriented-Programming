#pragma once
#include "services.h"

typedef struct
{
	Services* services;
}Ui;

Ui* createUi(Services* services);
void startUi(Ui* ui);
void freeUi(Ui* ui);