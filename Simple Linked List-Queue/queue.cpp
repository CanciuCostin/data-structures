#include "iostream"
#include "stdio.h"
using namespace std;

struct Student
{
	int id;
	char* name;
};

struct QueueNode
{
	Student* info;
	QueueNode* next;
};

Student* createStudent(int id, char* name)
{
	Student* s = (Student*)malloc(sizeof(Student));
	s->id = id;
	s->name = (char*)malloc(sizeof(name) + 1);
	strcpy(s->name, name);

	return s;
}

QueueNode* createQueueNode(Student *s)
{
	QueueNode *queue = (QueueNode*)malloc(sizeof(QueueNode));
	queue->info = s;
	queue->next = nullptr;

	return queue;
}

void enqueueNode(QueueNode* &root, QueueNode* node)
{
	if (root == nullptr)
		root = node;
	else
	{
		QueueNode* tmp = root;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

Student* dequeueNode(QueueNode* &root)
{
	Student* s = nullptr;
	if (root != nullptr)
	{
		QueueNode* tmp = root;
		s = tmp->info;
		root = root->next;
		free(tmp);
	}
	return s;
}

void printqueue(QueueNode* root)
{
	if (root)
	{
		printf("Id:%d Name:%s\n", root->info->id, root->info->name);
		printqueue(root->next);
	}
}

void main()
{

	FILE* file = fopen("Text.txt", "r");
	int id; char buffer[50];
	QueueNode* queue = nullptr;

	fscanf(file, "%d", &id);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		Student* s = createStudent(id, buffer);
		QueueNode* node = createQueueNode(s);
		enqueueNode(queue, node);
		fscanf(file, "%d", &id);
	}
	dequeueNode(queue);
	printqueue(queue);
}