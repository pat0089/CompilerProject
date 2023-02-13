#include "Literal.hpp"
using std::string;

/// Reflect the token type for output
/// \return string of token type
string Literal::TypeString() const {
    return "Literal";
}

/// String Constructor
/// \param toInit string to read
Literal::Literal(const std::string & toInit, int curChar, int curLine) : Token(toInit, curChar, curLine) { }

/// Virtual copy constructor
/// \return new smart pointer copy of this token
Token *Literal::Clone() {
    return new Literal(*this);
}