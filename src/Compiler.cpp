#include "Compiler.hpp"
using std::vector;
using std::string;
using std::istream;
using std::deque;

void Compiler::Lex(istream & is) {
    _lexer->Lex(is);
}

void Compiler::Parse() {
    if (_lexer->Verify()) _parser->Parse(GetLexedList());
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

CodeGenerator& Compiler::GetCodeGenerator() const
{
    return *_codeGenerator;
}

Compiler::Compiler() {
    _lexer = new Lexer();
    _parser = new Parser();
    _codeGenerator = new CodeGenerator();
}

Compiler::~Compiler() {
    delete _lexer;
    delete _parser;
    delete _codeGenerator;
}

void Compiler::Generate(const std::string & fname) {
    if (_lexer->Verify() && _parser->Verify()) {
        //pass the function map information over to the code generator
        _codeGenerator->Map(_parser->Map());
        _codeGenerator->Generate(_parser->GetAST(), fname + ".s");
    }
}