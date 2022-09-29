#ifndef COMPILERPROJECT_UNARYOPERATORNODE_HPP
#define COMPILERPROJECT_UNARYOPERATORNODE_HPP
#include "../../../Lexing/Tokens/Symbol.hpp"
#include "ExpressionNode.hpp"
#include "IOperator.hpp"

class UnaryOperatorNode : public ExpressionNode, public IOperator {
public:
    UnaryOperatorNode(SymbolType stype, ExpressionNode * exp);
    SymbolType GetOperatorType() const;
    std::string PrettyPrint() override;

private:
    SymbolType _stype = SymbolType::None;
};

#endif //COMPILERPROJECT_UNARYOPERATORNODE_HPP
