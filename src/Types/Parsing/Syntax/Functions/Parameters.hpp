#ifndef COMPILERPROJECT_PARAMETERS_HPP
#define COMPILERPROJECT_PARAMETERS_HPP
#include "../../SyntaxNode.hpp"

class Parameters : public SyntaxNode {
public:

    SyntaxType Type() const override {
        return SyntaxType::Statement;
    }

private:

    std::string PrettyPrint() override;

};


#endif //COMPILERPROJECT_PARAMETERS_HPP
