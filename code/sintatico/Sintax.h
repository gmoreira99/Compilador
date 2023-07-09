#ifndef SINTAX_H
#define SINTAX_H

#include "../lexico/Lex.h"

class Sintax{
    public:
        Sintax(Lex& lex);
        virtual ~Sintax();

        void Program();

    private:
        Lex m_lex;
        Token m_atual;

        void eat(enum Tag t);
        void err();

        void DeclList();
        void Decl();
        void IdentList();
        void Type();

        void StmtList();
        void Stmt();
        void AssignStmt();
        void IfStmt();
        void IfStmt_();
        void Condition();

        void RepeatStmt();
        void StmtSuffix();
        void WhileStmt();
        void StmtPrefix();

        void ReadStmt();
        void WriteStmt();
        void Writable();

        void Expression();
        void Expression_();
        void SimpleExpr();
        void SimpleExpr_();
        void Term();
        void Term_();
        void FactorA();
        void Factor();
        void RelOp();
        void AddOp();
        void MulOp();
        void Constant();
};

#endif