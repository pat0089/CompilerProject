#include "CodeGenerator.hpp"
#include <fstream>

int CodeGenerator::_labelCount = 0;

void CodeGenerator::Generate(const AST &ast, const string & fname) {

    std::stringstream ss;
    Generate(ast.Program(), ss);

    std::ofstream fout;
    fout.open(fname);
    fout << ss.rdbuf();
    fout.close();
}

/// Dispatch function for processing the node types/children
/// \param snode SyntaxNode to try to generate for
/// \param file Assembly output file reference
void CodeGenerator::Generate(SyntaxNode * snode, std::ostream & file) {
    switch (snode->Type()) {
        case SyntaxType::Program:
            Generate(snode->Child(0), file);
            break;
        case SyntaxType::Function:
            HandleFunction(*(FunctionNode * )(snode), file);
            break;
        case SyntaxType::Parameters:
            break;
        case SyntaxType::Body:
            HandleBody(*(BodyNode * )(snode), file);
            break;
        case SyntaxType::Statement:
            break;
        case SyntaxType::Return:
            HandleReturn(*(ReturnNode *)(snode), file);
            break;
        case SyntaxType::Constant:
            HandleConstant(*(ConstantNode *)(snode), file);
            break;
        case SyntaxType::Unary_Operator:
            HandleUnaryOperator(*(UnaryOperatorNode *)(snode), file);
            break;
        case SyntaxType::Binary_Operator:
            HandleBinaryOperator(*(BinaryOperatorNode *)(snode), file);
            break;
        case SyntaxType::Assignment:
            HandleAssignment(*(AssignmentNode *)(snode), file);
            break;
        case SyntaxType::Variable:
            HandleVariable(*(VariableNode *)(snode), file);
            break;
        case SyntaxType::Conditional_Statement:
            HandleConditionalStatement(*(ConditionalStatementNode *)(snode), file);
            break;
        case SyntaxType::Conditional_Expression:
            HandleConditionalExpression(*(ConditionalExpressionNode *)(snode), file);
            break;
        case SyntaxType::None:
        default:
            break;
    }
}

void CodeGenerator::HandleFunction(const FunctionNode & fnode, std::ostream &file) {
    WriteFunctionName(fnode, file);
    WriteFunctionPrologue(file);
    for (int i = 0; i < fnode.ChildCount(); i++) {
        Generate(fnode.Child(i), file);
    }
    //if function contains no return statement, return 0
    if (!_symbolMap->ContainsReturn())
    {
        ZeroOutRegister("eax", file);
        WriteFunctionEpilogue(file);
        WriteReturn(file);
    }
}

void CodeGenerator::HandleReturn(const ReturnNode & rnode, std::ostream &file) {
    if (rnode.ChildCount()) Generate(rnode.Child(0), file);
    WriteFunctionEpilogue(file);
    WriteReturn(file);
}

void CodeGenerator::HandleUnaryOperator(UnaryOperatorNode &uonode, std::ostream &file) {
    Generate(uonode.Child(0), file);
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

void CodeGenerator::HandleBinaryOperator(const BinaryOperatorNode & bonode, std::ostream & file) {
    //generate children in a specific order
    //separate from the recursive Generate call
    string r0 = "eax";
    string r1 = "ecx";
    auto op = bonode.GetOperator();
    if (op == OperatorType::AND || op == OperatorType::OR) {
        auto jump = CreateNewLabel();
        auto end = CreateNewLabel();
        Generate(bonode.Child(0), file);
        CompareWithZero(r0, file);
        if (op == OperatorType::AND) {
            JumpIfNotEqual(jump, file);
            JumpUnconditional(end, file);
        } else {
            JumpIfEqual(jump, file);
            SetRegisterVal(r0, 1, file);
            JumpUnconditional(end, file);
        }
        MarkLabel(jump, file);
        Generate(bonode.Child(1), file);

        CompareWithZero(r0, file);
        ZeroOutRegister(r0, file);
        SetIfNotEqual(r0, file);

        MarkLabel(end, file);
        return;
    }

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
        default:
            break;
    }
}

void CodeGenerator::LogicalNegateRegister(const string &reg, std::ostream &file) {
    CompareWithZero(reg, file);
    ZeroOutRegister(reg, file);
    SetIfEqual(reg, file);
}

void CodeGenerator::SwapRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    CopyFromRegister(reg1, "edx", file);
    CopyFromRegister(reg2, reg1, file);
    CopyFromRegister("edx", reg2, file);
}

void CodeGenerator::CompareEqual(const string &reg1, const string &reg2, std::ostream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfEqual(reg1, file);
}


void CodeGenerator::CompareNotEqual(const string &reg1, const string &reg2, std::ostream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfNotEqual(reg1, file);
}

void CodeGenerator::ZeroOutRegister(const string &reg, std::ostream &file) {
    SetRegisterVal(reg, 0, file);
}

void CodeGenerator::CompareWithZero(const string &reg, std::ostream &file) {
    CompareRegisterVal(reg, 0, file);
}

void CodeGenerator::HandleConstant(ConstantNode &cnode, std::ostream &file) {
    SetRegisterVal("eax", cnode.Value(), file);
}

void CodeGenerator::SubtractRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    SwapRegisters(reg1, reg2, file);
    file << "\tsubl\t%" << reg2 << ", %"<< reg1 << "\n";
}

void CodeGenerator::DivideRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    SwapRegisters(reg1, reg2, file);
    file << "\tcdq\n";
    file << "\tidivl\t%" << reg2 << "\n";
}


void CodeGenerator::WriteFunctionName(const FunctionNode & fnode, std::ostream & file) {
    file << ".globl " << fnode.Name() << "\n";
    MarkLabel(fnode.Name(), file);
}

void CodeGenerator::AddRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    file << "\taddl\t%" << reg2 << ", %"<< reg1 << "\n";
}

void CodeGenerator::CompareRegisterVal(const string &reg, int val, std::ostream &file) {
    file << "\tcmpl\t$" << val << ", %" << reg << "\n";
}

void CodeGenerator::CompareRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    file << "\tcmpl\t%" << reg1 << ", %" << reg2 << "\n";
}

void CodeGenerator::SetRegisterVal(const string &reg, int val, std::ostream &file) {
    file << "\tmovl\t$" << val << ", %" << reg << "\n";
}

void CodeGenerator::SetIfGreaterThan(const string &reg, std::ostream &file) {
    file << "\tsetg\t%" << reg[1] << "l\n";
}

void CodeGenerator::SetIfEqual(const string &reg, std::ostream &file) {
    file << "\tsete\t%" << reg[1] << "l\n";
}

void CodeGenerator::CopyFromRegister(const string &reg1, const string &reg2, std::ostream &file) {
    file << "\tmovl\t%" << reg1 << ", %" << reg2 << "\n";
}

void CodeGenerator::MultiplyRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    file << "\timul\t%" << reg2 << ", %"<< reg1 << "\n";
}

void CodeGenerator::PushRegisterToStack(const string &reg, std::ostream &file) {
    file << "\tpush\t%" << reg << "\n";
}

void CodeGenerator::PopRegisterFromStack(const string &reg, std::ostream &file) {
    file << "\tpop\t\t%" << reg << "\n";
}

void CodeGenerator::WriteReturn(std::ostream & file) {
    file << "\tret\n";
}

void CodeGenerator::NegateRegister(const string &reg, std::ostream &file) {
    file << "\tneg\t\t%" << reg << "\n";
}

void CodeGenerator::BitwiseComplementRegister(const std::string & reg, std::ostream &file) {
    file << "\tnot\t\t%" << reg << "\n";
}

void CodeGenerator::SetIfNotEqual(const string &reg, std::ostream &file) {
    file << "\tsetne\t%" << reg[1] << "l\n";
}

void CodeGenerator::SetIfLessThan(const string &reg, std::ostream &file) {
    file << "\tsetl\t%" << reg[1] << "l\n";
}

void CodeGenerator::SetIfLessThanOrEqual(const string &reg, std::ostream &file) {
    file << "\tsetle\t%" << reg[1] << "l\n";
}

void CodeGenerator::SetIfGreaterThanOrEqual(const string &reg, std::ostream &file) {
    file << "\tsetge\t%" << reg[1] << "l\n";
}

void CodeGenerator::CompareGreaterThan(const string &reg1, const string &reg2, std::ostream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfGreaterThan(reg1, file);
}

void CodeGenerator::CompareLessThan(const string &reg1, const string &reg2, std::ostream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfLessThan(reg1, file);
}

void CodeGenerator::CompareGreaterThanOrEqual(const string &reg1, const string &reg2, std::ostream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfGreaterThanOrEqual(reg1, file);
}

void CodeGenerator::CompareLessThanOrEqual(const string &reg1, const string &reg2, std::ostream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfLessThanOrEqual(reg1, file);
}

std::string CodeGenerator::CreateNewLabel() {
    auto temp = "_lab" + std::to_string(_labelCount);
    _labelCount++;
    return temp;
}

void CodeGenerator::MarkLabel(const string &label, std::ostream & file) {
    file << label << ":\n";
}

void CodeGenerator::JumpIfEqual(const string &label, std::ostream &file) {
    file << "\tje\t\t" << label << "\n";
}

void CodeGenerator::JumpIfNotEqual(const string &label, std::ostream &file) {
    file << "\tjne\t\t" << label << "\n";
}

void CodeGenerator::JumpUnconditional(const string &label, std::ostream &file) {
    file << "\tjmp\t\t" << label << "\n";
}

void CodeGenerator::WriteFunctionPrologue(std::ostream &file) {
    PushRegisterToStack("ebp", file);
    CopyFromRegister("esp", "ebp", file);
}

void CodeGenerator::WriteFunctionEpilogue(std::ostream &file) {
    CopyFromRegister("ebp", "esp", file);
    PopRegisterFromStack("ebp", file);
}

void CodeGenerator::Map(const SymbolMap &smap) {
    delete _symbolMap;
    _symbolMap = new SymbolMap(smap);
}

void CodeGenerator::HandleDeclaration(const DeclarationNode &dnode, std::unordered_set<std::string> & current_context, std::ostream &file) {
    if (current_context.find(dnode.GetVariableName()) != current_context.end()) {
        throw CodeGenerationException("Variable already declared in this scope: " + dnode.GetVariableName());
    } else {
        _symbolMap->AddVariable(dnode.GetVariableName());
        current_context.insert(dnode.GetVariableName());
    }
    if (dnode.ChildCount()) Generate(dnode.Child(0), file);
    PushRegisterToStack("eax", file);
}

void CodeGenerator::HandleAssignment(const AssignmentNode &anode, std::ostream &file) {
    int stack_var = _symbolMap->FindVariable(anode.GetVariableName());
    if (stack_var == -1) {
        throw CodeGenerationException("Variable Assignment before Declaration: " + anode.GetVariableName());
    }
    Generate(anode.Child(0), file);
    Movl("%eax, " + std::to_string(-4 * stack_var) + "(%ebp)", file);
}

void CodeGenerator::HandleVariable(const VariableNode &vnode, std::ostream &file) {
    int stack_var = _symbolMap->FindVariable(vnode.GetVariableName());
    if (stack_var == -1) {
        throw CodeGenerationException("Variable used before declaration: " + vnode.GetVariableName());
    } else {
        Movl(std::to_string(-4 * stack_var) + "(%ebp), %eax", file);
    }
}

void CodeGenerator::Movl(const string &statement, std::ostream &file) {
    file << "\tmovl\t" << statement << "\n";
}

void CodeGenerator::HandleConditionalStatement(const ConditionalStatementNode &csnode, std::ostream &file) {
    auto end = CreateNewLabel();

    //generate decision expression
    Generate(csnode.Child(0), file);
    CompareWithZero("eax", file);

    //future proofing for when I can handle context blocks
    if (csnode.ChildCount() > 2) {
        auto jump = CreateNewLabel();
        JumpIfEqual(jump, file);
        Generate(csnode.Child(1), file);
        JumpUnconditional(end, file);
        MarkLabel(jump, file);
        Generate(csnode.Child(2), file);
    } else {
        JumpIfEqual(end, file);
        Generate(csnode.Child(1), file);
    }
    MarkLabel(end, file);
}

void CodeGenerator::HandleConditionalExpression(const ConditionalExpressionNode &cenode, std::ostream &file) {
    auto jump = CreateNewLabel();
    auto end = CreateNewLabel();

    //this type of expression is guaranteed to have 3 children
    //generate decision expression
    Generate(cenode.Child(0), file);
    CompareWithZero("eax", file);
    JumpIfEqual(jump, file);
    //generate first possible path
    Generate(cenode.Child(1), file);
    JumpUnconditional(end, file);
    MarkLabel(jump, file);
    //generate second possible path
    Generate(cenode.Child(2), file);
    MarkLabel(end, file);
}

void CodeGenerator::HandleBody(const BodyNode & bnode, std::ostream &file) {
    SymbolMap * context = new SymbolMap(*_symbolMap);

    auto curContext = std::unordered_set<std::string>();
    //go through the list of statements and declarations and handle them differently:
    //-pass Body the current symbol map if we encounter another compound statement for
    // other further declarations, assignments, and references
    //-pass Declaration the current symbol map to be updated as well as the
    // current set of declarations for the current context
    //-pass Assignment and Variable the symbol map for referencing to the stack locations
    //-otherwise fall back on the recursive Generate for other types of statements since
    // they don't need to use the symbol map or context set
    for (int i = 0; i < bnode.ChildCount(); i++) {
        auto child = bnode.Child(i);

        if (child->Type() == SyntaxType::Declaration) {
            HandleDeclaration(*(DeclarationNode *)child, curContext, file);
        } else {
            Generate(child, file);
        }
    }

    //replace the context if we saved it
    delete _symbolMap;
    _symbolMap = context;

}

