#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

class TreeNode;

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	bool IsEmpty() const;
	void Insert(int a_nValue);
	TreeNode* Find(int a_nValue);
	TreeNode* GetRoot();


	void PrintOrdered();
	void PrintUnordered();

	void Draw(TreeNode* selected = nullptr);

private:
	//Find the node with the specified value.
	bool FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent);

	//Used to recurse through the nodes in value order and print their values.
	void PrintOrderedRecurse(TreeNode*);
	void PrintUnorderedRecurse(TreeNode*);


	void Draw(TreeNode*, int x, int y, int horizontalSpacing, TreeNode* selected = nullptr);

	//The root node of the tree
	TreeNode* m_pRoot;
};

#endif //_BINARYTREE_H_