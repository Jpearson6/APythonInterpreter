//
// Created by Ali Kooshesh on 4/4/23.
//

#ifndef APYTHONINTERPRETER_TOKEN_HPP
#define APYTHONINTERPRETER_TOKEN_HPP

#include<string>

class Token {

public:
    Token();

    bool &eof()  { return _eof; }
    bool &eol()  { return _eol; }

    bool eof() const { return _eof; }
    bool eol() const  { return _eol; }

    bool isOpenParen() const  { return _symbol == '('; }
    bool isCloseParen() const { return _symbol == ')'; }
    bool isOpenBraket() const  { return _symbol == '{'; }
    bool isCloseBraket() const { return _symbol == '}'; }
    bool isComa() const { return _symbol == ','; }

    void symbol(char c) { _symbol = c; }
    char symbol() { return _symbol; }

    void relationalSymbol(std::string s) { _relationalSymbol = s; }
    void integerDivision(std::string s) { _intDivision = s; }
    std::string relationalSymbol() { return "a"; }

    bool isSemiColon() const { return _symbol == ';'; }
    bool isAssignmentOperator() const              { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; }
    bool isAdditionOperator() const       { return _symbol == '+'; }
    bool isSubtractionOperator() const    { return _symbol == '-'; }
    bool isModuloOperator() const         { return _symbol == '%'; }
    bool isDivisionOperator() const       { return _symbol == '/'; }
    bool isIntegerDivision() const        { return _intDivision == "//"; }
    bool isArithmeticOperator() const {
        return isMultiplicationOperator() ||
               isAdditionOperator() ||
               isSubtractionOperator() ||
               isModuloOperator() ||
               isDivisionOperator();
    }
    bool isEquality() const { return _relationalSymbol == "=="; }
    bool isNotEqual() const { return _relationalSymbol == "!="; }
    bool isGreaterThan() const { return _symbol == '>'; }
    bool isLessThan() const { return _symbol == '<'; }
    bool isGreaterEqual() const { return _relationalSymbol == ">="; }
    bool isLessEqual() const { return _relationalSymbol == "<="; }
    bool isRelationalOperator() const {
        return isEquality() ||
               isNotEqual() ||
               isGreaterThan() ||
               isLessThan() ||
               isGreaterEqual() ||
               isLessEqual();
    }
    bool isName() const                   { return _name.length() > 0 && _name != "for" && _name != "print" && _isComment == false; }
    bool isKeyWord() const  { return _name == "for" || _name == "print"; }
    bool isFor() const { return _name == "for"; }
    bool isPrint() const { return _name == "print"; }

    std::string getName() const                  { return _name; }
    void setName(std::string n) { _name = n; }

    bool &isWholeNumber() { return _isWholeNumber; }
    bool isWholeNumber() const { return _isWholeNumber; }
    int getWholeNumber() const { return _wholeNumber; }
    void setWholeNumber(int n) {
        _wholeNumber = n;
        isWholeNumber() = true;
    }
    bool &isDoubleNumber() { return _isDoubleNumber; }
    bool isDoubleNumber() const {return _isDoubleNumber; }
    double getDoubleNumber() const { return _doubleNumber; }
    void setDoubleNumber(double d) {
        _doubleNumber = d;
        isDoubleNumber() = true;
    }
    bool &isStringValue() { return _isStringValue; }
    bool isStringValue() const { return _isStringValue; }

    bool &isComment() { return _isComment; }
    bool isComment() const { return _isComment; }


    void print() const;

private:
    std::string _name;
    bool _eof, _eol;
    bool _isWholeNumber;
    bool _isDoubleNumber;
    bool _isStringValue;
    bool _isComment;
    char _symbol;
    std::string _relationalSymbol;
    std::string _intDivision;
    int _wholeNumber;
    double _doubleNumber;
};


#endif //APYTHONINTERPRETER_TOKEN_HPP
