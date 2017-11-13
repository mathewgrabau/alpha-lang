/**
 *  @file VariableNode.hpp
 *  @brief	Defines the class used to store the instance of variable nodes.
 */

#ifndef VARIABLE_NODE_H_
#define VARIABLE_NODE_H_

#include <string>

/**
 * Class for storing the variable node information.
 */
class VariableNode
{
public:
	/**
	 * Default constructor.
	 * @param	name	A string containing the name for the object.
	 */
	VariableNode(std::string &name);

	/**
	 * Alternate constructor for wrapping into the strings.
	 */
	VariableNode(char * name);

	/**
	 * Constructor to initialize to a value.
	 * @param	name	A string containing the name for the variable.
	 * @param	value	The current value of the variable.
	 */
	VariableNode(std::string &name, long int value);
	/**
	 * Destructor
	 */
	~VariableNode(void);

	/**
	 * @brief Insert a new variable node into the tree. Generated node has the name assigned to it.
	 * @returns The pointer to the newly created variable tree entry.
	 */
	VariableNode *insert(std::string &name);

	std::string& get_name(void);

private:
	std::string name;
	bool assigned;
	long int value;
	VariableNode *right;
	VariableNode *left;
};

#endif/*VARIABLE_NODE_H_*/
