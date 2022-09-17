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
    //what does this do?
    // takes in an AST and generates the x86 assembly for it
public:

    void Generate(const AST & ast, const string & fname);
    void Map(const SymbolMap & smap);

private:

    //recursive generate call
    void Generate(SyntaxNode * snode, std::ostream & file);

    //write higher programmatic constructs
    void WriteFunctionName(const FunctionNode & fnode, std::ostream & file);
    void WriteFunctionPrologue(std::ostream & file);
    void WriteFunctionEpilogue(std::ostream & file);
    void WriteReturn(std::ostream & file);

    //register operations
    void HandleConstant(ConstantNode &cnode, std::ostream &file);
    void SwapRegisters(const std::string & reg1, const std::string & reg2, std::ostream & file);

    //unary operators
    void NegateRegister(const std::string & reg, std::ostream & file);
    void LogicalNegateRegister(const std::string & reg, std::ostream & file);
    void BitwiseComplementRegister(const std::string & reg, std::ostream &file);

    //binary operators
    void AddRegisters(const std::string & reg1, const std::string & reg2, std::ostream & file);
    void SubtractRegisters(const std::string & reg1, const std::string & reg2, std::ostream & file);
    void DivideRegisters(const std::string & reg1, const std::string & reg2, std::ostream & file);
    void MultiplyRegisters(const std::string & reg1, const std::string & reg2, std::ostream & file);

    void CompareEqual(const std::string & reg1, const std::string & reg2, std::ostream & file);
    void CompareNotEqual(const std::string & reg1, const std::string & reg2, std::ostream & file);
    void CompareGreaterThan(const std::string & reg1, const std::string & reg2, std::ostream & file);
    void CompareLessThan(const std::string & reg1, const std::string & reg2, std::ostream & file);
    void CompareGreaterThanOrEqual(const std::string & reg1, const std::string & reg2, std::ostream & file);
    void CompareLessThanOrEqual(const std::string & reg1, const std::string & reg2, std::ostream & file);


    //stack operations
    void PushRegisterToStack(const std::string & reg, std::ostream & file);
    void PopRegisterFromStack(const std::string & reg, std::ostream & file);

    //helper handler functions
    void HandleUnaryOperator(UnaryOperatorNode &uonode, std::ostream & file);
    void HandleBinaryOperator(const BinaryOperatorNode & bonode, std::ostream & file);


    //helper single-line functions
    void ZeroOutRegister(const std::string & reg, std::ostream & file);
    void CompareRegisters(const std::string & reg1, const std::string & reg2, std::ostream & file);
    void CompareRegisterVal(const std::string & reg, int val, std::ostream & file);
    void CompareWithZero(const std::string & reg, std::ostream & file);
    void SetIfEqual(const std::string & reg, std::ostream & file);
    void SetIfNotEqual(const std::string & reg, std::ostream & file);
    void SetIfLessThan(const std::string & reg, std::ostream & file);
    void SetIfGreaterThan(const std::string & reg, std::ostream & file);
    void SetIfLessThanOrEqual(const std::string & reg, std::ostream & file);
    void SetIfGreaterThanOrEqual(const std::string & reg, std::ostream & file);
    void SetRegisterVal(const std::string & reg, int val, std::ostream & file);
    void CopyFromRegister(const std::string & reg1, const std::string & reg2, std::ostream & file);
    void AddToRegister(int value, const std::string reg, std::ostream & file);

    void Movl(const std::string & statement, std::ostream & file);

    void JumpUnconditional(const std::string & label, std::ostream & file);
    void JumpIfEqual(const std::string & label, std::ostream & file);
    void JumpIfNotEqual(const std::string & label, std::ostream & file);

    //label functions
    static int _labelCount;
    std::string CreateNewLabel();
    void MarkLabel(const std::string & label, std::ostream & file);

    //std::unordered_map<std::string, FunctionInfoTable> _functionMap;
    SymbolMap * _symbolMap = nullptr;

    void HandleDeclaration(const DeclarationNode & dnode, std::unordered_set<std::string> & current_context, std::ostream &file);
    void HandleAssignment(const AssignmentNode & anode, std::ostream &file);
    void HandleVariable(const VariableNode & vnode, std::ostream &file);

    void HandleConditionalStatement(const ConditionalStatementNode & csnode, std::ostream &file);
    void HandleConditionalExpression(const ConditionalExpressionNode & cenode, std::ostream &file);

    void HandleFunction(const FunctionNode & fnode, std::ostream &file);

    void HandleBody(const BodyNode & bnode, std::ostream &file);

    void HandleReturn(const ReturnNode & rnode, std::ostream &file);
};


#endif //COMPILERPROJECT_CODEGENERATOR_HPP
