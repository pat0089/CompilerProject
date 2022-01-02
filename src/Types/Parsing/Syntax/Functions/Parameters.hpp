#ifndef COMPILERPROJECT_PARAMETERS_HPP
#define COMPILERPROJECT_PARAMETERS_HPP
#include "../../SyntaxNode.hpp"

class Parameters : public SyntaxNode {
    std::string PrettyPrint() override;
};


#endif //COMPILERPROJECT_PARAMETERS_HPP
