#include "BinaryOperatorNode.hpp"

BinaryOperatorNode::BinaryOperatorNode() : ExpressionNode(SyntaxType::BinaryOperator) {}

std::string BinaryOperatorNode::PrettyPrint() {
    return "Binary Operator: " + Symbol::GetString(GetOperatorType());
};

BinaryOperatorNode::BinaryOperatorNode(SymbolType stype, ExpressionNode * t1, ExpressionNode * t2) : ExpressionNode(SyntaxType::BinaryOperator), _stype(stype) {
    Add(t1);
    Add(t2);
}

SymbolType BinaryOperatorNode::GetOperatorType() const {
    return _stype;
};
