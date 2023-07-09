#include <iostream>
#include <cstdlib>
#include "Sintax.h"

Sintax::Sintax (Lex& lex)
    : m_lex(lex) {
        m_atual = m_lex.next();
}

Sintax::~Sintax() {}

void Sintax::eat (enum Tag t) {
    std::cout << "Next: " << tt2str(t)
              << "; Token: \"" << m_atual.getLex() << "\"" <<std::endl;
    
    if (t == m_atual.getTag()) {
        m_atual = m_lex.next();
    } else { err(); }
}

void Sintax::err() {
    switch(m_atual.getTag()) {
        case T_INVALIDO:
            std::cout << "Token Invalido: \""
                      << m_atual.getLex() << "\"" << std::endl;
            break;
        case T_UNEXP_EOF:
        case T_EOF:
            std::cout << "Fim de Arquivo" << std::endl;
            break;
        default:
            std::cout << "Token Inesperado: \"" << m_atual.getLex() << "\", "
                      << tt2str(m_atual.getTag()) << std::endl;
    }

    std::cout << "Linha: " << m_lex.line() << std::endl;

    exit(1);
}

// Program ::= program Identifier [DeclList] begin StmtList end "."
void Sintax::Program() {
    eat(T_PROGRAM);
    eat(T_ID);
    DeclList();
    eat(T_BEGIN);
    StmtList();
    eat(T_END);
    eat(T_PONTO);
    eat(T_EOF);
}

// DeclList ::= Decl ";" {Decl ";"}
void Sintax::DeclList() {
    Decl();
    eat(T_SEMI);
    while (m_atual.getTag() == T_ID) {
        Decl();
        eat(T_SEMI);
    }
}

// Decl ::= IdentList is Type
void Sintax::Decl() {
    IdentList();
    eat(T_IS);
    Type();
}

// IdentList ::= Identifier {"," Identifier}
void Sintax::IdentList() {
    eat(T_ID);
    while (m_atual.getTag() == T_VIRG) {
        eat(T_VIRG);
        eat(T_ID);
    }
}

// Type ::= int | float | char
void Sintax::Type() {
    switch (m_atual.getTag()) {
        case T_INT: eat(T_INT);
            break;
        case T_FLOAT: eat(T_FLOAT);
            break;
        default: eat(T_CHAR);
    }
}

// StmtList ::= Stmt {";" Stmt}
void Sintax::StmtList() {
    Stmt();
    while (m_atual.getTag() == T_SEMI) {
        eat(T_SEMI);
        Stmt();
    }
}

// Stmt ::= AssignStmt | IfStmt | WhileStmt | Repeat-Stmt
// | ReadStmt | WriteStmt
void Sintax::Stmt() {
    switch (m_atual.getTag()) {
        case T_ID: AssignStmt();
            break;
        case T_IF: IfStmt();
            break;
        case T_WHILE: WhileStmt();
            break;
        case T_REPEAT: RepeatStmt();
            break;
        case T_READ: ReadStmt();
            break;
        default: WriteStmt();
    }
}

// AssignStmt ::= Identifier "=" SimpleExpr
void Sintax::AssignStmt() {
    eat(T_ID);
    eat(T_ATRIB);
    SimpleExpr();
}

// IfStmt ::= if Condition then StmtList IfStmt_
void Sintax::IfStmt() {
    eat(T_IF);
    Condition();
    eat(T_THEN);
    StmtList();
    IfStmt_();
}

// IfStmt_ ::= end | else StmtList end
void Sintax::IfStmt_() {
    if (m_atual.getTag() == T_END) {
        eat(T_END);
    } else {
        eat(T_ELSE);
        StmtList();
        eat(T_END);
    }
}

// Condition ::= Expression
void Sintax::Condition() {
    Expression();
}

// RepeatStmt ::= repeat StmtList StmtSuffix
void Sintax::RepeatStmt() {
    eat(T_REPEAT);
    StmtList();
    StmtSuffix();
}

// StmtSuffix ::= until Condition
void Sintax::StmtSuffix() {
    eat(T_UNTIL);
    Condition();
}

// WhileStmt ::= StmtPrefix StmtList end
void Sintax::WhileStmt() {
    StmtPrefix();
    StmtList();
    eat(T_END);
}

// StmtPrefix ::= while Condition do
void Sintax::StmtPrefix() {
    eat(T_WHILE);
    Condition();
    eat(T_DO);
}

// ReadStmt ::= read "(" Identifier ")"
void Sintax::ReadStmt() {
    eat(T_READ);
    eat(T_OP_PAR);
    eat(T_ID);
    eat(T_CL_PAR);
}

// WriteStmt ::= write "(" Writable ")"
void Sintax::WriteStmt() {
    eat(T_WRITE);
    eat(T_OP_PAR);
    Writable();
    eat(T_CL_PAR);
}

// Writable ::= SimpleExpr | Literal
void Sintax::Writable() {
    switch (m_atual.getTag()) {
        case T_ID:
        case T_INT_NUM:
        case T_FLT_NUM:
        case T_ASP:
        case T_OP_PAR:
        case T_NOT:
        case T_SUB: SimpleExpr();
            break;
        default: eat(T_LIT);
    }
}

// Expression ::= SimpleExpr Expression_
void Sintax::Expression() {
    SimpleExpr();
    Expression_();
}

// Expression_ ::=   | RelOp SimpleExpr
void Sintax::Expression_() {
    switch (m_atual.getTag()) {
        case T_EQ:
        case T_GRT:
        case T_GRT_EQ:
        case T_LOW:
        case T_LOW_EQ:
        case T_NEQ:
            RelOp();
            SimpleExpr();
            break;
        default: break;
    }
}

// SimpleExpr ::= Term SimpleExpr_
void Sintax::SimpleExpr() {
    Term();
    SimpleExpr_();
}

// SimpleExpr_ ::=   | AddOp Term SimpleExpr_
void Sintax::SimpleExpr_() {
    switch (m_atual.getTag()) {
        case T_ADD:
        case T_SUB:
        case T_OR:
            AddOp();
            Term();
            SimpleExpr_();
            break;
        default: break;
    }
}

// Term ::= FactorA Term_
void Sintax::Term() {
    FactorA();
    Term_();
}

// Term_ ::=   | MulOp FactorA Term_
void Sintax::Term_() {
    switch (m_atual.getTag()) {
        case T_MUL:
        case T_DIV:
        case T_AND:
            MulOp();
            FactorA();
            Term_();
            break;
        default: break;
    }
}

// FactorA ::= Factor | "!" Factor | "-" Factor
void Sintax::FactorA() {
    switch (m_atual.getTag()) {
        case T_ID:
        case T_INT_NUM:
        case T_FLT_NUM:
        case T_CH:
        case T_OP_PAR: Factor();
            break;
        case T_NOT:
            eat(T_NOT);
            Factor();
            break;
        default:
            eat(T_SUB);
            Factor();
    }
}

// Factor ::= Identifier | Constant | "(" Expression ")"
void Sintax::Factor() {
    switch (m_atual.getTag()) {
        case T_ID: eat(T_ID);
            break;
        case T_INT_NUM:
        case T_FLT_NUM:
        case T_CH: Constant();
            break;
        default:
            eat(T_OP_PAR);
            Expression();
            eat(T_CL_PAR);
    }
}

// Relop ::= "==" | ">" | ">=" | "<" | "<=" | "!="
void Sintax::RelOp() {
    switch (m_atual.getTag()) {
        case T_EQ: eat(T_EQ);
            break;
        case T_GRT: eat(T_GRT);
            break;
        case T_GRT_EQ: eat(T_GRT_EQ);
            break;
        case T_LOW: eat(T_LOW);
            break;
        case T_LOW_EQ: eat(T_LOW_EQ);
            break;
        default: eat(T_NEQ);
    }
}

// Addop ::= "+" | "-" | "||"
void Sintax::AddOp() {
    switch (m_atual.getTag()) {
        case T_ADD: eat(T_ADD);
            break;
        case T_SUB: eat(T_SUB);
            break;
        default: eat(T_OR);
    }
}

// Mulop ::= "*" | "/" | "&&"
void Sintax::MulOp() {
    switch (m_atual.getTag()) {
        case T_MUL: eat(T_MUL);
            break;
        case T_DIV: eat(T_DIV);
            break;
        default: eat(T_AND);
    }
}

// Constant ::= integer_const | float_const | char_const
void Sintax::Constant() {
    switch (m_atual.getTag()) {
        case T_INT_NUM: eat(T_INT_NUM);
            break;
        case T_FLT_NUM: eat(T_FLT_NUM);
            break;
        default: eat(T_CH);
    }
}