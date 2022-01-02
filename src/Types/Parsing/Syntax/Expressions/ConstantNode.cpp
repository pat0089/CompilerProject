#include "ConstantNode.hpp"
using std::string;

ConstantNode::ConstantNode(int toInit) {
    _val = new int(toInit);
}

int & ConstantNode::Value() const {
    return *_val;
}

ConstantNode::ConstantNode() : _val(nullptr) { }

void ConstantNode::Value(int i) {
    *_val = i;
}

string ConstantNode::PrettyPrint() {
    return string("Constant: ") + string(std::to_string(Value()));
}
