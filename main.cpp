#include <iostream>
#include "src/Token.hpp"
#include "src/Compiler.hpp"
#include <vector>
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;

int main() {
    Compiler c;
    //most basic program, return a value:
    string return_2 = "int main() {    \n"
                      "    return 2;   \n"
                      "}               ";
    vector<Token> lexedReturn2 = c.Lex(return_2);

    for (int i = 0; i < lexedReturn2.size(); i++) {
        cout << lexedReturn2[i] << endl;
    }

    cout << "********************" << endl;
    cout << return_2 << endl;
    cout << "********************" << endl;

    return 0;
}
