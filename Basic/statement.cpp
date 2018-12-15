/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement(StatementType tp) {
   type = tp;
}

Statement::~Statement() {
   /* Empty */
}

StatementType Statement::GetStatementType() {return type;}
void Statement::SetStatementType(StatementType tp) {type = tp;}




void REMstatement::execute(EvalState &state) {}
StatementType REMstatement::GetStatementType() {return REM;}
REMstatement::REMstatement() {type = REM;}

void ENDstatement::execute(EvalState &state) {}
StatementType ENDstatement::GetStatementType() {return END;}
ENDstatement::ENDstatement() {type = END;}



void PRINTstatement::execute(EvalState &state)
{  cout << exp->eval(state) << endl;  }
PRINTstatement::PRINTstatement(Expression * e) {exp = e; type = PRINT;}




void LETstatement::execute(EvalState &state)
{
   state.setValue(exp->getLHS()->toString(), exp->getRHS()->eval(state));
}
LETstatement::LETstatement(CompoundExp * e) {exp = e; type = LET;}




INPUTstatement::INPUTstatement(string variabel) {
   var = variabel;
   type = INPUT;
}
void INPUTstatement::execute(EvalState &state) {
   cout << " ? ";
   int value;
   cin >> value;
   cin.get();
   state.setValue(var, value);
}



GOTOstatement::GOTOstatement(int des) {destination = des; type = GOTO;}
void GOTOstatement::execute(EvalState &state) {}
int GOTOstatement::getvalue(){return destination;}


void IFstatement::execute(EvalState &state) {
    ok = presence->eval(state);
}
IFstatement::IFstatement(Expression * pre,Expression * np)
{
    presence = pre ; newplace = np;
    type = IF;
}
bool IFstatement::OKornot() {
    return ok;
}
int IFstatement::GETdes(EvalState &state) {return newplace->eval(state);}






