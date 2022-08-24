#ifndef COMPILERPROJECT_EXPRESSIONNODE_HPP
#define COMPILERPROJECT_EXPRESSIONNODE_HPP
#include "../../SyntaxNode.hpp"

class ExpressionNode : public SyntaxNode {
public:

    ExpressionNode();
    explicit ExpressionNode(SyntaxType stype);

};


#endif //COMPILERPROJECT_EXPRESSIONNODE_HPP
