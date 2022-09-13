#include "Literal.hpp"
using std::string;

string Literal::TypeString() const {
    return "Literal";
}

Literal::Literal(const string &toInit) : Token(toInit) { }

Token *Literal::Clone() {
    return new Literal(*this);
}

Literal::Literal(const Literal &toCopy) : Token(toCopy) {}
