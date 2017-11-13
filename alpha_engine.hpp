/**
 * @file alpha_engine.hpp
 * 
 * @brief	Implements the base of the interpretor.
 */

#ifndef ALPHA_ENGINE_HPP_
#define ALPHA_ENGINE_HPP_

class VariableNode;	// Forward declaration of the class.

/**
 * This class defines the item that is used to run the language interpretation, etc.
 */
class AlphaEngine
{
	public:
		/**
		 * Default constructor.
		 */
		AlphaEngine(void);
		/**
		 * Destructor
		 */
		void ~AlphaEngine(void);
		/**
		 * Add a string of input to the applications.
		 */
		void AddString(std::string &s);

	private:
		/**
		 * The file name for the executing file.
		 */
		std::string filename;

		/**
		 * The (current) symbol table.
		 */
		VariableNode * symbols;
};

#endif/*ALPHA_ENGINE_HPP_*/

