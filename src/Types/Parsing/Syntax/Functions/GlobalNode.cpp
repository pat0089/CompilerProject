#include "GlobalNode.hpp"

GlobalNode::GlobalNode(const std::string &name, int value) : SyntaxNode(SyntaxType::Global_Variable), IVariable(name), _val(value) {}
int GlobalNode::Value() const { return _val; }

std::string GlobalNode::PrettyPrint() {
    return "Global Variable: " + GetVariableName();
}
