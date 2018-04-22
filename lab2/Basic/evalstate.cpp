/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */

#include <string>
#include "evalstate.h"

#include "../StanfordCPPLib/map.h"
using namespace std;

/* Implementation of the EvalState class */

EvalState::EvalState() :currLineNumber(0) {
	/* Empty */
}

EvalState::~EvalState() {
	/* Empty */
}

void EvalState::setValue(string var, int value) {
	symbolTable.put(var, value);
}

int EvalState::getValue(string var) {
	return symbolTable.get(var);
}

bool EvalState::isDefined(string var) {
	return symbolTable.containsKey(var);
}

void EvalState::setCurrentLine(int lineNumber) {
	currLineNumber = lineNumber;
}

int EvalState::getCurrentLine() {
	return currLineNumber;
}

void EvalState::clear() {
	symbolTable.clear();
	setCurrentLine(0);
}