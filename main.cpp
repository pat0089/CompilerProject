#include <iostream>
#include "src/Types/Lexing/Tokens/Token.hpp"
#include "src/Compiler.hpp"
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;

int main(int argc, char * argv[]) {

    std::string fname = argv[1] ? argv[1] : "";

    std::ifstream fin;

    if (!fname.empty()) {
        fin.open(fname);
    }

    //fake program to parse if we have no filename input
    auto temp = std::string("int main() {\n") +
            std::string("\treturn 2;\n") +
            std::string("}");

    std::istringstream sin(temp);

    std::istream& in = fin.is_open() ? static_cast<std::istream&>(fin) : sin;

    Compiler.Lex(in);
    cout << "Split by tokens:" << endl;
    cout << Compiler.GetLexer();
    cout << endl << "********************" << endl;

    Compiler.Parse();
    cout << Compiler.GetAST();

    if (fname.empty()) {
        Compiler.GetCodeGenerator().Generate(Compiler.GetAST(), "a.out");
    }
    else {
        Compiler.GetCodeGenerator().Generate(Compiler.GetAST(), fname.substr(0, fname.find_last_of('.')));
    }

    return 0;
}
