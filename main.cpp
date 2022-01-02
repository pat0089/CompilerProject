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

    std::ifstream in;

    if (argc > 1) {

        in.open(argv[1]);
        if (in.fail()) {
            return -1;
        }
        Compiler.Lex(in);
        in.close();
    } else {
        //most basic program, return a value:
        string return_2 = "int main() {    \n"
                          "    return 2;   \n"
                          "}               ";

        Compiler.Lex(return_2);
        cout << "********************" << endl;
        cout << "Original:" << endl;
        cout << return_2 << endl;
        cout << "********************" << endl;
    }

    cout << "Split by tokens:" << endl;
    cout << Compiler.GetLexer();
    cout << endl << "********************" << endl;

    Compiler.Parse();
    cout << Compiler.GetAST();

    string outString;

    std::ofstream out;

    if (argc > 1) {

        //get path from argv[1]
        string folder = string(argv[1]);
        auto lastFolderOffset = folder.find_last_of('/');
        folder = folder.substr(0, lastFolderOffset);
        string name = string(argv[1]);
        name.substr(lastFolderOffset+1);

    } else {

    }

    return 0;
}
