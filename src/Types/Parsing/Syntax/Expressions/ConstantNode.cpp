#include "ConstantNode.hpp"
using std::string;

ConstantNode::ConstantNode(int toInit): ExpressionNode(SyntaxType::Constant), _val(new int(toInit)) {}
ConstantNode::ConstantNode() : ExpressionNode(SyntaxType::Constant), _val(nullptr) {}
ConstantNode::~ConstantNode() { delete _val; }
ConstantNode::ConstantNode(Literal * lit) : ExpressionNode(SyntaxType::Constant), _val(new int(std::stoi(lit->GetRaw()))) {}

int & ConstantNode::Value() const {
    return *_val;
}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
string ConstantNode::PrettyPrint() {
    return "Constant: " + std::to_string(Value());
}
