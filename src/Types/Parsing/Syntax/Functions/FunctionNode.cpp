#include "FunctionNode.hpp"
using std::string;

FunctionNode::FunctionNode() : SyntaxNode(SyntaxType::Function), IFunction() {}

FunctionNode::FunctionNode(const string &toInit) : SyntaxNode(SyntaxType::Function), IFunction(toInit) {}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
string FunctionNode::PrettyPrint() {
    return "Function: " + Name();
}

BodyNode *FunctionNode::BodyPtr() const {
    if (ChildCount() == 1) return nullptr;
    return (BodyNode *)_children[1];
}

Parameters *FunctionNode::ParamsPtr() const {
    return (Parameters *)_children[0];
}
