#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>

using namespace std;


BinaryTree::BinaryTree()
{
    m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{

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

TreeNode* BinaryTree::GetRoot()
{
	return m_pRoot;
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

void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::PrintUnordered()
{
	PrintUnorderedRecurse(m_pRoot);
	std::cout << endl;
}

void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{

	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);

			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		pNode->Draw(x, y, (selected == pNode));
	}
}