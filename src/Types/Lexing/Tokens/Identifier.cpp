#include "Identifier.hpp"
using std::string;

string Identifier::TypeString() const {
    return "Identifier";
}

Identifier::Identifier(const string &toInit) : Token(toInit) {
    _tokenType = GetType(toInit);
}
