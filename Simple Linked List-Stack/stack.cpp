#include "iostream"
#include "stdio.h"
using namespace std;

struct Student
{
	int id;
	char* name;
};

struct StackNode
{
	Student* info;
	StackNode* next;
};

Student* createStudent(int id, char* name)
{
	Student* s = (Student*)malloc(sizeof(Student));
	s->id = id;
	s->name=(char*)malloc(sizeof(name) + 1);
	strcpy(s->name, name);

	return s;
}

StackNode* createStackNode(Student *s)
{
	StackNode *stack = (StackNode*)malloc(sizeof(StackNode));
	stack->info = s;
	stack->next = nullptr;

	return stack;
}

void pushNode(StackNode* &root, StackNode* node)
{
	if (root == nullptr)
		root = node;
	else
	{
		node->next = root;
		root=node;
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
		free(tmp);
	}
	return s;
}

void printStack(StackNode* root)
{
	if (root)
	{
		printf("Id:%d Name:%s\n", root->info->id, root->info->name);
		printStack(root->next);
	}
}

void main()
{

	FILE* file = fopen("Text.txt", "r");
	int id; char buffer[50];
	StackNode* stack = nullptr;

	fscanf(file,"%d", &id);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		Student* s = createStudent(id, buffer);
		StackNode* node = createStackNode(s);
		pushNode(stack, node);
		fscanf(file,"%d", &id);
	}
	popNode(stack);
	printStack(stack);
}