#ifndef COMPILERPROJECT_IFUNCTION_HPP
#define COMPILERPROJECT_IFUNCTION_HPP

#include "../Statements/BodyNode.hpp"
#include "../Functions/Parameters.hpp"

class IFunction {
public:
    IFunction();
    explicit IFunction(const std::string & toInit);
    bool ContainsBody() const;
    std::string & Name() const;
    Parameters & Params() const;
    BodyNode & Body() const;
    virtual ~IFunction();

protected:
    virtual BodyNode * BodyPtr() const = 0;
    virtual Parameters * ParamsPtr() const = 0;
    std::string * _name;
};

#endif //COMPILERPROJECT_IFUNCTION_HPP
