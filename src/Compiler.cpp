#include "Compiler.hpp"
using std::vector;
using std::string;
using std::istream;
using std::deque;

/// Lexes tokens from a source input stream
/// \param is Source input stream
void Compiler::Lex(istream & is) {
    _lexer->Lex(is);
}

/// Parses the lexed tokens
void Compiler::Parse() {
    if (_lexer->Verify()) _parser->Parse(GetLexedList());
}

const TokenList & Compiler::GetLexedList() const {
    return _lexer->GetList();
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

/// Generates an assembly file with the name supplied based on the parsed AST
/// \param fname Name of the file we're generating
void Compiler::Generate(const std::string & fname) {
    if (_lexer->Verify()) {
        if (_parser->Verify()) {
            //pass the function map information over to the code generator
            _codeGenerator->Map(_parser->Map());
            _codeGenerator->Generate(_parser->GetAST(), fname + ".s");
        } else {
            throw CodeGenerationException("Failed to verify valid parse tree (doesn't contain \'main\')!");
        }
    } else {
        throw CodeGenerationException("Failed to verify match all braces!");
    }
}