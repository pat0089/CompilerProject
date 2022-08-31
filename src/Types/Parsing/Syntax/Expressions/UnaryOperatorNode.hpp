#ifndef COMPILERPROJECT_UNARYOPERATORNODE_HPP
#define COMPILERPROJECT_UNARYOPERATORNODE_HPP
#include "../../../Lexing/Tokens/Symbol.hpp"
#include "ExpressionNode.hpp"
#include "IOperator.hpp"

class UnaryOperatorNode : public ExpressionNode, public IOperator {
public:

    UnaryOperatorNode(SymbolType stype, ExpressionNode * exp);

    SymbolType GetOperatorType() const;

    OperatorType GetOperator() override;

private:
    SymbolType _stype = SymbolType::None;
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_UNARYOPERATORNODE_HPP
