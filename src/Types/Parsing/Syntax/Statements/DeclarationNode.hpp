#ifndef COMPILERPROJECT_DECLARATIONNODE_HPP
#define COMPILERPROJECT_DECLARATIONNODE_HPP

#include "StatementNode.hpp"
#include "../Expressions/ExpressionNode.hpp"
#include "../Expressions/IVariable.hpp"

class DeclarationNode : public StatementNode, public IVariable {
public :
    DeclarationNode();
    explicit DeclarationNode(const std::string & name, ExpressionNode * option_expr = nullptr);
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_DECLARATIONNODE_HPP
