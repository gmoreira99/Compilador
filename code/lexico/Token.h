#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <sstream>
#include "Tag.h"

class Token {
    public:
        Token() : m_lex(""), m_tag(T_EOF) {}
        Token(std::string lex, enum Tag t);
        virtual ~Token();

        const std::string str();
        const std::string getLex();
        const enum Tag getTag();

    private:
        std::string m_lex;
        enum Tag m_tag;
};

#endif