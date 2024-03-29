#include "Token.hpp"
#include "Literal.hpp"
#include "Keyword.hpp"
#include "Identifier.hpp"
#include "Symbol.hpp"
#include <regex>
using std::string;
using std::ostream;
using std::istream;

Token::Token() : _readCharacters(nullptr), _tokenType(TokenType::None) { }
Token::~Token() { delete _readCharacters; }

/// String Constructor, initializes type of token
/// \param chars string to read
Token::Token(const string & chars, int curChar, int curLine) {
    _char = curChar;
    _line = curLine;
    _readCharacters = new string(chars);
    _tokenType = GetType(chars);
}

/// Get the string of characters read for this token
/// \return the string of characters lexed for this token
string & Token::GetRaw() const {
    return *_readCharacters;
}

/// Stream output operator
/// \param os output stream
/// \param token token to output
/// \return reference to output stream
ostream &operator<<(ostream &os, const Token &token) {
    if (!token._readCharacters->empty()) {
        os << token.TypeString()[0] << ":" << token.GetRaw() << " L:" << token.GetLine() << " C:" << token.GetChar();
    }
    return os;
}

bool Token::operator==(const Token &token) const {
    return (GetRaw() == token.GetRaw());
}

///Copy Constructor
Token::Token(const Token &toCopy) : _readCharacters(new string(*toCopy._readCharacters)), _tokenType(toCopy._tokenType), _char(toCopy._char), _line(toCopy._line) {}

/// Creates a new token with its type from a string
/// \param rawString string to create from
/// \return smart pointer to typed token
Token * Token::Create(const string & rawString, int curChar, int curLine) {
    switch (GetType(rawString)) {
        case TokenType::Keyword:
            return (Token *)(new Keyword(rawString, curChar, curLine));
        case TokenType::Identifier:
            return (Token *)(new Identifier(rawString, curChar, curLine));
        case TokenType::Literal:
            return (Token *)(new Literal(rawString, curChar, curLine));
        case TokenType::Symbol:
            return (Token *)(new Symbol(rawString, curChar, curLine));
        case TokenType::None:
        default:
            return nullptr;
    }
}

/// Gets the token type from a provided string
/// \param rawString string to test
/// \return token type of the string
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

/// Get the type of the token
/// \return type of the token
TokenType Token::Type() const {
    return _tokenType;
}

int Token::GetChar() const {
    return _char;
}

int Token::GetLine() const {
    return _line;
}


