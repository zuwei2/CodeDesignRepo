/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>
using namespace std;


BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

// destructor
BinaryTree::~BinaryTree()
{
	while (m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
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
	TreeNode* temp;
	if (m_pRoot == NULL)
	{
		m_pRoot = new TreeNode(a_nValue);
	}
	TreeNode* current_node = m_pRoot;
	TreeNode* parent = current_node;
	while (current_node != nullptr)
	{
		if (current_node->GetData() > a_nValue)
		{
			parent = current_node;
			current_node = current_node->GetLeft();

		}
		else if (current_node->GetData() < a_nValue)
		{
			parent = current_node;
			current_node = current_node->GetRight();
		}
		else
		{
			return;
		}
	}
	if (parent->GetData() > a_nValue)
	{
		temp = new TreeNode(a_nValue);
		parent->SetLeft(temp);
	}
	else
	{
		temp = new  TreeNode(a_nValue);
		parent->SetRight(temp);
	}
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent : nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	TreeNode* parent_node = NULL;
	TreeNode* current_node = m_pRoot;
	while (current_node != NULL) {
		if (a_nSearchValue < current_node->GetData())
		{
			parent_node = current_node;
			current_node = current_node->GetLeft();
		}
		else if (a_nSearchValue > current_node->GetData())
		{
			parent_node = current_node;
			current_node = current_node->GetRight();
		}
		else
		{
			ppOutParent = parent_node;
			ppOutNode = current_node;
			return true;
		}
	}
	return false;
}

void BinaryTree::Remove(int a_nValue)
{
	TreeNode* p_current = nullptr;
	TreeNode* p_parent = nullptr;
	TreeNode* min_node = nullptr;
	TreeNode* min_parent = nullptr;

	// If node not found, exit
	if (!FindNode(a_nValue, p_current, p_parent)) {
		return;
	}

	// If p_current is m_pRoot and has no children
	if (p_current == m_pRoot && !m_pRoot->HasLeft() && !m_pRoot->HasRight()) {
		delete m_pRoot;
		m_pRoot = nullptr;
		return;
	}
	// Create a temp parent for the m_pRoot that has children
	else if (p_current == m_pRoot) {
		TreeNode rootParent = TreeNode(m_pRoot->GetData());
		rootParent.SetRight(m_pRoot);
		p_parent = &rootParent;
	}

	min_parent = p_parent;
	min_node = p_current;

	// Find the closest value to p_current from its children
	if (p_current->HasRight()) {
		min_parent = p_current;
		min_node = p_current->GetRight();

		while (min_node->HasLeft()) {
			min_parent = min_node;
			min_node = min_node->GetLeft();
		}
	}
	else if (p_current->HasLeft()) {
		min_parent = p_current;
		min_node = p_current->GetLeft();

		while (min_node->HasRight()) {
			min_parent = min_node;
			min_node = min_node->GetRight();
		}
	}

	// Remove the node from the tree
	// p_current has no children and is a right child
	if (p_parent->HasRight() && p_parent->GetRight() == min_node) {
		p_parent->SetRight(nullptr);
	}
	// p_current has no children and is a left child
	else if (p_parent->HasLeft() && p_parent->GetLeft() == min_node) {
		p_parent->SetLeft(nullptr);
	}
	// p_current has children
	else {
		p_current->SetData(min_node->GetData());

		// min_node is right child of p_current
		if (min_node == p_current->GetRight()) {
			min_parent->SetRight(min_node->GetRight());
		}
		// min_node is left child of p_current
		else if (min_node == p_current->GetLeft()) {
			min_parent->SetLeft(min_node->GetLeft());
		}
		// min_node is a right child 
		else if (min_node == min_parent->GetRight()) {
			min_parent->SetRight(min_node->GetLeft());
		}
		// min_node is a left child 
		else if (min_node == min_parent->GetLeft()) {
			min_parent->SetLeft(min_node->GetRight());
		}
	}
	delete min_node;
	min_node = nullptr;

	//if (!Find(a_nValue))
	//	return;

	//// Look for location to insert
	//bool found = false;
	//TreeNode* current_node = m_pRoot;

	//// Find the data
	//while (!found)
	//{
	//	// Compare and traverse
	//	if (a_nValue == current_node->GetData())
	//	{
	//		// Data already existed
	//		found = true;
	//	}
	//	// Left child check / insert
	//	else if (a_nValue < current_node->GetData())
	//	{
	//		if (current_node->GetLeft()) // Is there already node?
	//		{
	//			current_node = current_node->GetLeft();
	//		}
	//	}

	//	// Right child check / insert
	//	else if (a_nValue > current_node->GetData())
	//	{
	//		if (current_node->HasRight()) // Is there already node?
	//		{
	//			current_node = current_node->GetRight();
	//		}
	//	}
	//}

	////If the current node has a right branch, then
	//if (current_node->HasRight())
	//{
	//	// find the minimum value in the right 
	//	// branch by iterating down the left branch of the
	//	// current node’s right child until there are no more left branch nodes
	//	TreeNode* search_node = current_node->GetRight();
	//	while (search_node->HasLeft())
	//	{
	//		search_node = search_node->GetLeft();
	//	}
	//	//copy the value from this minimum node to the current node
	//	current_node->SetData(search_node->GetData());
	//	//find the minimum node’s parent node
	//	//	(the parent of the node you are deleting)
	//	// search_node->m_parent
	//	if (search_node == search_node->GetParent()->GetLeft())
	//	{
	//		//if you are deleting the parent’s left node
	//		//	set this left child of the parent to the right 
	//		//  child of the minimum node
	//		search_node->GetParent()->SetLeft(search_node->GetRight());
	//		if (search_node->HasRight())
	//			search_node->GetRight()->SetParent(search_node->GetParent());
	//		delete search_node;
	//		search_node = nullptr;
	//	}
	//	else if (search_node == search_node->GetParent()->GetRight())
	//	{
	//		//if you are deleting the parent’s right node
	//		// set the right child of the parent to 
	//		// the minimum node’s right child
	//		search_node->GetParent()->SetRight(search_node->GetRight());
	//		if (search_node->HasRight())
	//			search_node->GetRight()->SetParent(search_node->GetParent());
	//		delete search_node;
	//		search_node = nullptr;
	//	}
	//	else
	//	{
	//		std::cout << "Massive Error in remove!";
	//	}

	//	return;

	//}
	//else
	//{
	//	//If we are deleting the root, the root becomes the left child of the current node
	//	if (current_node == m_pRoot)
	//	{
	//		if (m_pRoot->GetLeft())
	//		{
	//			m_pRoot = m_pRoot->GetLeft();
	//			m_pRoot->SetParent(nullptr);
	//		}
	//		else
	//		{
	//			//Last node?
	//			m_pRoot = nullptr;
	//		}

	//	}
	//	//If the current node has no right branch
	//	//if we are deleting the parent’s left child,
	//	//	set the left child of the parent to the left
	//	// child of the current node
	//	else if (current_node == current_node->GetParent()->GetLeft())
	//	{
	//		current_node->GetParent()->SetLeft(current_node->GetLeft());
	//		current_node->GetLeft()->SetParent(current_node->GetParent());
	//	}
	//	//If we are deleting the parent’s right child, set the right child of the parent to the left
	//	//child of the current node
	//	else if (current_node == current_node->GetParent()->GetRight())
	//	{
	//		current_node->GetParent()->SetRight(current_node->GetLeft());
	//		current_node->GetLeft()->SetParent(current_node->GetParent());
	//	}
	//	delete current_node;
	//	current_node = nullptr;
	//	return;
	//}
}

void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{
	if (pNode->HasLeft())
	{
		PrintOrderedRecurse(pNode->GetLeft());
	}
	else
	{
		std::cout << pNode->GetData() << std::endl;
	}
	std::cout << pNode->GetData() << std::endl;
	if (pNode->HasRight())
	{
		PrintOrderedRecurse(pNode->GetRight());
	}
}

void BinaryTree::PrintUnordered()
{
	PrintUnorderedRecurse(m_pRoot);
	std::cout << endl;
}

void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{
	std::cout << pNode->GetData() << std::endl;
	if (pNode->HasLeft())
	{
		PrintUnorderedRecurse(pNode->GetLeft());
	}
	std::cout << pNode->GetData() << std::endl;
	if (pNode->HasRight())
	{
		PrintUnorderedRecurse(pNode->GetRight());
	}
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