#include "Lex.h"

Lex::Lex (const char* file)
    : m_line(1), m_words(nullptr) {
    m_reader = fopen(file, "r");
    if (!m_reader)
        throw std::string("Arquivo nao encontrado");
    }

Lex::~Lex() {
    if (m_reader != nullptr) {
        fclose(m_reader);
    }
}

void Lex::readch() {
    ch = fgetc(m_reader);
}

bool Lex::readch (char c) {
    readch();
    if (ch != c) return false;
    ch = ' ';
    return true;
}

Token Lex::next() {
    int state;
    Token w;
    std::string lex = "";

    state = 1;
    while (state != 9 && state != 10) {
        readch();

        // std::cout << "[" << state << ", " << ch
        //           << " ('" << (char) ch << "')]" << std::endl;

        switch (state) {
            case 1:
                if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\b') {
                    state = 1;
                } else if (ch == '\n') {
                    m_line++;
                    state = 1;
                } else if (ch == '/') {
                    if (readch('*')) {
                        state = 2;
                    } else {
                        ungetc(ch, m_reader);
                        w = Token ("/", T_DIV);
                        state = 10;
                    }
                } else if (ch == '=' || ch == '>' || ch == '<' || ch == '!') {
                    lex = (char) ch;
                    if (readch('=')) {
                        lex += '=';
                        state = 9;
                    } else {
                        ungetc(ch, m_reader);
                        state = 9;
                    }
                } else if (ch == ';' || ch == '.' || ch == ',' || ch == '(' || ch == ')' ||
                           ch == '+' || ch == '-' || ch == '*') {
                    lex = (char) ch;
                    state = 9;
                } else if (ch == '\'') {
                    lex = "'";
                    state = 8;
                } else if (ch == '{') {
                    lex = "{";
                    state = 7;
                } else if (ch == '&') {
                    if (readch('&')) {
                        w = Token ("&&", T_AND);
                        state = 10;
                    } else {
                        ungetc(ch, m_reader);
                        lex += "&";
                        w = Token (lex, T_INVALIDO);
                        state = 10;
                    }
                } else if (ch == '|') {
                    if (readch('|')) {
                        w = Token ("||", T_OR);
                        state = 10;
                    } else {
                        ungetc(ch, m_reader);
                        lex += "|";
                        w = Token (lex, T_INVALIDO);
                        state = 10;
                    }
                } else if (isalpha(ch)) {
                    lex = (char) ch;
                    state = 3;
                } else if (isdigit(ch)) {
                    lex = (char) ch;
                    state = 4;
                } else if (ch == -1) {
                    w = Token();
                    state = 10;
                } else {
                    lex += char (ch);
                    w = Token (lex, T_INVALIDO);
                    state = 10;
                }
                break;
            case 2:
                if (ch == '\n') {
                    m_line++;
                    state = 2;
                } else if (ch == '*') {
                    if (readch('/')) {
                        state = 1;
                    } else {
                        state = 2;
                    }
                } else if (ch == -1) {
                    w = Token();
                    state = 10;
                } else {
                    state = 2;
                }
                break;
            case 3:
                if (isalpha(ch) || isdigit(ch) || ch == '_') {
                    lex += (char) ch;
                    state = 3;
                } else {
                    ungetc(ch, m_reader);
                    state = 9;
                }
                break;
            case 4:
                if (isdigit(ch)) {
                    lex += (char) ch;
                    state = 4;
                } else if (ch == '.') {
                    lex += (char) ch;
                    state = 5;
                } else {
                    ungetc(ch, m_reader);
                    w = Token (lex, T_INT_NUM);
                    state = 10;
                }
                break;
            case 5:
                if (isdigit(ch)) {
                    lex += (char) ch;
                    state = 6;
                } else if (ch == -1) {
                    w = Token("", T_UNEXP_EOF);
                    state = 10;
                } else {
                    ungetc(ch, m_reader);
                    w = Token (lex, T_INVALIDO);
                    state = 10;
                }
                break;
            case 6:
                if (isdigit(ch)) {
                    lex += (char) ch;
                    state = 6;
                } else {
                    ungetc(ch, m_reader);
                    w = Token (lex, T_FLT_NUM);
                    state = 10;
                }
                break;
            case 7:
                if (ch == '}') {
                    lex += "}";
                    w = Token (lex, T_LIT);
                    state = 10;
                } else if (ch == '\n') {
                    ungetc(ch, m_reader);
                    w = Token (lex, T_INVALIDO);
                    state = 10;
                } else if (ch == -1) {
                    w = Token("", T_UNEXP_EOF);
                    state = 10;
                } else {
                    lex += (char) ch;
                    state = 7;
                }
                break;
            case 8:
                lex += (char) ch;
                if (readch('\'')) {
                    lex += "'";
                    w = Token (lex, T_CH);
                    state = 10;
                } else if (ch == -1) {
                    w = Token(lex, T_UNEXP_EOF);
                    state = 10;
                } else {
                    ungetc(ch, m_reader);
                    w = Token (lex, T_INVALIDO);
                    state = 10;
                }
                break;
            default:
                throw std::string ("ERROR");
        }
    }

    if (state == 9) {
        Tag t = m_words.get(lex);
        if (t == T_ID) {
            m_words.put(lex, t);
        }
        w = Token (lex, t);
    }

    return w;
}