#include "CodeGenerator.hpp"
#include <fstream>

void CodeGenerator::Generate(const AST &ast, const string & fname) {
    std::ofstream fout;
    //maybe do path finding for this?
    fout.open(fname);
    Generate(ast.Program(), fout);
    fout.close();
}

void CodeGenerator::Generate(SyntaxNode & snode, std::ofstream & file) {
    if (snode.Type() == SyntaxType::Function)
        WriteFunction(dynamic_cast<FunctionNode &>(snode), file);
    if (snode.Type() == SyntaxType::Return)
        WriteReturn(dynamic_cast<ReturnNode &>(snode), file);
    for (int i = 0; i < snode.ChildCount(); i++) {
        Generate(snode[i], file);
    }
}

void CodeGenerator::WriteFunction(FunctionNode & fnode, std::ofstream & file) {

    if (fnode.Name() == "main") {
        //file << ".globl _start\n_start:\n";
        //return;
    }

    file << ".globl " << fnode.Name() << "\n" << fnode.Name() << ":\n";
}

void CodeGenerator::WriteToRegister(const string &reg, ConstantNode & cnode, std::ofstream & file) {
    file << "\tmovl\t$" << cnode.Value() << ", %" << reg << "\n";
}

void CodeGenerator::WriteReturn(ReturnNode & rnode, std::ofstream & file) {
    if (rnode.ChildCount() == 1)
        if (rnode[0].Type() == SyntaxType::Constant)
            WriteToRegister("eax", dynamic_cast<ConstantNode &>(rnode[0]), file);
    file << "\tret\n";
}


