#include "Token.h"

Token::Token (std::string lex, enum Tag t)
    : m_lex(lex), m_tag(t) {};

Token::~Token() {}

const std::string Token::str() {
    std::stringstream ss;
    ss << "(\"" << m_lex << "\", " << tt2str(m_tag) << ")";
    return ss.str();
}

const std::string Token::getLex() {
    return m_lex;
}

const enum Tag Token::getTag() {
    return m_tag;
}