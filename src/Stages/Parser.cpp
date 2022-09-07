#include "Parser.hpp"
#include "../Types/Lexing/Tokens.hpp"
#include <sstream>
using std::cerr;
using std::endl;

string Parser::_curFunction;
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

FunctionNode * Parser::ParseMainFunction() {

    (!IsNextToken(KeywordType::Int)) ? Fail(KeywordType::Int) : PopFront();
    auto return_type = _lastParsed;
    //check if function name is 'main'
    (!IsNextToken(TokenType::Identifier)) ? Fail(TokenType::Identifier) : PopFront();

    if (_lastParsed->GetRaw() != "main") Fail(false);
    PutbackFront(_lastParsed);
    PutbackFront(return_type);

    return ParseFunction();
}

FunctionNode * Parser::ParseFunction() {

    (!IsNextToken(KeywordType::Int)) ? Fail(KeywordType::Int) : PopFront();

    (!IsNextToken(TokenType::Identifier)) ? Fail(TokenType::Identifier) : PopFront();

    _functionMap.insert(std::make_pair(_lastParsed->GetRaw(), FunctionInfoTable()));
    _curFunction = _lastParsed->GetRaw();

    auto newFunction = new FunctionNode(_lastParsed->GetRaw());

    auto params = ParseParameters();

    //parse args
    newFunction->Add(params);

    auto body = ParseBody();

    //parse body
    newFunction->Add(body);

    _curFunction = "";

    return newFunction;
}

Parameters * Parser::ParseParameters() {
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

StatementNode * Parser::ParseStatement() {
    //this will eventually support different types of statements
    TokenList * context = _curList;
    _curList = List().SeekToPop(List().SeekToNextSymbol(SymbolType::Semicolon));
    StatementNode * toReturn;
    if (IsNextToken(KeywordType::Return)) {
        //generate return statement
        PopFront();

        _functionMap[_curFunction].containsReturn = true;

        toReturn = new ReturnNode(ParseExpression());
    } else if (!IsNextToken(KeywordType::Int)) {
        auto temp = ParseExpression();
        toReturn = (StatementNode * )temp;
    } else {
        PopFront();
        auto var_name = Front();
        ExpressionNode * option = nullptr;
        if (IsNextToken(SymbolType::Equals)) {
            PopFront();
            option = ParseExpression();
        }

        if (_functionMap[_curFunction].variables.find(var_name->GetRaw()) != _functionMap[_curFunction].variables.end()) {
            throw UnexpectedTokenException("Variable Redefinition: " + var_name->GetRaw());
        } else {
            _functionMap[_curFunction].variables.insert(std::make_pair(var_name->GetRaw(), _functionMap[_curFunction].variables.size()));
        }

        toReturn = new DeclarationNode(var_name->GetRaw(), option);
    }

    //DONT FORGET THE SEMICOLON
    (!IsNextToken(SymbolType::Semicolon)) ? Fail(SymbolType::Semicolon) : PopFront();

    _curList = context;
    return toReturn;
}

ExpressionNode * Parser::ParseExpression() {

    if (IsNextToken(TokenType::Identifier)) {
        auto var_name = Front();
        if (IsNextToken(SymbolType::Equals)) {
            //parse assignment
            PopFront();

            if (_functionMap[_curFunction].variables.find(var_name->GetRaw()) == _functionMap[_curFunction].variables.end()) {
                throw UnexpectedTokenException("Variable Assignment before Declaration: " + var_name->GetRaw());
            }

            auto temp = new AssignmentNode(var_name->GetRaw(), ParseExpression());
            return (ExpressionNode *)temp;
        } else {
            PutbackFront(var_name);
        }
    }
    return ParseLogicalOrExpression();
}


ExpressionNode *Parser::ParseLogicalOrExpression() {
    ExpressionNode * logical_or_expr = ParseLogicalAndExpression();

    while (IsNextToken(SymbolType::Vertical_Line)) {
        SymbolType op = GetSymbolType(Front());
        SymbolType op2 = SymbolType::None;
        if (IsNextToken(SymbolType::Vertical_Line)) op2 = GetSymbolType(Front());
        auto next_expr = ParseLogicalAndExpression();
        logical_or_expr = new BinaryOperatorNode(op, op2, logical_or_expr, next_expr);
    }

    return logical_or_expr;
}

ExpressionNode *Parser::ParseLogicalAndExpression() {
    ExpressionNode * logical_and_expr = ParseEqualityExpression();

    while (IsNextToken(SymbolType::And)) {
        SymbolType op = GetSymbolType(Front());
        SymbolType op2 = SymbolType::None;
        if (IsNextToken(SymbolType::And)) op2 = GetSymbolType(Front());
        auto next_expr = ParseEqualityExpression();
        logical_and_expr = new BinaryOperatorNode(op, op2, logical_and_expr, next_expr);
    }

    return logical_and_expr;
}

ExpressionNode *Parser::ParseEqualityExpression() {
    ExpressionNode * equality_expr = ParseRelationalExpression();

    while (IsNextToken(SymbolType::Equals) || IsNextToken(SymbolType::Exclaimation)) {
        SymbolType op = GetSymbolType(Front());
        SymbolType op2 = SymbolType::None;
        if (IsNextToken(SymbolType::Equals)) op2 = GetSymbolType(Front());

        if (op2 == SymbolType::None) throw UnexpectedTokenException("Invalid Left Side Operator");

        auto next_expr = ParseRelationalExpression();
        equality_expr = new BinaryOperatorNode(op, op2, equality_expr, next_expr);
    }

    return equality_expr;
}

ExpressionNode *Parser::ParseRelationalExpression() {
    ExpressionNode * relational_expr = ParseAdditiveExpression();

    while (IsNextToken(SymbolType::Open_Chevron) || IsNextToken(SymbolType::Close_Chevron)) {
        SymbolType op = GetSymbolType(Front());
        SymbolType op2 = SymbolType::None;
        if (IsNextToken(SymbolType::Equals)) op2 = GetSymbolType(Front());
        auto next_expr = ParseAdditiveExpression();
        relational_expr = new BinaryOperatorNode(op, op2, relational_expr, next_expr);
    }

    return relational_expr;
}

ExpressionNode *Parser::ParseAdditiveExpression() {
    ExpressionNode * term = ParseTerm();

    while (IsNextToken(SymbolType::Plus) || IsNextToken(SymbolType::Minus)) {
        SymbolType op = GetSymbolType(Front());
        auto next_term = ParseTerm();
        term = new BinaryOperatorNode(op, SymbolType::None, term, next_term);
    }

    return term;
}

TermNode *Parser::ParseTerm() {
    TermNode * factor = ParseFactor();

    while (IsNextToken(SymbolType::Asterisk) || IsNextToken(SymbolType::ForwardSlash)) {
        SymbolType op = GetSymbolType(Front());
        auto next_factor = ParseFactor();
        factor = (TermNode *)(new BinaryOperatorNode(op, SymbolType::None, factor, next_factor));
    }

    return factor;
}

FactorNode *Parser::ParseFactor() {
    if (IsNextToken(SymbolType::Open_Parenthesis)) {
        PopFront();
        auto exp = (FactorNode *)ParseExpression();
        if (!IsNextToken(SymbolType::Close_Parenthesis)) {
            Fail(SymbolType::Close_Parenthesis);
        } else {
            PopFront();
            return exp;
        }
    } else if (IsUnaryOperation(PeekFront())) {
        auto next = Front();
        SymbolType stype = GetSymbolType(next);
        FactorNode * factor = ParseFactor();
        auto temp = new UnaryOperatorNode(stype, (ExpressionNode *)factor);
        return (FactorNode *)temp;
    } else if (IsNextToken(TokenType::Literal)) {
        auto temp = new ConstantNode((Literal *)Front());
        return (FactorNode *)temp;
    } else if (IsNextToken(TokenType::Identifier)) {
        auto tempToken = Front();
        if (_functionMap[_curFunction].variables.find(tempToken->GetRaw()) == _functionMap[_curFunction].variables.end())
            throw UnexpectedTokenException("Variable used before Declaration: " + tempToken->GetRaw());
        auto temp = new VariableNode(tempToken->GetRaw());
        return (FactorNode *)temp;
    } else {
        Fail("Tried to parse Factor and Failed!!!");
        return nullptr;
    }
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
    return IsTokenType(stype, _curList->PeekFront());
}

bool Parser::IsNextToken(KeywordType ktype) const {
    return IsTokenType(ktype, _curList->PeekFront());
}

bool Parser::IsNextTokenAfter(TokenType type) {
    auto temp = Front();
    bool flag = IsNextToken(type);
    PutbackFront(temp);
    return flag;
}

bool Parser::IsNextTokenAfter(SymbolType stype) {
    auto temp = Front();
    bool flag = IsNextToken(stype);
    PutbackFront(temp);
    return flag;
}

bool Parser::IsNextTokenAfter(KeywordType ktype) {
    auto temp = Front();
    bool flag = IsNextToken(ktype);
    PutbackFront(temp);
    return flag;
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
    return _curList->PeekFront();
}

//fail should output a bit more information now
void Parser::Fail(bool hasMain) {
    std::stringstream err;
    if (_verified) _verified = false;
    if (_lastParsed->Type() == TokenType::None) {
        cerr << "FAIL0!: Empty Token\n";
    } else if (!hasMain) {
        cerr << "FAIL1!: No \'main\' function found\n";
    } else {
        err << "FAIL2!: Unexpected Token -> " << _lastParsed->GetRaw() << "\n\tExpected: ";
        switch (_expectedType) {
            case TokenType::Symbol:
                err << "Symbol \'";
                switch (_expectedSymbolType) {
                    case SymbolType::Semicolon:
                        err << ";";
                        break;
                    case SymbolType::Open_Parenthesis:
                        err << "(";
                        break;
                    case SymbolType::Close_Parenthesis:
                        err << ")";
                        break;
                    case SymbolType::Open_Bracket:
                        err << "[";
                        break;
                    case SymbolType::Close_Bracket:
                        err << "]";
                        break;
                    case SymbolType::Open_Brace:
                        err << "{";
                        break;
                    case SymbolType::Close_Brace:
                        err << "}";
                        break;
                    case SymbolType::Equals:
                        err << "=";
                        break;
                    case SymbolType::Comma:
                        err << ",";
                        break;
                    case SymbolType::Period:
                        err << ".";
                        break;
                    case SymbolType::Tilde:
                        err << "~";
                        break;
                    case SymbolType::Exclaimation:
                        err << "!";
                        break;
                    case SymbolType::Hashmark:
                        err << "#";
                        break;
                    case SymbolType::And:
                        err << "&";
                        break;
                    case SymbolType::Asterisk:
                        err << "*";
                        break;
                }
                err << "\'\n";
                break;
            case TokenType::Keyword:
                err << "Keyword \"";
                switch (_expectedKeyType) {
                    case KeywordType::Int:
                        err << "int";
                        break;
                    case KeywordType::Return:
                        err << "return";
                        break;
                }
                err << "\"\n";
                break;
            case TokenType::Identifier:
                err << "Identifier\n";
                break;
            case TokenType::Literal:
                err << "Literal\n";
                break;
        }
        err << endl;
        throw UnexpectedTokenException(err.str());
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

void Parser::PutbackFront(Token *t) {
    _curList->PutbackFront(t);
}

std::unordered_map<std::string, FunctionInfoTable> Parser::FunctionMap() const {
    return _functionMap;
}
