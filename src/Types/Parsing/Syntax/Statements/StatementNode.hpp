#ifndef COMPILERPROJECT_STATEMENTNODE_HPP
#define COMPILERPROJECT_STATEMENTNODE_HPP
#include "../../SyntaxNode.hpp"

class StatementNode : public SyntaxNode {
public:

    StatementNode();
    StatementNode(SyntaxType stype);

};

#endif //COMPILERPROJECT_STATEMENTNODE_HPP
