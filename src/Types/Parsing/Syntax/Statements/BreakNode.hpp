#ifndef COMPILERPROJECT_BREAKNODE_HPP
#define COMPILERPROJECT_BREAKNODE_HPP
#include "StatementNode.hpp"

class BreakNode : public StatementNode {

public:
    BreakNode();
    std::string PrettyPrint() override;

};

#endif //COMPILERPROJECT_BREAKNODE_HPP
