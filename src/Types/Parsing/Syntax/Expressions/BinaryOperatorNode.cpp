#include "BinaryOperatorNode.hpp"

BinaryOperatorNode::BinaryOperatorNode() : ExpressionNode(SyntaxType::Binary_Operator), IOperator() {}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string BinaryOperatorNode::PrettyPrint() {
    return "Binary Operator: " + Symbol::GetString(GetOperatorType()) + Symbol::GetString(GetOperatorType2());
}

BinaryOperatorNode::BinaryOperatorNode(SymbolType stype, SymbolType stype2, ExpressionNode * t1, ExpressionNode * t2) : ExpressionNode(SyntaxType::Binary_Operator), IOperator(),  _stype(stype), _stype2(stype2) {
    Add(t1);
    Add(t2);
    _otype = ConvertOperator(stype, stype2, SyntaxType::Binary_Operator);
}

SymbolType BinaryOperatorNode::GetOperatorType() const {
    return _stype;
}

SymbolType BinaryOperatorNode::GetOperatorType2() const {
    return _stype2;
}
