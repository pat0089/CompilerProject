#ifndef COMPILERPROJECT_PARSER_HPP
#define COMPILERPROJECT_PARSER_HPP
#include "../Types/Parsing/AST.hpp"
#include "../Types/Parsing/Syntax/ParsedNodes.hpp"
#include "../Types/Lexing/TokenList.hpp"

class Parser {
public:
    void Parse(const TokenList & tokens);
    const AST & GetAST() const;

private:
    AST _ast;

    //std::deque<Token> _tokens;
    TokenList * _tokens;

    //thinking ahead for error detection and mitigation
    TokenList * _curList;
    Token * _lastParsed;

    //Lexed list manipulation functions

    ProgramNode * ParseProgram();
    FunctionNode * ParseMainFunction();

    FunctionNode * ParseFunction();
    Parameters * ParseParameters();
    ParameterNode * ParseParameter();

    BodyNode * ParseBody();
    StatementNode * ParseStatement();
    ExpressionNode * ParseExpression();

    void Fail();

    TokenList & List();
    void PopFront();
    Token * PeekFront();

    bool IsNextToken(TokenType type);
    bool IsNextToken(SymbolType stype);
    bool IsNextToken(KeywordType ktype);
};

#endif //COMPILERPROJECT_PARSER_HPP
