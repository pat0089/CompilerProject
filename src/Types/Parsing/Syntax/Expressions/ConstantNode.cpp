#include "ConstantNode.hpp"
using std::string;

ConstantNode::ConstantNode(int toInit): ExpressionNode(SyntaxType::Constant), _val(new int(toInit)) {}
ConstantNode::ConstantNode() : ExpressionNode(SyntaxType::Constant), _val(nullptr) {}
ConstantNode::~ConstantNode() { delete _val; }
ConstantNode::ConstantNode(Literal * lit) : ExpressionNode(SyntaxType::Constant), _val(new int(std::stoi(lit->GetRaw()))) {}

int & ConstantNode::Value() const {
    return *_val;
}

void ConstantNode::Value(int i) {
    *_val = i;
}

string ConstantNode::PrettyPrint() {
    return string("Constant: ") + string(std::to_string(Value()));
}
