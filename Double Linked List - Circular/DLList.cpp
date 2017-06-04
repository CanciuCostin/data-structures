//circular double linked list
//insertion is done at the tail, implementation is FIFO(queue)
#include "iostream"
#include "stdio.h"
using namespace std;
struct Student
{
	int id;
	char* name;
};

struct DLList
{
	Student* info;
	DLList* next;
	DLList* prev;
};

Student* createStudent(int id, char* name)
{
	Student* s = (Student*)malloc(sizeof(Student));
	s->id = id;
	s->name = (char*)malloc(sizeof(name) + 1);
	strcpy(s->name, name);

	return s;
}

DLList* createDLLNode(Student *s)
{
	DLList *node = (DLList*)malloc(sizeof(DLList));
	node->info = s;
	node->next = nullptr;
	node->prev = nullptr;

	return node;
}

void insertDLList(DLList* &root, DLList* node)
{
	if (root == nullptr)
	{
		root = node;
		root->next = root->prev = root;
	}
	else
	{
		DLList* tmp = root;
		while (tmp->next != root)
			tmp = tmp->next;
		node->next = root;
		node->prev = tmp;
		tmp->next = node;
		root->prev = node;
	}
}

Student* deleteDLList(DLList* &root)
{
	Student* s = nullptr;
	if (root != nullptr)
	{
		if (root == root->next)
		{
			s = root->info;
			free(root);
			root = root->next = root->prev = nullptr;
		}
		else
		{
			DLList* tmp = root;
			s = tmp->info;
			root->next->prev = root->prev;
			root->prev->next = root->next;
			root = root->next;
			free(tmp);
		}
	}
	return s;
}

//extra:write a function to count the students with even id number
int countStudents(DLList* list)
{
	static DLList* copy = list->prev;
	if (list != copy)
		return list->info->id % 2 ? countStudents(list->next) : 1+countStudents(list->next);
	else
		return list->info->id % 2 ? 0 : 1;
}

//extra: write a function to insert a node after a given id
void insertAfterValue(DLList* &list, int value,int id,char *name)
{
	Student* newStudent = createStudent(id, name);
	DLList* newNode = createDLLNode(newStudent);
	DLList* tmp = list;
	do
	{
		tmp = tmp->next;
	} while (tmp != list&&tmp->info->id != value);
	if (tmp->info->id == value)
	{
		newNode->next = tmp->next;
		newNode->prev = tmp;
		tmp->next->prev = newNode;
		tmp->next = newNode;
	}
	else
		cout << "\nCannot insert student, value does not exists!\n";
}

void printList(DLList* root)
{
	DLList *tmp = root;
	do
	{
		printf("Id:%d Name:%s\n", tmp->info->id, tmp->info->name);
		tmp = tmp->next;
	} while (tmp != root);
}

void main()
{

	FILE* file = fopen("Text.txt", "r");
	int id; char buffer[50];
	DLList* list = nullptr;

	fscanf(file, "%d", &id);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		Student* s = createStudent(id, buffer);
		DLList* node = createDLLNode(s);
		insertDLList(list, node);
		fscanf(file, "%d", &id);
	}
	deleteDLList(list);
	insertAfterValue(list, 3, 8, "Gheorghe Vlad");
	printList(list);

	printf("\nStudents with even id:%d\n", countStudents(list));
}