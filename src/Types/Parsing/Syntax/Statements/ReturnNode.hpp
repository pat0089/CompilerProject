#ifndef COMPILERPROJECT_RETURNNODE_HPP
#define COMPILERPROJECT_RETURNNODE_HPP
#include "../Expressions/ExpressionNode.hpp"
#include "StatementNode.hpp"

class ReturnNode : public StatementNode {
public:
    explicit ReturnNode(ExpressionNode * exp);
    std::string PrettyPrint() override;
};

#endif //COMPILERPROJECT_RETURNNODE_HPP
