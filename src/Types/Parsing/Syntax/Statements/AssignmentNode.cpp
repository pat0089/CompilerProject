#include "AssignmentNode.hpp"

AssignmentNode::AssignmentNode() : StatementNode(SyntaxType::Assignment), IVariable("") {}

AssignmentNode::AssignmentNode(const std::string &name, ExpressionNode *exp) : StatementNode(SyntaxType::Assignment), IVariable(name) {
    Add(exp);
}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string AssignmentNode::PrettyPrint() {
    return "Assignment: " + GetVariableName();
}
