#ifndef COMPILERPROJECT_PARSER_HPP
#define COMPILERPROJECT_PARSER_HPP
#include "../Types/Parsing/AST.hpp"
#include "../Types/Parsing/Syntax/ParsedNodes.hpp"
#include "../Types/Lexing/TokenList.hpp"
#include "../Types/Parsing/Syntax/Expressions/TermNode.hpp"
#include "../Types/Parsing/Syntax/Expressions/FactorNode.hpp"

class Parser {
public:
    void Parse(const TokenList & tokens);
    const AST & GetAST() const;

    static Token * _lastParsed;
    static TokenType _expectedType;
    static KeywordType _expectedKeyType;
    static SymbolType _expectedSymbolType;

    static bool Verify();

private:
    AST _ast;

    //std::deque<Token> _tokens;
    TokenList * _tokens;

    //thinking ahead for error detection and mitigation
    TokenList * _curList;

    //Lexed list manipulation functions

    ProgramNode * ParseProgram();
    FunctionNode * ParseMainFunction();

    FunctionNode * ParseFunction();
    Parameters * ParseParameters();
    ParameterNode * ParseParameter();

    //Running code parsers
    BodyNode * ParseBody();
    StatementNode * ParseStatement();
    ExpressionNode * ParseExpression();
    TermNode * ParseTerm();
    FactorNode * ParseFactor();


    static void Fail(bool hasMain = true);
    static void Fail(TokenType type);
    static void Fail(SymbolType stype);
    static void Fail(KeywordType ktype);


    TokenList & List();
    void PopFront();
    Token * PeekFront();
    Token * Front();

    bool IsPrevToken(TokenType type) const;
    bool IsPrevToken(SymbolType stype) const;
    bool IsPrevToken(KeywordType ktype) const;

    bool IsNextToken(TokenType type) const;
    bool IsNextToken(SymbolType stype) const;
    bool IsNextToken(KeywordType ktype) const;

    bool IsTokenType(TokenType type, Token * t) const;
    bool IsTokenType(SymbolType stype, Token * t) const;
    bool IsTokenType(KeywordType ktype, Token * t) const;

    SymbolType GetSymbolType(Token * t) const;
    KeywordType GetKeywordType(Token * t) const;

    bool IsUnaryOperation(Token * t);

    static bool _verified;

};

#endif //COMPILERPROJECT_PARSER_HPP
