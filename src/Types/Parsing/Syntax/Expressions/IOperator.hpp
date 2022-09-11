#ifndef COMPILERPROJECT_IOPERATOR_HPP
#define COMPILERPROJECT_IOPERATOR_HPP
#include "../../../Lexing/Tokens/Symbol.hpp"
#include "../../SyntaxNode.hpp"

enum class OperatorType { None,
        Bitwise_Complement, Logical_Negation, Negation,
        Minus, Addition, Multiplication, Division,
        AND, OR,
        Equal, Not_Equal, Less_Than, Less_Than_Or_Equal, Greater_Than, Greater_Than_Or_Equal,
        Assignment
};

class IOperator {
public:
    OperatorType GetOperator() const;
protected:
    OperatorType _otype;
    static OperatorType ConvertOperator(SymbolType stype1, SymbolType stype2 = SymbolType::None, SyntaxType stype3 = SyntaxType::Unary_Operator);
};


#endif //COMPILERPROJECT_IOPERATOR_HPP
