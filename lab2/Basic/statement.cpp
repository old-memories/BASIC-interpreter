/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "parser.h"
#include "statement.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
	/* Empty */
}

Statement::~Statement() {
	/* Empty */
}

Print_statement::Print_statement(string line) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp;
	temp = scanner.nextToken();
	exp = parseExp(scanner);
	if (exp->getType() == COMPOUND && ((CompoundExp*)exp)->getOp() == "=")
		error("SYNTAX ERROR");
}

Print_statement::~Print_statement() {
	delete exp;
}

void Print_statement::execute(EvalState & state) {
	int value = exp->eval(state);
	cout << value << endl;
}

Let_statement::Let_statement(string line) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp;
	temp = scanner.nextToken();
	var = scanner.nextToken();
	if ((var == "LET") || (var == "PRINT") || (var == "INPUT") || (var == "IF") || (var == "GOTO") || (var == "END"))
		error("SYNTAX ERROR");
	//cout << "var:" << var << ";" << endl;
	string eqal = scanner.nextToken();
	//cout << "eqal:" << eqal << endl;
	if (eqal != "=")
		error("SYNTAX ERROR");
	string first = temp + var + eqal;
	int begin = 0;
	begin = line.find(" ", begin);
	while (begin != -1) {
		line.replace(begin, 1, "");
		begin = line.find(" ", begin);
	}
	//cout << "line:" << line << ";" << endl;
	//cout << "first:" << first << ";" << endl;
	int numberPos = first.length();
	int lineLength = line.length() - first.length();
	string val;
	if (lineLength != 0)
		val = line.substr(numberPos, lineLength);
	else
		error("SYNTAX ERROR");
	//cout << "val:" << val << ";" << endl;
	scanner.setInput(val);
	exp = parseExp(scanner);
	if (exp->getType() == COMPOUND && ((CompoundExp*)exp)->getOp() == "=")
		error("SYNTAX ERROR");
}

Let_statement::~Let_statement() {
	delete exp;
}

void Let_statement::execute(EvalState & state) {
	int value = exp->eval(state);
	state.setValue(var, value);
}

Run_statement::Run_statement(string line) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp;
	temp = scanner.nextToken();
	if (scanner.hasMoreTokens())
		error("SYNTAX ERROR");
}

Run_statement::~Run_statement() {
	/* Empty */
}

void Run_statement::execute(EvalState & state) {
	/* Empty */
}

Input_statement::Input_statement(string line) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp;
	temp = scanner.nextToken();
	var = scanner.nextToken();
	//cout << "var:" << var << endl;
	if (scanner.hasMoreTokens()) {
		error("SYNTAX ERROR");
	}
}

Input_statement::~Input_statement() {
	/* Empty */
}

void Input_statement::execute(EvalState & state) {
	int value;
	string line;
	while (true) {
		cout << " ? ";
		getline(cin, line);
		istringstream stream(line);
		stream >> value >> ws;
		if (!stream.fail() && stream.eof()) break;
		cout << "INVALID NUMBER" << endl;
	}
	state.setValue(var, value);
}

Goto_statement::Goto_statement(string line) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp;
	temp = scanner.nextToken();
	temp = scanner.nextToken();
	if (scanner.hasMoreTokens())
		error("SYNTAX ERROR");
	jumpToLineNumber = stringToInteger(temp);
}

Goto_statement::~Goto_statement() {
	/* Empty */
}

void Goto_statement::execute(EvalState & state) {
	state.setCurrentLine(jumpToLineNumber);
}

If_statement::If_statement(string line) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp;
	temp = scanner.nextToken();
	exp1 = readE(scanner, 0);
	op = scanner.nextToken();
	exp2 = readE(scanner, 0);
	if (scanner.nextToken() != "THEN") {
		error("SYNTAX ERROR");
	}
	jumpToLineNumber = stringToInteger(scanner.nextToken());
	if (scanner.hasMoreTokens()) {
		error("SYNTAX ERROR");
	}
}

If_statement::~If_statement() {
	delete exp1;
	delete exp2;
}

void If_statement::execute(EvalState & state) {
	if (op == "=") {
		if (exp1->eval(state) == exp2->eval(state)) state.setCurrentLine(jumpToLineNumber);
		return;
	}

	if (op == "<") {
		if (exp1->eval(state) < exp2->eval(state)) state.setCurrentLine(jumpToLineNumber);
		return;
	}

	if (op == ">") {
		if (exp1->eval(state) > exp2->eval(state)) state.setCurrentLine(jumpToLineNumber);
		return;
	}
	else {
		error("SYNTAX ERROR");
		return;
	}
}

Rem_statement::Rem_statement(string line) {
	/* Empty */
}

Rem_statement::~Rem_statement() {
	/* Empty */
}

void Rem_statement::execute(EvalState & state) {
	/* Empty */
};

End_statement::End_statement(string line) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp;
	temp = scanner.nextToken();
	if (scanner.hasMoreTokens())
		error("SYNTAX ERROR");
}

End_statement::~End_statement() {
}

void End_statement::execute(EvalState & state) {
	state.setCurrentLine(-1);
}

Clear_statement::Clear_statement(string line) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp;
	temp = scanner.nextToken();
	if (scanner.hasMoreTokens())
		error("SYNTAX ERROR");
}

Clear_statement::~Clear_statement() {
	/* Empty */
}

void Clear_statement::execute(EvalState & state) {
	/* Empty */
}

Quit_statement::Quit_statement(string line) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp;
	temp = scanner.nextToken();
	if (scanner.hasMoreTokens())
		error("SYNTAX ERROR");
}

Quit_statement::~Quit_statement() {
	/* Empty */
}

void Quit_statement::execute(EvalState & state) {
	/* Empty */
}

List_statement::List_statement(string line) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp;
	temp = scanner.nextToken();
	if (scanner.hasMoreTokens())
		error("SYNTAX ERROR");
}

List_statement::~List_statement() {
	/* Empty */
}

void List_statement::execute(EvalState & state) {
	/* Empty */
}

Help_statement::Help_statement(string line) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string temp;
	temp = scanner.nextToken();
	if (scanner.hasMoreTokens())
		error("SYNTAX ERROR");
}

Help_statement::~Help_statement() {
	/* Empty */
}

void Help_statement::execute(EvalState & state) {
	/* Empty */
}