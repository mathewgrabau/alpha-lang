#include <fstream>
#include <iostream>
#include <cctype>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

ifstream infile;	// pointer to the input stream
ostream &printer = std::cout;	// pointer to the output stream (printer)
ofstream file_output;
string input_string;	// stores the source read in from the file
int position;		// stores the current position within input_string
int STACK_PRIORITY[14] = { 0,  0,  0,  15, 40, 40, 30, 30, 45, 5,  0, 0, 0, 0 };	// stores the operator priorities while in the stack
int INPUT_PRIORITY[14] = { 0,  0,  0,  75, 40, 40, 30, 30, 55, 65, 0, 0, 0, 0 };	// stores the operator priorities for input
const char EJECT = 12;
const char FILENAME[] = "SOURCE3.TXT";	// string literal containing the source file name
const char OUTPUT[] = "CON";	// string literal containing the desired output stream

struct variable_node
{
	string name;	// stores the name of the variable
	bool assigned;	// checks whether or not the value has been assigned
	long int value;	// stores the value of the variable
	variable_node *right;	// pointer to the right node
	variable_node *left;	// pointer to the left node
}; // variable_node declaration

struct tree_node
{
	int code;	// stores the code of this node
	long int value;	// stores the numeric value if it is a constant
	tree_node *left;	// pointer to the left node
	tree_node *right;	// pointer to the right node
	variable_node *variable;	// pointer to the corresponding variable if needed
}; // tree_node declaration

void initialize();
// initializes global variables, opens the input/output streams
// called from main
int syntactic_unit(string &unit);
// returns the next valid syntactic unit
// called from main
variable_node *insert_variable(string variable_name, variable_node *&root);
// inserts a variable into the symbol table
// always returns a pointer to the node, even if the variable is inserted
// called from main
void display_symbol_table(variable_node *root);
// uses recursion to display the symbol table
// called from main
long int evaluate(tree_node *root);
// uses recursion to evaluate the expression tree
// called from main
void empty_expression_tree(tree_node *root);
// uses recursion to empty the expression tree
// called from main

int main()
{
	int code;	// stores the code of the current syntactic unit
	string unit;	// stores the current syntactic unit
	variable_node *root = NULL;	// pointer to the root of the variable tree
	tree_node *top = NULL;	// pointer to the top node in the expression stack
	tree_node *temp = NULL;	// temporary pointer used in stack traversal
	bool op_done;	// boolean to test whether operator processing is complete
	tree_node* subtree = NULL;	// pointer to the beginning of a subtree
	tree_node* remove_temp = NULL; // pointer used to remove nodes if necessary
	top = new tree_node;
	top->left = NULL;
	top->right = NULL;
	top->code = 13;

	initialize();
	// TODO
	//clrscr();
	printer << FILENAME << " - Mathew Grabau" << endl << endl;

	do
	{
		code = syntactic_unit(unit);

		if (code < 3)
		{
			temp = new tree_node;
			temp->left = top;
			temp->right = NULL;
			top = temp;
			top->code = code;

			if (code == 1)
			{
				top->variable = insert_variable(unit, root);
			} // if
			else
			{
				top->value = strtol(unit.c_str(), NULL, 0);
			} // else
		} // if
		else
		{
			temp = top;
			op_done = false;

			while (!op_done && code != 12)
			{
				while (temp->code <= 2)
				{
					remove_temp = temp;
					temp = temp->left;
				} // while

				if (INPUT_PRIORITY[code] > STACK_PRIORITY[temp->code])
				{
					temp = new tree_node;
					temp->left = top;
					temp->right = NULL;
					top = temp;
					top->code = code;
					op_done = true;
				} // if
				else
				{
					if (temp->code == 13)
					{
						evaluate(subtree->right);
						empty_expression_tree(subtree->right);
						top = subtree->left;
						delete subtree;
						op_done = true;
					} // if
					else
					{
						if (temp->code == 9)
						{
							remove_temp->left = temp->left;
							delete temp;
							temp = remove_temp;
							op_done = true;
						} // if
						else
						{
							subtree = new tree_node;
							subtree->code = 0;
							subtree->right = temp;
							subtree->left = subtree->right->left->left;
							temp = top;

							if (temp->code == 0)
							{
								subtree->right->right = temp->right;
								delete temp;
							} // if
							else
							{
								subtree->right->right = temp;
								temp->left = NULL;
							} // else
							
							subtree->right->left->left = NULL;

							if (subtree->right->left->code == 0)
							{
								temp = subtree->right->left;
								subtree->right->left = temp->right;
								delete temp;
							} // if

							top = subtree;
							temp = top;
						} // else
					} // else
				} // else
			} // while
		} // else
	} while (code != 12); // do-while

	printer << endl << endl << "VARIABLE SYMBOL TABLE" << endl << endl;
	printer << "Name" << "\t\t" << "Assigned" << "\t" << "Value" << endl;
	display_symbol_table(root);
	printer << EJECT;
	infile.close();
	// TODO replaced printer.close, but doesn't seem right.
	if (file_output.is_open())
	{
		file_output.close();
	}
	cin.ignore();
	cin.get();

	return 0;
} // main

void initialize()
{
	if (OUTPUT == "CON")
	{
	}
	else
	{
		// TODO this is not working properly
		file_output.open(OUTPUT, ios::out);
	}
	infile.open(FILENAME, ios::in);
	input_string = '#';
	position = 0;
	return;
} // initialize

int syntactic_unit(string &unit)
{
	cout << "inside syntactic_unit" << endl;
	int code = 0;	// stores the code of the current syntactic unit

	do
	{
		while (input_string[position] == ' ' || input_string[position] == '\t')
		{
			position++;
		} // while

		switch (input_string[position])
		{
			case '#':
				if (infile.eof())
				{
					code = 12;
					unit = "END-OF-FILE";
				} // if
				else
				{
					getline(infile, input_string);
					position = 0;
					input_string += "#";
				} // else

				break;

			case '=':
				cout << "hit assignment operator" << endl;
				code = 3;
				unit = '=';
				position++;
				break;

			case '*':
				code = 4;
				unit = '*';
				position++;
				break;

			case '/':
				code = 5;
				unit = '/';
				position++;
				break;

			case '+':
				code = 6;
				unit = '+';
				position++;
				break;

			case '-':
				code = 7;
				unit = '-';
				position++;
				break;

			case '^':
				code = 8;
				unit = '^';
				position++;
				break;

			case '(':
				code = 9;
				unit = '(';
				position++;
				break;

			case ')':
				code = 10;
				unit = ')';
				position++;
				break;

			case ';':
				code = 11;
				unit = ';';
				position++;
				break;

			default:
				if (isalpha(input_string[position]))
				{
					code = 1;
					unit = "";
					do
					{
						unit += input_string[position++];
					} while (isalpha(input_string[position]) || isdigit(input_string[position]) || input_string[position] == '_');	// do-while

					if (unit.length() > 20)
					{
						printer << "WARNING: " << unit << endl << "Exceeds max length for variable names." << endl << "Truncated to: ";
						unit = unit.substr(0, 20);
						printer << unit << endl;
					} // if
				} // if
				else
				{
					if (isdigit(input_string[position]))
					{
						code = 2;
						unit = "";

						do 
						{
							unit += input_string[position++];
						} while (isdigit(input_string[position])); // do-while

						if (unit.length() > 5)
						{
							printer << "ERROR: " << unit << endl << endl << "Exceeds max length for integers." << endl << "Truncated to: ";
							unit = unit.substr(0, 5);
							printer << unit << endl;
						} // if
					} // if
					else
					{
						unit = input_string[position];
						position++;
						printer << "ERROR: Invalid character " << unit << endl;
					} // else
				} // else
				break;
			} // switch
		} while (code == 0); // do-while

	cout << code << endl;

	return code;
} // syntactic_unit

variable_node *insert_variable(string variable_name, variable_node *&root)
{
	variable_node *temp;	// pointer to the current node being examined
	variable_node *new_node;	// pointer to the new node, used in insertion
	bool finished;	// boolean variable to determine whether or not the variable is already in the tree

	if (root == NULL)
	{
		root = new variable_node;
		root->name = variable_name;
		root->assigned = false;
		root->value = 0;
		root->left = NULL;
		root->right = NULL;
		new_node = root;
	} // if
	else
	{
		temp = root;
		finished = false;

		while (!finished)
		{
			if (temp->name == variable_name)
			{
				finished = true;
				new_node = temp;
			} // if
			else
			{
				if (variable_name > temp->name)
				{
					if (temp->right == NULL)
					{
						new_node = new variable_node;
						new_node->name = variable_name;
						new_node->assigned = false;
						new_node->value = 0;
						new_node->left = NULL;
						new_node->right = NULL;
						temp->right = new_node;
					} // if
					else
					{
						temp = temp->right;
					} // else
				} // if
				else
				{
					if (temp->left == NULL)
					{
						new_node = new variable_node;
						new_node->name = variable_name;
						new_node->assigned = false;
						new_node->value = 0;
						new_node->left = NULL;
						new_node->right = NULL;
						temp->left = new_node;
					} // if
					else
					{
						temp = temp->left;
					} // else
				} // else
			} // else
		} // while
	} // else

	return new_node;
} // insert_variable

void display_symbol_table(variable_node *root)
{
	if (root->left != NULL)
	{
		display_symbol_table(root->left);
	} // if 

	printer << root->name << "\t\t" << root->assigned << "\t\t" << root->value << endl;

	if (root->right != NULL)
	{
		display_symbol_table(root->right);
	} // if
} // display_symbol_table

long int evaluate(tree_node *root)
{
	switch (root->code)
	{
		case 1:
			if (root->variable->assigned)
			{
				return root->variable->value;
			} // if
			else
			{
				printer << "WARNING: " << root->variable->name << " is not assigned." << endl;
				printer << "0 assigned." << endl << endl;
				return 0;
			} // else
			break;

		case 2:
			return root->value;
			break;

		case 3:
			root->left->variable->value = evaluate(root->right);
			root->left->variable->assigned = true;
			printer << root->left->variable->name << " is assigned " << root->left->variable->value << endl;
			return root->left->variable->value;
			break;

		case 4:
			return evaluate(root->left) * evaluate(root->right);
			break;

		case 5:
			return evaluate(root->left) / evaluate(root->right);
			break;

		case 6:
			return evaluate(root->left) + evaluate(root->right);
			break;

		case 7:
			return evaluate(root->left) - evaluate(root->right);
			break;

		case 8:
			return exp(log(evaluate(root->left))) * evaluate(root->right);
			break;

		default:
			printer << "ERROR: Invalid operator code " << root->code << " in expression tree" << endl;
			break;
	} // switch

	printer << "Abnormal termination of expression tree evaluation" << endl;
	return 0;
} // evaluate

void empty_expression_tree(tree_node *root)
{
	if (root != NULL)
	{
		empty_expression_tree(root->left);
		empty_expression_tree(root->right);
		delete root;
	}
} // empty_expression_tree


