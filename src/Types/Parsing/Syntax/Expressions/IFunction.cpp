#include "IFunction.hpp"

IFunction::IFunction(): _name(new std::string()) {}

IFunction::IFunction(const std::string &toInit): _name(new std::string(toInit)) {}

bool IFunction::ContainsBody() const {
    return BodyPtr() != nullptr;
}

IFunction::~IFunction() {
    delete _name;
}

std::string &IFunction::Name() const {
    return *_name;
}

Parameters &IFunction::Params() const {
    return *ParamsPtr();
}

BodyNode &IFunction::Body() const {
    return *BodyPtr();
}
