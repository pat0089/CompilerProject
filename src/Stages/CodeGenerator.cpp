#include "CodeGenerator.hpp"
#include <fstream>

void CodeGenerator::Generate(const AST &ast, const string & fname) {
    std::ofstream fout;
    fout.open(fname);
    Generate(ast.Program(), fout);
    fout.close();
}

void CodeGenerator::Generate(SyntaxNode * snode, std::ofstream & file) {
    if (snode->Type() == SyntaxType::Function)
        WriteFunction(*(FunctionNode *)(snode), file);

    if (snode->Type() == SyntaxType::BinaryOperator) {
        HandleBinaryOperator(*(BinaryOperatorNode *)(snode), file);
        return;
    }

    for (int i = 0; i < snode->ChildCount(); i++) {
        Generate(snode->Child(i), file);
    }
    if (snode->Type() == SyntaxType::Return)
        WriteReturn(file);
    if (snode->Type() == SyntaxType::UnaryOperator)
        HandleUnaryOperator(*(UnaryOperatorNode *)(snode), file);
    if (snode->Type() == SyntaxType::Constant)
        WriteToRegister("eax", *(ConstantNode *)(snode), file);

}

void CodeGenerator::WriteFunction(FunctionNode & fnode, std::ofstream & file) {
    file << ".globl " << fnode.Name() << "\n" << fnode.Name() << ":\n";
}

void CodeGenerator::WriteToRegister(const string &reg, ConstantNode & cnode, std::ofstream & file) {
    file << "\tmovl\t$" << cnode.Value() << ", %" << reg << "\n";
}

void CodeGenerator::WriteReturn(std::ofstream & file) {
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
    file << "\tsete\t%" << reg[1] << "l\n";
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

void CodeGenerator::HandleBinaryOperator(const BinaryOperatorNode & bonode, std::ofstream & file) {
    //generate children in a specific order
    //separate from the recursive Generate call
    Generate(bonode.Child(0), file);
    PushRegisterToStack("eax", file);
    Generate(bonode.Child(1), file);
    PopRegisterFromStack("ecx", file);

    switch (bonode.GetOperatorType()) {
        case SymbolType::Plus:
            AddRegisters("eax", "ecx", file);
            break;
        case SymbolType::Minus:
            SubtractRegisters("eax", "ecx", file);
            break;
        case SymbolType::ForwardSlash:
            DivideRegisters("eax", "ecx", file);
            break;
        case SymbolType::Asterisk:
            MultiplyRegisters("eax", "ecx", file);
            break;
    }
}

void CodeGenerator::AddRegisters(const string &reg1, const string &reg2, std::ofstream &file) {
    file << "\taddl\t%" << reg2 << ", %"<< reg1 << "\n";
}

void CodeGenerator::SubtractRegisters(const string &reg1, const string &reg2, std::ofstream &file) {
    SwapRegisters(reg1, reg2, file);
    file << "\tsubl\t%" << reg2 << ", %"<< reg1 << "\n";
}

void CodeGenerator::DivideRegisters(const string &reg1, const string &reg2, std::ofstream &file) {
    SwapRegisters(reg1, reg2, file);
    file << "\tcdq\n";
    file << "\tidivl\t%" << reg2 << "\n";
}

void CodeGenerator::MultiplyRegisters(const string &reg1, const string &reg2, std::ofstream &file) {
    file << "\timul\t%" << reg2 << ", %"<< reg1 << "\n";
}

void CodeGenerator::PushRegisterToStack(const string &reg, std::ofstream &file) {
    file << "\tpush\t%" << reg << "\n";
}

void CodeGenerator::PopRegisterFromStack(const string &reg, std::ofstream &file) {
    file << "\tpop\t%" << reg << "\n";
}

void CodeGenerator::SwapRegisters(const string &reg1, const string &reg2, std::ofstream &file) {
    file << "\tmovl\t%" << reg1 << ", %edx\n";
    file << "\tmovl\t%" << reg2 << ", %" << reg1 << "\n";
    file << "\tmovl\t%edx, %" << reg2 << "\n";
}


