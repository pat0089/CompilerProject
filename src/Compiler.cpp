#include "Compiler.hpp"
#include <sstream>
using std::string;
using std::vector;
using std::istream;

vector<Token> Compiler::Lex(string toLex) {
    vector<Token> toReturn;
    std::stringstream processor(toLex);
    for (Token t; processor >> t;) {
        toReturn.push_back(t);
    }
    return toReturn;
}

vector<Token> Compiler::Lex(istream &is) {
    vector<Token> toReturn;
    for (Token t; is >> t;) {
        toReturn.push_back(t);
    }
    return toReturn;
}
