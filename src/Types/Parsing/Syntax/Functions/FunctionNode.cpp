#include "FunctionNode.hpp"
using std::string;

string & FunctionNode::Name() const {
    return *_name;
}

FunctionNode::FunctionNode(string toInit) {
    _name = new string(toInit);
}

string FunctionNode::PrettyPrint() {
    return string("Function: ") + *_name;
}

Parameters &FunctionNode::Params() const {
    return *(Parameters *)_children[0];
}

BodyNode &FunctionNode::Body() const {
    return *(BodyNode *)_children[1];
}
