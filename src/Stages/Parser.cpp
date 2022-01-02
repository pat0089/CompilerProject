#include "Parser.hpp"
#include "../Types/Parsing/Syntax/Statements/StatementNode.hpp"
#include "../Types/Lexing/Tokens.hpp"

using std::deque;
const AST &Parser::GetAST() const {
    return _ast;
}

void Parser::Parse(const TokenList & tokens) {
    //create a copy of the token list to modify and parse as necessary
    _tokens = new TokenList(tokens);
    _ast.Program(ParseProgram());
}

ProgramNode * Parser::ParseProgram() {
    _curList = _tokens;
    return new ProgramNode(ParseMainFunction());
}

//main function node does not have a name
FunctionNode * Parser::ParseMainFunction() {

    (!IsNextToken(KeywordType::Int)) ? Fail() : PopFront();

    //check if function name is 'main'
    (!IsNextToken(TokenType::Identifier)) ? Fail() : PopFront();
    if (_lastParsed->GetRaw() != "main") Fail();

    auto newFunction = new FunctionNode(_lastParsed->GetRaw());

    //parse args
    newFunction->Add(ParseParameters());

    //parse body
    newFunction->Add(ParseBody());

    return newFunction;
}

StatementNode * Parser::ParseStatement() {
    //this will eventually support different types of statements
    _curList = new TokenList(List().SeekSymbolPop(SymbolType::Semicolon));
    (!IsNextToken(TokenType::Keyword)) ? Fail() : PopFront();

    //peek and error check for expression
    (!IsNextToken(TokenType::Literal)) ? Fail() : PopFront();
    auto newReturn = new ReturnNode(ParseExpression());

    //DONT FORGET THE SEMICOLON
    (!IsNextToken(SymbolType::Semicolon)) ? Fail() : PopFront();

    _curList = _tokens;
    return (StatementNode *)newReturn;
}

ExpressionNode * Parser::ParseExpression() {
    Token * integerConstant = List().SeekToNextLiteral();
    int realVal = atoi(integerConstant->GetRaw().c_str());
    //initialize constant value node
    return new ConstantNode(realVal);
}

//currently just spits out the error token or
//  if the token is empty (when list is empty)
//will handle gracefully once compiler is more fleshed out
void Parser::Fail() {
    if (_lastParsed->Type() == TokenType::None) {
        std::cerr << "FAIL0!: Empty Token\n";
    } else {
        std::cerr << "FAIL1!: Unexpected Token -> " << _lastParsed->GetRaw() << std::endl;
    }
}

Parameters * Parser::ParseParameters() {
    _curList = new TokenList(List().SeekSymbolPop(SymbolType::Close_Parenthesis));
    (!IsNextToken(SymbolType::Open_Parenthesis)) ? Fail() : PopFront();

    auto newArgs = new Parameters();

    while (!IsNextToken(SymbolType::Close_Parenthesis)) {
        newArgs->Add(ParseParameter());
        PopFront();
    }
    _curList = _tokens;
    return newArgs;
}

FunctionNode * Parser::ParseFunction() {
    (!IsNextToken(KeywordType::Int)) ? Fail() : PopFront();

    (!IsNextToken(TokenType::Identifier)) ? Fail() : PopFront();

    auto newFunction = new FunctionNode(_lastParsed->GetRaw());

    //parse args
    newFunction->Add(ParseParameters());

    //parse body
    newFunction->Add(ParseBody());

    return newFunction;
}

BodyNode * Parser::ParseBody() {
    _curList = new TokenList(List().SeekSymbolPop(SymbolType::Close_Brace));
    (!IsNextToken(SymbolType::Open_Brace)) ? Fail() : PopFront();

    auto newBody = new BodyNode();

    while (!IsNextToken(SymbolType::Close_Brace)) {
        newBody->Add(ParseStatement());
        PopFront();
    }
    _curList = _tokens;
    return newBody;
}

ParameterNode * Parser::ParseParameter() {
    //add code to parse the arguments of functions
    //Fail();


    return new ParameterNode();
}

TokenList &Parser::List() {
    return *_tokens;
}

bool Parser::IsNextToken(TokenType type) {
    return _curList->PeekType() == type;
}

bool Parser::IsNextToken(SymbolType stype) {
    if (IsNextToken(TokenType::Symbol)) {
        auto symToCheck = (Symbol *)(List().PeekFront());
        return symToCheck->SymType() == stype;
    }
    return false;
}

bool Parser::IsNextToken(KeywordType ktype) {
    if (IsNextToken(TokenType::Keyword)) {
        auto keyToCheck = (Keyword *)(List().PeekFront());
        return keyToCheck->KeyType() == ktype;
    }
    return false;
}

void Parser::PopFront() {
    _lastParsed = _curList->PopFront();
}

Token *Parser::PeekFront() {
    return _curList->PeekFront();
}
