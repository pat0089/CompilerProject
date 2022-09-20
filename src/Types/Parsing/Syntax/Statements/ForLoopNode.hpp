#ifndef COMPILERPROJECT_FORLOOPNODE_HPP
#define COMPILERPROJECT_FORLOOPNODE_HPP
#include "../../SyntaxNode.hpp"
#include "../Expressions/ExpressionNode.hpp"
#include "DeclarationNode.hpp"

class ForLoopNode : public StatementNode {

public:

    ForLoopNode(StatementNode * first, ExpressionNode * second, ExpressionNode * third, StatementNode * to_loop);
    std::string PrettyPrint() override;

};


#endif //COMPILERPROJECT_FORLOOPNODE_HPP
