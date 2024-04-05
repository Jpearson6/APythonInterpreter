//
// Created by Ali Kooshesh on 4/4/23.
//

#include "Statements.hpp"
#include "NumberDescriptor.hpp"

// Statement
Statement::Statement() {}

// Statements

Statements::Statements() {}
void Statements::addStatement(Statement *statement) { _statements.push_back(statement); }

void Statements::print() {
    for (auto s: _statements)
        s->print();
}

void Statements::evaluate(SymTab &symTab) {
    for (auto s: _statements)
        s->evaluate(symTab);
}

// AssignmentStatement

AssignmentStatement::AssignmentStatement() : _lhsVariable{""}, _rhsExpression{nullptr} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr):
        _lhsVariable{lhsVar}, _rhsExpression{rhsExpr} {}

void AssignmentStatement::evaluate(SymTab &symTab) {
    auto rhs = rhsExpression()->evaluate(symTab);
    symTab.setValueFor(lhsVariable(), rhs);
}

std::string &AssignmentStatement::lhsVariable() {
    return _lhsVariable;
}

ExprNode *&AssignmentStatement::rhsExpression() {
    return _rhsExpression;
}

void AssignmentStatement::print() {
    std::cout << _lhsVariable << " = ";
    _rhsExpression->print();
    std::cout << std::endl;
}

PrintStatement::PrintStatement() : testList{nullptr} {}

PrintStatement::PrintStatement(std::vector<ExprNode*> print_statements):
        testList{print_statements} {}


void PrintStatement::evaluate(SymTab &symTab) {
    for(int i = 0 ; i < testList.size(); i++){
        TypeDescriptor a = testList.at(i)->evaluate(symTab);
        std::cout << a ;
    }
    std::cout<<std::endl;
}

void PrintStatement::print() {
    std::cout << "print(";
    for( int i = 0; i < testList.size(); i++){
        testList.at(i)->print();
    }
    std::cout << ')' << std::endl;
}

ForStatement::ForStatement() : _initialAssignment{nullptr}, _comparison{nullptr}, _counter{nullptr}, _statements{nullptr} {}

ForStatement::ForStatement(AssignmentStatement *initialAssignment, ExprNode *comparison, AssignmentStatement *counter, Statements *statements):
                _initialAssignment{initialAssignment}, _comparison{comparison}, _counter{counter}, _statements{statements} {}

AssignmentStatement *&ForStatement::initialAssignment(){
    return _initialAssignment;
}

ExprNode *&ForStatement::comparison(){
    return _comparison;
}

AssignmentStatement *&ForStatement::counter(){
    return _counter;
}

Statements *&ForStatement::statements(){
    return _statements;
}

void ForStatement::evaluate(SymTab &symTab) {

    for (_initialAssignment->evaluate(symTab) ; _comparison->evaluate(symTab).getIntValue() ; _counter->evaluate(symTab) ) {
        _statements->evaluate(symTab);
    }
}

void ForStatement::print() {
    std::cout << "for ( ";
    _initialAssignment->print();
    std::cout << " ; ";
    _comparison->print();
    std::cout << " ; ";
    _counter->print();
    std::cout << " ) { ";
    _statements->print();
    std::cout << " }" << std::endl;
}
