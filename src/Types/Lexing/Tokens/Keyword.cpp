#include "Keyword.hpp"
using std::string;

string Keyword::TypeString() const {
    return "Keyword";
}

KeywordType Keyword::KeyType() const {
    return _keyType;
}

Keyword::Keyword(const string &toInit) : Token(toInit) {
    _keyType = GetKeyType();
}

KeywordType Keyword::GetKeyType() {
    return KeywordType::Return;
}
