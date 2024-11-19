#pragma once
#include "material.h"

typedef void* Elem;

typedef void (*freeElem)(Elem);

typedef struct
{
	int len, capacity;
	Elem* elems;
	freeElem freeElem;
}Repo;

Repo* createRepo(int capacity,freeElem* freeElem);
void freeRepo(Repo* repo);
void resizeRepo(Repo* repo);
int getLen(Repo* repo);
int getCapacity(Repo* repo);
Elem* getElems(Repo* repo);
void setLen(Repo* repo, int len);
Elem* getElem_for_position(Repo* repo, int position);
void addElem(Repo* repo, Elem elem, int position);
void updateElem(Repo* repo, Elem elem, int position);
void deleteElem(Repo* repo, int position);
void printElem(Repo* repo, int position);
int checkExistance_repo(Repo* repo, Material* material);