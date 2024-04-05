//
// Created by Ali Kooshesh on 4/4/23.
//

#include <iostream>
#include <string>
#include "Tokenizer.hpp"

std::string Tokenizer::readName() {
    // This function is called when it is known that
    // the first character in input is an alphabetic character.
    // The function reads and returns all characters of the name.

    std::string name;
    char c;
    while( inStream.get(c) && isalnum(c) ) {
        name += c;
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return name;
}

int Tokenizer::readInteger(std::string intAsString) {
    // This function is called when it is known that
    // the first character in input is a digit.
    // The function reads and returns all remaining digits.
    return std::stoi(intAsString);
}

double Tokenizer::readDouble(std::string doubleAsString) {
    // This function is called when it is known that
    // the first character in input is a digit.
    // The function reads and returns all remaining digits.
    return std::stod(doubleAsString);
}

Tokenizer::Tokenizer(std::ifstream &stream): ungottenToken{false}, inStream{stream}, lastToken{} {}

Token Tokenizer::getToken() {

    std::string tempString;
    bool isFloat = false;

    if(ungottenToken) {
        ungottenToken = false;
        return lastToken;
    }

    char c;
    /*
    while( inStream.get(c) && isspace(c) && c != '\n' )  // Skip spaces but not new-line chars.
        ;
    */

    while( inStream.get(c) && isspace(c) && c != '\n')  // Skip spaces but not new-line chars.
        ;

    if(inStream.bad()) {
        std::cout << "Error while reading the input stream in Tokenizer.\n";
        exit(1);
    }

    //    std::cout << "c = " << c << std::endl;

    Token token;
    if( inStream.eof()) {
        token.eof() = true;
    } else if( c == '\n' ) {  // will not ever be the case unless new-line characters are not supressed.
        token.eol() = true;
    } else if( c == '#'){
        //if we see a # we know the rest of the line is a comment
        tempString += c;
        while( inStream.get(c) && c != '\n'){
            tempString += c;
        }
        token.setName(tempString);
        token.isComment() = true;
        inStream.putback(c);
    } else if (c == '\"'){
        // if we see a " we read in all characters until we see another "
        while( inStream.get(c) && c != '\"'){
            tempString += c;
        }
        token.setName(tempString);
        token.isStringValue() = true;
    } else if( isdigit(c) ) { // a integer?
        // put the digit back into the input stream so
        // we read the entire number in a function
        inStream.putback(c);
        while( inStream.get(c) && (isdigit(c) || c == '.')) {
            if(c == '.')
                isFloat = true;
            tempString += c;
        }
        if(isFloat){
            token.setDoubleNumber( readDouble(tempString) );
            inStream.putback(c);
        }
        else {
            token.setWholeNumber( readInteger(tempString) );
            inStream.putback(c);
        }


    } else if( c == '=' )
        if( inStream.get(c) && c == '=')
            token.relationalSymbol("==");
        else {
            inStream.putback(c);
            token.symbol('=');
        }
    else if( c == '+' || c == '-' || c == '*' || c == '%')
        token.symbol(c);
    else if( c == '/' ){
        if( inStream.get(c) && c == '/')
            token.integerDivision("//");
        else{
            inStream.putback(c);
            token.symbol('/');
        }
    }
    else if( c == ';' )
        token.symbol(c);
    else if( c == '(' || c == ')' || c == '{' || c == '}' || c == ',' )
        token.symbol(c);
    else if( c == '>')
        if ( inStream.get(c) && c == '=')
            token.relationalSymbol(">=");
        else {
            inStream.putback(c);
            token.symbol('>');
        }
    else if( c == '<')
        if ( inStream.get(c) && c == '=')
            token.relationalSymbol("<=");
        else {
            inStream.putback(c);
            token.symbol('<');
        }
    else if( c == '!')
        if ( inStream.get(c) && c == '=')
            token.relationalSymbol("!=");
        else {
            std::cout << "Unknown character in input. ->!<-" << std::endl;
            exit(1);
        }
    else if(isalpha(c)) {  // an identifier?
        // put c back into the stream so we can read the entire name in a function.
        inStream.putback(c);
        token.setName( readName() );
    } else {
        std::cout << "Unknown character in input. ->" << c << "<-" << std::endl;
        exit(1);
    }
    _tokens.push_back(token);
    return lastToken = token;
}

void Tokenizer::ungetToken() {
    ungottenToken = true;
}

void Tokenizer::printProcessedTokens() {
    for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
        iter->print();
        std::cout << std::endl;
    }
}
