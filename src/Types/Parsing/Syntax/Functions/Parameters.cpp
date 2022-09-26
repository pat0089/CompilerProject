#include "Parameters.hpp"
using std::string;

Parameters::Parameters() : SyntaxNode(SyntaxType::Parameters) {}

string Parameters::PrettyPrint() {
    return "Parameters:";
}
