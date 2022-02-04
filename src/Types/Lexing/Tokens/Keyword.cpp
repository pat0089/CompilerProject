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
    } else {
        return KeywordType::Int;
    }
}
