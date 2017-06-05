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
	Student* info;
	TreeNode* left;
	TreeNode* right;
};

Student* createStudent(int id, char* name)
{
	Student* s = (Student*)malloc(sizeof(Student));
	s->id = id;
	s->name = (char*)malloc(sizeof(name) + 1);
	strcpy(s->name, name);

	return s;
}

TreeNode* createTreeNode(Student *s)
{
	TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
	node->info = s;
	node->left = node->right = nullptr;

	return node;
}

void insertNode(TreeNode* & root, TreeNode* node)
{
	if (root == nullptr)
		root = node;
	else
		if (root->info->id > node->info->id)
			insertNode(root->left, node);
		else
			if (root->info->id < node->info->id)
				insertNode(root->right, node);
			else
				printf("\nThe node already exists!\n");
}

void inOrder(TreeNode* root)
{
	if (root)
	{
		inOrder(root->left);
		printf("Id:%d Name:%s\n", root->info->id, root->info->name);
		inOrder(root->right);
	}
}

void logicalDeletion(TreeNode* &root, TreeNode* &leftSubtree)
{
	if (leftSubtree->right)
		logicalDeletion(root,leftSubtree->right);
	else
	{
		free(root->info);
		root->info = leftSubtree->info;
		TreeNode* tmp = leftSubtree;
		leftSubtree = leftSubtree->left;
		free(leftSubtree);
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
				root  = nullptr;
			}
			else
				if (root->left&&!root->right)
				{
					TreeNode* tmp = root;
					root = root->left;
					tmp->info->name = nullptr;
					free(tmp->info);
					free(tmp);
					tmp = nullptr;
				}
				else
					if (!root->left&&root->right)
					{
						TreeNode* tmp = root;
						root = root->right;
						free(tmp->info);
						free(tmp);
						tmp = nullptr;
					}
					else
						logicalDeletion(root, root->left);
	else
		if (root->info->id > id)
			deleteNode(root->left, id);
		else
			deleteNode(root->right, id);
}

void test(TreeNode* &node)
{
	free(node->info->name);
	free(node->info);
	free(node);
	node = nullptr;
}

void main()
{
	FILE* file = fopen("Text.txt", "r");
	int id; char buffer[50];
	TreeNode* root = nullptr;

	fscanf(file, "%d", &id);
	while (!feof(file))
	{
		fgetc(file);
		fscanf(file, "%[^\n]s", buffer);
		Student* s = createStudent(id, buffer);
		TreeNode* node = createTreeNode(s);
		insertNode(root, node);
		fscanf(file, "%d", &id);
	}
	deleteNode(root, 3);
	inOrder(root);




}