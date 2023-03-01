#include "Identifier.hpp"
using std::string;

/// Reflect the token type for output
/// \return string of token type
string Identifier::TypeString() const {
    return "Identifier";
}

/// String constructor
/// \param toInit string
Identifier::Identifier(const std::string & toInit, int curChar, int curLine) : Token(toInit, curChar, curLine) {}

/// Virtual copy constructor
/// \return new smart pointer copy of this token
Token *Identifier::Clone() {
    return new Identifier(*this);
}
