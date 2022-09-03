#include "BinaryOperatorNode.hpp"

BinaryOperatorNode::BinaryOperatorNode() : ExpressionNode(SyntaxType::BinaryOperator) {}

std::string BinaryOperatorNode::PrettyPrint() {
    return "Binary Operator: " + Symbol::GetString(GetOperatorType()) + Symbol::GetString(GetOperatorType2());
};

BinaryOperatorNode::BinaryOperatorNode(SymbolType stype, SymbolType stype2, ExpressionNode * t1, ExpressionNode * t2) : ExpressionNode(SyntaxType::BinaryOperator), _stype(stype), _stype2(stype2) {
    Add(t1);
    Add(t2);
    _otype = ConvertOperator(stype, stype2, SyntaxType::BinaryOperator);
}

SymbolType BinaryOperatorNode::GetOperatorType() const {
    return _stype;
}

SymbolType BinaryOperatorNode::GetOperatorType2() const {
    return _stype2;
}
