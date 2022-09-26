#ifndef COMPILERPROJECT_IVARIABLE_HPP
#define COMPILERPROJECT_IVARIABLE_HPP
#include <string>

class IVariable {
public:
    IVariable();
    explicit IVariable(const std::string & vname);
    ~IVariable();
    std::string & GetVariableName() const;
protected:
    std::string * _vname = nullptr;
};


#endif //COMPILERPROJECT_IVARIABLE_HPP
