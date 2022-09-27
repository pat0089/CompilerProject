#ifndef COMPILERPROJECT_SYMBOLMAP_HPP
#define COMPILERPROJECT_SYMBOLMAP_HPP
#include <unordered_map>
#include <string>
#include <vector>
#include <unordered_set>

struct FunctionInfoTable {
    int numParams = -1;
    std::unordered_map<std::string, int> variables;
    bool beenDefined = false;
    bool containsReturn = false;
};

class SymbolMap {
public:
    SymbolMap();
    SymbolMap(const SymbolMap & toCopy);
    ~SymbolMap();

    void AddFunction(const std::string & fname, bool setCur = false);
    bool FindFunction(const std::string &name);

    void AddGlobal(const std::string & gname);
    bool FindGlobal(const std::string & gname);

    int AddVariable(const std::string & vname);
    int RedeclareVariable(const std::string & vname);
    void AddParameter(const std::string & pname, int stackIndex);
    int FindVariable(const std::string & vname) const;

    void BeenDefined(bool val);
    bool BeenDefined();

    void NumParams(int val);
    int NumParams();

    void ContainsReturn(bool val);
    bool ContainsReturn() const;

    std::vector<std::string> FunctionVariableNames();

    static std::string CurrentFunction;
    bool containsMain;

private:
    std::unordered_map<std::string, FunctionInfoTable> * _functionMap = nullptr;
    std::unordered_set<std::string> * _globalMap = nullptr;
    std::unordered_set<std::string> * _globalScope = nullptr;
};


#endif //COMPILERPROJECT_SYMBOLMAP_HPP
