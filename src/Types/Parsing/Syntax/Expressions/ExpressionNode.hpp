#ifndef COMPILERPROJECT_EXPRESSIONNODE_HPP
#define COMPILERPROJECT_EXPRESSIONNODE_HPP
#include "../../SyntaxNode.hpp"

class ExpressionNode : public SyntaxNode {
public:

    SyntaxType Type() const override {
        return SyntaxType::Expression;
    }

};


#endif //COMPILERPROJECT_EXPRESSIONNODE_HPP
