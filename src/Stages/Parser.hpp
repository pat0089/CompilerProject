#ifndef COMPILERPROJECT_PARSER_HPP
#define COMPILERPROJECT_PARSER_HPP
#include <exception>
#include "../Types/Parsing/AST.hpp"
#include "../Types/Parsing/Syntax/ParsedNodes.hpp"
#include "../Types/Lexing/TokenList.hpp"
#include "../Types/Parsing/Syntax/Expressions/TermNode.hpp"
#include "../Types/Parsing/Syntax/Expressions/FactorNode.hpp"
#include "../Types/SymbolMap.hpp"

class UnexpectedTokenException : public std::exception {
public:
    UnexpectedTokenException(const std::string & msg) : message("UnexpectedTokenException: " + msg) {}
    const char * what() {
        return message.c_str();
    }
private:
    std::string message;
};

class Parser {
public:
    ~Parser();
    void Parse(const TokenList & tokens);
    const SymbolMap & Map() const;
    const AST & GetAST() const;

    static Token * _lastParsed;
    static TokenType _expectedType;
    static KeywordType _expectedKeyType;
    static SymbolType _expectedSymbolType;

    static bool Verify();

private:
    AST _ast;
    SymbolMap _symbolMap;

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
    StatementNode * ParseDeclaration();
    ExpressionNode * ParseExpression();
    ExpressionNode * ParseConditionalExpression();
    ExpressionNode * ParseLogicalOrExpression();
    ExpressionNode * ParseLogicalAndExpression();
    ExpressionNode * ParseEqualityExpression();
    ExpressionNode * ParseRelationalExpression();
    ExpressionNode * ParseAdditiveExpression();
    TermNode * ParseTerm();
    FactorNode * ParseFactor();



    static void Fail(bool hasMain = true);
    static void Fail(TokenType type);
    static void Fail(SymbolType stype);
    static void Fail(KeywordType ktype);


    TokenList & List();
    void PopFront();
    Token * PeekFront();
    void PutbackFront(Token * t);
    Token * Front();

    bool IsPrevToken(TokenType type) const;
    bool IsPrevToken(SymbolType stype) const;
    bool IsPrevToken(KeywordType ktype) const;

    bool IsNextToken(TokenType type) const;
    bool IsNextToken(SymbolType stype) const;
    bool IsNextToken(KeywordType ktype) const;

    bool IsNextTokenAfter(TokenType type);
    bool IsNextTokenAfter(SymbolType stype);
    bool IsNextTokenAfter(KeywordType ktype);

    bool IsTokenType(TokenType type, Token * t) const;
    bool IsTokenType(SymbolType stype, Token * t) const;
    bool IsTokenType(KeywordType ktype, Token * t) const;

    SymbolType GetSymbolType(Token * t) const;
    KeywordType GetKeywordType(Token * t) const;

    void TryParse(TokenType type);
    void TryParse(SymbolType stype);
    void TryParse(KeywordType ktype);

    bool IsUnaryOperation(Token * t);

    static bool _verified;
    static string _curFunction;
};

#endif //COMPILERPROJECT_PARSER_HPP
