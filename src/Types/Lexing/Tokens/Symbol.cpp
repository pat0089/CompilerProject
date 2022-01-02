#include "Symbol.hpp"
using std::string;

string Symbol::TypeString() const {
    return "Symbol";
}

Symbol::Symbol(const string &toInit) : Token(toInit) {
    _symType = GetSymType(toInit);
}

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
    }
    return SymbolType::None;
}

SymbolType Symbol::SymType() const {
    return _symType;
}
