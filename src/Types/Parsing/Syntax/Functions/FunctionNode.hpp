#ifndef COMPILERPROJECT_FUNCTIONNODE_HPP
#define COMPILERPROJECT_FUNCTIONNODE_HPP
#include "../../SyntaxNode.hpp"
#include "Parameters.hpp"
#include "../Statements/BodyNode.hpp"
#include "../Expressions/IFunction.hpp"

class FunctionNode : public SyntaxNode, public IFunction {
public:

    FunctionNode();
    explicit FunctionNode(const std::string &toInit);
    std::string PrettyPrint() override;
protected:
    BodyNode * BodyPtr() const override;
    Parameters * ParamsPtr() const override;
};


#endif //COMPILERPROJECT_FUNCTIONNODE_HPP
