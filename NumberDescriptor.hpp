//
// Created by jtonk on 4/25/2023.
//

#ifndef APYTHONINTERPRETER_NUMBERDESCRIPTOR_HPP
#define APYTHONINTERPRETER_NUMBERDESCRIPTOR_HPP


#include <string>

struct TypeDescriptor {
// The base class for datatype descriptors.
// This enum can expand to include additional types.
    enum types {INTEGER, DOUBLE, STRING};
    TypeDescriptor() = default;
    TypeDescriptor(types type): _type{type} {}
    types &type() { return _type; }
    virtual ~TypeDescriptor() = default;
    TypeDescriptor operator+(TypeDescriptor b);
    friend std::ostream& operator<<(std::ostream &out, TypeDescriptor& typeDesc);
    int getIntValue();
    double getDouValue();
    std::string getStrValue();
    void setValue(int num);
    void setValue(double dou);
    void setValue(std::string str);

private:
    types _type;
    union {
        int intValue;
        double doubleValue;
    } value;
    std::string stringValue = "";
};


#endif //APYTHONINTERPRETER_NUMBERDESCRIPTOR_HPP
