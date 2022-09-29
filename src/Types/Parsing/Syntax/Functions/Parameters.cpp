#include "Parameters.hpp"
using std::string;

Parameters::Parameters() : SyntaxNode(SyntaxType::Parameters) {}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
string Parameters::PrettyPrint() {
    return "Parameters:";
}
