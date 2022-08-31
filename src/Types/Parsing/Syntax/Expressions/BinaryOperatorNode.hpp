#ifndef COMPILERPROJECT_BINARYOPERATORNODE_HPP
#define COMPILERPROJECT_BINARYOPERATORNODE_HPP


#include "../../../Lexing/Tokens/Symbol.hpp"
#include "ExpressionNode.hpp"
#include "IOperator.hpp"
#include "TermNode.hpp"

class BinaryOperatorNode : public ExpressionNode, public IOperator {
public:

    BinaryOperatorNode();
    BinaryOperatorNode(SymbolType stype, SymbolType stype2, ExpressionNode * t1, ExpressionNode * t2);

    SymbolType GetOperatorType() const;
    SymbolType GetOperatorType2() const;

    OperatorType GetOperator() override;

private:

    SymbolType _stype = SymbolType::None;
    SymbolType _stype2 = SymbolType::None;
    std::string PrettyPrint() override;

};


#endif //COMPILERPROJECT_BINARYOPERATORNODE_HPP
