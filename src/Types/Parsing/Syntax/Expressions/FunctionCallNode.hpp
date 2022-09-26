#ifndef COMPILERPROJECT_FUNCTIONCALLNODE_HPP
#define COMPILERPROJECT_FUNCTIONCALLNODE_HPP
#include "../Functions/FunctionNode.hpp"
#include "ExpressionNode.hpp"
#include "IFunction.hpp"

class FunctionCallNode : public ExpressionNode, public IFunction {
public:
    FunctionCallNode();
    explicit FunctionCallNode(const std::string &toInit);
    std::string PrettyPrint() override;
protected:
    BodyNode * BodyPtr() const override;
    Parameters * ParamsPtr() const override;
};


#endif //COMPILERPROJECT_FUNCTIONCALLNODE_HPP
