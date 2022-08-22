#include "ParameterNode.hpp"
using std::string;

ParameterNode::ParameterNode() {
    _stype = SyntaxType::Parameters;
}

string ParameterNode::PrettyPrint() {
    return string("Parameter");
}