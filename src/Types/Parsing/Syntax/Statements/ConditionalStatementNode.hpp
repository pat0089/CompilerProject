#ifndef COMPILERPROJECT_CONDITIONALSTATEMENTNODE_HPP
#define COMPILERPROJECT_CONDITIONALSTATEMENTNODE_HPP
#include "../Expressions/ExpressionNode.hpp"

class ConditionalStatementNode : public StatementNode {
public:
    ConditionalStatementNode(ExpressionNode * exp, StatementNode * snode, StatementNode * option = nullptr);
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_CONDITIONALSTATEMENTNODE_HPP
