#ifndef COMPILERPROJECT_CONDITIONALEXPRESSIONNODE_HPP
#define COMPILERPROJECT_CONDITIONALEXPRESSIONNODE_HPP
#include "ExpressionNode.hpp"

class ConditionalExpressionNode : public ExpressionNode {

public:
    ConditionalExpressionNode(ExpressionNode * decision, ExpressionNode * res1, ExpressionNode * res2);
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_CONDITIONALEXPRESSIONNODE_HPP
