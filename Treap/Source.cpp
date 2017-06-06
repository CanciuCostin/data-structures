#include "iostream"
#include "stdio.h"
using namespace std;

struct Student
{
	int id;
	char* name;
};

struct TreeNode
{
	static int nrNodes;
	int priority;
	Student* info;
	TreeNode* left;
	TreeNode* right;
};
int TreeNode::nrNodes = 0;
Student* createStudent(int id, char* name)
{
	Student* s = (Student*)malloc(sizeof(Student));
	s->id = id;
	s->name = (char*)malloc(sizeof(name) + 1);
	strcpy(s->name, name);

	return s;
}

TreeNode* createTreeNode(Student *s,int priority)
{
	TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
	node->info = s;
	node->left = node->right = nullptr;
	node->priority = priority;
	return node;
}

TreeNode* SRR(TreeNode* pivot)
{
	TreeNode* desc = pivot->left;
	pivot->left = desc->right;
	desc->right = pivot;

	return desc;
}

TreeNode* SRL(TreeNode* pivot)
{
	TreeNode* desc = pivot->right;
	pivot->right = desc->left;
	desc->left = pivot;

	return desc;
}

void insertNode(TreeNode* & root, TreeNode* node)
{
	if (root == nullptr)
	{
		root = node;
		TreeNode::nrNodes++;
	}
	else
		if (root->info->id > node->info->id)
		{
			insertNode(root->left, node);
			if (root->left&&root->priority < root->left->priority)
				root = SRR(root);
		}
		else
			if (root->info->id < node->info->id)
			{
				insertNode(root->right, node);
				if (root->right&&root->priority < root->right->priority)
					root = SRL(root);
			}
			else
				printf("\nThe node already exists!\n");
}

void inOrder(TreeNode* root)
{
	if (root)
	{
		inOrder(root->left);
		printf("Priority:%d |Id:%d Name:%s\n", root->priority,root->info->id, root->info->name);
		inOrder(root->right);
	}
}


void deleteNode(TreeNode* &root, int id)
{
	if (root == nullptr)
		printf("\nThe node does not exists!\n");
	else
		if (root->info->id == id)
			if (!root->left && !root->right)
			{
				free(root->info);
				free(root);
				root = nullptr;
			}
			else
					if((root->left&&!root->right)||(root->left->priority > root->right->priority))
				{
					root = SRR(root);
					deleteNode(root->right, id);
				}
				else
				{
					root = SRL(root);
					deleteNode(root->left, id);
				}
		else
			if (root->info->id > id)
				deleteNode(root->left, id);
			else
				deleteNode(root->right, id);
}


void main()
{
	FILE* file = fopen("Text.txt", "r");
	int id; char buffer[50]; int priority;
	TreeNode* root = nullptr;

	fscanf(file, "%d %d", &id,&priority);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		Student* s = createStudent(id, buffer);
		TreeNode* node = createTreeNode(s,priority);
		insertNode(root, node);
		fscanf(file, "%d %d", &id, &priority);

	}
	deleteNode(root, 2);
	inOrder(root);
	cout << endl << TreeNode::nrNodes;




}