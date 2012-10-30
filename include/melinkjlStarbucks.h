#include "Starbucks.h"
#include "KDTree.h"

class melinkjlStarbucks : public Starbucks 
{
  public:
	KDTree* tree;
	virtual void build(Entry* c, int n);
	TreeNode* buildTree(Entry* c, int n);
	Entry* sortByX(Entry* c, int n);
	Entry* sortByY(Entry* c, int n);
	Entry* splitArrayLeft(Entry* c, int n);
	Entry* splitArrayRight(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
	Entry* getNearest(double x, double y, TreeNode* root, bool splitByX);
};