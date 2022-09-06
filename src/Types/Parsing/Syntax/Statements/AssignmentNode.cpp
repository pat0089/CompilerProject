#include "AssignmentNode.hpp"

AssignmentNode::AssignmentNode() : StatementNode(SyntaxType::Assignment), IVariable("") {}

AssignmentNode::AssignmentNode(const std::string &name, ExpressionNode *exp) : StatementNode(SyntaxType::Assignment), IVariable(name) {
    Add(exp);
}

std::string AssignmentNode::PrettyPrint() {
    return "Assignment: " + GetVariableName();
}
