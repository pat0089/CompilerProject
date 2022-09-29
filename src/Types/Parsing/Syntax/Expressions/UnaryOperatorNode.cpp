#include "UnaryOperatorNode.hpp"
using std::string;

UnaryOperatorNode::UnaryOperatorNode(SymbolType stype, ExpressionNode * exp) : ExpressionNode(SyntaxType::Unary_Operator), IOperator(), _stype(stype) {
    Add(exp);
    _otype = IOperator::ConvertOperator(stype);
}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
string UnaryOperatorNode::PrettyPrint() {
    return "Unary Operator: " + Symbol::GetString(GetOperatorType());
}

SymbolType UnaryOperatorNode::GetOperatorType() const {
    return _stype;
}
