#include "Parser.hpp"
#include "../Types/Lexing/Tokens.hpp"
#include "../Types/Parsing/Syntax/Expressions/FunctionCallNode.hpp"
#include <sstream>
using std::cerr;
using std::endl;

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

    auto temp = new ProgramNode();

    while (IsNextToken(KeywordType::Int)) {
        temp->Add(ParseFunction());
    }

    return temp;
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

    //can only currently have int return types
    TryParse(KeywordType::Int);

    Identifier * name = nullptr;
    if (!IsNextToken(TokenType::Identifier)) {
        Fail(TokenType::Identifier);
    } else {
        name = (Identifier *)Front();
    }

    auto funcName = name->GetRaw();

    //TODO: move check for main function to elsewhere
    if (funcName == "main") _symbolMap.containsMain = true;
    auto newFunction = new FunctionNode(name->GetRaw());

    //DONT FORGET TO DELETE THE TOKENS YOU Front() OFF THE QUEUE:
    delete name;

    auto params = ParseParameters();

    //parse args
    newFunction->Add(params);

    if (!IsNextToken(SymbolType::Semicolon)) {
        auto body = ParseBody();

        //parse body
        newFunction->Add(body);
    } else {
        TryParse(SymbolType::Semicolon);
    }
    return newFunction;
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

Parameters * Parser::ParseParameters() {
    TryParse(SymbolType::Open_Parenthesis);
    auto newArgs = new Parameters();
    while (!IsNextToken(SymbolType::Close_Parenthesis)) {
        newArgs->Add(ParseParameter());
        if (IsNextToken(SymbolType::Comma)) PopFront();
    }
    TryParse(SymbolType::Close_Parenthesis);
    return newArgs;
}

ParameterNode * Parser::ParseParameter() {

    //can only currently have int type parameters
    TryParse(KeywordType::Int);

    Identifier * name = nullptr;

    if (!IsNextToken(TokenType::Identifier)) {
        Fail(TokenType::Identifier);
    } else {
        name = (Identifier *)Front();
    }
    auto pname = name->GetRaw();
    delete name;

    return new ParameterNode(pname);
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
        toReturn = new ReturnNode(ParseExpression());
    } else if (!IsNextToken(TokenType::Keyword) && !IsNextToken(SymbolType::Open_Brace)) {
        auto temp = ParseOptionalExpression();
        toReturn = (StatementNode * )temp;
    } else if (IsNextToken(KeywordType::If)) {
        //conditional statement
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
    } else if (IsNextToken(SymbolType::Open_Brace)) {
        //braced scope
        toReturn = (StatementNode *)ParseBody();
    } else {
        //check for loop keywords
        auto temp = (Keyword *)Front();
        if (temp->Type() != TokenType::Keyword) Fail(TokenType::Keyword);

        //for loop
        if (temp->KeyType() == KeywordType::For) {
            TryParse(SymbolType::Open_Parenthesis);
            StatementNode *first = nullptr;
            if (IsNextToken(KeywordType::Int)) {
                first = ParseDeclaration();
            } else {
                first = ParseOptionalExpression();
            }
            if (first->Type() != SyntaxType::Declaration) TryParse(SymbolType::Semicolon);
            auto second = ParseOptionalExpression();
            TryParse(SymbolType::Semicolon);
            auto third = ParseOptionalExpression();
            TryParse(SymbolType::Close_Parenthesis);
            auto for_statement = ParseStatement();
            toReturn = new ForLoopNode(first, second, third, for_statement);
        } else if (temp->KeyType() == KeywordType::While) {
            TryParse(SymbolType::Open_Parenthesis);
            auto exp = ParseExpression();
            TryParse(SymbolType::Close_Parenthesis);
            auto while_statement = ParseStatement();
            toReturn = new WhileLoopNode(exp, while_statement);
        } else if (temp->KeyType() == KeywordType::Do) {
            auto do_statement = ParseStatement();
            TryParse(KeywordType::While);
            TryParse(SymbolType::Open_Parenthesis);
            auto exp = ParseExpression();
            TryParse(SymbolType::Close_Parenthesis);
            toReturn = new DoWhileLoopNode(do_statement, exp);
        } else if (temp->KeyType() == KeywordType::Break) {
            toReturn = new BreakNode();
        } else if (temp->KeyType() == KeywordType::Continue) {
            toReturn = new ContinueNode();
        } else {
            throw ParsingException("Failed to parse Statement");
        }
        delete temp;
    }
    //DONT FORGET THE SEMICOLON
    if (toReturn->Type() != SyntaxType::Conditional_Statement && toReturn->Type() != SyntaxType::Body && toReturn->Type() != SyntaxType::While_Loop && toReturn->Type() != SyntaxType::For_Loop)
        TryParse(SymbolType::Semicolon);
    return toReturn;
}

ExpressionNode *Parser::ParseOptionalExpression() {
    if (!IsNextToken(SymbolType::Semicolon) || !IsNextToken(SymbolType::Close_Parenthesis)) {
        auto temp = ParseExpression();
        if (temp) return temp;
    }
    return new ConstantNode(1);
}

ExpressionNode * Parser::ParseExpression() {
    if (IsNextToken(TokenType::Identifier)) {
        auto var_name = Front();
        if (IsNextToken(SymbolType::Equals)) {
            //parse assignment
            auto tempToken = Front();
            if (!IsNextToken(SymbolType::Equals)) {
                auto temp = new AssignmentNode(var_name->GetRaw(), ParseExpression());
                delete var_name;
                return (ExpressionNode *) temp;
            } else {
                PutbackFront(tempToken);
                PutbackFront(var_name);
            }
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
    ExpressionNode * logical_and_expr = ParseBitwiseOrExpression();

    while (IsNextToken(SymbolType::And)) {
        auto tempToken = Front();
        SymbolType op = GetSymbolType(tempToken);
        SymbolType op2 = SymbolType::None;
        if (IsNextToken(SymbolType::And)) {
            PopFront();
            op2 = SymbolType::And;
        }
        auto next_expr = ParseBitwiseOrExpression();
        logical_and_expr = new BinaryOperatorNode(op, op2, logical_and_expr, next_expr);
        delete tempToken;
    }

    return logical_and_expr;
}

ExpressionNode *Parser::ParseBitwiseOrExpression() {
    ExpressionNode * bitwise_or_expr = ParseBitwiseXorExpression();
    while (IsNextToken(SymbolType::Vertical_Line)) {
        auto temp = Front();
        if (!IsNextToken(SymbolType::Vertical_Line)) {
            auto next_expr = ParseBitwiseXorExpression();
            bitwise_or_expr = new BinaryOperatorNode(SymbolType::Vertical_Line, SymbolType::None, bitwise_or_expr, next_expr);
            delete temp;
        } else {
            PutbackFront(temp);
            break;
        }
    }
    return bitwise_or_expr;
}

ExpressionNode *Parser::ParseBitwiseXorExpression() {
    ExpressionNode * bitwise_xor_expr = ParseBitwiseAndExpression();
    while (IsNextToken(SymbolType::Carrot)) {
        TryParse(SymbolType::Carrot);
        auto next_expr = ParseBitwiseAndExpression();
        bitwise_xor_expr = new BinaryOperatorNode(SymbolType::Carrot, SymbolType::None, bitwise_xor_expr, next_expr);
    }
    return bitwise_xor_expr;
}

ExpressionNode *Parser::ParseBitwiseAndExpression() {
    ExpressionNode * bitwise_and_expr = ParseEqualityExpression();
    while (IsNextToken(SymbolType::And)) {
        auto temp = Front();
        if (!IsNextToken(SymbolType::And)) {
            auto next_expr = ParseEqualityExpression();
            bitwise_and_expr = new BinaryOperatorNode(SymbolType::And, SymbolType::None, bitwise_and_expr, next_expr);
            delete temp;
        } else {
            PutbackFront(temp);
            break;
        }
    }
    return bitwise_and_expr;
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
    ExpressionNode * relational_expr = ParseBitwiseShiftExpression();

    while (IsNextToken(SymbolType::Open_Chevron) || IsNextToken(SymbolType::Close_Chevron)) {
        auto tempToken = Front();
        SymbolType op = GetSymbolType(tempToken);
        SymbolType op2 = SymbolType::None;
        if (IsNextToken(SymbolType::Equals)) {
            PopFront();
            op2 = SymbolType::Equals;
        }
        auto next_expr = ParseBitwiseShiftExpression();
        relational_expr = new BinaryOperatorNode(op, op2, relational_expr, next_expr);
        delete tempToken;
    }

    return relational_expr;
}

ExpressionNode *Parser::ParseBitwiseShiftExpression() {
    ExpressionNode * shift_expr = ParseAdditiveExpression();

    while (IsNextToken(SymbolType::Open_Chevron) || IsNextToken(SymbolType::Close_Chevron)) {
        auto tempToken = Front();
        SymbolType op = GetSymbolType(tempToken);
        if (IsNextToken(SymbolType::Open_Chevron) && op == SymbolType::Open_Chevron ||
            IsNextToken(SymbolType::Close_Chevron) && op == SymbolType::Close_Chevron)
        {
            PopFront();
            auto next_expr = ParseAdditiveExpression();
            shift_expr = new BinaryOperatorNode(op, op, shift_expr, next_expr);
            delete tempToken;
        } else {
            PutbackFront(tempToken);
            break;
        }

    }
    return shift_expr;
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

    while (IsNextToken(SymbolType::Asterisk) || IsNextToken(SymbolType::ForwardSlash) || IsNextToken(SymbolType::Percent)) {
        auto tempToken = Front();
        SymbolType op = GetSymbolType(tempToken);
        auto next_factor = ParseFactor();
        factor = (TermNode *)(new BinaryOperatorNode(op, SymbolType::None, factor, next_factor));
        delete tempToken;
    }

    return factor;
}

FactorNode *Parser::ParseFactor() {
    auto function_call = ParseFunctionCall();
    if (!function_call) {
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
            auto temp = new VariableNode(tempToken->GetRaw());
            delete tempToken;
            return (FactorNode *)temp;
        } else {
            return nullptr;
        }
    } else {
        return (FactorNode *)function_call;
    }
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
    if (_curList->Empty()) return false;
    return _curList->PeekType() == type;
}

bool Parser::IsNextToken(SymbolType stype) const {
    if (_curList->Empty()) return false;
    return IsTokenType(stype, _curList->PeekFront());
}

bool Parser::IsNextToken(KeywordType ktype) const {
    if (_curList->Empty()) return false;
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
void Parser::Fail(bool hasMain, TokenType ttype, SymbolType stype, KeywordType ktype) {
    std::stringstream err;
    if (_verified) _verified = false;
    if (!hasMain) {
        err << "FAIL0!: No \'main\' function found\n";
    } else {
        err << "FAIL1!: Unexpected Token, Expected: ";
        switch (ttype) {
            case TokenType::Symbol:
                err << "Symbol \'";
                switch (stype) {
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
                switch (ktype) {
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
    }
    throw ParsingException(err.str());
}

void Parser::Fail(TokenType type)  {
    Fail(true, type, SymbolType::None, KeywordType::None);
}

void Parser::Fail(SymbolType stype) {
    Fail(true, TokenType::Symbol, stype, KeywordType::None);
}

void Parser::Fail(KeywordType ktype) {
    Fail(true, TokenType::Keyword, SymbolType::None, ktype);
}

bool Parser::Verify() {
    if (!_symbolMap.containsMain) Fail(false);
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

ExpressionNode *Parser::ParseFunctionCall() {
    if (IsNextToken(TokenType::Identifier)) {
        auto funcNameNode = Front();
        auto temp = new FunctionCallNode(funcNameNode->GetRaw());
        if (IsNextToken(SymbolType::Open_Parenthesis)) {
            PopFront();
            auto params = new Parameters();
            if (!IsNextToken(SymbolType::Close_Parenthesis)) {
                auto exp = ParseExpression();
                params->Add(exp);
                while (IsNextToken(SymbolType::Comma)) {
                    PopFront();
                    exp = ParseExpression();
                    params->Add(exp);
                }
            }
            temp->Add(params);
        } else {
            PutbackFront(funcNameNode);
            delete temp;
            return nullptr;
        }
        TryParse(SymbolType::Close_Parenthesis);
        delete funcNameNode;
        return temp;
    }
    return nullptr;
}
