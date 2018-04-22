/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
using namespace std;

Program::Program() {
}

Program::~Program() {
	list.clear();
}

void Program::clear() {
	list.clear();
	source.clear();
	sequence.clear();// Replace this stub with your own code
}

void Program::addSourceLine(int lineNumber, string line) {
	list.put(lineNumber, line);
	sequence.insert(lineNumber);
}

void Program::removeSourceLine(int lineNumber) {
	list.remove(lineNumber);
	sequence.erase(lineNumber);
	source.remove(lineNumber);// Replace this stub with your own code
}

string Program::getSourceLine(int lineNumber) {
	return list[lineNumber];
}

void Program::setParsedStatement(int lineNumber, Statement* stmt) {
	source.remove(lineNumber);
	source.put(lineNumber, stmt);// Replace this stub with your own code
}

Statement* Program::getParsedStatement(int lineNumber) {
	set<int, string>::iterator iter = sequence.find(lineNumber);
	iter = sequence.find(lineNumber);
	if (it == sequence.end()) {
		error("SYNTAX ERROR");
		return NULL;
	}
	else {
		return source[lineNumber];
	}
}

int Program::getFirstLineNumber() {
	if (sequence.empty())
		return 0;
	else {
		it = sequence.begin();
		return *it;
	}
	// Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
	it = sequence.find(lineNumber);
	if (it == sequence.end())
		return -1;
	else {
		++it;
		if (it == sequence.end())
			return -1;
		else
			return *it;
	}
}
void Program::addSource(int lineNumber, Statement* stmt) {
	source.put(lineNumber, stmt);
}