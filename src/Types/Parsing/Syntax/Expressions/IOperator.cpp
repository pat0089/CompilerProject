#include "IOperator.hpp"

OperatorType IOperator::ConvertOperator(SymbolType stype1, SymbolType stype2, SyntaxType stype3) {
    switch (stype1) {
        case SymbolType::Open_Chevron:
            if (stype2 == SymbolType::None) return OperatorType::Less_Than;
            if (stype2 == SymbolType::Equals) return OperatorType::Less_Than_Or_Equal;
            break;
        case SymbolType::Close_Chevron:
            if (stype2 == SymbolType::None) return OperatorType::Greater_Than;
            if (stype2 == SymbolType::Equals) return OperatorType::Greater_Than_Or_Equal;
            break;
        case SymbolType::Equals:
            if (stype2 == SymbolType::Equals) return OperatorType::Equal;
            if (stype2 == SymbolType::Exclaimation) return OperatorType::Not_Equal;
            break;
        case SymbolType::Plus:
            return OperatorType::Addition;
        case SymbolType::Minus:
            if (stype3 == SyntaxType::UnaryOperator) return OperatorType::Negation;
            if (stype3 == SyntaxType::BinaryOperator) return OperatorType::Minus;
        case SymbolType::ForwardSlash:
            return OperatorType::Division;
        case SymbolType::Asterisk:
            return OperatorType::Multiplication;
        case SymbolType::And:
            if (stype2 == SymbolType::And) return OperatorType::AND;
            break;
        case SymbolType::Exclaimation:
            return OperatorType::Logical_Negation;
        case SymbolType::Tilde:
            return OperatorType::Bitwise_Complement;
        case SymbolType::None:
        default:
            return OperatorType::None;
    }
    return OperatorType::None;
}

OperatorType IOperator::GetOperator() {
    return _otype;
}
