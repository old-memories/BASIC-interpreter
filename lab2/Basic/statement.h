/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"

 /*
  * Class: Statement
  * ----------------
  * This class is used to represent a statement in a program.
  * The model for this class is Expression in the exp.h interface.
  * Like Expression, Statement is an abstract class with subclasses
  * for each of the statement and command types required for the
  * BASIC interpreter.
  */

class Statement {
public:

	/*
	 * Constructor: Statement
	 * ----------------------
	 * The base class constructor is empty.  Each subclass must provide
	 * its own constructor.
	 */

	Statement();

	/*
	 * Destructor: ~Statement
	 * Usage: delete stmt;
	 * -------------------
	 * The destructor deallocates the storage for this expression.
	 * It must be declared virtual to ensure that the correct subclass
	 * destructor is called when deleting a statement.
	 */

	virtual ~Statement();

	/*
	 * Method: execute
	 * Usage: stmt->execute(state);
	 * ----------------------------
	 * This method executes a BASIC statement.  Each of the subclasses
	 * defines its own execute method that implements the necessary
	 * operations.  As was true for the expression evaluator, this
	 * method takes an EvalState object for looking up variables or
	 * controlling the operation of the interpreter.
	 */

	virtual void execute(EvalState & state) = 0;
};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */
class Print_statement : public Statement {
public:
	Print_statement(std::string line);
	~Print_statement();
	void execute(EvalState & state);
private:
	Expression *exp;
};
class Let_statement : public Statement {
public:
	Let_statement(std::string line);
	~Let_statement();
	void execute(EvalState & state);
private:
	string var;
	string val;
	Expression *exp;
};
class Run_statement : public Statement {
public:
	Run_statement(std::string line);
	~Run_statement();
	void execute(EvalState & state);
};
class Input_statement : public Statement {
public:
	Input_statement(std::string line);
	~Input_statement();
	void execute(EvalState & state);
private:
	string var;
};
class Goto_statement : public Statement {
public:
	Goto_statement(std::string line);
	~Goto_statement();
	void execute(EvalState & state);
private:
	int jumpToLineNumber;
};
class If_statement : public Statement {
public:
	If_statement(std::string);
	~If_statement();
	void execute(EvalState & state);
private:
	Expression* exp1;
	Expression* exp2;
	string op;
	int jumpToLineNumber;
};
class Rem_statement : public Statement {
public:
	Rem_statement(std::string line);
	~Rem_statement();
	void execute(EvalState & state);
private:
	string rem;
};
class  End_statement : public Statement {
public:
	End_statement(std::string);
	~End_statement();
	void execute(EvalState & state);
};
class Clear_statement : public Statement {
public:
	Clear_statement(std::string);
	~Clear_statement();
	void execute(EvalState & state);
};
class Quit_statement : public Statement {
public:
	Quit_statement(std::string);
	~Quit_statement();
	void execute(EvalState & state);
};
class List_statement : public Statement {
public:
	List_statement(std::string);
	~List_statement();
	void execute(EvalState & state);
};
class Help_statement : public Statement {
public:
	Help_statement(std::string);
	~Help_statement();
	void execute(EvalState & state);
};
#endif
