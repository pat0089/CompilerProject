#include "ProgramNode.hpp"
using std::string;

ProgramNode::ProgramNode() : SyntaxNode(SyntaxType::Program) {}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
string ProgramNode::PrettyPrint() {
    return "Program";
}
