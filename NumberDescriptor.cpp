//
// Created by jtonk on 4/25/2023.
//
#include "NumberDescriptor.hpp"
#include<iostream>


TypeDescriptor TypeDescriptor::operator+(TypeDescriptor b) {

    if (this->type() == TypeDescriptor::INTEGER && b.type() == TypeDescriptor::INTEGER) {
        auto *desc = new TypeDescriptor(TypeDescriptor::INTEGER);
        desc->value.intValue = this->value.intValue + b.value.intValue;

        return *desc;
    }
}

std::ostream & operator<<(std::ostream &out, TypeDescriptor& typeDesc) {
    TypeDescriptor *desc = dynamic_cast<TypeDescriptor *>(&typeDesc);

    if (desc->type() == TypeDescriptor::INTEGER) {
        out << desc->value.intValue;
        return out;
    }
    else if ( desc->type() == TypeDescriptor::STRING) {
        out << desc->stringValue;
        return out;
    }
    else {
        out << desc->value.doubleValue;
        return out;
    }
}

int TypeDescriptor::getIntValue() {
    return value.intValue;
}

double TypeDescriptor::getDouValue() {
    return value.doubleValue;
}

std::string TypeDescriptor::getStrValue() {
    return stringValue;
}

void TypeDescriptor::setValue(int num) {
    value.intValue = num;
}

void TypeDescriptor::setValue(double dou) {
    value.doubleValue = dou;
}

void TypeDescriptor::setValue(std::string str) {
    stringValue = str;
}


