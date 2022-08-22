#include "ReturnNode.hpp"
using std::string;

ReturnNode::ReturnNode(ExpressionNode * exp) : StatementNode(SyntaxType::Return) {
    Add(exp);
}

string ReturnNode::PrettyPrint() {
    return "Return";
}
