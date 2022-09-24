#ifndef COMPILERPROJECT_IOPERATOR_HPP
#define COMPILERPROJECT_IOPERATOR_HPP
#include "../../../Lexing/Tokens/Symbol.hpp"
#include "../../SyntaxNode.hpp"

enum class OperatorType { None,
        Bitwise_AND, Bitwise_XOR, Bitwise_OR, Bitwise_Complement, Bitwise_LShift, Bitwise_RShift,
        Logical_Negation, Logical_AND, Logical_OR,
        Negation, Minus, Addition, Multiplication, Division,
        Equal, Not_Equal, Less_Than, Less_Than_Or_Equal, Greater_Than, Greater_Than_Or_Equal,
        Assignment, Modulo,
};

class IOperator {
public:
    OperatorType GetOperator() const;
protected:
    OperatorType _otype;
    static OperatorType ConvertOperator(SymbolType stype1, SymbolType stype2 = SymbolType::None, SyntaxType stype3 = SyntaxType::Unary_Operator);
};


#endif //COMPILERPROJECT_IOPERATOR_HPP
