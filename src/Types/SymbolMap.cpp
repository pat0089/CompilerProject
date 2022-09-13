#include "SymbolMap.hpp"

std::string SymbolMap::CurrentFunction = "";

SymbolMap::SymbolMap() : _functionMap(new std::unordered_map<std::string, FunctionInfoTable>()) {}
SymbolMap::~SymbolMap() { delete _functionMap; }

int SymbolMap::AddVariable(const std::string &vname) {
    if (_functionMap) {
        if (FindVariable(vname) == -1) {
            _functionMap->at(CurrentFunction).variables.insert(std::make_pair(vname, 1 + _functionMap->at(CurrentFunction).variables.size()));
            return (int)_functionMap->at(CurrentFunction).variables.size();
        }
    }
    return -1;
}

void SymbolMap::AddFunction(const std::string &fname, bool setCur) {
    if (_functionMap) {
        if (_functionMap->find(fname) == _functionMap->end()) {
            _functionMap->insert(std::make_pair(fname, FunctionInfoTable()));
        }
    }
    if (setCur) CurrentFunction = fname;
}

int SymbolMap::FindVariable(const std::string &vname) const {
    if (_functionMap) {
        if (_functionMap->at(CurrentFunction).variables.find(vname) != _functionMap->at(CurrentFunction).variables.end()) {
            return _functionMap->at(CurrentFunction).variables[vname];
        }
    }
    return -1;
}

void SymbolMap::ContainsReturn(bool val) {
    if (_functionMap) _functionMap->at(CurrentFunction).containsReturn = val;
}

bool SymbolMap::ContainsReturn() const {
    if (_functionMap) return _functionMap->at(CurrentFunction).containsReturn;
    return false;
}
