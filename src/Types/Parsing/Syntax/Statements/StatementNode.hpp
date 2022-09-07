#ifndef COMPILERPROJECT_STATEMENTNODE_HPP
#define COMPILERPROJECT_STATEMENTNODE_HPP
#include "../../SyntaxNode.hpp"

class StatementNode : public SyntaxNode {
public:

    StatementNode();
    explicit StatementNode(SyntaxType stype);
    std::string PrettyPrint() override;

};

#endif //COMPILERPROJECT_STATEMENTNODE_HPP
