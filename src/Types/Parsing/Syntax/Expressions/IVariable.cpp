#include "IVariable.hpp"

IVariable::IVariable(const std::string &vname) : _vname(new std::string(vname)) {}
std::string &IVariable::GetVariableName() const { return *_vname; }
IVariable::~IVariable() { delete _vname; }
