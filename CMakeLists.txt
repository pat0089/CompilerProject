project(CompilerProject)

cmake_minimum_required(VERSION 3.16)
project(CompilerProject)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        src/Types/Lexing/Tokens/Token.cpp
        src/Compiler.cpp
        src/Stages/Lexer.cpp
        src/Types/Parsing/AST.cpp
        src/Stages/Parser.cpp
        src/Types/Parsing/SyntaxNode.cpp
        src/Types/Parsing/Syntax/Functions/ProgramNode.cpp
        src/Types/Parsing/Syntax/Functions/FunctionNode.cpp
        src/Types/Parsing/Syntax/Expressions/ConstantNode.cpp
        src/Types/Parsing/Syntax/Expressions/ExpressionNode.cpp
        src/Types/Parsing/Syntax/Statements/ReturnNode.cpp
        src/Types/Parsing/Syntax/Statements/StatementNode.cpp
        src/Types/Parsing/Syntax/Functions/Parameters.cpp
        src/Types/Parsing/Syntax/Functions/ParameterNode.cpp
        src/Types/Parsing/Syntax/Statements/BodyNode.cpp
        src/Types/Lexing/TokenList.cpp
        src/Types/Lexing/Tokens/Keyword.cpp
        src/Types/Lexing/Tokens/Symbol.cpp
        src/Types/Lexing/Tokens/Literal.cpp
        src/Types/Lexing/Tokens/Identifier.cpp
        src/Stages/CodeGenerator.cpp
        src/Types/Parsing/Syntax/Expressions/UnaryOperatorNode.cpp
        src/Types/Parsing/Syntax/Expressions/TermNode.cpp
        src/Types/Parsing/Syntax/Expressions/FactorNode.cpp
        src/Types/Parsing/Syntax/Expressions/BinaryOperatorNode.cpp
        src/Types/Parsing/Syntax/Expressions/IOperator.cpp
        src/Types/Parsing/Syntax/Statements/DeclarationNode.cpp
        src/Types/Parsing/Syntax/Expressions/VariableReferenceNode.cpp
        src/Types/Parsing/Syntax/Expressions/IVariable.cpp
        src/Types/Parsing/Syntax/Statements/AssignmentNode.cpp
        src/Types/Parsing/Syntax/Statements/ConditionalStatementNode.cpp
        src/Types/Parsing/Syntax/Expressions/ConditionalExpressionNode.cpp
        src/Types/SymbolMap.cpp
        src/Types/Parsing/Syntax/Statements/ForLoopNode.cpp src/Types/Parsing/Syntax/Statements/ForLoopNode.hpp src/Types/Parsing/Syntax/Statements/WhileLoopNode.cpp src/Types/Parsing/Syntax/Statements/WhileLoopNode.hpp src/Types/Parsing/Syntax/Statements/DoWhileLoopNode.cpp src/Types/Parsing/Syntax/Statements/DoWhileLoopNode.hpp src/Types/Parsing/Syntax/Statements/BreakNode.cpp src/Types/Parsing/Syntax/Statements/BreakNode.hpp src/Types/Parsing/Syntax/Statements/ContinueNode.cpp src/Types/Parsing/Syntax/Statements/ContinueNode.hpp src/Types/Parsing/Syntax/Expressions/FunctionCallNode.cpp src/Types/Parsing/Syntax/Expressions/FunctionCallNode.hpp src/Types/Parsing/Syntax/Expressions/IFunction.cpp src/Types/Parsing/Syntax/Expressions/IFunction.hpp src/Types/Parsing/Syntax/Functions/GlobalNode.cpp src/Types/Parsing/Syntax/Functions/GlobalNode.hpp)
add_executable(CompilerProject ${SOURCE_FILES})

set_target_properties(CompilerProject PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    VS_DEBUGGER_COMMAND_ARGUMENTS "res/return_2.txt"
)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/res
        ${PROJECT_BINARY_DIR}/res
        COMMENT "Copying resources (/res) to binary directory"
)

add_dependencies(CompilerProject copy_resources)