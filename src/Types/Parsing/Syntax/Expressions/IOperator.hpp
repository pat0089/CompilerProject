#ifndef COMPILERPROJECT_IOPERATOR_HPP
#define COMPILERPROJECT_IOPERATOR_HPP
#include "../../../Lexing/Tokens/Symbol.hpp"

enum class OperatorType { None, Minus, Bitwise_Complement, Logical_Negation, Addition, Multiplication, Division, AND, OR, Equal, Not_Equal, Less_Than, Less_Than_Or_Equal, Greater_Than, Greater_Than_Or_Equal };

class IOperator {
public:
    virtual OperatorType GetOperator() = 0;
protected:
    OperatorType _otype;
    static OperatorType ConvertOperator(SymbolType stype1, SymbolType stype2 = SymbolType::None);
};


#endif //COMPILERPROJECT_IOPERATOR_HPP
