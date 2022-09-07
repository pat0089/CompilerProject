#ifndef COMPILERPROJECT_IVARIABLE_HPP
#define COMPILERPROJECT_IVARIABLE_HPP
#include <string>

class IVariable {
public:
    explicit IVariable(const std::string & vname);
    std::string & GetVariableName() const;
protected:
    std::string * _vname = nullptr;
};


#endif //COMPILERPROJECT_IVARIABLE_HPP
