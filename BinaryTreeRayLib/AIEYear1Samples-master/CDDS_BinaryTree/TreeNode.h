#pragma once

class TreeNode
{
public:
	TreeNode(int value);
	~TreeNode();

	bool HasLeft() { return (m_left != nullptr); }
	bool HasRight() { return (m_right != nullptr); }

	int GetData() { return m_value; }
	TreeNode* GetLeft() { return m_left; }
	TreeNode* GetRight() { return m_right; }
	TreeNode* GetParent() { return m_parent; }

	void SetData(int value) { m_value = value; }
	void SetLeft(TreeNode* node) { m_left = node; }
	void SetRight(TreeNode* node) { m_right = node; }
	void SetParent(TreeNode* node) { m_parent = node; }

	void Draw(int x, int y, bool selected=false);
	
private:
	// this could also be a pointer to another object if you like
	int m_value;

	// node's children
	TreeNode* m_left;
	TreeNode* m_right;
	TreeNode* m_parent;
};

