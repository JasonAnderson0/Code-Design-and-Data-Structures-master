#include "BinaryTree.h"
#include "TreeNode.h"

using namespace std;


BinaryTree::BinaryTree()
{
    m_pRoot = nullptr;
}


// Return whether the tree is empty
bool BinaryTree::IsEmpty() const 
{ 
	return (m_pRoot == nullptr);
}

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
void BinaryTree::Insert(int a_nValue)
{

	if (IsEmpty()) { 
		m_pRoot = new TreeNode(a_nValue); 
		return;
	}

	TreeNode* currentNode = m_pRoot;
	TreeNode* parentNode = currentNode;

	while (currentNode != nullptr)
	{
		if (a_nValue < currentNode->GetData())
		{
			parentNode = currentNode;
			currentNode = currentNode->GetLeft();
			continue;
		}
		if (a_nValue > currentNode->GetData())
		{
			parentNode = currentNode;
			currentNode = currentNode->GetRight();
			continue;
		}
		if (a_nValue == currentNode->GetData())
		{
			return;
		}
	}

	if (a_nValue < parentNode->GetData()) 
	{ 
		TreeNode* newNode = new TreeNode(a_nValue);
		parentNode->SetLeft(newNode);
	}
	else 
	{
		TreeNode* newNode = new TreeNode(a_nValue);
		parentNode->SetRight(newNode);
	}
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent: nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	ppOutNode = m_pRoot;
	while (ppOutNode != nullptr) 
	{
		if (a_nSearchValue == ppOutNode->GetData()) {
			return (ppOutNode);
		}
		else {
			if (a_nSearchValue < ppOutNode->GetData()) ppOutNode = ppOutNode->GetLeft();
			else ppOutNode = ppOutNode->GetRight();
		}
	}

	return false;
}