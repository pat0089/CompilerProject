#include "FunctionCallNode.hpp"

FunctionCallNode::FunctionCallNode(const std::string &toInit) : ExpressionNode(SyntaxType::Function_Call), IFunction(toInit) {}

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

