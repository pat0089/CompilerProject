#include "Identifier.hpp"
using std::string;

string Identifier::TypeString() const {
    return "Identifier";
}

Identifier::Identifier(const string &toInit) : Token(toInit) {}

Token *Identifier::Clone() {
    return new Identifier(*this);
}

Identifier::Identifier(const Identifier & toCopy) : Token(toCopy) {}
