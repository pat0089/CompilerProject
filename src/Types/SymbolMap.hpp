#ifndef COMPILERPROJECT_SYMBOLMAP_HPP
#define COMPILERPROJECT_SYMBOLMAP_HPP
#include <unordered_map>
#include <string>

class FunctionInfoTable {
public:
    std::unordered_map<std::string, int> variables;
    bool containsReturn = false;
};

class SymbolMap {
public:
    SymbolMap();
    SymbolMap(const SymbolMap & toCopy);
    ~SymbolMap();

    void AddFunction(const std::string & fname, bool setCur = false);
    bool FindFunction(const std::string &name);

    int AddVariable(const std::string & vname);
    int RedeclareVariable(const std::string & vname);
    int FindVariable(const std::string & vname) const;

    void ContainsReturn(bool val);
    bool ContainsReturn() const;

    static std::string CurrentFunction;

private:
    std::unordered_map<std::string, FunctionInfoTable> * _functionMap = nullptr;
};


#endif //COMPILERPROJECT_SYMBOLMAP_HPP
