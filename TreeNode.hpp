#ifndef TREE_NODE_HPP_
#define TREE_NODE_HPP_

enum NodeCode
{
	VARIABLE_NAME = 1,
	CONSTANT_VALUE = 2,
	/**
	 * The operator for performing assignment.
	 */
	ASSIGNMENT = 3
};

class VariableNode;

class TreeNode 
{
public:
	TreeNode();

	~TreeNode();

	void EmptyExpressionTree(void);

	/**
	 * Return the representation of this node.
	 */
	std::string ToString(void);

private:
	/**
	 * Pointer to the left side of the tree.
	 */
	TreeNode *left;
	TreeNode *right;

	int code;

	VariableNode *left;
	VariableNode *right;
};


#endif/*TREE_NODE_HPP_*/
