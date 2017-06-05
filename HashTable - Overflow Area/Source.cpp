#include "iostream"
#include "stdio.h"
using namespace std;
//re-hashing
struct Student
{
	int id;
	char* name;
};

struct overflowList
{
	Student* data;
	overflowList* next;
};

struct HashTable
{
	int size;
	int noElements;
	Student** elements;
	overflowList* overflowArea;

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
	ht.overflowArea = nullptr;
}
overflowList* createNode(Student* s)
{
	overflowList* node = (overflowList*)malloc(sizeof(overflowList));
	node->data = s;
	node->next = nullptr;

	return node;
}

void insertNode(overflowList* &overflowArea, overflowList* node)
{
	if (!overflowArea)
		overflowArea = node;
	else
	{
		overflowList* tmp = overflowArea;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}


int fhash(int size, char* name)
{
	int sum = 0;
	for (int i = 0; i < strlen(name); i++)
		sum += name[i];
	return sum%size;
}
void reHashTable(HashTable &ht)
{

	ht.size *= 2;
	Student** newStudents = (Student**)malloc(ht.size*sizeof(Student*));
	overflowList* area = nullptr;

	memset(newStudents, NULL, ht.size*sizeof(Student*));
	for (int i = 0; i < ht.size / 2; i++)
	{
		if (ht.elements[i] != nullptr)
		{
			int poz = fhash(ht.size, ht.elements[i]->name);
			if (newStudents[poz])
			{
				overflowList* node = createNode(ht.elements[i]);
				insertNode(area, node);
			}
			else
				newStudents[poz] = ht.elements[i];
		}
	}
	free(ht.elements);
	ht.elements = newStudents;
}
void insertHashTable(HashTable &ht, char* name, int id)
{
	if (ht.noElements == ht.size)
		reHashTable(ht);
	int poz = fhash(ht.size, name);
	Student* s = createStudent(id, name);
	if (!ht.elements[poz])
	{
		ht.elements[poz] = s;
		ht.noElements++;
	}
	else
	{
		overflowList* node = createNode(s);
		insertNode(ht.overflowArea, node);
	}
}

Student* getElement(HashTable ht, char* name)
{
	Student* s = nullptr;
	int poz = fhash(ht.size, name);
	if (!strcmp(ht.elements[poz]->name, name))
		s = ht.elements[poz];
	else
	{
			overflowList* tmp = ht.overflowArea;
			while (strcmp(tmp->data->name,name))
				tmp = tmp->next;
			s = tmp->data;
	}

	return s;
}

void printHashTable(HashTable ht)
{
	for (int i = 0; i < ht.size;i++)
		if (ht.elements[i])
		    printf("Key:%d Id:%d Name:%s\n", i, ht.elements[i]->id, ht.elements[i]->name);
	printf("\nOverflow Area\n");
	while (ht.overflowArea)
	{
		printf("Id:%d Name:%s\n", ht.overflowArea->data->id, ht.overflowArea->data->name);
		ht.overflowArea = ht.overflowArea->next;
	}
}

void main()
{
	FILE* file = fopen("Text.txt", "r");
	int id; char buffer[50];
	HashTable ht;
	initHashTable(ht, 2);

	fscanf(file, "%d", &id);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		insertHashTable(ht, buffer, id);
		fscanf(file, "%d", &id);
	}
	printHashTable(ht);

	printf("\n\nGet element:%s\n", getElement(ht, "Stan Alina")->name);
}
