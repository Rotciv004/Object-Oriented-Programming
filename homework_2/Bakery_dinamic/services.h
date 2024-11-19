#pragma once
#include "repository.h"

typedef struct
{
	Repo* repo;
}Services;

Services* createServices(Repo* repo);
Repo* getRepo(Services* services);
void freeServices(Services* services);
void addMaterial_services(Services* services, Material* material);
void updateMaterial_services(Services* services, Material* material, Material* new_material);
void deleteMaterial_services(Services* sevices, Material* material);
void seeNOAvailableMaterialsString(Services* services, int day, int month, int year, char* string);
void seeMaterialsforSupplierLessthanQuantity(Services* services, char* supplier, int quantity);
void generateMaterials(Services* services);
void seeAllMaterials(Services* services);