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

    void Generate(SyntaxNode * snode, std::ofstream & file);

    void WriteFunction(FunctionNode & fnode, std::ofstream & file);

    //register operations
    void WriteToRegister(const std::string & reg, ConstantNode & cnode, std::ofstream & file);
    void SwapRegisters(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void NegateRegister(const std::string & reg, std::ofstream & file);
    void LogicalNegateRegister(const std::string & reg, std::ofstream & file);
    void NotRegister(const std::string & reg, std::ofstream &file);
    void WriteReturn(std::ofstream & file);

    void AddRegisters(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void SubtractRegisters(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void DivideRegisters(const std::string & reg1, const std::string & reg2, std::ofstream & file);
    void MultiplyRegisters(const std::string & reg1, const std::string & reg2, std::ofstream & file);

    void PushRegisterToStack(const std::string & reg, std::ofstream & file);
    void PopRegisterFromStack(const std::string & reg, std::ofstream & file);

    void HandleUnaryOperator(UnaryOperatorNode &uonode, std::ofstream & file);
    void HandleBinaryOperator(const BinaryOperatorNode & bonode, std::ofstream & file);

};


#endif //COMPILERPROJECT_CODEGENERATOR_HPP
