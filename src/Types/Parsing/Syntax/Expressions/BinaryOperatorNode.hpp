#ifndef COMPILERPROJECT_BINARYOPERATORNODE_HPP
#define COMPILERPROJECT_BINARYOPERATORNODE_HPP


#include "../../../Lexing/Tokens/Symbol.hpp"
#include "ExpressionNode.hpp"
#include "TermNode.hpp"

class BinaryOperatorNode : public ExpressionNode {
public:

    BinaryOperatorNode();
    BinaryOperatorNode(SymbolType stype, ExpressionNode * t1, ExpressionNode * t2);

    SymbolType GetSymbolType() const;

private:

    SymbolType _stype = SymbolType::None;
    std::string PrettyPrint() override;

};


#endif //COMPILERPROJECT_BINARYOPERATORNODE_HPP
