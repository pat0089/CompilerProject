#include "ParameterNode.hpp"
using std::string;

ParameterNode::ParameterNode() : SyntaxNode(SyntaxType::Parameter) {}

string ParameterNode::PrettyPrint() {
    return "Parameter";
}