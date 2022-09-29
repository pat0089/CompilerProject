#include "GlobalNode.hpp"

GlobalNode::GlobalNode(const std::string &name, int value) : SyntaxNode(SyntaxType::Global_Variable), IVariable(name), _val(value) {}
int GlobalNode::Value() const { return _val; }

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
std::string GlobalNode::PrettyPrint() {
    return "Global Variable: " + GetVariableName();
}
