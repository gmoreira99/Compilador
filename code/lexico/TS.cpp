#include "TS.h"

TS::TS (const TS* prev)
    : m_prev(prev) {
        m_reserved["program"] = T_PROGRAM;
        m_reserved["begin"] = T_BEGIN;
        m_reserved["end"] = T_END;
        m_reserved["if"] = T_IF;
        m_reserved["then"] = T_THEN;
        m_reserved["else"] = T_ELSE;
        m_reserved["repeat"] = T_REPEAT;
        m_reserved["until"] = T_UNTIL;
        m_reserved["while"] = T_WHILE;
        m_reserved["do"] = T_DO;
        m_reserved["is"] = T_IS;
        m_reserved["read"] = T_READ;
        m_reserved["write"] = T_WRITE;
        m_reserved["int"] = T_INT;
        m_reserved["float"] = T_FLOAT;
        m_reserved["char"] = T_CHAR;

        m_reserved["+"] = T_ADD;
        m_reserved["-"] = T_SUB;
        m_reserved["*"] = T_MUL;
        m_reserved["/"] = T_DIV;

        m_reserved["=="] = T_EQ;
        m_reserved["!="] = T_NEQ;
        m_reserved[">"] = T_GRT;
        m_reserved[">="] = T_GRT_EQ;
        m_reserved["<"] = T_LOW;
        m_reserved["<="] = T_LOW_EQ;

        m_reserved["&&"] = T_AND;
        m_reserved["||"] = T_OR;
        m_reserved["!"] = T_NOT;

        m_reserved[";"] = T_SEMI;
        m_reserved["."] = T_PONTO;
        m_reserved[","] = T_VIRG;
        m_reserved["="] = T_ATRIB;
        m_reserved["("] = T_OP_PAR;
        m_reserved[")"] = T_CL_PAR;
        m_reserved["{"] = T_OP_BRACK;
        m_reserved["}"] = T_CL_BRACK;
        m_reserved["'"] = T_ASP;
}

TS::~TS() {
    delete m_prev;
}

void TS::put (const std::string& lex, const enum Tag t) {
    m_tab[lex] = t;
}

enum Tag TS::get (const std::string& lex) {
    for (const TS* n = this; n != nullptr; n = n->m_prev) {
        try {
            enum Tag t = n->m_reserved.at(lex);
            return t;
        } catch (std::out_of_range& oor) {
            continue;
        }
    }

    return T_ID;
}

const std::string TS::str() {
    std::stringstream ss;
    std::map<std::string, enum Tag>::iterator it = m_tab.begin();

    while (it != m_tab.end()) {
        ss << "Token: " << it->first << ", Info: " << tt2str(it->second) << std::endl;
        ++it;
    }

    return ss.str();
}