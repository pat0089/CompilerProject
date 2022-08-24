#include "AST.hpp"

ProgramNode * AST::Program() const {
    return (ProgramNode*)_head;
}

void AST::Program(ProgramNode * main) {
    _head = main;
}

std::ostream &operator<<(std::ostream &os, const AST &ast) {
    ast.recursiveOutput(ast._head, os);
    return os;
}

void AST::recursiveOutput(const SyntaxNode * snode, std::ostream &os) const {
    outputNode(snode, os);
    //os << snode << "\n";
    for (int i = 0; i < snode->ChildCount(); i++) {
        for (int j = 0; j < i; j++) os << "\t";
        recursiveOutput(snode->Child(i), os);
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
        case SyntaxType::Statement:
            os << *(StatementNode *)snode << "\n";
            break;
        case SyntaxType::Return:
            os << *(ReturnNode *)snode << "\n";
            break;
        case SyntaxType::Constant:
            os << *(ConstantNode *)snode << "\n";
            break;
        case SyntaxType::UnaryOperator:
            os << *(UnaryOperatorNode *)snode << "\n";
            break;
        case SyntaxType::BinaryOperator:
            os << *(BinaryOperatorNode *)snode << "\n";
            break;
        case SyntaxType::None:
        default:
            break;
    }
}




