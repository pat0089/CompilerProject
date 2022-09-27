#include "ProgramNode.hpp"
using std::string;

ProgramNode::ProgramNode(FunctionNode * main) : SyntaxNode(SyntaxType::Program) {
    _main = main;
    Add(main);
}

FunctionNode &ProgramNode::Main() const {
    return *_main;
}

string ProgramNode::PrettyPrint() {
    return "Program";
}

FunctionNode &ProgramNode::operator[](int i) const {
    return *(FunctionNode *)_children[i];
}

ProgramNode::ProgramNode() : SyntaxNode(SyntaxType::Program) {}
