#include "CodeGenerator.hpp"
#include <fstream>

void CodeGenerator::Generate(const AST &ast, const string & fname) {
    std::ofstream fout;
    fout.open(fname);
    Generate(ast.Program(), fout);
    fout.close();
}

void CodeGenerator::Generate(SyntaxNode & snode, std::ofstream & file) {
    if (snode.Type() == SyntaxType::Function)
        WriteFunction(dynamic_cast<FunctionNode &>(snode), file);
    for (int i = 0; i < snode.ChildCount(); i++) {
        Generate(snode[i], file);
    }
    //std::cout << snode << "\n";

    if (snode.Type() == SyntaxType::Return)
        WriteReturn(dynamic_cast<ReturnNode &>(snode), file);
    if (snode.Type() == SyntaxType::UnaryOperator)
        HandleUnaryOperator(dynamic_cast<UnaryOperatorNode &>(snode), file);
    if (snode.Type() == SyntaxType::Constant)
        WriteToRegister("eax", dynamic_cast<ConstantNode &>(snode), file);
}

void CodeGenerator::WriteFunction(FunctionNode & fnode, std::ofstream & file) {
    file << ".globl " << fnode.Name() << "\n" << fnode.Name() << ":\n";
}

void CodeGenerator::WriteToRegister(const string &reg, ConstantNode & cnode, std::ofstream & file) {
    file << "\tmovl\t$" << cnode.Value() << ", %" << reg << "\n";
}

void CodeGenerator::WriteReturn(ReturnNode & rnode, std::ofstream & file) {
    file << "\tret\n";
}

void CodeGenerator::NegateRegister(const string &reg, std::ofstream &file) {
    file << "\tneg\t\t%" << reg << "\n";
}

void CodeGenerator::NotRegister(const std::string & reg, std::ofstream &file) {
    file << "\tnot\t\t%" << reg << "\n";
}

void CodeGenerator::LogicalNegateRegister(const string &reg, std::ofstream &file) {
    file << "\tcmpl\t$0, %" << reg << "\n\tmovl\t$0, %" << reg << "\n";
    //TODO: change this last statement to
    // represent the lower bytes of the corresponding
    // register
    file << "\tsete\t%al\n";
}

void CodeGenerator::HandleUnaryOperator(UnaryOperatorNode &uonode, std::ofstream &file) {
    switch (uonode.GetOperatorType()) {
        case SymbolType::Tilde:
            NotRegister("eax", file);
            break;
        case SymbolType::Minus:
            NegateRegister("eax", file);
            break;
        case SymbolType::Exclaimation:
            LogicalNegateRegister("eax", file);
            break;
        default:
            //maybe add an error message here?
            break;
    }
}


