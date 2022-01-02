#ifndef COMPILERPROJECT_PARAMETERNODE_HPP
#define COMPILERPROJECT_PARAMETERNODE_HPP
#include "../../SyntaxNode.hpp"

class ParameterNode : public SyntaxNode {
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_PARAMETERNODE_HPP
