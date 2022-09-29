#include "ReturnNode.hpp"
using std::string;

ReturnNode::ReturnNode(ExpressionNode * exp) : StatementNode(SyntaxType::Return) {
    Add(exp);
}

/// Virtual output string for each type of syntax
/// \return respective string containing pertinent information from this syntax node
string ReturnNode::PrettyPrint() {
    return "Return";
}
