#include "iostream"
#include "stdio.h"
using namespace std;

struct Student
{
	int id;
	char* name;
};

struct CollisionList
{
	Student* info;
	CollisionList* next;
};

struct HashTable
{
	int size;
	CollisionList** elements;
};

Student* createStudent(int id, char* name)
{
	Student* s = (Student*)malloc(sizeof(Student));
	s->id = id;
	s->name = (char*)malloc(sizeof(name) + 1);
	strcpy(s->name, name);

	return s;
}

CollisionList* createNode(Student *s)
{
	CollisionList *node = (CollisionList*)malloc(sizeof(CollisionList));
	node->info = s;
	node->next = nullptr;

	return node;
}

void initHashTable(HashTable &ht,int size)
{
	ht.size = size;
	ht.elements = (CollisionList**)malloc(size*sizeof(CollisionList*));
	memset(ht.elements, NULL, size*sizeof(CollisionList*));
}

int fhash(int size, char* name)
{
	int sum = 0;
	for (int i = 0; i < strlen(name); i++)
		sum += name[i];
	return sum%size;
}

void insertHashTable(HashTable ht, int id, char* name)
{
	Student* s = createStudent(id, name);
	CollisionList* node = createNode(s);
	int poz = fhash(ht.size, name);
	if (!ht.elements[poz])
		ht.elements[poz] = node;
	else
	{
		CollisionList* tmp = ht.elements[poz];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

Student* getElement(HashTable ht, char *name)
{
	int poz = fhash(ht.size, name);
	CollisionList* tmp = ht.elements[poz];
	while (strcmp(tmp->info->name,name))
		tmp = tmp->next;
	return tmp->info;

}

void removeElement(HashTable ht, char *name)
{
	int poz = fhash(ht.size, name);
	CollisionList* tmp = ht.elements[poz];
	while (strcmp(tmp->info->name, name))
		tmp = tmp->next;
	if (tmp->next == nullptr)
	{
		free(ht.elements[poz]);
		ht.elements[poz] = nullptr;
	}
	else
	{
		CollisionList* tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
		tmp2 = nullptr;
	}
}

void printHashTable(HashTable ht)
{
	for (int i = 0; i < ht.size; i++)
		if (ht.elements[i])
		{
			CollisionList* tmp = ht.elements[i];
			while (tmp)
			{
				printf("Key:%d Id:%d Name:%-20s     ", i, tmp->info->id, tmp->info->name);
				tmp = tmp->next;
			} 
			cout << endl;
		}

}

void main()
{
	FILE* file = fopen("Text.txt", "r");
	int id; char buffer[50];
	HashTable ht;
	initHashTable(ht, 10);

	fscanf(file, "%d", &id);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		insertHashTable(ht, id, buffer);
		fscanf(file, "%d", &id);
	}
	removeElement(ht, "Popescu Catalin");
	printHashTable(ht);

	printf("\n\nGet element:%s\n",getElement(ht, "Stan Alina")->name);
}