#include "AST.hpp"

AST::AST(): _head(nullptr) {}
AST::~AST() { delete _head; }

ProgramNode * AST::Program() const {
    return (ProgramNode*)_head;
}

void AST::Program(ProgramNode * main) {
    _head = main;
}

std::ostream &operator<<(std::ostream &os, const AST &ast) {
    ast.recursiveOutput(ast._head, os, 0);
    return os;
}

void AST::recursiveOutput(const SyntaxNode * snode, std::ostream &os, int layer) const {
    if (!snode) return;
    for (int i = 0; i < layer; i++) {
        if (i < layer - 1) {
            os << "|  ";
        } else os << "`->";
    }
    outputNode(snode, os);
    for (int i = 0; i < snode->ChildCount(); i++) {
        recursiveOutput(snode->Child(i), os, layer + 1);
    }
}

void AST::outputNode(const SyntaxNode * snode, std::ostream & os) const {
    switch (snode->Type()) {
        case SyntaxType::Program:
            os << *(ProgramNode *)snode << "\n";
            break;
        case SyntaxType::Function:
            os << *(FunctionNode *)snode << "\n";
            break;
        case SyntaxType::Parameters:
            os << *(ParameterNode *)snode << "\n";
            break;
        case SyntaxType::Body:
            os << *(BodyNode *)snode << "\n";
            break;
        case SyntaxType::Return:
            os << *(ReturnNode *)snode << "\n";
            break;
        case SyntaxType::Constant:
            os << *(ConstantNode *)snode << "\n";
            break;
        case SyntaxType::Unary_Operator:
            os << *(UnaryOperatorNode *)snode << "\n";
            break;
        case SyntaxType::Binary_Operator:
            os << *(BinaryOperatorNode *)snode << "\n";
            break;
        case SyntaxType::Declaration:
            os << *(DeclarationNode *)snode << "\n";
            break;
        case SyntaxType::Assignment:
            os << *(AssignmentNode *)snode << "\n";
            break;
        case SyntaxType::Variable:
            os << *(VariableNode *)snode << "\n";
            break;
        case SyntaxType::Conditional_Statement:
            os << *(ConditionalStatementNode *)snode << "\n";
            break;
        case SyntaxType::Conditional_Expression:
            os << *(ConditionalExpressionNode *)snode << "\n";
            break;
        case SyntaxType::For_Loop:
            os << *(ForLoopNode *)snode << "\n";
            break;
        case SyntaxType::While_Loop:
            os << *(WhileLoopNode *)snode << "\n";
            break;
        case SyntaxType::Do_While_Loop:
            os << *(DoWhileLoopNode *)snode << "\n";
            break;
        case SyntaxType::Break:
            os << *(BreakNode *)snode << "\n";
            break;
        case SyntaxType::Continue:
            os << *(ContinueNode *)snode << "\n";
            break;
        case SyntaxType::Function_Call:
            os << *(FunctionCallNode *)snode << "\n";
            break;
        case SyntaxType::Parameter:
            os << *(ParameterNode *)snode << "\n";
            break;
        case SyntaxType::Statement:
        case SyntaxType::Expression:
        case SyntaxType::Term:
        case SyntaxType::Factor:
        case SyntaxType::None:
        default:
            break;
    }
}
