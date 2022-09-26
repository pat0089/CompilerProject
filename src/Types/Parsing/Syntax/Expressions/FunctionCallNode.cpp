#include "FunctionCallNode.hpp"

FunctionCallNode::FunctionCallNode(const std::string &toInit) : ExpressionNode(SyntaxType::Function_Call), _name(new std::string(toInit)) {}

std::string FunctionCallNode::PrettyPrint() {
    return "Function call: " + *_name;
}

FunctionCallNode::~FunctionCallNode() {
    delete _name;
}

std::string &FunctionCallNode::Name() const {
    return *_name;
}

FunctionCallNode::FunctionCallNode() : ExpressionNode(SyntaxType::Function_Call), _name(new std::string()) {}

