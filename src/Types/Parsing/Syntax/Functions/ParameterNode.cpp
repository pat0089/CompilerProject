#include "ParameterNode.hpp"
using std::string;

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
string ParameterNode::PrettyPrint() {
    return "Parameter: " + GetVariableName();
}

ParameterNode::ParameterNode(const string &pname) : SyntaxNode(SyntaxType::Parameter), IVariable(pname) {}
