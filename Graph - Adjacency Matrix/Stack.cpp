#include "stack.h"
#include "stdio.h"
#include "iostream"
StackNode* createStackNode(Student *s)
{
	StackNode *stack = (StackNode*)malloc(sizeof(StackNode));
	stack->info = s;
	stack->next = nullptr;

	return stack;
}

void pushNode(StackNode* &root, Student* s)
{
	StackNode* node = createStackNode(s);
	if (root == nullptr)
		root = node;
	else
	{
		node->next = root;
		root = node;
	}
}

Student* popNode(StackNode* &root)
{
	Student* s = nullptr;
	if (root != nullptr)
	{
		StackNode* tmp = root;
		s = tmp->info;
		root = root->next;
	}
	return s;
}


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

void enqueueNode(QueueNode* &root, Student* s)
{
	QueueNode* node = createQueueNode(s);
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

	}
	return s;
}
