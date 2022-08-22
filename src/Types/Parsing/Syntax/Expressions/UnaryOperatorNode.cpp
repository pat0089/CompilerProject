#include "UnaryOperatorNode.hpp"
using std::string;

UnaryOperatorNode::UnaryOperatorNode(SymbolType stype, ExpressionNode * exp) : ExpressionNode(SyntaxType::UnaryOperator), _stype(stype) {
    Add(exp);
}

string UnaryOperatorNode::PrettyPrint() {
    return string("Unary Operator: ") + Symbol::GetString(_stype);
}

SymbolType UnaryOperatorNode::GetOperatorType() const {
    return _stype;
}

