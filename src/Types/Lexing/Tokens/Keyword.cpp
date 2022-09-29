#include "Keyword.hpp"
using std::string;

/// Reflect the token type for output
/// \return string of token type
string Keyword::TypeString() const {
    return "Keyword";
}

/// Gets the keyword type
/// \return type of keyword
KeywordType Keyword::KeyType() const {
    return _keyType;
}

/// String Constructor
/// \param toInit string to read
Keyword::Keyword(const string &toInit) : Token(toInit) {
    _keyType = GetKeyType(toInit);
}

/// Get the keyword type from a string
/// \param rawString string to test
/// \return keyword type from string
KeywordType Keyword::GetKeyType(const string & rawString) {
    if (rawString == "return") {
        return KeywordType::Return;
    } else if (rawString == "int") {
        return KeywordType::Int;
    } else if (rawString == "if") {
        return KeywordType::If;
    } else if (rawString == "else") {
        return KeywordType::Else;
    } else if (rawString == "for") {
        return KeywordType::For;
    } else if (rawString == "while") {
        return KeywordType::While;
    } else if (rawString == "do") {
        return KeywordType::Do;
    } else if (rawString == "break") {
        return KeywordType::Break;
    } else if (rawString == "continue") {
        return KeywordType::Continue;
    }
    return KeywordType::None;
}

/// Virtual copy constructor
/// \return new smart pointer copy of this token
Token *Keyword::Clone() {
    return new Keyword(*this);
}

/// Copy Constructor
/// \param toCopy keyword token to copy
Keyword::Keyword(const Keyword &toCopy) : Token(toCopy) {
    _keyType = toCopy._keyType;
}
