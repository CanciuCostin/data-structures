#include "iostream"
#include "stdio.h"
using namespace std;

struct Student
{
	int id;
	char* name;
};
struct GraphNode
{
	Student* info;
	GraphNode* next;
};

struct Graph
{
	int nrVertices;
	GraphNode** adjList;
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
	node->next = nullptr;
	return node;
}

void insertNode(GraphNode* &head, GraphNode* node)
{
	if (head == NULL)
		head = node;
	else
	{
		GraphNode* tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void initGraph(Graph &g,int nrVertices) {
	g.nrVertices = nrVertices;
	g.adjList = (GraphNode**)malloc(nrVertices*sizeof(GraphNode*));
	memset(g.adjList, NULL, nrVertices*sizeof(GraphNode*));
}

void BF(Graph g, int startPoint)
{
	GraphNode** queue = (GraphNode**)malloc(sizeof(GraphNode*)*g.nrVertices);
	memset(queue, NULL, sizeof(GraphNode*)*g.nrVertices);
	bool* visited = (bool*)malloc(g.nrVertices*sizeof(bool));
	memset(visited, 0, g.nrVertices*sizeof(bool));
	int first = 0;
	int last = -1;
	printf("\nBF Traversing\n");
	queue[++last] = g.adjList[startPoint];
	visited[queue[first]->info->id] = 1;
	while (first <= last)
	{
		GraphNode* tmp = g.adjList[queue[first]->info->id];
		while (tmp)
		{
			if (!visited[tmp->info->id])
			{
				queue[++last] = tmp;
				visited[tmp->info->id] = 1;
			}
			tmp = tmp->next;
		}
		printf("%d ", queue[first]->info->id);
		first++;
	}
}


void main()
{
	FILE* file = fopen("Studenti.txt", "r");
	int id; char buffer[50];
	Graph graph; int nrStudents;
	

	fscanf(file, "%d", &nrStudents);
	Student** students = students = (Student**)malloc(nrStudents*sizeof(Student*));
	memset(students, NULL, nrStudents*sizeof(Student*));
	initGraph(graph, nrStudents);

	fscanf(file, "%d", &id);
	int j = 0;
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		students[j] = createStudent(id, buffer);
		GraphNode* node = createGraphNode(students[j]);
		insertNode(graph.adjList[j], node);
		j++;
		fscanf(file, "%d", &id);
	}
	fclose(file);

	file = fopen("Conexiuni.txt", "r");
	int s, d;
	fscanf(file, "%d %d", &s, &d);
	while (!feof(file))
	{
		GraphNode* source= createGraphNode(students[s]);
		GraphNode* destination= createGraphNode(students[d]);
		insertNode(graph.adjList[s], destination);
		insertNode(graph.adjList[d], source);
		fscanf(file, "%d %d", &s, &d);
	}
	Student* ss = createStudent(2, "dasda");
	GraphNode* node = createGraphNode(ss);
	BF(graph, 3);
	cout << endl;
}