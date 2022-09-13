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
    _curList = new TokenList(tokens);
    _verified = true;
    _ast.Program(ParseProgram());
}

ProgramNode * Parser::ParseProgram() {
    return new ProgramNode(ParseMainFunction());
}

FunctionNode * Parser::ParseMainFunction() {

    auto return_type = Front();
    if (!IsTokenType(KeywordType::Int, return_type)) Fail(KeywordType::Int);

    //check if function name is 'main'
    auto func_name = Front();
    if (!IsTokenType(TokenType::Identifier, func_name)) Fail(TokenType::Identifier);
    if (func_name->GetRaw() != "main") Fail(false);
    PutbackFront(func_name);
    PutbackFront(return_type);

    return ParseFunction();
}

FunctionNode * Parser::ParseFunction() {

    TryParse(KeywordType::Int);

    Identifier * name = nullptr;

    if (!IsNextToken(TokenType::Identifier)) {
        Fail(TokenType::Identifier);
    } else {
        name = (Identifier *)Front();
    }

    _symbolMap.AddFunction(name->GetRaw(), true);
    auto newFunction = new FunctionNode(name->GetRaw());

    //DONT FORGET TO DELETE THE TOKENS YOU Front() OFF THE QUEUE:
    delete name;

    auto params = ParseParameters();

    //parse args
    newFunction->Add(params);

    auto body = ParseBody();

    //parse body
    newFunction->Add(body);

    return newFunction;
}

Parameters * Parser::ParseParameters() {
    TryParse(SymbolType::Open_Parenthesis);
    auto newArgs = new Parameters();
    while (!IsNextToken(SymbolType::Close_Parenthesis)) {
        newArgs->Add(ParseParameter());
    }
    TryParse(SymbolType::Close_Parenthesis);
    return newArgs;
}

BodyNode * Parser::ParseBody() {
    TryParse(SymbolType::Open_Brace);

    auto newBody = new BodyNode();

    while (!IsNextToken(SymbolType::Close_Brace)) {
        if (!IsNextToken(KeywordType::Int)) newBody->Add(ParseStatement());
        else newBody->Add(ParseDeclaration());
    }

    TryParse(SymbolType::Close_Brace);

    return newBody;
}

ParameterNode * Parser::ParseParameter() {
    //add code to parse the arguments of functions
    //Fail();
    return new ParameterNode();
}

StatementNode *Parser::ParseDeclaration() {
    StatementNode * toReturn;

    PopFront();
    auto var_name = Front();
    ExpressionNode * option = nullptr;
    if (IsNextToken(SymbolType::Equals)) {
        PopFront();
        option = ParseExpression();
    }

    if (_symbolMap.AddVariable(var_name->GetRaw()) == -1) {
        throw ParsingException("Variable redefinition: " + var_name->GetRaw());
    }

    toReturn = new DeclarationNode(var_name->GetRaw(), option);

    delete var_name;

    //DONT FORGET THE SEMICOLON
    TryParse(SymbolType::Semicolon);

    return toReturn;
}

StatementNode * Parser::ParseStatement() {
    StatementNode * toReturn = nullptr;
    if (IsNextToken(KeywordType::Return)) {
        //generate return statement
        PopFront();

        _symbolMap.ContainsReturn(true);

        toReturn = new ReturnNode(ParseExpression());
    } else if (!IsNextToken(KeywordType::If) && !IsNextToken(SymbolType::Open_Brace)) {
        auto temp = ParseExpression();
        toReturn = (StatementNode * )temp;
    } else if (!IsNextToken(SymbolType::Open_Brace)) {
        PopFront();
        TryParse(SymbolType::Open_Parenthesis);
        auto exp = ParseExpression();
        TryParse(SymbolType::Close_Parenthesis);
        auto state = ParseStatement();
        StatementNode * option = nullptr;
        if (IsNextToken(KeywordType::Else)) {
            PopFront();
            option = ParseStatement();
        }
        toReturn = new ConditionalStatementNode(exp, state, option);
    } else {
        PopFront();

        auto newBody = new BodyNode();

        while (!IsNextToken(SymbolType::Close_Brace)) {
            if (!IsNextToken(KeywordType::Int)) newBody->Add(ParseStatement());
            else newBody->Add(ParseDeclaration());
        }

        TryParse(SymbolType::Close_Brace);
        toReturn = (StatementNode *)newBody;
    }

    //DONT FORGET THE SEMICOLON
    if (toReturn->Type() != SyntaxType::Conditional_Statement && toReturn->Type() != SyntaxType::Body)
        TryParse(SymbolType::Semicolon);
    return toReturn;
}

ExpressionNode * Parser::ParseExpression() {
    if (IsNextToken(TokenType::Identifier)) {
        auto var_name = Front();
        if (IsNextToken(SymbolType::Equals)) {
            //parse assignment
            PopFront();

            if (_symbolMap.FindVariable(var_name->GetRaw()) == -1) {
                throw ParsingException("Variable Assignment before Declaration: " + var_name->GetRaw());
            }

            auto temp = new AssignmentNode(var_name->GetRaw(), ParseExpression());
            delete var_name;
            return (ExpressionNode *)temp;
        } else {
            PutbackFront(var_name);
        }
    }
    return ParseConditionalExpression();
}

ExpressionNode *Parser::ParseConditionalExpression() {
    ExpressionNode * conditional_expr = ParseLogicalOrExpression();

    if (IsNextToken(SymbolType::Question_Mark)) {
        PopFront();
        auto expr = ParseExpression();
        TryParse(SymbolType::Colon);
        auto expr2 = ParseConditionalExpression();
        conditional_expr = new ConditionalExpressionNode(conditional_expr, expr, expr2);
    }

    return conditional_expr;
}

ExpressionNode *Parser::ParseLogicalOrExpression() {
    ExpressionNode * logical_or_expr = ParseLogicalAndExpression();

    while (IsNextToken(SymbolType::Vertical_Line)) {
        auto tempToken = Front();
        SymbolType op = GetSymbolType(tempToken);
        SymbolType op2 = SymbolType::None;
        if (IsNextToken(SymbolType::Vertical_Line)) {
            PopFront();
            op2 = SymbolType::Vertical_Line;
        }
        auto next_expr = ParseLogicalAndExpression();
        logical_or_expr = new BinaryOperatorNode(op, op2, logical_or_expr, next_expr);
        delete tempToken;
    }

    return logical_or_expr;
}

ExpressionNode *Parser::ParseLogicalAndExpression() {
    ExpressionNode * logical_and_expr = ParseEqualityExpression();

    while (IsNextToken(SymbolType::And)) {
        auto tempToken = Front();
        SymbolType op = GetSymbolType(tempToken);
        SymbolType op2 = SymbolType::None;
        if (IsNextToken(SymbolType::And)) {
            PopFront();
            op2 = SymbolType::And;
        }
        auto next_expr = ParseEqualityExpression();
        logical_and_expr = new BinaryOperatorNode(op, op2, logical_and_expr, next_expr);
        delete tempToken;
    }

    return logical_and_expr;
}

ExpressionNode *Parser::ParseEqualityExpression() {
    ExpressionNode * equality_expr = ParseRelationalExpression();

    while (IsNextToken(SymbolType::Equals) || IsNextToken(SymbolType::Exclaimation)) {
        auto tempToken = Front();
        SymbolType op = GetSymbolType(tempToken);
        SymbolType op2 = SymbolType::None;
        if (IsNextToken(SymbolType::Equals)) {
            PopFront();
            op2 = SymbolType::Equals;
        }
        if (op2 == SymbolType::None) throw ParsingException("Invalid Left Side Operator");

        auto next_expr = ParseRelationalExpression();
        equality_expr = new BinaryOperatorNode(op, op2, equality_expr, next_expr);
        delete tempToken;
    }

    return equality_expr;
}

ExpressionNode *Parser::ParseRelationalExpression() {
    ExpressionNode * relational_expr = ParseAdditiveExpression();

    while (IsNextToken(SymbolType::Open_Chevron) || IsNextToken(SymbolType::Close_Chevron)) {
        auto tempToken = Front();
        SymbolType op = GetSymbolType(tempToken);
        SymbolType op2 = SymbolType::None;
        if (IsNextToken(SymbolType::Equals)) {
            PopFront();
            op2 = SymbolType::Equals;
        }
        auto next_expr = ParseAdditiveExpression();
        relational_expr = new BinaryOperatorNode(op, op2, relational_expr, next_expr);
        delete tempToken;
    }

    return relational_expr;
}

ExpressionNode *Parser::ParseAdditiveExpression() {
    ExpressionNode * term = ParseTerm();

    while (IsNextToken(SymbolType::Plus) || IsNextToken(SymbolType::Minus)) {
        auto tempToken = Front();
        SymbolType op = GetSymbolType(tempToken);
        auto next_term = ParseTerm();
        term = new BinaryOperatorNode(op, SymbolType::None, term, next_term);
        delete tempToken;
    }

    return term;
}

TermNode *Parser::ParseTerm() {
    TermNode * factor = ParseFactor();

    while (IsNextToken(SymbolType::Asterisk) || IsNextToken(SymbolType::ForwardSlash)) {
        auto tempToken = Front();
        SymbolType op = GetSymbolType(tempToken);
        auto next_factor = ParseFactor();
        factor = (TermNode *)(new BinaryOperatorNode(op, SymbolType::None, factor, next_factor));
        delete tempToken;
    }

    return factor;
}

FactorNode *Parser::ParseFactor() {
    if (IsNextToken(SymbolType::Open_Parenthesis)) {
        PopFront();
        auto exp = (FactorNode *)ParseExpression();
        TryParse(SymbolType::Close_Parenthesis);
        return exp;
    } else if (IsUnaryOperation(PeekFront())) {
        auto next = Front();
        SymbolType stype = GetSymbolType(next);
        FactorNode * factor = ParseFactor();
        auto temp = new UnaryOperatorNode(stype, (ExpressionNode *)factor);
        delete next;
        return (FactorNode *)temp;
    } else if (IsNextToken(TokenType::Literal)) {
        auto tempToken = (Literal*)Front();
        auto temp = new ConstantNode(tempToken);
        delete tempToken;
        return (FactorNode *)temp;
    } else if (IsNextToken(TokenType::Identifier)) {
        auto tempToken = Front();
        if (_symbolMap.FindVariable(tempToken->GetRaw()) == -1)
            throw ParsingException("Variable used before Declaration: " + tempToken->GetRaw());
        auto temp = new VariableNode(tempToken->GetRaw());
        delete tempToken;
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
    if (!t) return false;
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

bool Parser::IsNextToken(TokenType type) const {
    return _curList->PeekType() == type;
}

bool Parser::IsNextToken(SymbolType stype) const {
    return IsTokenType(stype, _curList->PeekFront());
}

bool Parser::IsNextToken(KeywordType ktype) const {
    return IsTokenType(ktype, _curList->PeekFront());
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
    delete _curList->PopFront();
}

Token *Parser::PeekFront() {
    return _curList->PeekFront();
}

//fail should output a bit more information now
void Parser::Fail(bool hasMain) {
    std::stringstream err;
    if (_verified) _verified = false;
    if (!hasMain) {
        cerr << "FAIL0!: No \'main\' function found\n";
    } else {
        err << "FAIL1!: Unexpected Token, Expected: ";
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
                    case KeywordType::If:
                        err << "if";
                        break;
                    case KeywordType::Else:
                        err << "else";
                        break;
                    case KeywordType::None:
                    default:
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
        throw ParsingException(err.str());
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
    return _curList->PopFront();
}

bool Parser::IsUnaryOperation(Token * t) {
    return (IsTokenType(SymbolType::Tilde, t) || IsTokenType(SymbolType::Minus, t) || IsTokenType(SymbolType::Exclaimation, t));
}

void Parser::PutbackFront(Token *t) {
    _curList->PutbackFront(t);
}

const SymbolMap & Parser::Map() const {
    return _symbolMap;
}

void Parser::TryParse(TokenType type) {
    IsNextToken(type) ? PopFront() : Fail(type);
}

void Parser::TryParse(SymbolType stype) {
    IsNextToken(stype) ? PopFront() : Fail(stype);
}

void Parser::TryParse(KeywordType ktype) {
    IsNextToken(ktype) ? PopFront() : Fail(ktype);
}

Parser::~Parser() {
    delete _curList;
}
