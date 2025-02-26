//
// Created by Ali Kooshesh on 4/4/23.
//

#include <iostream>
#include "Token.hpp"

Token::Token(): _name{""}, _eof{false}, _eol{false}, _symbol{'\0'}, _isWholeNumber{false}, _isDoubleNumber{false}, _isStringValue{false}, _isComment{false} {}

void Token::print() const {
    if( eol() ) std::cout << "EOL\n" ;
    else if( eof() )                    std::cout << "EOF" ;
    else if( isOpenParen() )  std::cout << "(" ;
    else if( isCloseParen() )  std::cout << ")" ;
    else if( isOpenBraket() )  std::cout << "{" ;
    else if( isCloseBraket() )  std::cout << "}" ;
    else if( isAssignmentOperator() )  std::cout << " = " ;
    else if( isSemiColon() )  std::cout << ";" ;
    else if( isComa() ) std::cout << "," ;
    else if( isMultiplicationOperator() )  std::cout << " * " ;
    else if( isAdditionOperator() )  std::cout << " + " ;
    else if( isSubtractionOperator() )  std::cout << " - " ;
    else if( isModuloOperator() )  std::cout << " % " ;
    else if( isDivisionOperator() )  std::cout << " / " ;
    else if( isIntegerDivision() )  std::cout << " // " ;
    else if ( isStringValue() ) std::cout << "\"" + getName() + "\"";
    else if( isName() )  std::cout << getName();
    else if( isKeyWord() ) std::cout << getName();
    else if( isComment() ) std::cout << getName();
    else if( isWholeNumber() ) std::cout << getWholeNumber();
    else if ( isDoubleNumber() ) std::cout << getDoubleNumber();
    else if( isEquality() ) std:: cout << " == ";
    else if ( isNotEqual() ) std:: cout << " != ";
    else if ( isGreaterThan() ) std:: cout << " > ";
    else if ( isLessThan() ) std:: cout << " < ";
    else if ( isGreaterEqual() ) std:: cout << " >= ";
    else if ( isLessEqual() ) std:: cout << " <= ";
    else std::cout << "Uninitialized token.\n";
}
