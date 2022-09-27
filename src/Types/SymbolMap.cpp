#include "SymbolMap.hpp"

std::string SymbolMap::CurrentFunction;

SymbolMap::SymbolMap() : _functionMap(new std::unordered_map<std::string, FunctionInfoTable>()), _globalMap(new std::unordered_set<std::string>()), _globalScope(new std::unordered_set<std::string>()) {}
SymbolMap::~SymbolMap() {
    delete _functionMap;
    delete _globalScope;
    delete _globalMap;
}

/// Adds a variable to the symbol map
/// \param vname Variable_Reference name
/// \return if the variable is already in the map, we treat it as a redefinition and return the new place on the stack that it occupies\n
///  otherwise, we try to add it to the table and then return the stack index it occupies
int SymbolMap::AddVariable(const std::string &vname) {
    if (_functionMap && _globalScope) {
        if (FindVariable(vname) == -1) {
            _functionMap->at(CurrentFunction).variables.insert(std::make_pair(vname, 1 + _functionMap->at(CurrentFunction).variables.size()));
            return (int)_functionMap->at(CurrentFunction).variables.size();
        }
    }
    return -1;
}

void SymbolMap::AddFunction(const std::string &fname, bool setCur) {
    if (_functionMap && _globalScope) {
        if (_functionMap->find(fname) == _functionMap->end()) {
            _functionMap->insert(std::make_pair(fname, FunctionInfoTable()));
        }
    }
    if (setCur) CurrentFunction = fname;
}

/// Finds a named variable in the map
/// \param vname Variable_Reference name
/// \return If the named variable exists, returns the current stack index of that variable\n
///  if not, returns -1 (all stack indexes will be either 1 or greater)
int SymbolMap::FindVariable(const std::string &vname) const {
    if (_functionMap && _globalScope) {
        if (_functionMap->at(CurrentFunction).variables.find(vname) != _functionMap->at(CurrentFunction).variables.end()) {
            return _functionMap->at(CurrentFunction).variables[vname];
        }
    }
    return -1;
}

void SymbolMap::ContainsReturn(bool val) {
    if (_functionMap && _globalScope) _functionMap->at(CurrentFunction).containsReturn = val;
}

bool SymbolMap::ContainsReturn() const {
    if (_functionMap && _globalScope) return _functionMap->at(CurrentFunction).containsReturn;
    return false;
}

SymbolMap::SymbolMap(const SymbolMap &toCopy) {
    _functionMap = new std::unordered_map<std::string, FunctionInfoTable>(*toCopy._functionMap);
}

int SymbolMap::RedeclareVariable(const std::string &vname) {
    if (_functionMap && _globalScope) {
        if (FindVariable(vname) != -1) {
            _functionMap->at(CurrentFunction).variables[vname] = (int)_functionMap->at(CurrentFunction).variables.size() + 1;
            return (int)_functionMap->at(CurrentFunction).variables.size();
        }
    }
    return -1;
}

bool SymbolMap::FindFunction(const std::string &name) {
    if (!_functionMap) return false;
    return _functionMap->find(name) != _functionMap->end();
}

void SymbolMap::NumParams(int val) {
    if (_functionMap && _globalScope) _functionMap->at(CurrentFunction).numParams = val;
}

int SymbolMap::NumParams() {
    if (_functionMap && _globalScope) return _functionMap->at(CurrentFunction).numParams;
    return -1;
}

bool SymbolMap::BeenDefined() {
    if (_functionMap && _globalScope) return _functionMap->at(CurrentFunction).beenDefined;
    return false;
}

void SymbolMap::BeenDefined(bool val) {
    if (_functionMap && _globalScope) _functionMap->at(CurrentFunction).beenDefined = val;
}

void SymbolMap::AddParameter(const std::string &pname, int stackIndex) {
    if (_functionMap && _globalScope) {
        if (FindVariable(pname) == -1) {
            _functionMap->at(CurrentFunction).variables.insert(std::make_pair(pname, stackIndex));
        }
    }
}

std::vector<std::string> SymbolMap::FunctionVariableNames() {
    if (_functionMap && _globalScope) {
        auto toReturn = std::vector<std::string>();
        for (const auto& kvp : _functionMap->at(CurrentFunction).variables) {
            toReturn.push_back(kvp.first);
        }
        return toReturn;
    }
    return {};
}

void SymbolMap::AddGlobal(const std::string &gname) {
    if (_globalMap && _globalScope) {
        _globalMap->insert(gname);
        _globalScope->insert(gname);
    }
}

bool SymbolMap::FindGlobal(const std::string &gname) {
    if (_globalMap) return _globalMap->find(gname) != _globalMap->end();
    return false;
}
