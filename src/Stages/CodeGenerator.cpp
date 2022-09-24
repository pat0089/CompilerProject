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
        case SyntaxType::For_Loop:
            HandleForLoop(*(ForLoopNode *)(snode), file);
            break;
        case SyntaxType::While_Loop:
            HandleWhileLoop(*(WhileLoopNode *)(snode), file);
            break;
        case SyntaxType::Do_While_Loop:
            HandleDoWhileLoop(*(DoWhileLoopNode *)(snode), file);
            break;
        case SyntaxType::Break:
            HandleBreak(*(BreakNode *)(snode), file);
            break;
        case SyntaxType::Continue:
            HandleContinue(*(ContinueNode *)(snode), file);
            break;
        case SyntaxType::None:
        case SyntaxType::Expression:
        case SyntaxType::Term:
        case SyntaxType::Factor:
        case SyntaxType::Declaration:
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
    if (rnode.Parent().Parent().Type() == SyntaxType::Function && _symbolMap) _symbolMap->ContainsReturn(true);
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
    if (op == OperatorType::Logical_AND || op == OperatorType::Logical_OR) {
        auto jump = CreateNewLabel();
        auto end = CreateNewLabel();
        Generate(bonode.Child(0), file);
        CompareWithZero(r0, file);
        if (op == OperatorType::Logical_AND) {
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

    if (requires_swap(bonode.GetOperator())) {
        Generate(bonode.Child(1), file);
        PushRegisterToStack(r0, file);
        Generate(bonode.Child(0), file);
        PopRegisterFromStack(r1, file);
    } else {
        Generate(bonode.Child(0), file);
        PushRegisterToStack(r0, file);
        Generate(bonode.Child(1), file);
        PopRegisterFromStack(r1, file);
    }

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
        case OperatorType::Modulo:
            ModuloRegisters(r0, r1, file);
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
        case OperatorType::Bitwise_AND:
            BitwiseAndRegisters(r0, r1, file);
            break;
        case OperatorType::Bitwise_XOR:
            BitwiseXorRegisters(r0, r1, file);
            break;
        case OperatorType::Bitwise_OR:
            BitwiseOrRegisters(r0, r1, file);
            break;
        case OperatorType::Bitwise_LShift:
            BitwiseLShiftRegisters(r0, r1, file);
            break;
        case OperatorType::Bitwise_RShift:
            BitwiseRShiftRegisters(r0, r1, file);
            break;
        default:
        case OperatorType::None:
            break;
    }
}

void CodeGenerator::LogicalNegateRegister(const string &reg, std::ostream &file) {
    CompareWithZero(reg, file);
    ZeroOutRegister(reg, file);
    SetIfEqual(reg, file);
}

void CodeGenerator::CompareEqual(const string &reg1, const string &reg2, std::ostream &file) {
    CompareRegisters(reg1, reg2, file);
    ZeroOutRegister(reg1, file);
    SetIfEqual(reg1, file);
}

void CodeGenerator::BitwiseAndRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    file << "\tand\t\t%" << reg2 << ", %" << reg1 << "\n";
}

void CodeGenerator::BitwiseOrRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    file << "\tor\t\t%" << reg2 << ", %" << reg1 << "\n";
}

void CodeGenerator::BitwiseXorRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    file << "\txor\t\t%" << reg2 << ", %" << reg1 << "\n";
}

void CodeGenerator::BitwiseLShiftRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    file << "\tshl\t\t%" << reg2[1] << "l, %" << reg1 << "\n";
}

void CodeGenerator::BitwiseRShiftRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    file << "\tshr\t\t%" << reg2[1] << "l, %" << reg1 << "\n";
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
    //generated constants with no context are null statements, so don't generate their values
    switch (cnode.Parent().Type()) {
        case SyntaxType::Body:
        case SyntaxType::For_Loop:
        case SyntaxType::While_Loop:
        case SyntaxType::Do_While_Loop:
            break;
        default:
            SetRegisterVal("eax", cnode.Value(), file);
            break;
    }
}

void CodeGenerator::SubtractRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    file << "\tsubl\t%" << reg2 << ", %"<< reg1 << "\n";
}

void CodeGenerator::DivideRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    file << "\tcdq\n";
    file << "\tidivl\t%" << reg2 << "\n";
}


void CodeGenerator::ModuloRegisters(const string &reg1, const string &reg2, std::ostream &file) {
    DivideRegisters(reg1, reg2, file);
    Movl("%edx, %" + reg1, file);
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
        if (_symbolMap->FindVariable(dnode.GetVariableName()) == -1) {
            _symbolMap->AddVariable(dnode.GetVariableName());
        } else {
            _symbolMap->RedeclareVariable(dnode.GetVariableName());
        }
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

    auto curScope = std::unordered_set<std::string>();
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
            HandleDeclaration(*(DeclarationNode *)child, curScope, file);
        } else {
            Generate(child, file);
        }
    }

    //replace the context because we saved it
    if (_symbolMap->ContainsReturn()) context->ContainsReturn(true);
    delete _symbolMap;
    _symbolMap = context;
    if ((int)curScope.size() && bnode.Parent().Type() != SyntaxType::Function) AddToRegister((int)curScope.size() * 4, "esp", file);
}

void CodeGenerator::AddToRegister(int value, const std::string & reg, std::ostream &file) {
    file << "\taddl\t$" << value << ", %" << reg << "\n";
}

CodeGenerator::~CodeGenerator() {
    delete _symbolMap;
}

void CodeGenerator::HandleContinue(const ContinueNode &cnode, std::ostream &file) {
    if (!_beginLoop.empty() && _endLoopBody.empty()) {
        JumpUnconditional(_beginLoop, file);
    } else if (!_endLoopBody.empty()) {
        JumpUnconditional(_endLoopBody, file);
    } else {
        throw CodeGenerationException("Break statement used outside of loop");
    }
}

void CodeGenerator::HandleBreak(const BreakNode &bnode, std::ostream &file) {
    if (!_endLoop.empty()) {
        JumpUnconditional(_endLoop, file);
    } else {
        throw CodeGenerationException("Continue statement used outside of loop");
    }
}

void CodeGenerator::HandleWhileLoop(const WhileLoopNode &wnode, std::ostream &file) {
    auto first = _beginLoop;
    auto second = _endLoop;

    //allocate labels for loop
    _beginLoop = CreateNewLabel();
    _endLoop = CreateNewLabel();

    MarkLabel(_beginLoop, file);

    Generate(wnode.Child(0), file);
    CompareWithZero("eax", file);
    JumpIfEqual(_endLoop, file);

    Generate(wnode.Child(1), file);

    JumpUnconditional(_beginLoop, file);

    MarkLabel(_endLoop, file);

    //reset labels at end of loop
    _beginLoop = first.empty() ? "": first;
    _endLoop = second.empty() ? "": second;
}

void CodeGenerator::HandleDoWhileLoop(const DoWhileLoopNode &dwnode, std::ostream &file) {
    auto first = _beginLoop;
    auto second = _endLoop;

    //allocate labels for loop
    _beginLoop = CreateNewLabel();
    _endLoop = CreateNewLabel();

    MarkLabel(_beginLoop, file);

    Generate(dwnode.Child(0), file);

    Generate(dwnode.Child(1), file);
    CompareWithZero("eax", file);
    JumpIfEqual(_endLoop, file);

    JumpUnconditional(_beginLoop, file);

    MarkLabel(_endLoop, file);

    //reset labels at end of loop
    _beginLoop = first.empty() ? "": first;
    _endLoop = second.empty() ? "": second;
}

void CodeGenerator::HandleForLoop(const ForLoopNode &fnode, std::ostream &file) {
    //allocate labels for loop
    auto first = _beginLoop;
    auto second = _endLoop;
    auto third = _endLoopBody;

    _beginLoop = CreateNewLabel();
    _endLoop = CreateNewLabel();
    _endLoopBody = CreateNewLabel();

    std::unordered_set<std::string> curScope;
    SymbolMap * context = new SymbolMap(*_symbolMap);

    if (fnode.Child(0)->Type() == SyntaxType::Declaration) {
        HandleDeclaration(*(DeclarationNode *)fnode.Child(0), curScope, file);
    } else {
        Generate(fnode.Child(0), file);
    }

    MarkLabel(_beginLoop, file);

    if (fnode.Child(1)->Type() == SyntaxType::Constant) {
        //this is to override the no output default from empty statement
        //so that for loops run forever if specified
        SetRegisterVal("eax", 1, file);
    } else {
        Generate(fnode.Child(1), file);
    }

    CompareWithZero("eax", file);
    JumpIfEqual(_endLoop, file);

    Generate(fnode.Child(3), file);

    //label the post-expression:
    MarkLabel(_endLoopBody, file);
    Generate(fnode.Child(2), file);

    JumpUnconditional(_beginLoop, file);

    MarkLabel(_endLoop, file);

    if ((int)curScope.size()) AddToRegister((int)curScope.size() * 4, "esp", file);

    //reset labels at end of loop
    _beginLoop = first.empty() ? "": first;
    _endLoop = second.empty() ? "": second;
    _endLoopBody = third.empty() ? "": third;

    delete _symbolMap;
    _symbolMap = context;

}

bool CodeGenerator::requires_swap(OperatorType otype) {
    return otype == OperatorType::Minus ||
    otype == OperatorType::Division || otype == OperatorType::Modulo ||
    otype == OperatorType::Bitwise_RShift || otype == OperatorType::Bitwise_LShift;
}
