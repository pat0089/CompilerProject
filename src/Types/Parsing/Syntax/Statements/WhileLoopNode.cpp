#include "WhileLoopNode.hpp"

WhileLoopNode::WhileLoopNode(ExpressionNode *exp, StatementNode *statement) : StatementNode(SyntaxType::While_Loop) {
    Add(exp);
    Add(statement);
}

std::string WhileLoopNode::PrettyPrint() {
    return "While Loop: ";
}

WhileLoopNode::WhileLoopNode(SyntaxType stype) : StatementNode(stype) {}
