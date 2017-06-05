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
	int balanceFactor;
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
	node->balanceFactor = 0;

	return node;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int getHeight(TreeNode* root)
{
	if (root)
		return 1 + max(getHeight(root->left), getHeight(root->right));
	else
		return 0;
}

int getBalanceBactor(TreeNode* root)
{
	return getHeight(root->right) - getHeight(root->left);
}

TreeNode* SRR(TreeNode* pivot)
{
	TreeNode* desc = pivot->left;
	pivot->left = desc->right;
	desc->right = pivot;
	
	pivot->balanceFactor = getBalanceBactor(pivot);
	desc->balanceFactor = getBalanceBactor(desc);

	return desc;
}

TreeNode* SRL(TreeNode* pivot)
{
	TreeNode* desc = pivot->right;
	pivot->right = desc->left;
	desc->left = pivot;
	
	pivot->balanceFactor = getBalanceBactor(pivot);
	desc->balanceFactor = getBalanceBactor(desc);

	return desc;
}

TreeNode* rebalanceTree(TreeNode* &pivot)
{
	pivot->balanceFactor = getBalanceBactor(pivot);
	TreeNode* desc = nullptr;
	if (pivot->balanceFactor == 2)
	{
		desc = pivot->right;
		if (desc->balanceFactor == -1)
		{
			desc = SRR(desc);
			pivot = SRL(pivot);
		}
		else
			pivot = SRL(pivot);
	}
	else if (pivot->balanceFactor == -2)
	{
		desc = pivot->left;
		if (desc->balanceFactor == 1)
		{
			desc = SRL(desc);
			pivot = SRR(pivot);
		}
		else
			pivot = SRR(pivot);
	}
	return pivot;
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
	root = rebalanceTree(root);
}

void inOrder(TreeNode* root)
{
	if (root)
	{
		inOrder(root->left);
		printf("BalanceFactor:%2d| Id:%d Name:%s\n",root->balanceFactor,root->info->id, root->info->name);
		inOrder(root->right);
	}
}

void logicalDeletion(TreeNode* &root, TreeNode* &leftSubtree)
{
	if (leftSubtree->right)
		logicalDeletion(root, leftSubtree->right);
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
				root = nullptr;
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
					root = rebalanceTree(root);
				}
				else
					if (!root->left&&root->right)
					{
						TreeNode* tmp = root;
						root = root->right;
						free(tmp->info);
						free(tmp);
						tmp = nullptr;
						root = rebalanceTree(root);
					}
					else
					{
						logicalDeletion(root, root->left);
						root = rebalanceTree(root);
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
	deleteNode(root, 5);
	inOrder(root);


}