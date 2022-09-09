#include "Lexer.hpp"
#include <sstream>
using std::string;
using std::deque;
using std::istream;
using std::ostream;
using std::regex;

const regex Lexer::isKeyword = regex("int|char|return|if|else");
const regex Lexer::isIdentifier = regex("[_a-zA-Z][_a-zA-Z0-9]{0,30}");
const regex Lexer::isLiteral = regex("[0-9]+");
const regex Lexer::isSymbol = regex(R"(\(|\)|\{|\}|\<|\>|\[|\]|\;|\+|\-|\*|\/|\=|\~|\!|\||\&|\:|\?)");

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
    string toTokenize, toTest;
    char cur;

    while (!isspace(is.peek()) && !is.eof()) {
        //grab the next char and put it on the string
        //also assign it to test for symbol
        is.get(cur);
        toTest = cur;
        if (!isspace(cur)) toTokenize.push_back(cur);

        //test if the token we're reading is a symbol character
        if (std::regex_match(toTest, isSymbol)) {
            //if the token isn't the only char we've read,
            //  putback the token to be read on the next << call on the file
            //else the token is the only char we've read,
            //  then return it
            //     either way, remember to remove the trailing whitespace
            //     whenever we return a value so that the next time it's called
            //     the function returns a non-empty string
            if (toTokenize.length() > 1) {
                is.putback(cur);
                toTokenize.pop_back();
                //get rid of trailing whitespace
                while (isspace(is.peek()) && !is.eof()) { is.get(cur); }
                return toTokenize;
            } else {
                //get rid of trailing whitespace
                while (isspace(is.peek()) && !is.eof()) { is.get(cur); }
                return toTokenize;
            }
        }

    }
    //get rid of trailing whitespace
    while (isspace(is.peek()) && !is.eof()) { is.get(cur); }

    return toTokenize;
}

Lexer::~Lexer() {
    delete _tokens;
}

bool Lexer::Verify() {
    if (!_verified) _verified = _tokens->Verify();
    return _verified;
}