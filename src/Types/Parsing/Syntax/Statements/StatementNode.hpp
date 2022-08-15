#ifndef COMPILERPROJECT_STATEMENTNODE_HPP
#define COMPILERPROJECT_STATEMENTNODE_HPP
#include "../../SyntaxNode.hpp"

class StatementNode : public SyntaxNode {
public:

    SyntaxType Type() const override {
        return SyntaxType::Statement;
    }

};

#endif //COMPILERPROJECT_STATEMENTNODE_HPP
