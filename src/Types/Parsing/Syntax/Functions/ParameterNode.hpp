#ifndef COMPILERPROJECT_PARAMETERNODE_HPP
#define COMPILERPROJECT_PARAMETERNODE_HPP
#include "../../SyntaxNode.hpp"
#include "../Expressions/IVariable.hpp"

class ParameterNode : public SyntaxNode, public IVariable {
public:
    explicit ParameterNode(const std::string & pname);
private:
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_PARAMETERNODE_HPP
