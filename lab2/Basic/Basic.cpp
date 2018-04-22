/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
	EvalState state;
	Program program;
	while (true) {
		try {
			processLine(getLine(), program, state);
		}
		catch (ErrorException & ex) {
			cout << ex.getMessage() << endl;
		}
	}
	return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.setInput(line);
	if (!scanner.hasMoreTokens()) {
		return;
	}
	string first = scanner.nextToken();
	//cout << "first:"<<first << endl;
	if (first == "PRINT") {
		Statement* st = new Print_statement(line);
		st->execute(state);
		return;
	}
	if (first == "LET") {
		Statement* st = new Let_statement(line);
		st->execute(state);
		return;
	}
	if (first == "INPUT") {
		Statement* st = new Input_statement(line);
		st->execute(state);
		return;
	}
	if (first == "RUN") {
		Statement* st = new Run_statement(line);
		//cout << "RUN initialized" << endl;
		state.setCurrentLine(program.getFirstLineNumber());
		//int CurrentLineNumber = state.getCurrentLine();
		Statement* stmt;
		if ((state.getCurrentLine() == 0) || (state.getCurrentLine() == -1)) {
			state.setCurrentLine(0);
			return;
		}
		else {
			while (state.getCurrentLine() != -1) {
				//cout <<"current linenumber:"<< state.getCurrentLine() << endl;
				stmt = program.getParsedStatement(state.getCurrentLine());
				if (stmt == NULL) {
					error("LINE NUMBER ERROR");
					return;
				}
				int temp1 = state.getCurrentLine();
				stmt->execute(state);
				int temp2 = state.getCurrentLine();
				//cout << "current linenumber:" << state.getCurrentLine() << endl;
				if (temp1 == temp2)
					state.setCurrentLine(program.getNextLineNumber(state.getCurrentLine()));
				//cout << "current linenumber:" << state.getCurrentLine() << endl;
			}
			state.setCurrentLine(0);
			return;
		}
	}
	if (first == "CLEAR") {
		Statement* st = new Clear_statement(line);
		//cout << "CLEAR initialized" << endl;
		state.clear();
		program.clear();
		return;
	}
	if (first == "QUIT") {
		Statement* st = new Quit_statement(line);
		//cout << "QUIT initialized" << endl;
		exit(0);
		return;
	}
	if (first == "LIST") {
		Statement* st = new List_statement(line);
		//cout << "LIST initialized" << endl;
		int CurrentLineNumber = program.getFirstLineNumber();
		while ((CurrentLineNumber != -1) && (CurrentLineNumber != 0)) {
			cout << CurrentLineNumber << " "
				<< program.getSourceLine(CurrentLineNumber) << endl;
			CurrentLineNumber = program.getNextLineNumber(CurrentLineNumber);
		}
		return;
	}
	if (first == "HELP") {
		Statement* st = new Help_statement(line);
		//cout << "HELP initialized" << endl;
		cout << "KEEP CALM AND MAKE MONEY" << endl;
		return;
	}
	if ((first > "0") || (first < "999999")) {
		int lineNumber = stringToInteger(first);
		//cout << "lineNumber:" << lineNumber << endl;
		int numberPos = first.length() + 1;
		int lineLength = line.length() - first.length();
		string source;
		if (lineLength != 0) {
			source = line.substr(numberPos, lineLength);
		}
		if (source == "") {
			program.removeSourceLine(lineNumber);
		}
		else {
			program.addSourceLine(lineNumber, source);
			string order = scanner.nextToken();
			//cout << "source:" << source << endl;
			//cout << "order:"<<order << endl;
			Statement *stmt = parseStatement(order, source);
			program.addSource(lineNumber, stmt);
		}
	}
	return;
}