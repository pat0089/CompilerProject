#include "Keyword.hpp"
using std::string;

string Keyword::TypeString() const {
    return "Keyword";
}

KeywordType Keyword::KeyType() const {
    return _keyType;
}

Keyword::Keyword(const string &toInit) : Token(toInit) {
    _keyType = GetKeyType(toInit);
}

KeywordType Keyword::GetKeyType(const string & rawString) {
    if (rawString == "return") {
        return KeywordType::Return;
    } else if (rawString == "int") {
        return KeywordType::Int;
    } else if (rawString == "if") {
        return KeywordType::If;
    } else if (rawString == "else") {
        return KeywordType::Else;
    }
    return KeywordType::None;
}

Token *Keyword::Clone() {
    return new Keyword(*this);
}

Keyword::Keyword(const Keyword &toCopy) : Token(toCopy) {
    _keyType = toCopy._keyType;
}

Keyword::~Keyword() {}
