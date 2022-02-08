#include <iostream>
#include "src/Types/Lexing/Tokens/Token.hpp"
#include "src/Compiler.hpp"
#include <vector>
#include <fstream>

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;

int main(int argc, char * argv[]) {

    std::ifstream fin;

    if (argc > 1) {
        fin.open(argv[1]);
    }

    std::istream &in = fin.is_open() ? fin : std::cin;

    Compiler.Lex(in);
    cout << "Split by tokens:" << endl;
    cout << Compiler.GetLexer();
    cout << endl << "********************" << endl;

    Compiler.Parse();
    cout << Compiler.GetAST();



    return 0;
}
