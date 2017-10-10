

Operation Codes
01 = VARIABLE	Declare a variable name
02 = CONST	Numerical constant
03 = ASSIGN	Assign a variable with an expression.
04 = MULTIPLY	Multiplication operator
05 = DIVIDE	Division operator
06 = ADD	Addition operator
07 = SUB	Subtraction operator
08 = EXP	Exponent operator
09 = LEFT PAREN	open parenthesis expression
10 = RIGHT PAREN	close parenthesis expression
11 = SEMICOLON	End of statement
12 = EJECT	Print the final dump of table, etc. This is also known as the end-of-input character.
13 = ?

The strings are std::string because the original version of this code was written before it was added (or at least the Borland TurboC++ that I used at the time did not have it). The original oostring header is not available (at the moment), and std::string is used to just make do.
