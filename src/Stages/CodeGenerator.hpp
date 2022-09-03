#ifndef COMPILERPROJECT_CODEGENERATOR_HPP
#define COMPILERPROJECT_CODEGENERATOR_HPP
#include <functional>
#include "../Types/Parsing/AST.hpp"

class CodeGenerator {
    //what does this do?
    // takes in an AST and generates the x86 assembly for it
public:

    void Generate(const AST & ast, const string & fname);

private:

    //recursive generate call
    void Generate(SyntaxNode * snode, std::ofstream & file);

    //write higher programmatic constructs
    void WriteFunction(FunctionNode & fnode, std::ofstream & file);
    void WriteReturn(std::ofstream & file);

    //register operations
    void WriteToRegister(const std::string & reg, ConstantNode & cnode, std::ofstream & file);
    void SwapRegisters(const std::string & reg1, const std::string & reg2, std::ofstream & file);

    //unary operators
    void NegateRegister(const std::string & reg, std::ofstream & file);
    void LogicalNegateRegister(const std::string & reg, std::ofstream & file);
    void BitwiseComplementRegister(const std::string & reg, std::ofstream &file);

    //binary operators
    void AddRegisters(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void SubtractRegisters(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void DivideRegisters(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void MultiplyRegisters(const std::string & reg1, const std::string & reg2, std::ofstream & file);

    void CompareEqual(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void CompareNotEqual(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void CompareGreaterThan(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void CompareLessThan(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void CompareGreaterThanOrEqual(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void CompareLessThanOrEqual(const std::string & reg1, const std::string & reg2, std::ofstream & file);


    //stack operations
    void PushRegisterToStack(const std::string & reg, std::ofstream & file);
    void PopRegisterFromStack(const std::string & reg, std::ofstream & file);

    //helper handler functions
    void HandleUnaryOperator(UnaryOperatorNode &uonode, std::ofstream & file);
    void HandleBinaryOperator(const BinaryOperatorNode & bonode, std::ofstream & file);


    //helper single-line functions
    void ZeroOutRegister(const std::string & reg, std::ofstream & file);
    void CompareRegisters(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void CompareRegisterVal(const std::string & reg, int val, std::ofstream & file);
    void CompareWithZero(const std::string & reg, std::ofstream & file);
    void SetIfEqual(const std::string & reg, std::ofstream & file);
    void SetIfNotEqual(const std::string & reg, std::ofstream & file);
    void SetIfLessThan(const std::string & reg, std::ofstream & file);
    void SetIfGreaterThan(const std::string & reg, std::ofstream & file);
    void SetIfLessThanOrEqual(const std::string & reg, std::ofstream & file);
    void SetIfGreaterThanOrEqual(const std::string & reg, std::ofstream & file);
    void SetRegisterVal(const std::string & reg, int val, std::ofstream & file);
    void CopyFromRegister(const std::string & reg1, const std::string & reg2, std::ofstream & file);

    void JumpUnconditional(const std::string & label, std::ofstream & file);
    void JumpIfEqual(const std::string & label, std::ofstream & file);
    void JumpIfNotEqual(const std::string & label, std::ofstream & file);

    //label functions
    static int _labelCount;
    std::string & CreateNewLabel();
    void MarkLabel(const std::string & label, std::ofstream & file);

};


#endif //COMPILERPROJECT_CODEGENERATOR_HPP
