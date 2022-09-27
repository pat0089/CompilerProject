#ifndef COMPILERPROJECT_GLOBALNODE_HPP
#define COMPILERPROJECT_GLOBALNODE_HPP
#include "../../SyntaxNode.hpp"
#include "../Expressions/IVariable.hpp"

class GlobalNode : public SyntaxNode, public IVariable {
public:
    GlobalNode(const std::string & name, int value);
    int Value() const;
    std::string PrettyPrint() override;
private:
    //default value is 0 for globals
    int _val = 0;
};


#endif //COMPILERPROJECT_GLOBALNODE_HPP
