#include <iostream>

#include "lexico/Lex.h"
#include "sintatico/Sintax.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Uso: " << argv[0] << " [programa] " << std::endl;
        exit(1);
    }

    try {
        Lex l(argv[1]);
        Sintax s(l);

        s.Program();
    } catch (const std::string& error) {
        std::cerr << error << std::endl;
    }

    return 0;
}