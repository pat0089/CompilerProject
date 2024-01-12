#include <iostream>
#include <vector>
#include <fstream>
#include "src/Compiler.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;

int main(int argc, char * argv[]) {

    if (argc != 2) return -1;
    std::string fname = argv[1];

    std::ifstream fin(fname);
    Compiler.Lex(fin);
    //cout << Compiler.GetLexedList();

    try {
        Compiler.Parse();
        //cout << Compiler.GetAST();
    } catch (ParsingException & e) {
        cerr << e.what();
        exit(1);
    }

    auto fnameWithoutExtension = fname.substr(0, fname.find_last_of('.'));
    try {
        Compiler.Generate(fnameWithoutExtension);
    } catch (CodeGenerationException & e) {
        cerr << e.what();
        exit(2);
    }

    std::system(std::string("gcc -m32 " + fnameWithoutExtension + ".s -o " + fnameWithoutExtension).c_str());

    return 0;
}
