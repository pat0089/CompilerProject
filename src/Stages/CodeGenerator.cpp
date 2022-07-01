#include "CodeGenerator.hpp"
#include <fstream>

void CodeGenerator::Generate(const AST &ast, const string & fname) {
    std::ofstream fout;
    //maybe do path finding for this?
    fout.open(fname);
    Generate(ast.Program(), fout);
}

void CodeGenerator::Generate(SyntaxNode & snode, std::ofstream & file) {
    for (int i = 0; i < snode.ChildCount(); i++) {
        Generate(snode[i], file);
    }

}
