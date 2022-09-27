#include "ParameterNode.hpp"
using std::string;

string ParameterNode::PrettyPrint() {
    return "Parameter: " + GetVariableName();
}

ParameterNode::ParameterNode(const string &pname) : SyntaxNode(SyntaxType::Parameter), IVariable(pname) {}
