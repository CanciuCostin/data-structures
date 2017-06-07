#include "iostream"
#include "stdio.h"
using namespace std;
//quadratic probbing
struct Student
{
	int id;
	char* name;
};

struct HashTable
{
	int size;
	int noElements;
	Student** elements;
};

Student* createStudent(int id, char* name)
{
	Student* s = (Student*)malloc(sizeof(Student));
	s->id = id;
	s->name = (char*)malloc(sizeof(name) + 1);
	strcpy(s->name, name);

	return s;
}

void initHashTable(HashTable &ht, int size)
{
	ht.size = size;
	ht.noElements = 0;
	ht.elements = (Student**)malloc(size*sizeof(Student*));
	memset(ht.elements, NULL, size*sizeof(Student*));
}

int fhash(int size, char* name)
{
	int sum = 0;
	for (int i = 0; i < strlen(name); i++)
		sum += name[i];
	return sum%size;
}
void insertHashTable(HashTable &ht, int id, char* name);

void reHashTable(HashTable &ht)
{

	ht.size *= 2;
	Student** newStudents = (Student**)malloc(ht.size*sizeof(Student*));
	memset(newStudents, NULL, ht.size*sizeof(Student*));
	for (int i = 0; i < ht.size/2; i++)
	{
		if (ht.elements[i]!=nullptr)
		{
			int poz = fhash(ht.size, ht.elements[i]->name);
			int nrCollisons = 0;
			while (newStudents[poz])
			{
				nrCollisons++;
				poz = poz + 2 * (nrCollisons *nrCollisons);
				if (poz >= ht.size )
					poz = poz %ht.size;
			}
			newStudents[poz] = ht.elements[i];
		}
	}

	free(ht.elements);
	ht.elements = newStudents;
	
	

}

void insertHashTable(HashTable &ht, int id, char* name)
{
	if (ht.noElements == ht.size)
		reHashTable(ht);
	Student* s = createStudent(id, name);
	int poz = fhash(ht.size, name);
	int nrCollisons = 0;
	while (ht.elements[poz])
	{
		nrCollisons++;
		poz = poz + 2 * (nrCollisons *nrCollisons);
		if (poz >= ht.size)
			poz = poz % ht.size;
	}
	ht.elements[poz] = s;
	ht.noElements++;
}


Student* getElement(HashTable ht, char* name)
{
	int poz = fhash(ht.size, name);
	int nrCollisions = 0;
	while (strcmp(ht.elements[poz]->name, name))
	{
		nrCollisions++;
		poz = poz + 2 * (nrCollisions *nrCollisions);
		if (poz >= ht.size)
			poz = poz % ht.size;
	}
	return ht.elements[poz];
}

void printHashTable(HashTable ht)
{
	for (int i = 0; i < ht.size; i++)
		if (ht.elements[i])
			printf("Key:%d Id:%d Name:%s\n", i, ht.elements[i]->id, ht.elements[i]->name);

}

void main()
{
	FILE* file = fopen("Text.txt", "r");
	int id; char buffer[50];
	HashTable ht;
	initHashTable(ht, 5);

	fscanf(file, "%d", &id);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		insertHashTable(ht, id, buffer);
		//printHashTable(ht); cout << endl;
		fscanf(file, "%d", &id);
	}
	printHashTable(ht);

	printf("\n\nGet element:%s\n", getElement(ht, "Stan Alina")->name);
}
