#include "iostream"
#include "stdio.h"
using namespace std;


int const TREE_ORDER = 6;
int MAX_KEYS = TREE_ORDER - 1;


struct Student
{
	int id;
	char* name;
};
struct Btree
{
	Btree** desc;
	Student** info;
	int nrDesc;
	int nrKeys;
};


Btree* createNode()
{
	Btree* node = (Btree*)malloc(sizeof(Btree));
	node->nrDesc = 0;
	node->nrKeys = 0;
	node->desc = (Btree**)malloc(TREE_ORDER*sizeof(Btree*));
	memset(node->desc, NULL, TREE_ORDER*sizeof(Btree*));
	node->info = (Student**)malloc(TREE_ORDER*sizeof(Student*));
	memset(node->info, NULL, TREE_ORDER*sizeof(Student*));
	return node;
}

Student* createStudent(int id, char* name)
{
	Student* s = (Student*)malloc(sizeof(Student));
	s->id = id;
	s->name = (char*)malloc(sizeof(name) + 1);
	strcpy(s->name, name);

	return s;
}


void split_child(Btree* &parent,int poz, Btree* &child)
{
	Btree* rightChild = createNode();
	rightChild->nrKeys = MAX_KEYS  / 2;

	for (int j = 0; j < rightChild->nrKeys; j++)
	{
		rightChild->info[j] = child->info[j + MAX_KEYS/2+1];
		child->info[j + MAX_KEYS/2+1] = nullptr;
		
	}
	if (child->nrDesc > 0)
	{
		for (int j = 0; j < MAX_KEYS / 2; j++)
		{
			rightChild->desc[j] = child->desc[j + MAX_KEYS / 2];
			rightChild->nrDesc++;
			child->desc[j] = nullptr;
			child->nrDesc--;
		}
	}

	child->nrKeys = MAX_KEYS / 2;

	for (int j = parent->nrKeys; j>=poz+1; j--)
		parent->desc[j + 1] = parent->desc[j];
	parent->desc[poz + 1] = rightChild;
	parent->nrDesc++;
	
	for (int j = parent->nrKeys - 1; j >= poz; j--)
		parent->info[j + 1] = parent->info[j];

	parent->info[poz] = child->info[MAX_KEYS / 2];
	child->info[MAX_KEYS / 2] = nullptr;
	parent->nrKeys++;
}
void insertKey(Btree* &root, Student* s)
{
	int poz = root->nrKeys - 1;
	if (root->nrDesc == 0)
	{
		while (poz >= 0 && root->info[poz]->id > s->id)
		{
			root->info[poz + 1] = root->info[poz];
			poz--;
		}
		root->info[poz + 1] = s;
		root->nrKeys++;
	}
	else
	{
		while (poz >= 0 && root->info[poz]->id > s->id)
			poz--;
		if (root->desc[poz + 1]->nrKeys == MAX_KEYS)
		{
			split_child(root, poz + 1, root->desc[poz + 1]);
			if (root->info[poz + 1]->id < s->id)
				poz++;
		}
		insertKey(root->desc[poz + 1], s);
	}
}
void insert(Btree* &treeRoot, Student* s)
{
	if (treeRoot == nullptr)
	{
		treeRoot = createNode();
		treeRoot->info[0] = s;
		treeRoot->nrKeys++;
	}
	else
		if (treeRoot->nrKeys == MAX_KEYS)
		{
			Btree* newRoot = createNode();
			newRoot->desc[0] = treeRoot;
			newRoot->nrDesc++;
			split_child(newRoot, 0, treeRoot);
			int i = 0;
			if (newRoot->info[0]->id < s->id)
				i++;
			insertKey(newRoot->desc[i], s);
			treeRoot = newRoot;
		}
		else
			insertKey(treeRoot, s);
}



void traverse(Btree* root)
{
	if (root != NULL)
	{
		int i;
		for ( i = 0; i < root->nrKeys; i++)
		{
			if (root->nrDesc>0)
				traverse(root->desc[i]);
            printf("   %d %s\n", root->info[i]->id,root->info[i]->name);
		}
		if (root->desc[i] != NULL)
		    traverse(root->desc[i]);
	}
}


void main()
{

	FILE* file = fopen("Text.txt", "r");
	int id; char buffer[50];
	Btree* root = nullptr;

	fscanf(file, "%d", &id);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		Student* s = createStudent(id, buffer);
		insert(root, s);
		fscanf(file, "%d", &id);
	}
	cout << "InOrder Traversing:\n";
	traverse(root);
}