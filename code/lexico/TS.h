#ifndef TS_H
#define TS_H

#include <map>
#include <stdexcept>
#include "Tag.h"
#include "Token.h"

class TS {
    public:
        TS (const TS* prev);
        virtual ~TS();

        void put (const std::string& lex, const enum Tag t);
        enum Tag get (const std::string& lex);

        const std::string str();

    private:
        std::map<std::string, enum Tag> m_tab;
        std::map<std::string, enum Tag> m_reserved;
        const TS* m_prev;
};

#endif