#include "SymbolMap.hpp"

std::string SymbolMap::CurrentFunction;

/// Default Constructor
/// initializes an empty map for symbols to be added to
SymbolMap::SymbolMap() : _functionMap(new std::unordered_map<std::string, FunctionInfoTable>()), _globalMap(new std::unordered_map<std::string, int>()), _globalScope(new std::unordered_set<std::string>()), containsMain(false) {}

/// Destructor
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

/// Add a function to the global symbol map
/// \param fname Name of the function
/// \param setCur whether or not to set the current function context in the symbol map
/// NOTE: the name here has to be unique from all of the global symbols (global names too)
void SymbolMap::AddFunction(const std::string &fname, bool setCur) {
    if (_functionMap && _globalScope) {
        if (_globalScope->find(fname) == _globalScope->end()) {
            _functionMap->insert(std::make_pair(fname, FunctionInfoTable()));
            _globalScope->insert(fname);
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

/// Set whether or not the current function contains a return function
/// \param val Value to set to
void SymbolMap::ContainsReturn(bool val) {
    if (_functionMap && _globalScope) _functionMap->at(CurrentFunction).containsReturn = val;
}

/// Get whether the current function contains a return or not.
/// \return whether or not the current function contains a return statement
bool SymbolMap::ContainsReturn() const {
    if (_functionMap && _globalScope) return _functionMap->at(CurrentFunction).containsReturn;
    return false;
}

/// Copy Constructor
SymbolMap::SymbolMap(const SymbolMap &toCopy) {
    _functionMap = new std::unordered_map<std::string, FunctionInfoTable>(*toCopy._functionMap);
    _globalScope = new std::unordered_set<std::string>(*toCopy._globalScope);
    _globalMap = new std::unordered_map<std::string, int>(*toCopy._globalMap);
    containsMain = toCopy.containsMain;
}

/// Redeclare the stack index of a variable already in the SymbolMap for the current function
/// \param vname Name of variable to redeclare
/// \return the new stack index of the variable
int SymbolMap::RedeclareVariable(const std::string &vname) {
    if (_functionMap && _globalScope) {
        if (FindVariable(vname) != -1) {
            _functionMap->at(CurrentFunction).variables[vname] = (int)_functionMap->at(CurrentFunction).variables.size() + 1;
            return (int)_functionMap->at(CurrentFunction).variables.size();
        }
    }
    return -1;
}

/// Finds whether or not a function exists in the current SymbolMap
/// \param name Name of function to find
/// \return whether or not the named function exists in the map
bool SymbolMap::FindFunction(const std::string &name) {
    if (!_functionMap) return false;
    return _functionMap->find(name) != _functionMap->end();
}

/// Set the number of parameters of the current function
/// \param val Value to set to
void SymbolMap::NumParams(int val) {
    if (_functionMap && _globalScope) _functionMap->at(CurrentFunction).numParams = val;
}

/// Get the number of parameters of the current function
/// \return the number of parameters of the current function
int SymbolMap::NumParams() {
    if (_functionMap && _globalScope) return _functionMap->at(CurrentFunction).numParams;
    return -1;
}

/// Get whether or not the current function's body has been defined
/// \return whether or not the current function's body has been defined
bool SymbolMap::BeenDefined() {
    if (_functionMap && _globalScope) return _functionMap->at(CurrentFunction).beenDefined;
    return false;
}

/// Set whether or not the current function's body has been defined
/// \param val Value to set to
void SymbolMap::BeenDefined(bool val) {
    if (_functionMap && _globalScope) _functionMap->at(CurrentFunction).beenDefined = val;
}

/// Add a parameter with the given name and stack index to the current function's variable map
/// \param pname Name of the parameter
/// \param stackIndex Stack index to set to
void SymbolMap::AddParameter(const std::string &pname, int stackIndex) {
    if (_functionMap && _globalScope) {
        if (FindVariable(pname) == -1) {
            _functionMap->at(CurrentFunction).variables.insert(std::make_pair(pname, stackIndex));
        }
    }
}

/// Gets a vector of names from the current function's variable map
/// \return List of variable names
std::vector<std::string> SymbolMap::GetFunctionVariableNames() {
    if (_functionMap && _globalScope) {
        auto toReturn = std::vector<std::string>();
        for (const auto& kvp : _functionMap->at(CurrentFunction).variables) {
            toReturn.push_back(kvp.first);
        }
        return toReturn;
    }
    return {};
}

/// Add a named global to the map of globals
/// \param gname Name of global
/// \param val Value to set to
/// NOTE: the name here has to be unique from all of the global symbols (function names too)
void SymbolMap::AddGlobal(const std::string &gname, int val) {
    if (_globalMap && _globalScope) {
        if (_globalScope->find(gname) == _globalScope->end()) {
            _globalMap->insert(std::make_pair(gname, val));
            _globalScope->insert(gname);
        }
    }
}

/// Find a named global in the global map
/// \param gname Name of global
/// \return whether or not the named global exists in the map
bool SymbolMap::FindGlobal(const std::string &gname) const {
    if (_globalMap) return _globalMap->find(gname) != _globalMap->end();
    return false;
}

/// Get the value of an existing global in the global map
/// \param gname Name of global
/// \return Value of global in map
int SymbolMap::GetGlobal(const std::string &gname) const {
    if (_globalMap) return _globalMap->at(gname);
    return 0;
}

/// Set the value of a global in the symbol map
/// \param gname Name of global
/// \param val Value to set to
void SymbolMap::SetGlobal(const std::string &gname, int val) {
    if (_globalMap) _globalMap->at(gname) = val;
}

/// Get the pairs of names and initialized values from the global map
/// \return the list of name-value pairs
std::vector<std::pair<std::string, int>> SymbolMap::GetGlobals() {
    auto toReturn = std::vector<std::pair<std::string, int>>();
    if (_globalMap) {
        for (const auto &kvp: *_globalMap) {
            if (kvp.second) toReturn.emplace_back(kvp);
        }
    }
    return toReturn;
}

/// Get the list of names of uninitialized globals from the global map
/// \return list of names
std::vector<std::string> SymbolMap::GetUninitializedGlobals() {
    auto toReturn = std::vector<std::string>();
    if (_globalMap) {
        for (const auto &kvp: *_globalMap) {
            if (!kvp.second) toReturn.emplace_back(kvp.first);
        }
    }
    return toReturn;
}
