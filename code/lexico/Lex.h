#ifndef LEX_H
#define LEX_H

#include "Token.h"
#include "TS.h"

class Lex {
    public:
        Lex (const char* file);
        virtual ~Lex();

        Token next();
        int line() const { return m_line; }
        TS getTS() const { return m_words; }
    
    private:
        int m_line;
        int ch;
        FILE* m_reader;
        TS m_words;

        void readch();
        bool readch(char c);
};

#endif