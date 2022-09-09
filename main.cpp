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

    if (argc != 2) return -1;
    std::string fname = argv[1];

    std::ifstream fin(fname);
    Compiler.Lex(fin);
    //cout << "Split by tokens:" << endl;
    //
    cout << Compiler.GetLexer();
    //
    // cout << endl << "********************" << endl;


    try {
        //Compiler.Parse();
        //cout << Compiler.GetAST();
    } catch (UnexpectedTokenException e) {
        cerr << e.what();
        exit(1);
    }

    //auto fnameWithoutFS = fname.substr(0, fname.find_last_of('.'));
    //Compiler.Generate(fnameWithoutFS);

    //std::system(std::string("gcc -m32 " + fnameWithoutFS + ".s -o " + fnameWithoutFS).c_str());

    return 0;
}
