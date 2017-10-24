#ifndef ALPHA_ENGINE_HPP_
#define ALPHA_ENGINE_HPP_

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
};

#endif/*ALPHA_ENGINE_HPP_*/

