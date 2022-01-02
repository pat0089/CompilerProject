#ifndef COMPILERPROJECT_CONSTANTNODE_HPP
#define COMPILERPROJECT_CONSTANTNODE_HPP
#include "ExpressionNode.hpp"
class ConstantNode : public ExpressionNode {
public:
    ConstantNode();
    explicit ConstantNode(int toInit);
    int & Value() const;
    void Value(int i);
    std::string PrettyPrint() override;

private:
    int * _val;
};


#endif //COMPILERPROJECT_CONSTANTNODE_HPP
