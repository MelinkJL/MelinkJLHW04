#include "melinkjlStarbucks.h"

void melinkjlStarbucks::build(Entry* c, int n)
{
	tree = new KDTree;
	(*tree).root = buildTree(c, n);
}

TreeNode* melinkjlStarbucks::buildTree(Entry* c, int n)
{
	bool sortByX == true;
	if (c == NULL || n == 0)
	{
		return NULL;
	}
	TreeNode* root = new TreeNode;
	if (sortByX == true)
	{
		(*c).sortByX(c, n);
		(*root).left = buildTree((*c).splitArrayLeft(c, n), ((*c).splitArrayLeft(c, n)).length());
		(*root).right = buildTree((*c).splitArrayRight(c, n), ((*c).splitArrayRight(c, n)).length());
		sortByX = false;
	}
	else if (sortByX == false)
	{
		(*c).sortByY(c, n);
		(*root).left = buildTree((*c).splitArrayLeft(c, n), ((*c).splitArrayLeft(c, n)).length());
		(*root).right = buildTree((*c).splitArrayRight(c, n), ((*c).splitArrayRight(c, n)).length());
		sortByX = true;
	}
	return root;
}

Entry* melinkjlStarbucks::sortByX(Entry* c, int n)
{
	double currentLowest = 1.0;
	int currentLowestIndex = 0;
	Entry* newArray = new Entry[n];
	while (index < n)
	{
		for (int i = 0; i < n; i++)
		{
			if (c[i].x < currentLowest)
			{
				currentLowest = c[i].x;
				currentLowestIndex = i;
			}
		}
		newArray[index] = c[currentLowestIndex];
		currentLowest = 1.0;
		index++;
	}
}

Entry* melinkjlStarbucks::sortByY(Entry* c, int n)
{
	double currentLowest = 1.0;
	int currentLowestIndex = 0;
	Entry* newArray = new Entry[n];
	while (index < n)
	{
		for (int i = 0; i < n; i++)
		{
			if (c[i].x < currentLowest)
			{
				currentLowest = c[i].y;
				currentLowestIndex = i;
			}
		}
		newArray[index] = c[currentLowestIndex];
		currentLowest = 1.0;
		index++;
	}
}

Entry* melinkjlStarbucks::splitArrayLeft(Entry* c, int n)
{
	int median; // Size of the front of the array.
	if (n < 2)
	{
		return NULL;
	}
	else if (n == 2)
	{
		median = 1;
	}
	else if (n % 2 == 0)
	{
		median = (n - 2) / 2;
	}
	else
	{
		median = (n - 1) / 2;
	}
	Entry* newArray = new Entry[median];
	for (int i = 0; i < median; i++)
	{
		newArray[i] = c[i];
	}
	return newArray;
}

Entry* melinkjlStarbucks::splitArrayRight(Entry* c, int n)
{
	int median; // Size of the back of the array.
	if (n <= 2)
	{
		return NULL;
	}
	else if (n % 2 == 0)
	{
		median = n / 2;
	}
	else
	{
		median = (n - 1) / 2;
	}
	Entry* newArray = new Entry[median];
	for (int i = 0; i < median; i++)
	{
		newArray[i] = c[(median + 1) + i];
	}
	return newArray;
}

Entry* melinkjlStarbucks::getNearest(double x, double y)
{
	bool splitByX = true;
	return (*(getNearest(x, y, (*tree).root, splitByX))).data;
}

// This algorithm could probably use some work...
Entry* melinkjlStarbucks::getNearest(double x, double y, TreeNode* root, bool splitByX)
{
	if (root == NULL)
	{
		return NULL;
	}
	double dist = sqrt((((*root).x - x) * ((*root).x - x)) + (((*root).y - y) * ((*root).y - y)));
	if (splitByX == true)
	{
		if (x < (*(*root).data).x)
		{
			if ((*root).left != NULL)
			{
				double distLeft = sqrt((((*(*root).left).x - x) * ((*(*root).left).x - x)) + (((*(*root).left).y - y) * ((*(*root).left).y - y)));
				if (distLeft < dist)
				{
					getNearest(x, y, (*root).left, false);
				}
				else
				{
					return root;
				}
			}
			else
			{
				return root;
			}
		}
		else
		{
			if ((*root).right != NULL)
			{
				double distRight = sqrt((((*(*root).right).x - x) * ((*(*root).right).x - x)) + (((*(*root).right).y - y) * ((*(*root).right).y - y)));
				if (distRight < dist)
				{
					getNearest(x, y, (*root).right, false);
				}
				else
				{
					return root;
				}
			}
			else
			{
				return root;
			}
		}
	}
	else
	{
		if (x < (*(*root).data).y)
		{
			if ((*root).left != NULL)
			{
				double distLeft = sqrt((((*(*root).left).x - x) * ((*(*root).left).x - x)) + (((*(*root).left).y - y) * ((*(*root).left).y - y)));
				if (distLeft < dist)
				{
					getNearest(x, y, (*root).left, true);
				}
				else
				{
					return root;
				}
			}
			else
			{
				return root;
			}
		}
		else
		{
			if ((*root).right != NULL)
			{
				double distRight = sqrt((((*(*root).right).x - x) * ((*(*root).right).x - x)) + (((*(*root).right).y - y) * ((*(*root).right).y - y)));
				if (distRight < dist)
				{
					getNearest(x, y, (*root).right, true);
				}
				else
				{
					return root;
				}
			}
			else
			{
				return root;
			}
		}
	}
}