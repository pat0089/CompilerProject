#ifndef COMPILERPROJECT_CONTINUENODE_HPP
#define COMPILERPROJECT_CONTINUENODE_HPP
#include "StatementNode.hpp"

class ContinueNode : public StatementNode {

public:
    ContinueNode();
    std::string PrettyPrint() override;

};


#endif //COMPILERPROJECT_CONTINUENODE_HPP
