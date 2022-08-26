#include "Parser.hpp"
#include "../Types/Lexing/Tokens.hpp"
#include "../Types/Parsing/Syntax/Expressions/BinaryOperatorNode.hpp"
#include <sstream>
using std::cerr;
using std::endl;

Token * Parser::_lastParsed = nullptr;
TokenType Parser::_expectedType = TokenType::None;
SymbolType Parser::_expectedSymbolType = SymbolType::None;
KeywordType Parser::_expectedKeyType = KeywordType::None;

const AST &Parser::GetAST() const {
    return _ast;
}

void Parser::Parse(const TokenList & tokens) {
    //create a copy of the token list to modify and parse as necessary
    _tokens = new TokenList(tokens);
    _curList = _tokens;
    _verified = true;
    _ast.Program(ParseProgram());
}

ProgramNode * Parser::ParseProgram() {
    return new ProgramNode(ParseMainFunction());
}

//main function node does not have a name
FunctionNode * Parser::ParseMainFunction() {

    (!IsNextToken(KeywordType::Int)) ? Fail(KeywordType::Int) : PopFront();

    //check if function name is 'main'
    (!IsNextToken(TokenType::Identifier)) ? Fail(TokenType::Identifier) : PopFront();
    if (_lastParsed->GetRaw() != "main") Fail(false);

    auto newFunction = new FunctionNode(_lastParsed->GetRaw());

    //parse args
    newFunction->Add(ParseParameters());

    //parse body
    newFunction->Add(ParseBody());

    return newFunction;
}

Parameters * Parser::ParseParameters() {
    //_curList = new TokenList(List().SeekSymbolPop(SymbolType::Close_Parenthesis));
    _curList = List().SeekToPop(List().SeekToNextSymbol(SymbolType::Close_Parenthesis));
    (!IsNextToken(SymbolType::Open_Parenthesis)) ? Fail(SymbolType::Open_Parenthesis) : PopFront();

    auto newArgs = new Parameters();
    while (!IsNextToken(SymbolType::Close_Parenthesis)) {
        newArgs->Add(ParseParameter());
    }

    (!IsNextToken(SymbolType::Close_Parenthesis)) ? Fail(SymbolType::Close_Parenthesis) : PopFront();

    _curList = _tokens;
    return newArgs;
}

StatementNode * Parser::ParseStatement() {
    //this will eventually support different types of statements
    TokenList * context = _curList;
    _curList = List().SeekToPop(List().SeekToNextSymbol(SymbolType::Semicolon));

    //generate return statement
    (!IsNextToken(TokenType::Keyword)) ? Fail(TokenType::Keyword) : PopFront();
    auto newReturn = new ReturnNode(ParseExpression());

    //DONT FORGET THE SEMICOLON
    (!IsNextToken(SymbolType::Semicolon)) ? Fail(SymbolType::Semicolon) : PopFront();

    _curList = context;
    return (StatementNode *)newReturn;
}

ExpressionNode * Parser::ParseExpression() {
    ExpressionNode * term = ParseTerm();

    while (IsNextToken(SymbolType::Plus) || IsNextToken(SymbolType::Minus)) {
        SymbolType op = GetSymbolType(Front());
        auto next_term = ParseTerm();
        term = new BinaryOperatorNode(op, term, next_term);
    }

    return term;
}

TermNode *Parser::ParseTerm() {
    TermNode * factor = ParseFactor();

    while (IsNextToken(SymbolType::Asterisk) || IsNextToken(SymbolType::ForwardSlash)) {
        SymbolType op = GetSymbolType(Front());
        auto next_factor = ParseFactor();
        factor = (TermNode *)(new BinaryOperatorNode(op, factor, next_factor));
    }

    return factor;
}

FactorNode *Parser::ParseFactor() {
    auto next = Front();
    if (IsTokenType(SymbolType::Open_Parenthesis, next)) {
        auto exp = (FactorNode *)ParseExpression();
        if (!IsNextToken(SymbolType::Close_Parenthesis)) {
            Fail(SymbolType::Close_Parenthesis);
        } else {
            PopFront();
            return exp;
        }
    } else if (IsUnaryOperation(next)) {
        SymbolType stype = GetSymbolType(next);
        FactorNode * factor = ParseFactor();
        auto temp = new UnaryOperatorNode(stype, (ExpressionNode *)factor);
        return (FactorNode *)temp;
    } else if (IsTokenType(TokenType::Literal, next)) {
        auto temp = new ConstantNode((Literal *)next);
        return (FactorNode *)temp;
    } else {
        Fail("Tried to parse Factor and Failed!!!");
        return nullptr;
    }
}

FunctionNode * Parser::ParseFunction() {
    (!IsNextToken(KeywordType::Int)) ? Fail(KeywordType::Int) : PopFront();

    (!IsNextToken(TokenType::Identifier)) ? Fail(TokenType::Identifier) : PopFront();

    auto newFunction = new FunctionNode(_lastParsed->GetRaw());

    //parse args
    newFunction->Add(ParseParameters());

    //parse body
    newFunction->Add(ParseBody());

    return newFunction;
}

BodyNode * Parser::ParseBody() {
    TokenList * context = _curList;
    _curList = List().SeekToPop(List().SeekToNextSymbol(SymbolType::Close_Brace));
    (!IsNextToken(SymbolType::Open_Brace)) ? Fail(SymbolType::Open_Brace) : PopFront();

    auto newBody = new BodyNode();

    while (!IsNextToken(SymbolType::Close_Brace)) {
        newBody->Add(ParseStatement());
    }

    (!IsNextToken(SymbolType::Close_Brace)) ? Fail(SymbolType::Close_Brace) : PopFront();

    _curList = context;
    return newBody;
}

ParameterNode * Parser::ParseParameter() {
    //add code to parse the arguments of functions
    //Fail();
    return new ParameterNode();
}

TokenList &Parser::List() {
    return *_curList;
}

bool Parser::IsTokenType(TokenType type, Token * t) const {
    return t->Type() == type;
}

bool Parser::IsTokenType(SymbolType stype, Token * t) const {
    if (IsTokenType(TokenType::Symbol, t)) {
        auto temp = (Symbol *) t;
        return temp->SymType() == stype;
    }
    return false;
}

bool Parser::IsTokenType(KeywordType ktype, Token * t) const {
    if (IsTokenType(TokenType::Keyword, t)) {
        auto temp = (Keyword *) t;
        return temp->KeyType() == ktype;
    }
    return false;
}

bool Parser::IsPrevToken(TokenType type) const {
    return _lastParsed->Type() == type;
}

bool Parser::IsPrevToken(SymbolType stype) const {
    return IsTokenType(stype, _lastParsed);
}

bool Parser::IsPrevToken(KeywordType ktype) const {
    return IsTokenType(ktype, _lastParsed);
}

bool Parser::IsNextToken(TokenType type) const {
    return _curList->PeekType() == type;
}

bool Parser::IsNextToken(SymbolType stype) const {
    return IsTokenType(stype, _curList->Front());
}

bool Parser::IsNextToken(KeywordType ktype) const {
    return IsTokenType(ktype, _curList->Front());
}

SymbolType Parser::GetSymbolType(Token *t) const {
    if (IsTokenType(TokenType::Symbol, t)) {
        auto temp = (Symbol *)t;
        return temp->SymType();
    }
    return SymbolType::None;
}

KeywordType Parser::GetKeywordType(Token *t) const {
    if (IsTokenType(TokenType::Keyword, t)) {
        auto temp = (Keyword *)t;
        return temp->KeyType();
    }
    return KeywordType::None;
}

void Parser::PopFront() {
    _lastParsed = _curList->PopFront();
}

Token *Parser::PeekFront() {
    return _curList->Front();
}

//fail should output a bit more information now
void Parser::Fail(bool hasMain) {
    if (_verified) _verified = false;
    if (_lastParsed->Type() == TokenType::None) {
        cerr << "FAIL0!: Empty Token\n";
    } else if (!hasMain) {
        cerr << "FAIL1!: No \'main\' function found\n";
    } else {
        cerr << "FAIL2!: Unexpected Token -> " << _lastParsed->GetRaw() << "\n\tExpected: ";
        switch (_expectedType) {
            case TokenType::Symbol:
                cerr << "Symbol \'";
                switch (_expectedSymbolType) {
                    case SymbolType::Semicolon:
                        cerr << ";";
                        break;
                    case SymbolType::Open_Parenthesis:
                        cerr << "(";
                        break;
                    case SymbolType::Close_Parenthesis:
                        cerr << ")";
                        break;
                    case SymbolType::Open_Bracket:
                        cerr << "[";
                        break;
                    case SymbolType::Close_Bracket:
                        cerr << "]";
                        break;
                    case SymbolType::Open_Brace:
                        cerr << "{";
                        break;
                    case SymbolType::Close_Brace:
                        cerr << "}";
                        break;
                    case SymbolType::Equals:
                        cerr << "=";
                        break;
                    case SymbolType::Comma:
                        cerr << ",";
                        break;
                    case SymbolType::Period:
                        cerr << ".";
                        break;
                    case SymbolType::Tilde:
                        cerr << "~";
                        break;
                    case SymbolType::Exclaimation:
                        cerr << "!";
                        break;
                    case SymbolType::Hashmark:
                        cerr << "#";
                        break;
                    case SymbolType::And:
                        cerr << "&";
                        break;
                    case SymbolType::Asterisk:
                        cerr << "*";
                        break;
                }
                cerr << "\'\n";
                break;
            case TokenType::Keyword:
                cerr << "Keyword \"";
                switch (_expectedKeyType) {
                    case KeywordType::Int:
                        cerr << "int";
                        break;
                    case KeywordType::Return:
                        cerr << "return";
                        break;
                }
                cerr << "\"\n";
                break;
            case TokenType::Identifier:
                cerr << "Identifier\n";
                break;
            case TokenType::Literal:
                cerr << "Literal\n";
                break;
        }
        cerr << endl;
    }
}

void Parser::Fail(TokenType type)  {
    _expectedSymbolType = SymbolType::None;
    _expectedKeyType = KeywordType::None;
    _expectedType = type;
    Fail();
}

void Parser::Fail(SymbolType stype) {
    _expectedType = TokenType::Symbol;
    _expectedSymbolType = stype;
    _expectedKeyType = KeywordType::None;
    Fail();
}

void Parser::Fail(KeywordType ktype) {
    _expectedType = TokenType::Keyword;
    _expectedKeyType = ktype;
    _expectedSymbolType = SymbolType::None;
    Fail();
}

bool Parser::_verified = true;

bool Parser::Verify() {
    return _verified;
}

Token *Parser::Front() {
    auto temp = PeekFront();
    PopFront();
    return temp;
}

bool Parser::IsUnaryOperation(Token * t) {
    return (IsTokenType(SymbolType::Tilde, t) || IsTokenType(SymbolType::Minus, t) || IsTokenType(SymbolType::Exclaimation, t));
}
