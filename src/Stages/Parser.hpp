#ifndef COMPILERPROJECT_PARSER_HPP
#define COMPILERPROJECT_PARSER_HPP
#include <exception>
#include "../Types/Parsing/AST.hpp"
#include "../Types/Parsing/Syntax/ParsedNodes.hpp"
#include "../Types/Lexing/TokenList.hpp"
#include "../Types/Lexing/Tokens.hpp"
#include "../Types/Parsing/Syntax/Expressions/TermNode.hpp"
#include "../Types/Parsing/Syntax/Expressions/FactorNode.hpp"
#include "../Types/SymbolMap.hpp"

class ParsingException : public std::runtime_error {
public:
    explicit ParsingException(const char * msg) : std::runtime_error(std::string("ParsingException: ") + msg) {}
};

static_assert(std::is_nothrow_copy_constructible<ParsingException>::value, "ParsingException must be nothrow copy constructible");

class Parser {
public:
    ~Parser();
    void Parse(const TokenList & tokens);
    const SymbolMap & Map() const;
    const AST & GetAST() const;

    bool Verify();

private:
    AST * _ast;
    SymbolMap _symbolMap;
    TokenList * _curList;

    //Lexed list manipulation functions

    ProgramNode * ParseProgram();

    FunctionNode * ParseFunction();
    Parameters * ParseParameters();
    ParameterNode * ParseParameter();

    //Running code parsers
    BodyNode * ParseBody();
    StatementNode * ParseStatement();
    StatementNode * ParseDeclaration();
    ExpressionNode * ParseExpression();
    ExpressionNode * ParseOptionalExpression();

    ExpressionNode * ParseConditionalExpression();

    ExpressionNode * ParseLogicalOrExpression();
    ExpressionNode * ParseLogicalAndExpression();

    ExpressionNode * ParseBitwiseOrExpression();
    ExpressionNode * ParseBitwiseXorExpression();
    ExpressionNode * ParseBitwiseAndExpression();

    ExpressionNode * ParseEqualityExpression();
    ExpressionNode * ParseRelationalExpression();

    ExpressionNode * ParseBitwiseShiftExpression();

    ExpressionNode * ParseAdditiveExpression();

    TermNode * ParseTerm();
    FactorNode * ParseFactor();

    void Fail(bool hasMain = true);
    void Fail(TokenType ttype, Token * errToken);
    void Fail(SymbolType stype, Token * errToken);
    void Fail(KeywordType ktype, Token * errToken);
    void Fail(const char * message);

    void PopFront();
    Token * PeekFront();
    void PutbackFront(Token * t);
    Token * Front();

    bool IsNextToken(TokenType type) const;
    bool IsNextToken(SymbolType stype) const;
    bool IsNextToken(KeywordType ktype) const;

    static bool IsTokenType(TokenType type, Token * t) ;
    static bool IsTokenType(SymbolType stype, Token * t) ;
    static bool IsTokenType(KeywordType ktype, Token * t) ;

    static SymbolType GetSymbolType(Token * t) ;
    static KeywordType GetKeywordType(Token * t) ;

    void TryParse(TokenType type);
    void TryParse(SymbolType stype);
    void TryParse(KeywordType ktype);

    static bool IsUnaryOperation(Token * t);

    bool _verified = true;

    ExpressionNode *ParseFunctionCall();

    GlobalNode *ParseGlobalDeclaration();

    void OutputToken(Token * token, std::ostream & os);
};

#endif //COMPILERPROJECT_PARSER_HPP
