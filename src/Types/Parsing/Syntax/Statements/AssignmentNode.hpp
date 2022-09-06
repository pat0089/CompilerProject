#ifndef COMPILERPROJECT_ASSIGNMENTNODE_HPP
#define COMPILERPROJECT_ASSIGNMENTNODE_HPP

#include "StatementNode.hpp"
#include "../Expressions/IVariable.hpp"
#include "../Expressions/ExpressionNode.hpp"

class AssignmentNode : public StatementNode, public IVariable {
public:
    AssignmentNode();
    AssignmentNode(const std::string & name, ExpressionNode * exp);
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_ASSIGNMENTNODE_HPP
