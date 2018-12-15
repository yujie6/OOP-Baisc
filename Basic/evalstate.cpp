/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */

#include <string>
#include <map>
#include "evalstate.h"

#include "../StanfordCPPLib/map.h"
using namespace std;

/* Implementation of the EvalState class */

EvalState::EvalState() {
   /* Empty */
}

EvalState::~EvalState() {
   /* Empty */
}

void EvalState::setValue(string var, int value) {
   symbolTable[var] = value;
}

void EvalState::clear(){
   symbolTable.clear();
}

int EvalState::getValue(string var) {
   return symbolTable[var];
}

bool EvalState::isDefined(string var) {
   auto it = symbolTable.find(var);
   if (it != symbolTable.end()) return true;
   else return false;
}
