#include "Compiler.hpp"
using std::vector;
using std::string;
using std::istream;
using std::deque;

void Compiler::Lex(const string & toLex) {
    _lexer->Lex(toLex);
}

void Compiler::Lex(istream & is) {
    _lexer->Lex(is);
}

void Compiler::Parse() {
    _parser->Parse(GetLexedList());
}

const TokenList & Compiler::GetLexedList() const {
    return _lexer->GetList();
}

const AST &Compiler::GetAST() const {
    return _parser->GetAST();
}

Parser &Compiler::GetParser() const {
    return *_parser;
}

Lexer &Compiler::GetLexer() const {
    return *_lexer;
}

Compiler::Compiler() {
    _lexer = new Lexer();
    _parser = new Parser();
}

Compiler::~Compiler() {
    delete _lexer;
    delete _parser;
}
