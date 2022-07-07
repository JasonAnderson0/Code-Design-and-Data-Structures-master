#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

class TreeNode;

class BinaryTree
{
public:
	BinaryTree();

	bool IsEmpty() const;
	void Insert(int a_nValue);
	TreeNode* Find(int a_nValue);
	TreeNode* GetRoot() { return m_pRoot; }

private:
	//Find the node with the specified value.
	bool FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent);


	//The root node of the tree
	TreeNode* m_pRoot;
};

#endif //_BINARYTREE_H_