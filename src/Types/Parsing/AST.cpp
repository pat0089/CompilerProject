#include "AST.hpp"

ProgramNode & AST::Program() const {
    return *(ProgramNode*)_head;
}

void AST::Program(ProgramNode * main) {
    _head = main;
}

std::ostream &operator<<(std::ostream &os, const AST &ast) {

    //reference to the AST's ProgramNode
    auto program = ast.Program();
    os << program << "\n";

    for (int i = 0; i < program.ChildCount(); i++) {

        //reference to ProgramNode's children (FunctionNodes)
        auto function = program[i];
        os << "  " << function << "\n";

        //Reference to the FunctionNode's Parameters
        auto params = function.Params();
        os << "\t" << params << "(";
        for (int j = 0; j < params.ChildCount(); j++) {
            os << params[i];
        }
        os << ")\n";

        //Reference to the FunctionNode's BodyNode
        auto body = function.Body();
        os << "\t" << body << "\n";

        for (int j = 0; j < body.ChildCount(); j++) {
            os << "\t\t" << body[i] << "->";
            for (int k = 0; k < body[j].ChildCount(); k++) {
                os << body[j][k];
            }
            os << "\n";
        }
    }
    return os;
}
