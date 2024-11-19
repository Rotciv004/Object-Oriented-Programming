#include "ui.h"

Ui* createUi(Services* services)
{
	Ui* ui = (Ui*)malloc(sizeof(Ui));

	if (ui == NULL)
		return;

	ui->services = services;

	return ui;
}

Services* getServices(Ui* ui)
{
	return ui->services;
}

void freeUi(Ui* ui)
{
	if (ui == NULL)
		return;

	freeServices(getServices(ui));
	free(ui);
}

void printMenu()
{
	printf("1.Add material\n");
	printf("2.Delete material\n");
	printf("3.Update material\n");
	printf("4.See all expired materials witch containing a string\n");
	printf("5.See all material form a supplier less than a quantity\n");
	printf("6.See all materials\n");
	printf("0.Exit\n\n");
}

void EXIT(Ui* ui)
{
	printf("You exit!");
}

void ADD_MATERIAL(Ui* ui)
{
	char name[20],supplier[20];
	int quantity, day, month, year;

	printf("Name: ");
	scanf("%s", name);
	printf("\n");

	printf("Supplier: ");
	scanf("%s", supplier);
	printf("\n");

	printf("Quantity: ");
	scanf("%d", &quantity);
	printf("\n");

	printf("day: ");
	scanf("%d", &day);
	printf("\n");

	printf("Month: ");
	scanf("%d", &month);
	printf("\n");

	printf("Year: ");
	scanf("%d", &year);
	printf("\n");

	addMaterial_services(getServices(ui), createMaterial(name, supplier, quantity, day, month, year));
}

void DELETE_MATERIAL(Ui* ui)
{
	char name[20], supplier[20];
	int quantity, day, month, year;

	printf("Name: ");
	scanf("%s", name);
	printf("\n");

	printf("Supplier: ");
	scanf("%s", supplier);
	printf("\n");

	printf("Quantity: ");
	scanf("%d", &quantity);
	printf("\n");

	printf("day: ");
	scanf("%d", &day);
	printf("\n");

	printf("Month: ");
	scanf("%d", &month);
	printf("\n");

	printf("Year: ");
	scanf("%d", &year);
	printf("\n");

	deleteMaterial_services(getServices(ui), createMaterial(name, supplier, quantity, day, month, year));
}

void UPDATE_MATERIAL(Ui* ui)
{
	char name_i[20], supplier_i[20];
	int quantity_i, day_i, month_i, year_i;

	printf("Initial material\n");

	printf("Name: ");
	scanf("%s", name_i);
	printf("\n");

	printf("Supplier: ");
	scanf("%s", supplier_i);
	printf("\n");

	printf("Quantity: ");
	scanf("%d", &quantity_i);
	printf("\n");

	printf("day: ");
	scanf("%d", &day_i);
	printf("\n");

	printf("Month: ");
	scanf("%d", &month_i);
	printf("\n");

	printf("Year: ");
	scanf("%d", &year_i);
	printf("\n\n");

	char name_n[20], supplier_n[20];
	int quantity_n, day_n, month_n, year_n;

	printf("New material\n");
	printf("Name: ");
	scanf("%s", name_n);
	printf("\n");

	printf("Supplier: ");
	scanf("%s", supplier_n);
	printf("\n");

	printf("Quantity: ");
	scanf("%d", &quantity_n);
	printf("\n");

	printf("day: ");
	scanf("%d", &day_n);
	printf("\n");

	printf("Month: ");
	scanf("%d", &month_n);
	printf("\n");

	printf("Year: ");
	scanf("%d", &year_n);
	printf("\n");

	updateMaterial_services(getServices(ui), createMaterial(name_i, supplier_i, quantity_i, day_i, month_i, year_i), 
		createMaterial(name_n, supplier_n, quantity_n, day_n, month_n, year_n));
}

void EXPIRED_MATERIALS_STRING(Ui* ui)
{
	int day, month, year;
	char string[20];

	printf("Input current date\n");
	printf("day: ");
	scanf("%d", &day);
	printf("\n");

	printf("Month: ");
	scanf("%d", &month);
	printf("\n");

	printf("Year: ");
	scanf("%d", &year);
	printf("\n");

	printf("Input a string or N\n");
	printf("String: ");
	scanf("%s", string);
	printf("\n");

	seeNOAvailableMaterialsString(getServices(ui), day, month, year, string);
}

void MATERIAL_SUPPLIER_QUANTITY(Ui* ui)
{
	char supplier[20];
	int quantity;

	printf("Supplier: ");
	scanf("%s", supplier);
	printf("\n");

	printf("Quantity: ");
	scanf("%d", &quantity);
	printf("\n");

	seeMaterialsforSupplierLessthanQuantity(getServices(ui), supplier, quantity);
}

void SEE_MATERIALS(Ui* ui)
{
	seeAllMaterials(getServices(ui));
}

void startUi(Ui* ui)
{
	generateMaterials(getServices(ui));

	while (1)
	{
		printMenu();
		int command;

		printf("Input a command -> ");
		scanf("%d", &command);

		if (command == 1)
		{
			ADD_MATERIAL(ui);
		}
		else
			if (command == 2)
			{
				DELETE_MATERIAL(ui);
			}
			else
				if (command == 3)
				{
					UPDATE_MATERIAL(ui);
				}
				else
					if (command == 4)
					{
						EXPIRED_MATERIALS_STRING(ui);
					}
					else
						if (command == 5)
						{
							MATERIAL_SUPPLIER_QUANTITY(ui);
						}
						else
							if (command == 6)
							{
								SEE_MATERIALS(ui);
							}
							else
								if (command == 0)
								{
									EXIT(ui);
									break;
								}
								else
									printf("Invalid command!\n");
	}
}