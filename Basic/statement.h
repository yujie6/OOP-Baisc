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
enum StatementType {PRINT ,GOTO, IF, REM, END , LET, INPUT};

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement(StatementType tp);

   Statement()= default;
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

   void SetStatementType(StatementType);

   virtual StatementType GetStatementType();

public:
    StatementType type;

};




class REMstatement: public Statement {
public:

    REMstatement();

    virtual void execute(EvalState &state);

    virtual StatementType GetStatementType();

private:

};

class ENDstatement: public Statement{
public:
    ENDstatement();

    virtual void execute(EvalState &state);

    virtual StatementType GetStatementType();

private:
};

class INPUTstatement: public Statement{
public:
    INPUTstatement(string variabel);

    virtual void execute(EvalState &state);

private:
    string var;
};

class GOTOstatement: public Statement{
public:
    GOTOstatement(int des);

    virtual void execute(EvalState &state);

    int getvalue();

private:

    int destination;
};




class PRINTstatement: public Statement{
public:

    PRINTstatement(Expression *);

    virtual void execute(EvalState &state);

private:

    Expression * exp;
};






class LETstatement: public Statement{
public:
    virtual void execute(EvalState &state);

    LETstatement(CompoundExp *);
private:
    CompoundExp *exp;
};






class IFstatement: public Statement{
public:
    virtual void execute(EvalState &state);
    IFstatement(Expression *,Expression *);
    int GETdes(EvalState &state);
    bool OKornot();

private:
    Expression * presence;
    Expression * newplace;
    bool ok;

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

#endif
