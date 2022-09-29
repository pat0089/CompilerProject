#include "FunctionCallNode.hpp"

FunctionCallNode::FunctionCallNode(const std::string &toInit) : ExpressionNode(SyntaxType::Function_Call), IFunction(toInit) {}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string FunctionCallNode::PrettyPrint() {
    return "Function call: " + Name();
}

FunctionCallNode::FunctionCallNode() : ExpressionNode(SyntaxType::Function_Call), IFunction() {}

BodyNode *FunctionCallNode::BodyPtr() const {
    return nullptr;
}

Parameters *FunctionCallNode::ParamsPtr() const {
    return (Parameters *)_children[0];
}

