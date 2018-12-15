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
#include "statement.h"
#include "../StanfordCPPLib/map.h"
using namespace std;

Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {
   // Replace this stub with your own code
}

int Program::size(){
    return SourceLines.size();
}

void Program::clear() {
    SourceLines.clear();
    //ParsedStatements.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
    SourceLines[lineNumber] = line;
}

void Program::removeSourceLine(int lineNumber) {
    SourceLines.erase(lineNumber);
    ParsedStatements.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
    return SourceLines[lineNumber];
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    ParsedStatements[lineNumber] = stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {
    return ParsedStatements[lineNumber];
}

int Program::getFirstLineNumber() {
    auto it = SourceLines.begin();
    return it->first;
}

int Program::getNextLineNumber(int lineNumber) {
    auto next = SourceLines.upper_bound(lineNumber);
    return next->first;
}

void Program::Run(EvalState& state) {
    bool reRun = false;
    for (auto i = ParsedStatements.begin(); i != ParsedStatements.end(); i++){
        i->second->execute(state);
        if (i->second->GetStatementType() == END) break;
        else if (i->second->GetStatementType() == GOTO){
            auto a = (GOTOstatement *)i->second;
            i = ParsedStatements.find(a->getvalue());
            if (i == ParsedStatements.end()) error("LINE NUMBER ERROR");
            if (i->first != getFirstLineNumber()) i = --i;
            else {
                reRun = true;
                break;
            }
            //i->second->execute(state);
            continue;
        }
        else if (i->second->GetStatementType() == IF){
            auto TheIF = (IFstatement *)i->second;
            if (TheIF->OKornot()) {
                i = ParsedStatements.find(TheIF->GETdes(state));
                if (i == ParsedStatements.end()) error("LINE NUMBER ERROR");
                i = --i;
                //i->second->execute(state);
                continue;
            }
        }
    }
    if (reRun) Run(state);
}

void Program::list(){
    for (auto i = SourceLines.begin(); i != SourceLines.end(); i++) {
        cout << i->second << endl;
    }
}


