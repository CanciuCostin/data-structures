#include "iostream"
#include "stdio.h"
#define PARENT (last-1)/2
#define LEFT_CHILD 2*first+1
#define RIGHT_CHILD 2*first+2
using namespace std;

struct Student
{
	int id;
	char* name;
};

struct HeapItem
{
	Student* info;
	int priority;
};

struct Heap
{
	int size;
	int noElements;
	HeapItem** elements;
};

Student* createStudent(int id, char* name)
{
	Student* s = (Student*)malloc(sizeof(Student));
	s->id = id;
	s->name = (char*)malloc(sizeof(name) + 1);
	strcpy(s->name, name);

	return s;
}

void initHeap(Heap &heap,int size)
{
	heap.size = size;
	heap.noElements = 0;
	heap.elements = (HeapItem**)malloc(sizeof(HeapItem*)*size);
	memset(heap.elements, 0, size*sizeof(HeapItem*));
}

HeapItem* createHeapItem(int priority, int id, char *name)
{
	Student* s = createStudent(id, name);
	HeapItem* heapItem = (HeapItem*)malloc(sizeof(HeapItem));
	heapItem->info = s;
	heapItem->priority = priority;
	return heapItem;
}

void reHeapUP(Heap &heap,int first,int last)
{
	if (first < last)
	{
		if (heap.elements[PARENT]->priority < heap.elements[last]->priority)
		{
			HeapItem* aux = heap.elements[PARENT];
			heap.elements[PARENT] = heap.elements[last];
			heap.elements[last] = aux;
			reHeapUP(heap, 0, PARENT);
		}
	}
}

void reHeapDown(Heap& heap, int first, int last)
{
	unsigned short maxChild;
	if (LEFT_CHILD <= last)
	{
		if (LEFT_CHILD == last)
			maxChild = LEFT_CHILD;
		else
			maxChild = heap.elements[LEFT_CHILD]->priority > heap.elements[RIGHT_CHILD]->priority ? LEFT_CHILD : RIGHT_CHILD;
		if (heap.elements[first]->priority < heap.elements[maxChild]->priority)
		{
			HeapItem* aux = heap.elements[first];
			heap.elements[first] = heap.elements[maxChild];
			heap.elements[maxChild] = aux;
			reHeapDown(heap, maxChild, last);
		}
	}
}

void insertHeap(Heap& heap,int priority,int id,char* name)
{
	if (heap.noElements < heap.size)
	{
		HeapItem* element = createHeapItem(priority, id, name);
		heap.elements[heap.noElements] = element;
		reHeapUP(heap, 0, heap.noElements++);
	}
}

HeapItem* deleteHeap(Heap &heap)
{
	HeapItem* item = nullptr;
	if (heap.noElements > 0)
	{
		item = heap.elements[0];
		heap.elements[0] = heap.elements[--heap.noElements];
		reHeapDown(heap, 0, heap.noElements-1);
	}
	return item;
}
void printHeap(Heap heap)
{
	for (int i = 0; i < heap.noElements; i++)
		printf("Priority:%d Id:%d Name:%s\n", heap.elements[i]->priority, heap.elements[i]->info->id, heap.elements[i]->info->name);
}
void main()
{
	Heap heap;
	initHeap(heap, 10);
	FILE* file = fopen("Text.txt", "r");
	int id; int priority; char buffer[50];

	fscanf(file, "%d", &id);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		fscanf(file, "%d", &priority);
		insertHeap(heap,priority,id,buffer);
		fscanf(file, "%d", &id);
		
	}
	deleteHeap(heap);
	printHeap(heap);

	
}