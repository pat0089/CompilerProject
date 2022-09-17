#include "SymbolMap.hpp"

std::string SymbolMap::CurrentFunction = "";

SymbolMap::SymbolMap() : _functionMap(new std::unordered_map<std::string, FunctionInfoTable>()) {}
SymbolMap::~SymbolMap() { delete _functionMap; }

/// Adds a variable to the symbol map
/// \param vname Variable name
/// \return if the variable is already in the map, we treat it as a redefinition and return the new place on the stack that it occupies\n
///  otherwise, we try to add it to the table and then return the stack index it occupies
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

/// Finds a named variable in the map
/// \param vname Variable name
/// \return If the named variable exists, returns the current stack index of that variable\n
///  if not, returns -1 (all stack indexes will be either 1 or greater)
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

SymbolMap::SymbolMap(const SymbolMap &toCopy) {
    _functionMap = new std::unordered_map<std::string, FunctionInfoTable>(*toCopy._functionMap);
}

int SymbolMap::RedeclareVariable(const std::string &vname) {
    if (_functionMap) {
        if (FindVariable(vname) != -1) {
            _functionMap->at(CurrentFunction).variables[vname] = (int)_functionMap->at(CurrentFunction).variables.size() + 1;
            return (int)_functionMap->at(CurrentFunction).variables.size();
        }
    }
    return -1;
}
