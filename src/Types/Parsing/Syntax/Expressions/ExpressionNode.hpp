#ifndef COMPILERPROJECT_EXPRESSIONNODE_HPP
#define COMPILERPROJECT_EXPRESSIONNODE_HPP
#include "../Statements/StatementNode.hpp"

class ExpressionNode : public StatementNode {
public:
    ExpressionNode();
    explicit ExpressionNode(SyntaxType stype);
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_EXPRESSIONNODE_HPP
