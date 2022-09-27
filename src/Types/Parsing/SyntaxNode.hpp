#ifndef COMPILERPROJECT_SYNTAXNODE_HPP
#define COMPILERPROJECT_SYNTAXNODE_HPP
#include <iostream>
#include <string>

enum class SyntaxType { None, Program,
        Function, Function_Call, Parameters, Parameter, Body,
        Statement, Return, Expression, Term,
        Factor, Constant,
        Unary_Operator, Binary_Operator,
        Declaration, Assignment, Variable_Reference,
        Conditional_Statement, Conditional_Expression,
        For_Loop, While_Loop, Do_While_Loop,
        Break, Continue, Global_Variable,
};

class SyntaxNode {

public:

    SyntaxNode();
    virtual ~SyntaxNode();
    SyntaxNode(const SyntaxNode & node);
    explicit SyntaxNode(SyntaxType stype);

    SyntaxNode * operator[](int i);
    SyntaxNode & Parent() const;
    SyntaxNode * Child(int i) const;

    void Parent(SyntaxNode * parent);

    void Add(SyntaxNode ** children, int childCount);
    void Add(SyntaxNode * child);

    void Remove(int i);
    void Remove(const SyntaxNode & child);
    void Remove(SyntaxNode * child);

    int IndexOf(const SyntaxNode & child) const;
    int IndexOf(SyntaxNode * child) const;

    bool ContainsChildType(SyntaxType stype) const;

    int ChildCount() const;
    bool operator==(const SyntaxNode & node) const;

    //for output, one centralized ostream operator, and one private function to turn the node into a string for output
    friend std::ostream & operator << (std::ostream & os, SyntaxNode & rhs);
    virtual std::string PrettyPrint() = 0;

    SyntaxType Type() const;

protected:

    int _childCount;
    SyntaxNode ** _children;
    SyntaxNode * _parent;

    SyntaxType _stype;

};

#endif //COMPILERPROJECT_SYNTAXNODE_HPP
