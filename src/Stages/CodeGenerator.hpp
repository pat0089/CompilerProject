#ifndef COMPILERPROJECT_CODEGENERATOR_HPP
#define COMPILERPROJECT_CODEGENERATOR_HPP
#include <unordered_set>
#include "../Types/Parsing/AST.hpp"
#include "../Types/SymbolMap.hpp"

class CodeGenerationException : public std::exception {
public:
    explicit CodeGenerationException(const std::string & msg) : message("CodeGenerationException: " + msg) {}
    const char * what() {
        return message.c_str();
    }
private:
    std::string message;
};

class CodeGenerator {
public:
    ~CodeGenerator();
    void Generate(const AST & ast, const string & fname);
    void Map(const SymbolMap & smap);

private:
    //recursive generate call
    void Generate(SyntaxNode * snode, std::ostream & file);

    //write higher programmatic constructs
    static void WriteFunctionName(const FunctionNode & fnode, std::ostream & file);
    static void WriteFunctionPrologue(std::ostream & file);
    static void WriteFunctionEpilogue(std::ostream & file);
    static void WriteReturn(std::ostream & file);

    //unary operators
    static void NegateRegister(const std::string & reg, std::ostream & file);
    static void LogicalNegateRegister(const std::string & reg, std::ostream & file);
    static void BitwiseComplementRegister(const std::string & reg, std::ostream &file);

    //binary operators
    static void AddRegisters(const std::string & reg1, const std::string & reg2, std::ostream & file);
    static void SubtractRegisters(const std::string & reg1, const std::string & reg2, std::ostream & file);
    static void DivideRegisters(const std::string & reg1, const std::string & reg2, std::ostream & filestatic );
    static void MultiplyRegisters(const std::string & reg1, const std::string & reg2, std::ostream & file);
    static void ModuloRegisters(const string &reg1, const string &reg2, std::ostream &file);

    static void CompareEqual(const std::string & reg1, const std::string & reg2, std::ostream & file);
    static void CompareNotEqual(const std::string & reg1, const std::string & reg2, std::ostream & file);
    static void CompareGreaterThan(const std::string & reg1, const std::string & reg2, std::ostream & file);
    static void CompareLessThan(const std::string & reg1, const std::string & reg2, std::ostream & file);
    static void CompareGreaterThanOrEqual(const std::string & reg1, const std::string & reg2, std::ostream & file);
    static void CompareLessThanOrEqual(const std::string & reg1, const std::string & reg2, std::ostream & file);

    static void BitwiseAndRegisters(const string &reg1, const string &reg2, std::ostream &file);
    static void BitwiseOrRegisters(const string &reg1, const string &reg2, std::ostream &file);
    static void BitwiseXorRegisters(const string &reg1, const string &reg2, std::ostream &file);
    static void BitwiseLShiftRegisters(const string &reg1, const string &reg2, std::ostream &file);
    static void BitwiseRShiftRegisters(const string &reg1, const string &reg2, std::ostream &file);

    //stack operations
    static void PushRegisterToStack(const std::string & reg, std::ostream & filestatic );
    static void PopRegisterFromStack(const std::string & reg, std::ostream & file);

    //helper handler functions
    static void HandleConstant(ConstantNode &cnode, std::ostream &file);

    void HandleUnaryOperator(const UnaryOperatorNode &uonode, std::ostream & file);
    void HandleBinaryOperator(const BinaryOperatorNode & bonode, std::ostream & file);

    void HandleParameters(const Parameters &pnode, std::ostream &file);
    void HandleParameter(const ParameterNode &pnode, int index);
    void HandleGlobal(const GlobalNode &gnode, std::ostream &file);
    void HandleFunction(const FunctionNode & fnode, std::ostream &file);
    void HandleFunctionCall(const FunctionCallNode &fcnode, std::ostream &file);

    void HandleDeclaration(const DeclarationNode & dnode, std::unordered_set<std::string> & current_context, std::ostream &file);
    void HandleAssignment(const AssignmentNode & anode, std::ostream &file);
    void HandleVariableReference(const VariableReferenceNode & vnode, std::ostream &file);

    void HandleConditionalStatement(const ConditionalStatementNode & csnode, std::ostream &file);
    void HandleConditionalExpression(const ConditionalExpressionNode & cenode, std::ostream &file);

    void HandleBody(const BodyNode & bnode, std::ostream &file);
    void HandleReturn(const ReturnNode & rnode, std::ostream &file);

    void HandleContinue(const ContinueNode &cnode, std::ostream &file);
    void HandleBreak(const BreakNode &bnode, std::ostream &file);

    void HandleForLoop(const ForLoopNode &fnode, std::ostream &file);
    void HandleWhileLoop(const WhileLoopNode &wnode, std::ostream &file);
    void HandleDoWhileLoop(const DoWhileLoopNode &dwnode, std::ostream &file);


    //helper single-line functions
    static void ZeroOutRegister(const std::string & reg, std::ostream & file);
    static void CompareRegisters(const std::string & reg1, const std::string & reg2, std::ostream & file);
    static void CompareRegisterVal(const std::string & reg, int val, std::ostream & file);
    static void CompareWithZero(const std::string & reg, std::ostream & file);

    static void JumpUnconditional(const std::string & label, std::ostream & file);
    static void JumpIfEqual(const std::string & label, std::ostream & file);
    static void JumpIfNotEqual(const std::string & label, std::ostream & file);

    static void SetIfEqual(const std::string & reg, std::ostream & file);
    static void SetIfNotEqual(const std::string & reg, std::ostream & file);
    static void SetIfLessThan(const std::string & reg, std::ostream & file);
    static void SetIfGreaterThan(const std::string & reg, std::ostream & file);
    static void SetIfLessThanOrEqual(const std::string & reg, std::ostream & file);
    static void SetIfGreaterThanOrEqual(const std::string & reg, std::ostream & file);

    static void SetRegisterVal(const std::string & reg, int val, std::ostream & file);
    static void CopyFromRegister(const std::string & reg1, const std::string & reg2, std::ostream & file);
    static void AddToRegister(int value, const std::string & reg, std::ostream & file);

    static void CallFunction(const string &fname, std::ostream &file);
    static void MarkGlobalSymbol(const string &gsname, std::ostream &file);
    void OutputGlobals(std::ostream &file);

    static void Movl(const std::string & statement, std::ostream & file);

    //label functions
    static int _labelCount;
    static std::string CreateNewLabel();
    static void MarkLabel(const std::string & label, std::ostream & file);

    //std::unordered_map<std::string, FunctionInfoTable> _functionMap;
    SymbolMap * _symbolMap = nullptr;

    std::string _beginLoop;
    std::string _endLoop;
    std::string _endLoopBody;

    static bool requires_swap(OperatorType otype);

};


#endif //COMPILERPROJECT_CODEGENERATOR_HPP
