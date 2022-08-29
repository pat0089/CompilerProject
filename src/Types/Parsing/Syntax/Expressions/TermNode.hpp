#ifndef COMPILERPROJECT_TERMNODE_HPP
#define COMPILERPROJECT_TERMNODE_HPP

#include "ExpressionNode.hpp"

class TermNode : public ExpressionNode {
public:
    TermNode();
    explicit TermNode(SyntaxType stype);
};


#endif //COMPILERPROJECT_TERMNODE_HPP
