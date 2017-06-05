#include "iostream"
#include "stdio.h"
#include "stack.h"
#include <list>
using namespace std;


struct Graph
{
	int nrStudents;
	Student** vertices;
	int** matrix;
};
void initGraph(Graph &g,int nrStudents)
{
	g.nrStudents = 0;
	g.vertices = (Student**)malloc( nrStudents*sizeof(Student*));
	memset(g.vertices, NULL, nrStudents*sizeof(Student*));
	g.matrix = (int**)malloc(nrStudents *sizeof(int*));
	for (int i = 0; i < nrStudents; i++)
	{
		g.matrix[i] = (int*)malloc(nrStudents*sizeof(int));
		memset(g.matrix[i], 0, nrStudents*sizeof(int));
	}
}

void insertNode(Graph &g,int id,char* name)
{

	Student* node = createStudent(id, name);
	g.vertices[g.nrStudents++] = node;
}
void insertEdge(Graph g, int source, int destination)
{
	g.matrix[source][destination] = 1;
	g.matrix[destination][source] = 1;//unoriented graph
}
void DF(Graph g, char* startingStudent)
{
	static StackNode* head = nullptr;
	static bool* visited;
	if (startingStudent != NULL)
	{
		visited= (bool*)malloc(g.nrStudents*sizeof(bool));
		memset(visited, 0, g.nrStudents*sizeof(bool));
		printf("\n--DF Traversal--\n");
		for (int i = 0; i < g.nrStudents; i++)
			if (!strcmp(g.vertices[i]->name, startingStudent))
			{
				pushNode(head, g.vertices[i]);
				printf("%d %s\n", head->info->id,head->info->name);
				visited[head->info->id] = 1;
				break;
			}
	}
	while (head)
	{
		int ok = 0;
		for (int i = 0; i < g.nrStudents&&!ok; i++)
			if (g.matrix[head->info->id][i] && !visited[i])
			{
				ok = 1;
				pushNode(head, g.vertices[i]);
				visited[i] = 1;
				printf("%d %s\n", head->info->id, head->info->name);
			}
		if (ok == 0)
			popNode(head);
	}
}
void BF(Graph g, char* startingStudent)
{
	static QueueNode* head = nullptr;
	static bool* visited;
	if (startingStudent != NULL)
	{
		visited = (bool*)malloc(g.nrStudents*sizeof(bool));
		memset(visited, 0, g.nrStudents*sizeof(bool));
		printf("\n--BF Traversal--\n");
		for (int i = 0; i < g.nrStudents; i++)
			if (!strcmp(g.vertices[i]->name, startingStudent))
			{
				enqueueNode(head, g.vertices[i]);
				printf("%d %s\n", head->info->id, head->info->name);
				visited[head->info->id] = 1;
				break;
			}
	}
	while (head)
	{
		bool ok = 0;
		for (int i = 0; i < g.nrStudents;i++)
			if (g.matrix[head->info->id][i] && !visited[i])
			{
				enqueueNode(head, g.vertices[i]);
				visited[i] = 1;
				printf("%d %s\n", g.vertices[i]->id, g.vertices[i]->name);
				ok = 1;
			}
		dequeueNode(head);
	}

}


void BF2(Graph g,char* startingStudent)
{
	bool* visited = NULL;
	Student** queue = NULL;
	int first = 0, last = -1;
	visited = (bool*)malloc(g.nrStudents*sizeof(bool));
	queue = (Student**)malloc(g.nrStudents*sizeof(Student*));
	memset(visited, 0, g.nrStudents*sizeof(int));
	int startVertex;
	printf("\n--BF Traversal(Without extra structures)--\n");
	for (int i = 0; i < g.nrStudents;i++)
		if (!strcmp(g.vertices[i]->name, startingStudent))
		{
			queue[++last] = g.vertices[i];
			visited[g.vertices[i]->id] = 1;
			break;
		}

	while (first <= last)
	{
		
		for (int i = 0; i < g.nrStudents; i++)
			if (g.matrix[queue[first]->id][i]==1 && !visited[i])
			{
				
				visited[i] = 1;
				queue[++last] = g.vertices[i];
				

			}
		printf("%d %s\n", queue[first]->id, queue[first]->name);
		first++;
	}
}

int getNext(bool* visited, int* distances,int n)
{
	int max = INT_MAX;
	int next;
	for (int i = 0; i < n;i++)
		if (!visited[i] && distances[i] < max)
		{
			max = distances[i];
			next = i;
		}
	return next;
}

bool gata(bool* visited, int n)
{
	for (int i = 0; i < n; i++)
		if (!visited[i])
			return false;
	return true;
}
void Dijkstra(Graph g,int startVertex)
{
	bool* visited = (bool*)malloc(g.nrStudents*sizeof(bool));
	memset(visited, 0, g.nrStudents*sizeof(bool));
	int* distances = (int*)malloc(g.nrStudents*sizeof(int));
	for (int i = 0; i < g.nrStudents; i++)
		distances[i] = INT_MAX;
	int* prev = (int*)malloc(g.nrStudents*sizeof(int));
	memset(prev, -1, g.nrStudents*sizeof(int));
	distances[startVertex] = 0; visited[startVertex ]=1;
	for (int i = 0; i < g.nrStudents; i++)
		if (g.matrix[startVertex][i])
		{
			distances[i] = 1;
			prev[i] = startVertex;
		}

	while (!gata(visited, g.nrStudents))
	{
		int current = getNext(visited, distances, g.nrStudents);
		visited[current] = 1;
		for (int i = 0; i < g.nrStudents; i++)
		{
			if (g.matrix[current][i] == 1 && g.matrix[current][i] + distances[current] < distances[i])
			{
				distances[i] = g.matrix[current][i] + distances[current];
				prev[i] = current;
			}
		}
	}
		printf("\nDijksta--Starting Vertex:%d\n",startVertex);
		list<int> drum;
		for (int i = 0; i < g.nrStudents; i++)
		{
			drum.clear();
			if (i != startVertex)
			{
				printf("Path from %d to %d ->", startVertex, i);
				int k = i;
				do
				{
					drum.push_front(k);
					k = prev[k];
				}while (prev[k] != -1);
				drum.push_front(startVertex);
				for (list<int>::iterator it = drum.begin(); it != drum.end();it++)
					printf("%d ", *it);
				printf("\n");
			}
		}
}


void printMatrix(Graph g)
{
	for (int i = 0; i < g.nrStudents; i++)
	{
		for (int j = 0; j < g.nrStudents; j++)
			printf("%d ", g.matrix[i][j]);
		printf("\n");
	}
}

void main()
{
	FILE* file = fopen("Studenti.txt", "r");
	int id; char buffer[50];
	Graph graph; int nrStudents;

	fscanf(file, "%d", &nrStudents);
	initGraph(graph,nrStudents);

	fscanf(file, "%d", &id);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		insertNode(graph, id, buffer);
		fscanf(file, "%d", &id);
	}
	fclose(file);

	file = fopen("Conexiuni.txt", "r");
	int s, d;
	fscanf(file, "%d %d", &d, &s);

	while (!feof(file))
	{
		insertEdge(graph, s, d);
		fscanf(file, "%d %d", &d, &s);
	}
	printMatrix(graph);
	DF(graph, "Stan Alina");
	BF(graph, "Stan Alina");
	BF2(graph, "Stan Alina");
	cout << endl;
	Dijkstra(graph, 0);
}
