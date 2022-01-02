#include "ReturnNode.hpp"
using std::string;

ReturnNode::ReturnNode(ExpressionNode * exp) {
    Add(exp);
}

string ReturnNode::PrettyPrint() {
    return string("Return");
}
