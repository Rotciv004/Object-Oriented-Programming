#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
	int day, month, year,quantity;
	char* name;
	char* supplier;
}Material;

Material* createMaterial(char* name, char* supplier, int quantity, int day, int month, int year);
void freeMaterial(Material* material);
char* getName(Material* material);
char* getSupplier(Material* material);
int getQuantity(Material* material);
int getDay(Material* material);
int getMonth(Material* material);
int getYear(Material* material);
void setName(Material* material, char* name);
void setSupplier(Material* material, char* supplier);
void setQuantity(Material* material, int quantity);
void setDay(Material* material, int day);
void setMonth(Material* material, int month);
void setYear(Material* material, int year);
int MaterialcontainingString(Material* material, char* string);
int MaterialcontainingLessthanaquantity(Material* material, int quantity);
int availableMaterial(Material* material, int day, int month, int year);
void printMaterial(Material* material);
int equalMaterials(Material* material1, Material* material2);
int material_for_a_supplier(Material* material, char* supplier);