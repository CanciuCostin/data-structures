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

struct DummyQueue
{
	QueueNode* first;
	QueueNode* last;
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

void initQueue(DummyQueue &dq)
{
	dq.first = dq.last = nullptr;
}

void enqueueNode(DummyQueue& dq, QueueNode* node)
{
	if (dq.first == nullptr)
		 dq.first = dq.last = node;
	else
	{
		dq.last->next = node;
		dq.last = node;
	}
}

Student* dequeueNode(DummyQueue &dq)
{
	Student* s = nullptr;
	if (dq.first)
	{
		if (dq.first == dq.last)
		{
			s = dq.first->info;
			free(dq.first);
			dq.first = dq.last = nullptr;
		}
		else
		{
			s = dq.first->info;
			QueueNode* tmp = dq.first;
			dq.first = dq.first->next;
			free(tmp);
		}
	}
	return s;
}

void printqueue(DummyQueue dq)
{
	QueueNode* node = dq.first;
	if (dq.first)
	{
		printf("Id:%d Name:%s\n", dq.first->info->id, dq.first->info->name);
		dq.first = dq.first->next;
		printqueue(dq);
	}
}

void main()
{

	FILE* file = fopen("Text.txt", "r");
	int id; char buffer[50];
	DummyQueue dq;
	initQueue(dq);

	fscanf(file, "%d", &id);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		Student* s = createStudent(id, buffer);
		QueueNode* node = createQueueNode(s);
		enqueueNode(dq, node);
		fscanf(file, "%d", &id);
	}
	dequeueNode(dq);
	printqueue(dq);
}