#include "repository.h"

Repo* createRepo(int capacity,freeElem* freeElem)
{
	Repo* repo = (Repo*)malloc(sizeof(Repo));

	if (repo == NULL)
		return NULL;

	repo->elems = (Elem*)malloc(capacity * sizeof(Elem));

	if (repo->elems == NULL)
	{
		free(repo);
		return NULL;
	}

	repo->capacity = capacity;
	repo->len = 0;
	repo->freeElem = freeElem;

	return repo;
}

void freeRepo(Repo* repo)
{
	if (repo == NULL)
		return;

	for (int i = 0; i < getLen(repo); ++i)
		repo->freeElem(getElem_for_position(repo, i));
		
	free(repo->elems);
	free(repo);
}

void resizeRepo(Repo* repo)
{
	if (repo == NULL)
		return;

	repo->capacity *= 2;

	Elem* aux = (Elem*)realloc(repo->elems, sizeof(Elem) * getCapacity(repo));

	if (repo->elems == NULL)
		return;

	repo->elems = aux;
}

int getLen(Repo* repo)
{
	return repo->len;
}

int getCapacity(Repo* repo)
{
	return repo->capacity;
}
Elem* getElems(Repo* repo)
{
	return repo->elems;
}

void setLen(Repo* repo, int len)
{
	repo->len = len;

	if (repo->len == repo->capacity)
		resizeRepo(repo);
}

Elem* getElem_for_position(Repo* repo, int position)
{
	if (position < 0 || position >= repo->len)
		return NULL;

	return repo->elems[position];
}

void updateElem(Repo* repo, Elem elem, int position)
{
	if (position < 0 || position >= getLen(repo))
		return;

	repo->elems[position] = elem;
}

void addElem(Repo* repo, Elem elem, int position)
{
	if (repo == NULL)
		return;

	if (position >= 0 && position < getLen(repo))
		setQuantity(getElem_for_position(repo, position), getQuantity(getElem_for_position(repo, position)) + getQuantity(elem));
	else
	{
		repo->elems[getLen(repo)] = elem;
		setLen(repo, getLen(repo) + 1);
	}
}

void deleteElem(Repo* repo, int position)
{
	if (repo == NULL && (position < 0 || position >= getLen(repo)))
		return;

	for (int i = position; i < getLen(repo) - 1; ++i)
		repo->elems[i] = repo->elems[i + 1];

	repo->freeElem(getElem_for_position(repo, getLen(repo) - 1));

	setLen(repo, getLen(repo) -1);
}

void printElem(Repo* repo, int position)
{
	printMaterial(getElem_for_position(repo, position));
}

int checkExistance_repo(Repo* repo, Material* material)
{
	for (int i = 0; i < getLen(repo); ++i)
		if (equalMaterials(getElem_for_position(repo, i), material))
			return i;

	return -1;

}