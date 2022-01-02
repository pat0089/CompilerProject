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
        )

set(HEADER_FILES
        src/Types/Lexing/Tokens/Token.hpp
        src/Compiler.hpp
        src/Stages/Lexer.hpp
        src/Types/Parsing/AST.hpp
        src/Stages/Parser.hpp
        src/Types/Parsing/SyntaxNode.hpp
        src/Types/Parsing/Syntax/Functions/ProgramNode.hpp
        src/Types/Parsing/Syntax/Functions/FunctionNode.hpp
        src/Types/Parsing/Syntax/Expressions/ConstantNode.hpp
        src/Types/Parsing/Syntax/Expressions/ExpressionNode.hpp
        src/Types/Parsing/Syntax/Statements/ReturnNode.hpp
        src/Types/Parsing/Syntax/Statements/StatementNode.hpp
        src/Types/Parsing/Syntax/Functions/Parameters.hpp
        src/Types/Parsing/Syntax/Functions/ParameterNode.hpp
        src/Types/Parsing/Syntax/Statements/BodyNode.hpp
        src/Types/Lexing/TokenList.hpp
        src/Types/Lexing/Tokens/Keyword.hpp
        src/Types/Lexing/Tokens/Symbol.hpp
        src/Types/Lexing/Tokens/Literal.hpp
        src/Types/Lexing/Tokens/Identifier.hpp
        )

add_executable(CompilerProject ${SOURCE_FILES})
