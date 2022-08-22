#ifndef COMPILERPROJECT_BODYNODE_HPP
#define COMPILERPROJECT_BODYNODE_HPP
#include "StatementNode.hpp"
#include "../../SyntaxNode.hpp"

class BodyNode : public SyntaxNode {
public:

    BodyNode();

private:

    std::string PrettyPrint() override;

};

#endif //COMPILERPROJECT_BODYNODE_HPP
