#ifndef VARIABLE_NODE_H_
#define VARIABLE_NODE_H_

/**
 * Class for storing the variable node information.
 */
class VariableNode
{
public:
	/**
	 * Default constructor.
	 */
	VariableNode(std::string &name);
	VariableNode(std::string &name, long int value);
	~VariableNode(void);

	/**
	 * @brief Insert a new variable node into the tree. Generated node has the name assigned to it.
	 * @returns The pointer to the newly created variable tree entry.
	 */
	VariableNode *Insert(std::string &name);

private:
	std::string name;
	bool assigned;
	long int value;
	VariableNode *right;
	VariableNode *left;
};

#endif/*VARIABLE_NODE_H_*/
