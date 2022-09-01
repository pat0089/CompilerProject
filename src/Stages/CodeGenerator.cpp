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

void CodeGenerator::HandleUnaryOperator(UnaryOperatorNode &uonode, std::ofstream &file) {
    switch (uonode.GetOperator()) {
        case OperatorType::Bitwise_Complement:
            BitwiseComplementRegister("eax", file);
            break;
        case OperatorType::Negation:
            NegateRegister("eax", file);
            break;
        case OperatorType::Logical_Negation:
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
    string r0 = "eax";
    string r1 = "ecx";

    Generate(bonode.Child(0), file);
    PushRegisterToStack(r0, file);
    Generate(bonode.Child(1), file);
    PopRegisterFromStack(r1, file);

    switch (bonode.GetOperator()) {
        case OperatorType::Addition:
            AddRegisters(r0, r1, file);
            break;
        case OperatorType::Minus:
            SubtractRegisters(r0, r1, file);
            break;
        case OperatorType::Division:
            DivideRegisters(r0, r1, file);
            break;
        case OperatorType::Multiplication:
            MultiplyRegisters(r0, r1, file);
            break;
        case OperatorType::Equal:
            CompareEqual(r0, r1, file);
            break;
        case OperatorType::Not_Equal:
            CompareNotEqual(r0, r1, file);
        default:
            break;
        case OperatorType::AND:
            break;
        case OperatorType::OR:
            break;
        case OperatorType::Less_Than:
            CompareLessThan(r0, r1, file);
            break;
        case OperatorType::Less_Than_Or_Equal:
            CompareLessThanOrEqual(r0, r1, file);
            break;
        case OperatorType::Greater_Than:
            CompareGreaterThan(r0, r1, file);
            break;
        case OperatorType::Greater_Than_Or_Equal:
            CompareGreaterThanOrEqual(r0, r1, file);
            break;
    }
}

void CodeGenerator::LogicalNegateRegister(const string &reg, std::ofstream &file) {
    CompareWithZero(reg, file);
    ZeroOutRegister(reg, file);
    SetIfEqual(reg, file);
}

void CodeGenerator::SwapRegisters(const string &reg1, const string &reg2, std::ofstream &file) {
    CopyFromRegister(reg1, "edx", file);
    CopyFromRegister(reg2, reg1, file);
    CopyFromRegister("edx", reg2, file);
}

void CodeGenerator::CompareEqual(const string &reg1, const string &reg2, std::ofstream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfEqual(reg1, file);
}


void CodeGenerator::CompareNotEqual(const string &reg1, const string &reg2, std::ofstream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfNotEqual(reg1, file);
}

void CodeGenerator::ZeroOutRegister(const string &reg, std::ofstream &file) {
    SetRegisterVal(reg, 0, file);
}

void CodeGenerator::CompareWithZero(const string &reg, std::ofstream &file) {
    CompareRegisterVal(reg, 0, file);
}

void CodeGenerator::WriteToRegister(const string &reg, ConstantNode & cnode, std::ofstream & file) {
    SetRegisterVal(reg, cnode.Value(), file);
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


void CodeGenerator::WriteFunction(FunctionNode & fnode, std::ofstream & file) {
    file << ".globl " << fnode.Name() << "\n";
    file << fnode.Name() << ":\n";
}

void CodeGenerator::AddRegisters(const string &reg1, const string &reg2, std::ofstream &file) {
    file << "\taddl\t%" << reg2 << ", %"<< reg1 << "\n";
}

void CodeGenerator::CompareRegisterVal(const string &reg, int val, std::ofstream &file) {
    file << "\tcmpl\t$" << val << ", %" << reg << "\n";
}

void CodeGenerator::CompareRegisters(const string &reg1, const string &reg2, std::ofstream &file) {
    file << "\tcmpl\t%" << reg1 << ", %" << reg2 << "\n";
}

void CodeGenerator::SetRegisterVal(const string &reg, int val, std::ofstream &file) {
    file << "\tmovl\t$" << val << ", %" << reg << "\n";
}

void CodeGenerator::SetIfGreaterThan(const string &reg, std::ofstream &file) {
    file << "\tsetg\t%" << reg[1] << "l\n";
}

void CodeGenerator::SetIfEqual(const string &reg, std::ofstream &file) {
    file << "\tsete\t%" << reg[1] << "l\n";
}

void CodeGenerator::CopyFromRegister(const string &reg1, const string &reg2, std::ofstream &file) {
    file << "\tmovl\t%" << reg1 << ", %" << reg2 << "\n";
}

void CodeGenerator::MultiplyRegisters(const string &reg1, const string &reg2, std::ofstream &file) {
    file << "\timul\t%" << reg2 << ", %"<< reg1 << "\n";
}

void CodeGenerator::PushRegisterToStack(const string &reg, std::ofstream &file) {
    file << "\tpush\t%" << reg << "\n";
}

void CodeGenerator::PopRegisterFromStack(const string &reg, std::ofstream &file) {
    file << "\tpop\t\t%" << reg << "\n";
}

void CodeGenerator::WriteReturn(std::ofstream & file) {
    file << "\tret\n";
}

void CodeGenerator::NegateRegister(const string &reg, std::ofstream &file) {
    file << "\tneg\t\t%" << reg << "\n";
}

void CodeGenerator::BitwiseComplementRegister(const std::string & reg, std::ofstream &file) {
    file << "\tnot\t\t%" << reg << "\n";
}

void CodeGenerator::SetIfNotEqual(const string &reg, std::ofstream &file) {
    file << "\tsetne\t%" << reg[1] << "l\n";
}

void CodeGenerator::SetIfLessThan(const string &reg, std::ofstream &file) {
    file << "\tsetl\t%" << reg[1] << "l\n";
}

void CodeGenerator::SetIfLessThanOrEqual(const string &reg, std::ofstream &file) {
    file << "\tsetle\t%" << reg[1] << "l\n";
}

void CodeGenerator::SetIfGreaterThanOrEqual(const string &reg, std::ofstream &file) {
    file << "\tsetge\t%" << reg[1] << "l\n";
}

void CodeGenerator::CompareGreaterThan(const string &reg1, const string &reg2, std::ofstream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfGreaterThan(reg1, file);
}

void CodeGenerator::CompareLessThan(const string &reg1, const string &reg2, std::ofstream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfLessThan(reg1, file);
}

void CodeGenerator::CompareGreaterThanOrEqual(const string &reg1, const string &reg2, std::ofstream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfGreaterThanOrEqual(reg1, file);
}

void CodeGenerator::CompareLessThanOrEqual(const string &reg1, const string &reg2, std::ofstream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfLessThanOrEqual(reg1, file);
}
