#ifndef COMPILERPROJECT_WHILELOOPNODE_HPP
#define COMPILERPROJECT_WHILELOOPNODE_HPP


#include "StatementNode.hpp"
#include "../Expressions/ExpressionNode.hpp"

class WhileLoopNode : public StatementNode {

public:
    explicit WhileLoopNode(SyntaxType stype);
    WhileLoopNode(ExpressionNode * exp, StatementNode * statement);
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_WHILELOOPNODE_HPP
