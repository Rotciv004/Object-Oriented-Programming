#include "material.h"

Material* createMaterial(char* name, char* supplier, int quantity, int day, int month, int year)
{
	Material* material = (Material*)malloc(sizeof(Material));

	if (material)
	{
		material->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));

		if (material->name)
		{
			strcpy(material->name, name);

			material->supplier = (char*)malloc(sizeof(char) * (strlen(supplier) + 1));

			if (material->supplier)
			{
				strcpy(material->supplier, supplier);

				material->quantity = quantity;
				material->day = day;
				material->month = month;
				material->year = year;

				return material;
			}
			else
			{
				free(material->name);
				free(material);
				return NULL;
			}
		}
		else
		{
			free(material);
			return NULL;
		}
	}
	else
		return NULL;
}

void freeMaterial(Material* material)
{
	if (material)
	{
		free(material->name);
		free(material->supplier);
		free(material);
	}
	return;
}

char* getName(Material* material)
{
	return material->name;
}

char* getSupplier(Material* material)
{
	return material->supplier;
}

int getQuantity(Material* material)
{
	return material->quantity;
}

int getDay(Material* material)
{
	return material->day;
}

int getMonth(Material* material)
{
	return material->month;
}

int getYear(Material* material)
{
	return material->year;
}
void setName(Material* material, char* name)
{
	material->name = name;
}

void setSupplier(Material* material, char* supplier)
{
	material->supplier = supplier;
}

void setQuantity(Material* material, int quantity)
{
	material->quantity = quantity;
}

void setDay(Material* material, int day)
{
	material->day = day;
}

void setMonth(Material* material, int month)
{
	material->month = month;
}

void setYear(Material* material, int year)
{
	material->year = year;
}

int MaterialcontainingString(Material* material, char* string)
{
	if (material)
	{
		if (strstr(getName(material), string) != NULL || strstr(getSupplier(material), string) != NULL)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int MaterialcontainingLessthanaquantity(Material* material, int quantity)
{
	if (material)
	{
		if (material->quantity < quantity)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int availableMaterial(Material* material, int day, int month, int year)
{
	if (material)
	{
		if (material->year < year)
			return 0;
		else
			if (material->year == year && material->month < month)
				return 0;
			else
				if (material->year == year && material->month == month && material->day < day)
					return 0;
				else
					return 1;
	}
	else
		return 0;
}

int equalMaterials(Material* material1, Material* material2)
{
	if (material1 == NULL || material2 == NULL)
		return 0;

	if (strcmp(getName(material1), getName(material2)) == 0 && strcmp(getSupplier(material1), getSupplier(material2)) == 0
		&& getDay(material1) == getDay(material2) && getMonth(material1) == getMonth(material2) && getYear(material1) == getYear(material2))
		return 1;
	else
		return 0;
}

int material_for_a_supplier(Material* material, char* supplier)
{
	if (material == NULL)
		return 0;
	if (strcmp(getSupplier(material), supplier) == 0)
		return 1;
	else
		return 0;
}

void printMaterial(Material* material)
{
	printf("Name: %s, Supplier: %s, Quantity: %d, Expiration date -> Day: %d, Month: %d, Year: %d\n", material->name,material->supplier,material->quantity,material->day,material->month,material->year);
}