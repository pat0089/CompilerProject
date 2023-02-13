#include "Symbol.hpp"
using std::string;

/// Reflect the token type for output
/// \return string of token type
string Symbol::TypeString() const {
    return "Symbol";
}

/// String Constructor
/// \param toInit string to read
Symbol::Symbol(const std::string & toInit, int curChar, int curLine) : Token(toInit, curChar, curLine) {
    _symType = GetSymType(toInit);
}

/// Get the symbol type from a string
/// \param rawString string to test
/// \return symbol type from string
SymbolType Symbol::GetSymType(const string & rawString) {
    switch (rawString.c_str()[0]) {
        case ';':
            return SymbolType::Semicolon;
        case '(':
            return SymbolType::Open_Parenthesis;
        case ')':
            return SymbolType::Close_Parenthesis;
        case '{':
            return SymbolType::Open_Brace;
        case '}':
            return SymbolType::Close_Brace;
        case '&':
            return SymbolType::And;
        case '!':
            return SymbolType::Exclaimation;
        case '~':
            return SymbolType::Tilde;
        case '=':
            return SymbolType::Equals;
        case '<':
            return SymbolType::Open_Chevron;
        case '>':
            return SymbolType::Close_Chevron;
        case '[':
            return SymbolType::Open_Bracket;
        case ']':
            return SymbolType::Close_Bracket;
        case ':':
            return SymbolType::Colon;
        case '*':
            return SymbolType::Asterisk;
        case '/':
            return SymbolType::ForwardSlash;
        case '\\':
            return SymbolType::BackSlash;
        case '.':
            return SymbolType::Period;
        case ',':
            return SymbolType::Comma;
        case '+':
            return SymbolType::Plus;
        case '-':
            return SymbolType::Minus;
        case '#':
            return SymbolType::Hashmark;
        case '|':
            return SymbolType::Vertical_Line;
        case '?':
            return SymbolType::Question_Mark;
        case '^':
            return SymbolType::Carrot;
        case '%':
            return SymbolType::Percent;
    }
    return SymbolType::None;
}

/// Gets the symbol type
/// \return type of symbol
SymbolType Symbol::SymType() const {
    return _symType;
}

/// Reflect the symbol type into a string
/// \param stype symbol type
/// \return converted symbol type to string
std::string Symbol::GetString(SymbolType stype) {
    switch (stype) {
        case SymbolType::Semicolon:
            return ";";
        case SymbolType::Colon:
            return ":";
        case SymbolType::Open_Parenthesis:
            return "(";
        case SymbolType::Close_Parenthesis:
            return ")";
        case SymbolType::Open_Brace:
            return "[";
        case SymbolType::Close_Brace:
            return "]";
        case SymbolType::Open_Bracket:
            return "}";
        case SymbolType::Close_Bracket:
            return "{";
        case SymbolType::Open_Chevron:
            return "<";
        case SymbolType::Close_Chevron:
            return ">";
        case SymbolType::Period:
            return ".";
        case SymbolType::Comma:
            return ",";
        case SymbolType::Equals:
            return "=";
        case SymbolType::Plus:
            return "+";
        case SymbolType::Minus:
            return "-";
        case SymbolType::ForwardSlash:
            return "/";
        case SymbolType::Asterisk:
            return "*";
        case SymbolType::BackSlash:
            return "\\";
        case SymbolType::And:
            return "&";
        case SymbolType::Hashmark:
            return "#";
        case SymbolType::Exclaimation:
            return "!";
        case SymbolType::Tilde:
            return "~";
        case SymbolType::Vertical_Line:
            return "|";
        case SymbolType::Question_Mark:
            return "?";
        case SymbolType::Carrot:
            return "^";
        case SymbolType::Percent:
            return "%";
        case SymbolType::None:
        default:
            return "";
    }
}

/// Virtual copy constructor
/// \return new smart pointer copy of this token
Token *Symbol::Clone() {
    return new Symbol(*this);
}

/// Copy Constructor
/// \param toCopy symbol to copy
Symbol::Symbol(const Symbol &toCopy) : Token(toCopy) {
    _symType = toCopy._symType;
}
