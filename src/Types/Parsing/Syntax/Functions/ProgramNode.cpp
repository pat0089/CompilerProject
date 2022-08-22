#include "ProgramNode.hpp"
using std::string;

ProgramNode::ProgramNode(FunctionNode * main) {
    _main = main;
    _stype = SyntaxType::Program;
    Add(main);
}

FunctionNode &ProgramNode::Main() const {
    return *_main;
}

string ProgramNode::PrettyPrint() {
    return string("Program");
}

FunctionNode &ProgramNode::operator[](int i) const {
    return *(FunctionNode *)_children[i];
}
