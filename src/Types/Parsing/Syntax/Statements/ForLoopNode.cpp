#include "ForLoopNode.hpp"

std::string ForLoopNode::PrettyPrint() {
    return "For Loop:";
}

ForLoopNode::ForLoopNode(StatementNode *first, ExpressionNode *second,
                         ExpressionNode *third, StatementNode *to_loop) : StatementNode(SyntaxType::For_Loop) {
    Add(first);
    Add(second);
    Add(third);
    Add(to_loop);
}

