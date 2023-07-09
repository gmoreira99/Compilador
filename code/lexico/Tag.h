#ifndef TAG_H
#define TAG_H

#include <string>

enum Tag {
    // ESPECIAIS
    T_INVALIDO = -2,
    T_UNEXP_EOF = -1,
    T_EOF = 0,

    // VARIAVEIS
    T_ID,       // variavel
    T_CH,       // caractere
    T_LIT,      // literal
    T_INT_NUM,  // inteiro
    T_FLT_NUM,  // ponto flutuante

    // PALAVRAS RESERVADAS
    T_PROGRAM,  // PROGRAM
    T_BEGIN,    // BEGIN
    T_END,      // END
    T_IS,       // IS

    T_IF,       // IF
    T_THEN,     // THEN
    T_ELSE,     // ELSE
    T_REPEAT,   // REPEAT
    T_UNTIL,    // UNTIL
    T_WHILE,    // WHILE
    T_DO,       // DO

    T_READ,     // READ
    T_WRITE,    // WRITE

    T_INT,      // INT
    T_FLOAT,    // FLOAT
    T_CHAR,     // CHAR

    // OPERADORES
    T_ADD,      // +
    T_SUB,      // -
    T_MUL,      // *
    T_DIV,      // /

    T_EQ,       // ==
    T_NEQ,      // !=
    T_GRT,      // >
    T_GRT_EQ,   // >=
    T_LOW,      // <
    T_LOW_EQ,   // <=

    T_AND,      // &&
    T_OR,       // ||
    T_NOT,      // !

    // SIMBOLOS
    T_SEMI,     // ;
    T_PONTO,    // .
    T_VIRG,     // ,
    T_ATRIB,    // =
    T_OP_PAR,   // (
    T_CL_PAR,   // )
    T_OP_BRACK, // {
    T_CL_BRACK, // }
    T_ASP       // '
};

inline std::string tt2str (enum Tag t) {
    switch (t) {
        case T_INVALIDO: return "INVALIDO";
        case T_UNEXP_EOF: return "UNEXPECTED_EOF";
        case T_EOF: return "EOF";

        case T_ID: return "ID";
        case T_CH: return "'CHAR'";
        case T_LIT: return "{LIT}";
        case T_INT_NUM: return "[INT NUM]";
        case T_FLT_NUM: return "[FLOAT NUM]";

        case T_PROGRAM: return "PROGRAM";
        case T_BEGIN: return "BEGIN";
        case T_END: return "END";
        case T_IF: return "IF";
        case T_THEN: return "THEN";
        case T_ELSE: return "ELSE";
        case T_REPEAT: return "REPEAT";
        case T_UNTIL: return "UNTIL";
        case T_WHILE: return "WHILE";
        case T_DO: return "DO";
        case T_IS: return "IS";
        case T_READ: return "READ";
        case T_WRITE: return "WRITE";
        case T_INT: return "INT";
        case T_FLOAT: return "FLOAT";
        case T_CHAR: return "CHAR";

        case T_ADD: return "ADD";
        case T_SUB: return "SUB";
        case T_MUL: return "MUL";
        case T_DIV: return "DIV";
        
        case T_EQ: return "EQ";
        case T_NEQ: return "NEQ";
        case T_GRT: return "GRT";
        case T_GRT_EQ: return "GRT_EQ";
        case T_LOW: return "LOW";
        case T_LOW_EQ: return "LOW_EQ";
        
        case T_AND: return "AND";
        case T_OR: return "OR";
        case T_NOT: return "NOT";
        
        case T_SEMI: return "SEMI";
        case T_PONTO: return "PONTO";
        case T_VIRG: return "VIRG";
        case T_ATRIB: return "ATRIB";
        case T_OP_PAR: return "OP_PAR";
        case T_CL_PAR: return "CL_PAR";
        case T_OP_BRACK: return "OP_BRACK";
        case T_CL_BRACK: return "CL_BRACK";
        case T_ASP: return "ASP";
    }

    return "INVALIDO";
}

#endif