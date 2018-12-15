/*
 * File: Basic.cpp
 * ---------------
 * Name: [yujie6]
 * Section: [TODO: Run!!]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: Make it run!!]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */
bool quit_or_not = false, Input = true;
void processLine(string line, Program & program, EvalState & state);
void tranverse(string a);
int choice;
/* Main program */

int main() {
   EvalState state;
   Program program;
   while (Input) {
      try {
         processLine(getLine(), program, state);
         if (quit_or_not) break;
      } catch (ErrorException & ex) {
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
   scanner.scanNumbers();
   scanner.setInput(line);
   Expression *firstorder = readE(scanner);
   if (firstorder->getType() == IDENTIFIER){
      tranverse(firstorder->toString());
      switch (choice) {
          case 1 : {
             Expression *exp = parseExp(scanner); int value;
             string variable = exp->toString();
             if (exp->getType() == IDENTIFIER){
                if (!state.isDefined(exp->toString() )) error("VARIABLE NOT DEFINED");
                else value = state.getValue(variable);
             }
             else value = exp->eval(state);
             cout << value << endl;
             delete exp; break;
          }
          case 2 : {quit_or_not = true; break; }
          case 3 : { program.list(); break; }
          case 4 : {program.clear(); state.clear(); break; }
          case 6 : {
             CompoundExp *Givevalue = (CompoundExp *)readE(scanner);
             if (Givevalue->getLHS()->toString() == "LET") error("SYNTAX ERROR");
             state.setValue( Givevalue->getLHS()->toString() ,Givevalue->getRHS()->eval(state));
             break;
          }
          case 7 : {
              string variable = scanner.nextToken();
              while(true) {
                  cout << " ? ";
                  Input = false;
                  string value;
                  getline(cin,value);
                  if (value[0] == '-') {
                      value = "0" + value;
                      scanner.setInput(value);
                      auto exp = readE(scanner);
                      state.setValue(variable, exp->eval(state));
                      break;
                  } else {
                      bool ValidNumber = true;
                      for (int i = 0; i < value.length(); i++){
                          if (value[i] > '9' || value[i] < '0') {
                              cout << "INVALID NUMBER" << endl;
                              ValidNumber = false;
                              break;
                          }
                      }
                      if (ValidNumber){
                      scanner.setInput(value);
                      auto exp = readE(scanner);
                      state.setValue(variable, exp->eval(state));
                      break;          }
                  }
              }
             break;
          }
          case 8 : {
              program.Run(state);
              break;
          }
          case 5 : {error("SYNTAX ERROR"); }
      }
   }
   else if (firstorder->getType() == CONSTANT){
      int lineNum = firstorder->eval(state);

      if (scanner.hasMoreTokens()) {
         program.addSourceLine(lineNum, line);
         Expression *SecondOrder = readE(scanner);
         if(SecondOrder->toString() == "REM"){
             auto stmt = new REMstatement;
             program.setParsedStatement(lineNum, (Statement*)stmt);
         }
         if(SecondOrder->toString() == "END"){
              auto stmt = new ENDstatement();
              program.setParsedStatement(lineNum, (Statement*)stmt);
         }
         if(SecondOrder->toString() == "PRINT"){
             Expression *output = readE(scanner);
             auto stmt = new PRINTstatement(output);
             program.setParsedStatement(lineNum, (Statement*)stmt);
         }
         if(SecondOrder->toString() == "LET"){
             CompoundExp *set = (CompoundExp *)readE(scanner);
             auto stmt = new LETstatement(set);
             program.setParsedStatement(lineNum, (Statement*)stmt);
         }
         if(SecondOrder->toString() == "INPUT"){
             string var = readE(scanner)->toString();
             auto stmt = new INPUTstatement(var);
             program.setParsedStatement(lineNum, (Statement*)stmt);
         }
         if(SecondOrder->toString() == "GOTO"){
             int destination = readE(scanner)->eval(state);
             auto stmt = new GOTOstatement(destination);
             program.setParsedStatement(lineNum, (Statement*)stmt);
         }
         if(SecondOrder->toString() == "IF"){

             Expression * PRE = readE(scanner);
             Expression * then = readE(scanner);
             Expression * newplace = readE(scanner);
             auto stmt = new IFstatement(PRE, newplace);
             program.setParsedStatement(lineNum, (Statement*)stmt);
         }

      }

      else {
          program.removeSourceLine(lineNum);

      }
   }

   else error("SYNTAX ERROR");
    Input = true;

}

void tranverse(string a){
                          choice = 5;
   if      (a == "PRINT") choice = 1;
   else if (a == "QUIT")  choice = 2;
   else if (a == "LIST")  choice = 3;
   else if (a == "CLEAR") choice = 4;
   else if (a == "LET")   choice = 6;
   else if (a == "INPUT") choice = 7;
   else if (a == "RUN")   choice = 8;
}
