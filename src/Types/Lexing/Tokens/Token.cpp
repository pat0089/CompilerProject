#include "Token.hpp"
#include "Literal.hpp"
#include "Keyword.hpp"
#include "Identifier.hpp"
#include "Symbol.hpp"
#include <regex>
using std::string;
using std::ostream;
using std::istream;

Token::Token() : _readCharacters(nullptr), _lastToken(nullptr), _nextToken(nullptr), _tokenType(TokenType::None) { }

Token::Token(const string & chars) : _lastToken(nullptr), _nextToken(nullptr) {
    _readCharacters = new string(chars);
    _tokenType = GetType(chars);
}

string & Token::GetRaw() const {
    return *_readCharacters;
}

ostream &operator<<(ostream &os, const Token &token) {
    if (!token._readCharacters->empty()) {
        os << "Token: " << token.GetRaw() << "\n";
        os << "Type: " << token.TypeString() << "\n";
    }
    return os;
}

void Token::SetRaw(const string & toSet) {
    *_readCharacters = toSet;
}

bool Token::operator==(const Token &token) const {
    return (GetRaw() == token.GetRaw());
}

Token::Token(const Token &toCopy) {
    _readCharacters = new string(toCopy.GetRaw());
}

Token * Token::Create(const string & rawString) {
    switch (GetType(rawString)) {
        case TokenType::Keyword:
            return (Token *)(new Keyword(rawString));
        case TokenType::Identifier:
            return (Token *)(new Identifier(rawString));
        case TokenType::Literal:
            return (Token *)(new Literal(rawString));
        case TokenType::Symbol:
            return (Token *)(new Symbol(rawString));
        case TokenType::None:
        default:
            return nullptr;
    }
}

Token::~Token() {
    delete _readCharacters;
}

Token *Token::Next() const {
    return _nextToken;
}

Token *Token::Last() const {
    return _lastToken;
}

TokenType Token::GetType(const string &rawString) {
    if (std::regex_match(rawString, Lexer::isKeyword)) {
        return TokenType::Keyword;
    } else if (std::regex_match(rawString, Lexer::isIdentifier)) {
        return TokenType::Identifier;
    } else if (std::regex_match(rawString, Lexer::isLiteral)) {
        return TokenType::Literal;
    } else if (std::regex_match(rawString, Lexer::isSymbol)) {
        return TokenType::Symbol;
    } else {
        return TokenType::None;
    }
}

TokenType Token::Type() const {
    return _tokenType;
}

void Token::Next(Token *next) {
    _nextToken = next;
}

void Token::Last(Token *last) {
    _lastToken = last;
}


