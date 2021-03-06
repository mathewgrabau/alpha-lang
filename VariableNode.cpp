#include "VariableNode.hpp"

#include <string>
#include <iostream>

VariableNode::VariableNode(std::string &name)
{
	this->name = name;
	this->value = 0;
	this->assigned = false;
}

VariableNode::VariableNode(char *name)
{
	this->name = name;
	this->value = 0;
	this->assigned = false;
}

VariableNode::VariableNode(std::string &name, long int value)
{
	this->name = name;
	this->value = value;
	this->assigned = true;
}

VariableNode::~VariableNode(void)
{
	if (this->right != nullptr) 
	{
		delete this->right;
	}

	if (this->left != nullptr)
	{
		delete this->left;
	}
}

VariableNode * VariableNode::insert(std::string &name)
{
	VariableNode * new_node;
	VariableNode * current;
	bool finished = false;

	current = this;	// Starting at this as the root.

	while (!finished)
	{
		// Found the entry for the variable in the tree already
		if (current->name == name)
		{
			new_node = current;
			finished = true;
		}
		else
		{
			if (name > current->name)
			{

			}
		}
	}
	

	

	new_node = new VariableNode(name);
	// TOOD finish porting this function
	return new_node;
}

std::string& VariableNode::get_name(void) 
{
	std::cout << "Inside get_name";
	return this->name;
}
