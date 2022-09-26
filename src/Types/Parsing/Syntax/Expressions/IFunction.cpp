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
    //TODO: throw an exception if null; should work for now so long as I use ContainsBody before accessing Body
    //(functions will always have a parameters node, but the children will be interpreted differently depending on the context

    //throw std::exception();
}
