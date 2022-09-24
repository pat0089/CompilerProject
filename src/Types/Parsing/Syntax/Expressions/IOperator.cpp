#include "IOperator.hpp"

OperatorType IOperator::ConvertOperator(SymbolType stype1, SymbolType stype2, SyntaxType stype3) {
    switch (stype1) {
        case SymbolType::Open_Chevron:
            if (stype2 == SymbolType::None) return OperatorType::Less_Than;
            if (stype2 == SymbolType::Equals) return OperatorType::Less_Than_Or_Equal;
            if (stype2 == SymbolType::Open_Chevron) return OperatorType::Bitwise_LShift;
        case SymbolType::Close_Chevron:
            if (stype2 == SymbolType::None) return OperatorType::Greater_Than;
            if (stype2 == SymbolType::Equals) return OperatorType::Greater_Than_Or_Equal;
            if (stype2 == SymbolType::Close_Chevron) return OperatorType::Bitwise_RShift;
        case SymbolType::Equals:
            if (stype2 == SymbolType::None) return OperatorType::Assignment;
            if (stype2 == SymbolType::Equals) return OperatorType::Equal;
        case SymbolType::Plus:
            return OperatorType::Addition;
        case SymbolType::Minus:
            if (stype3 == SyntaxType::Unary_Operator) return OperatorType::Negation;
            if (stype3 == SyntaxType::Binary_Operator) return OperatorType::Minus;
        case SymbolType::ForwardSlash:
            return OperatorType::Division;
        case SymbolType::Asterisk:
            return OperatorType::Multiplication;
        case SymbolType::And:
            if (stype2 == SymbolType::None) return OperatorType::Bitwise_AND;
            if (stype2 == SymbolType::And) return OperatorType::Logical_AND;
        case SymbolType::Vertical_Line:
            if (stype2 == SymbolType::None) return OperatorType::Bitwise_OR;
            if (stype2 == SymbolType::Vertical_Line) return OperatorType::Logical_OR;
        case SymbolType::Exclaimation:
            if (stype2 == SymbolType::None) return OperatorType::Logical_Negation;
            if (stype2 == SymbolType::Equals) return OperatorType::Not_Equal;
        case SymbolType::Tilde:
            return OperatorType::Bitwise_Complement;
        case SymbolType::Percent:
            return OperatorType::Modulo;
        case SymbolType::Carrot:
            return OperatorType::Bitwise_XOR;
        case SymbolType::None:
        default:
            return OperatorType::None;
    }
}

OperatorType IOperator::GetOperator() const {
    return _otype;
}
