#include "services.h"

Services* createServices(Repo* repo)
{
	Services* services = (Services*)malloc(sizeof(Services));

	if (services == NULL)
		return NULL;

	services->repo = repo;

	return services;
}

Repo* getRepo(Services* services)
{
	return services->repo;
}

void freeServices(Services* services)
{
	if (services == NULL)
		return;

	freeRepo(getRepo(services));
	free(services);
}

void addMaterial_services(Services* services, Material* material)
{
	int index = checkExistance_repo(getRepo(services), material);

	addElem(getRepo(services), material, index);
}

void updateMaterial_services(Services* services, Material* material, Material* new_material)
{
	int index = checkExistance_repo(getRepo(services), material);
	
	updateElem(getRepo(services), new_material, index);
}

void deleteMaterial_services(Services* sevices, Material* material)
{
	int index = checkExistance_repo(getRepo(sevices), material);

	deleteElem(getRepo(sevices), index);
}

void seeNOAvailableMaterialsString(Services* services, int day, int month, int year, char* string)
{
	if (strcmp(string, "N") != 0)
	{
		for (int i = 0; i < getLen(getRepo(services)); ++i)
			if (availableMaterial(getElem_for_position(getRepo(services), i), day, month, year) == 0 &&
				MaterialcontainingString(getElem_for_position(getRepo(services), i), string) == 1)
				printElem(getRepo(services), i);
	}
	else
	{
		for (int i = 0; i < getLen(getRepo(services)); ++i)
			if (availableMaterial(getElem_for_position(getRepo(services), i), day, month, year) == 0)
				printElem(getRepo(services), i);
	}
}

void seeMaterialsforSupplierLessthanQuantity(Services* services, char* supplier, int quantity)
{
	for (int i = 0; i < getLen(getRepo(services)); ++i)
		if (material_for_a_supplier(getElem_for_position(getRepo(services), i), supplier) == 1 &&
			MaterialcontainingLessthanaquantity(getElem_for_position(getRepo(services), i), quantity) == 1)
			printElem(getRepo(services), i);
}

void generateMaterials(Services* services)
{
	addMaterial_services(services, createMaterial("mere", "ana", 100, 1, 1, 2024));
	addMaterial_services(services, createMaterial("pere", "maria", 90, 2, 2, 2024));
	addMaterial_services(services, createMaterial("caise", "ion", 80, 3, 3, 2024));
	addMaterial_services(services, createMaterial("nuci", "vasile", 70, 4, 4, 2024));
	addMaterial_services(services, createMaterial("castane", "angela", 60, 5, 5, 2024));
	addMaterial_services(services, createMaterial("banane", "alin", 50, 6, 6, 2024));
	addMaterial_services(services, createMaterial("ananas", "cristi", 40, 7, 7, 2024));
	addMaterial_services(services, createMaterial("piersici", "marius", 30, 8, 8, 2024));
	addMaterial_services(services, createMaterial("prune", "mara", 20, 9, 9, 2024));
	addMaterial_services(services, createMaterial("struguri", "sebi", 10, 10, 10, 2024));
}

void seeAllMaterials(Services* services)
{
	if (services == NULL)
		return;

	for (int i = 0; i < getLen(getRepo(services)); ++i)
		printElem(getRepo(services), i);
}