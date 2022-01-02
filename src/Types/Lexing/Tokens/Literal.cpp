#include "Literal.hpp"
using std::string;

string Literal::TypeString() const {
    return "Literal";
}

Literal::Literal(const string &toInit) : Token(toInit) { }
