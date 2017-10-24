#include "TreeNode.hpp"

TreeNode::TreeNode()
{

}

TreeNode::~TreeNode()
{
	this->EmptyExpressionTree();
}

void TreeNode::EmptyExpressionTree(void)
{
	if (this->left != nullptr)
	{
		//this->left->EmptyExpressionTree();
		delete this->left;
	}

	if (this->right != nullptr)
	{
		//this->right->EmptyExpressionTree();
		delete this->right;
	}
}