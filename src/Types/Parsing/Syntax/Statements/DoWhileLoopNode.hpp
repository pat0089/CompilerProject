#ifndef COMPILERPROJECT_DOWHILELOOPNODE_HPP
#define COMPILERPROJECT_DOWHILELOOPNODE_HPP
#include "WhileLoopNode.hpp"

class DoWhileLoopNode : public WhileLoopNode {

public:
    DoWhileLoopNode(StatementNode *statement, ExpressionNode *exp);
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_DOWHILELOOPNODE_HPP
