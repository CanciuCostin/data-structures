#include "iostream"
#include "stdio.h"
#include <list>
#include <vector>
using namespace std;

struct Student
{
	int id;
	char* name;
};
struct GraphNode
{
	Student* info;
	GraphNode* adjList;
	GraphNode* next;
};


Student* createStudent(int id, char* name)
{
	Student* s = (Student*)malloc(sizeof(Student));
	s->id = id;
	s->name = (char*)malloc(sizeof(name) + 1);
	strcpy(s->name, name);

	return s;
}

GraphNode* createGraphNode(Student* s)
{
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	node->info = s;
	node->adjList = nullptr;
	node->next = nullptr;
	return node;
}

void insertAdjNode(GraphNode* &source, GraphNode* destination)
{

	if (source->adjList == nullptr)
		source->adjList = destination;
	else
	{
		GraphNode* tmp = source->adjList;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = destination;
	}
}
void insertGraphNode(GraphNode* &head, GraphNode* node)
{
	if (head == nullptr)
		head = node;
	else
	{
		GraphNode* tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void DF(GraphNode* head, int startVertex, int nrVertices)
{
	GraphNode** stack = (GraphNode**)malloc(sizeof(GraphNode*)*nrVertices);
	memset(stack, NULL, sizeof(GraphNode*)*nrVertices);
	bool* visited = (bool*)malloc(nrVertices*sizeof(bool));
	memset(visited, 0, nrVertices*sizeof(bool));
	int first = nrVertices;
	int last = nrVertices - 1;
	printf("\nDF Traversing\n");
	GraphNode* t = head;
	while (t->info->id != startVertex)
		t = t->next;
	stack[--first] = t;
	visited[t->info->id] = 1;
	printf("%d ", stack[first]->info->id);
	while (first <= last)
	{
		GraphNode* tmp = stack[first];
		bool ok = 0;
		GraphNode* tmp3 = tmp->adjList;
		while (tmp3&&!ok)
		{
			if (!visited[tmp3->info->id])
			{
				GraphNode* tmp2 = head;
				while (tmp2->info->id != tmp3->info->id)
					tmp2 = tmp2->next;
				stack[--first] = tmp2;
				printf("%d ", stack[first]->info->id);
				visited[tmp2->info->id] = 1;
				ok = 1;
			}
			tmp3 = tmp3->next;
		}
		if (!ok) 
			first++;
	}
	free(stack);
	free(visited);
}

void BF(GraphNode* head, int start,int nrVertices)
{
	bool* visited = (bool*)malloc(nrVertices*sizeof(bool));
	memset(visited, 0, nrVertices*sizeof(bool));
	list<GraphNode*> queue;
	printf("\nBF Traversing\n");
	GraphNode* t = head;
	while (t->info->id != start)
		t = t->next;
	queue.push_back(t);
	visited[t->info->id] = 1;
	printf("%d ", t->info->id);
	while (!queue.empty())
	{
		GraphNode* tmp = queue.front();
		while (tmp->adjList)
		{
			GraphNode* tmp2 = head;
			while (tmp2->info->id != tmp->adjList->info->id)
				tmp2 = tmp2->next;
			if (!visited[tmp2->info->id])
			{
				queue.push_back(tmp2);
				visited[tmp2->info->id] = 1;
				printf("%d ", tmp2->info->id);
			}
			tmp->adjList = tmp->adjList->next;
		}
		queue.pop_front();
	}
}
void main()
{
	FILE* file = fopen("Studenti.txt", "r");
	int id; char buffer[50];
    GraphNode* head = nullptr; 
	Student** students=nullptr;

	fscanf(file, "%d", &id);
	int j = 0;
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		j++;
		students = (Student**)realloc(students, j*sizeof(Student*));
		Student* s = createStudent(id, buffer);
		students[j - 1] = s;
		GraphNode* node = createGraphNode(students[j - 1]);
		insertGraphNode(head, node);
		fscanf(file, "%d", &id);
	}
	fclose(file);

	file = fopen("Conexiuni.txt", "r");
	int s, d;
	fscanf(file, "%d %d", &s, &d);
	while (!feof(file))
	{
		GraphNode* tmp = head;

		while (tmp->info->id != s)
			tmp = tmp->next;
		GraphNode* destination = createGraphNode(students[d]);
		insertAdjNode(tmp, destination);
		fscanf(file, "%d %d", &s, &d);
	}
	/*GraphNode* copy = head;
	while (copy)
	{
		cout << copy->info->id << ":";
		GraphNode* adj = copy->adjList;
		while (adj)
		{
			cout << adj->info->id << " ";
			adj=adj->next;
		}
		cout << endl;
		copy=copy->next;
	}*/

	GraphNode* head2 = head;
	DF(head, 3, 5);
	BF(head2, 3, 5);
	
	for (int i = 0; i < j; i++)
		free(students[i]);
	free(students);
	while (head)
	{
		GraphNode* tmp = head;
		while (head->adjList)
		{
			GraphNode* adj = head->adjList;
			head->adjList = head->adjList->next;
			free(adj);
		}
		head = head->next;
		free(tmp);
	}



}