#include "Lexer.hpp"
#include <sstream>
using std::string;
using std::deque;
using std::istream;
using std::ostream;
using std::regex;

const regex Lexer::isKeyword = regex("int|char|return");
const regex Lexer::isIdentifier = regex("[a-zA-Z]+");
const regex Lexer::isLiteral = regex("[0-9]+");
const regex Lexer::isSymbol = regex(R"(\(|\)|\{|\}|\;|\+|\-|\*|\/|\=)");

void Lexer::Lex(istream & is) {
    is >> *_tokens;
}

const TokenList & Lexer::GetList() const {
    return *_tokens;
}

Lexer::Lexer() {
    _tokens = new TokenList();
}

istream &operator>>(istream &is, Lexer &lexer) {
    is >> *lexer._tokens;
    return is;
}

ostream &operator<<(ostream &os, const Lexer &lexer) {
    os << *lexer._tokens;
    return os;
}

string Lexer::LexNextToken(istream & is) {
    char cur;
    char last = 0;
    string curChar;
    string toTokenize;
    //algorithm:
    //read in a character until we reach a symbol or a whitespace
    //is symbol:
    //      the string is empty, return the symbol itself
    //      string to return isn't empty, then put back the character and return the current string
    //is character:
    //      if the character read is numeric and the last character was alphabetical (and vice versa),
    //      put back the last character and return the string
    //
    //      else add the character to the string
    while (is.get(cur)) {
        if (isspace(cur)) {
            if (last != 0) {
                break;
            }
        } else {
            curChar.push_back(cur);
            if (regex_match(curChar, isSymbol)) {
                if (toTokenize.empty()) {
                    toTokenize = curChar;
                } else {
                    is.putback(cur);
                }
                break;
            } else {
                if (isalpha(cur) && isdigit(last) || isalpha(last) && isdigit(cur)) {
                    is.putback(cur);
                    break;
                } else if (isalpha(cur) || isdigit(cur)) {
                    toTokenize.push_back(cur);
                }
            }
            last = cur;
            curChar.erase();
        }
    }
    return toTokenize;
}

Lexer::~Lexer() {
    delete _tokens;
}

bool Lexer::Verify() {
    if (!_verified) _verified = _tokens->Verify();
    return _verified;
}