#ifndef COMPILERPROJECT_FUNCTIONCALLNODE_HPP
#define COMPILERPROJECT_FUNCTIONCALLNODE_HPP
#include "../Functions/FunctionNode.hpp"
#include "ExpressionNode.hpp"

class FunctionCallNode : public ExpressionNode {
public:
    FunctionCallNode();
    ~FunctionCallNode() override;
    std::string & Name() const;
    explicit FunctionCallNode(const std::string &toInit);
    std::string PrettyPrint() override;

private:
    std::string * _name;
};


#endif //COMPILERPROJECT_FUNCTIONCALLNODE_HPP
