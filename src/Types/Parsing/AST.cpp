#include "AST.hpp"

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
        os << " ";
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
        case SyntaxType::None:
        default:
            break;
    }
}




