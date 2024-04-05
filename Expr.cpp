//
// Created by Ali Kooshesh on 4/4/23.
//


#include<iostream>
#include "Expr.hpp"
#include "NumberDescriptor.hpp"

// ArithExprNode
ExprNode::ExprNode(Token token): _token{token} {}

Token ExprNode::token() { return _token; }

// InfixExprNode functions
InfixExprNode::InfixExprNode(Token tk) : ExprNode{tk}, _left(nullptr), _right(nullptr) {}

ExprNode *&InfixExprNode::left() { return _left; }

ExprNode *&InfixExprNode::right() { return _right; }

TypeDescriptor InfixExprNode::evaluate(SymTab &symTab) {
    // Evaluates an infix expression using a post-order traversal of the expression tree.
    TypeDescriptor lValue = left()->evaluate(symTab);
    TypeDescriptor rValue = right()->evaluate(symTab);
    if(debug)
        std::cout << "InfixExprNode::evaluate: " << lValue << " " <<
            token().symbol() << " " << rValue << std::endl;

    if (lValue.type() == TypeDescriptor::INTEGER && rValue.type() == TypeDescriptor::INTEGER) {
        TypeDescriptor a(TypeDescriptor::INTEGER);
        if (token().isAdditionOperator()) {
            a.setValue(lValue.getIntValue() + rValue.getIntValue());
            return a;
        } else if (token().isSubtractionOperator()) {
            a.setValue(lValue.getIntValue() - rValue.getIntValue());
            return a;
        }
        else if (token().isMultiplicationOperator()) {
            a.setValue(lValue.getIntValue() * rValue.getIntValue());
            return a;
        }
        else if (token().isDivisionOperator()) {
            a.setValue(lValue.getIntValue() / rValue.getIntValue());
            return a;
        }
        else if (token().isIntegerDivision() ) {
            a.setValue(lValue.getIntValue() / rValue.getIntValue());
            return a;
        }
        else if (token().isModuloOperator()) {
            a.setValue(lValue.getIntValue() % rValue.getIntValue());
            return a;
        }
        else if (token().isEquality()) {
            a.setValue(lValue.getIntValue() == rValue.getIntValue());
            return a;
        }
        else if (token().isNotEqual()) {
            a.setValue(lValue.getIntValue() != rValue.getIntValue());
            return a;
        }
        else if (token().isGreaterThan()) {
            a.setValue(lValue.getIntValue() > rValue.getIntValue());
            return a;
        }
        else if (token().isGreaterEqual()) {
            a.setValue(lValue.getIntValue() >= rValue.getIntValue());
            return a;
        }
        else if (token().isLessThan()) {
            a.setValue(lValue.getIntValue() < rValue.getIntValue());
            return a;
        }
        else if (token().isLessEqual()) {
            a.setValue(lValue.getIntValue() <= rValue.getIntValue());
            return a;
        }
        else {
            std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
            token().print();
            std::cout << std::endl;
            exit(2);
        }
    }
    else if (lValue.type() == TypeDescriptor::INTEGER && rValue.type() == TypeDescriptor::DOUBLE) {
        TypeDescriptor a(TypeDescriptor::DOUBLE);
        if (token().isAdditionOperator()) {
            a.setValue(lValue.getIntValue() + rValue.getDouValue());
            return a;
        } else if (token().isSubtractionOperator()) {
            a.setValue(lValue.getIntValue() - rValue.getDouValue());
            return a;
        }
        else if (token().isMultiplicationOperator()) {
            a.setValue(lValue.getIntValue() * rValue.getDouValue());
            return a;
        }
        else if (token().isDivisionOperator()) {
            a.setValue(lValue.getIntValue() / rValue.getDouValue());
            return a;
        }
        else if ( token().isIntegerDivision()) {
            TypeDescriptor b(TypeDescriptor::INTEGER);
            b.setValue(int(lValue.getIntValue() / rValue.getDouValue()));
            return b;
        }
        else if (token().isEquality()) {
            a.setValue(lValue.getIntValue() == rValue.getDouValue());
            return a;
        }
        else if (token().isNotEqual()) {
            a.setValue(lValue.getIntValue() != rValue.getDouValue());
            return a;
        }
        else if (token().isGreaterThan()) {
            a.setValue(lValue.getIntValue() > rValue.getDouValue());
            return a;
        }
        else if (token().isGreaterEqual()) {
            a.setValue(lValue.getIntValue() >= rValue.getDouValue());
            return a;
        }
        else if (token().isLessThan()) {
            a.setValue(lValue.getIntValue() < rValue.getDouValue());
            return a;
        }
        else if (token().isLessEqual()) {
            a.setValue(lValue.getIntValue() <= rValue.getDouValue());
            return a;
        }
        else {
            std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
            token().print();
            std::cout << std::endl;
            exit(2);
        }
    }

    else if (lValue.type() == TypeDescriptor::DOUBLE && rValue.type() == TypeDescriptor::INTEGER) {
        TypeDescriptor a(TypeDescriptor::DOUBLE);
        if (token().isAdditionOperator()) {
            a.setValue(lValue.getDouValue() + rValue.getIntValue());
            return a;
        } else if (token().isSubtractionOperator()) {
            a.setValue(lValue.getDouValue() - rValue.getIntValue());
            return a;
        } else if (token().isMultiplicationOperator()) {
            a.setValue(lValue.getDouValue() * rValue.getIntValue());
            return a;
        } else if (token().isDivisionOperator()) {
            a.setValue(lValue.getDouValue() / rValue.getIntValue());
            return a;
        } else if ( token().isIntegerDivision()) {
            TypeDescriptor b(TypeDescriptor::INTEGER);
            b.setValue(int(lValue.getDouValue() / rValue.getIntValue()));
            return b;
        } else if (token().isEquality()) {
            a.setValue(lValue.getDouValue() == rValue.getIntValue());
            return a;
        } else if (token().isNotEqual()) {
            a.setValue(lValue.getDouValue() != rValue.getIntValue());
            return a;
        } else if (token().isGreaterThan()) {
            a.setValue(lValue.getDouValue() > rValue.getIntValue());
            return a;
        } else if (token().isGreaterEqual()) {
            a.setValue(lValue.getDouValue() >= rValue.getIntValue());
            return a;
        } else if (token().isLessThan()) {
            a.setValue(lValue.getDouValue() < rValue.getIntValue());
            return a;
        } else if (token().isLessEqual()) {
            a.setValue(lValue.getDouValue() <= rValue.getIntValue());
            return a;
        } else {
            std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
            token().print();
            std::cout << std::endl;
            exit(2);
        }
    }

    else if (lValue.type() == TypeDescriptor::DOUBLE && rValue.type() == TypeDescriptor::DOUBLE) {
        TypeDescriptor a(TypeDescriptor::DOUBLE);
        if (token().isAdditionOperator()) {
            a.setValue(lValue.getDouValue() + rValue.getDouValue());
            return a;
        } else if (token().isSubtractionOperator()) {
            a.setValue(lValue.getDouValue() - rValue.getDouValue());
            return a;
        } else if (token().isMultiplicationOperator()) {
            a.setValue(lValue.getDouValue() * rValue.getDouValue());
            return a;
        } else if (token().isDivisionOperator()) {
            a.setValue(lValue.getDouValue() / rValue.getDouValue());
            return a;
        } else if ( token().isIntegerDivision()) {
            TypeDescriptor b(TypeDescriptor::INTEGER);
            b.setValue(int(lValue.getDouValue() / rValue.getDouValue()));
            return b;
        } else if (token().isEquality()) {
            a.setValue(lValue.getDouValue() == rValue.getDouValue());
            return a;
        } else if (token().isNotEqual()) {
            a.setValue(lValue.getDouValue() != rValue.getDouValue());
            return a;
        } else if (token().isGreaterThan()) {
            a.setValue(lValue.getDouValue() > rValue.getDouValue());
            return a;
        } else if (token().isGreaterEqual()) {
            a.setValue(lValue.getDouValue() >= rValue.getDouValue());
            return a;
        } else if (token().isLessThan()) {
            a.setValue(lValue.getDouValue() < rValue.getDouValue());
            return a;
        } else if (token().isLessEqual()) {
            a.setValue(lValue.getDouValue() <= rValue.getDouValue());
            return a;
        } else {
            std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
            token().print();
            std::cout << std::endl;
            exit(2);
        }
    }

    else if (lValue.type() == TypeDescriptor::STRING && rValue.type() == TypeDescriptor::STRING) {
        TypeDescriptor a(TypeDescriptor::STRING);
        if (token().isAdditionOperator()) {
            a.setValue(lValue.getStrValue() + rValue.getStrValue());
            return a;
        } else {
            std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
            token().print();
            std::cout << std::endl;
            exit(2);
        }
    }
}

void InfixExprNode::print() {
    _left->print();
    token().print();
    _right->print();
}

// WHoleNumber
WholeNumber::WholeNumber(Token token): ExprNode{token} {}

void WholeNumber::print() {
    token().print();
}

TypeDescriptor WholeNumber::evaluate(SymTab &symTab) {
    if(debug)
        std::cout << "WholeNumber::evaluate: returning " << token().getWholeNumber() << std::endl;
    int value = token().getWholeNumber();
    TypeDescriptor desc(TypeDescriptor::INTEGER);
    desc.setValue(value);
    return desc;
}

// Variable

Variable::Variable(Token token): ExprNode{token} {}

void Variable::print() {
    token().print();
}

TypeDescriptor Variable::evaluate(SymTab &symTab) {
    if( ! symTab.isDefined(token().getName())) {
        std::cout << "Use of undefined variable, " << token().getName() << std::endl;
        exit(1);
    }
    TypeDescriptor a = symTab.getValueFor(token().getName());
    if(debug)
        std::cout << "Variable::evaluate: returning " << a << std::endl;
    return symTab.getValueFor(token().getName());
}

DecimalNumber::DecimalNumber(Token token): ExprNode{token} {}

void DecimalNumber::print() {
    token().print();
}

TypeDescriptor DecimalNumber::evaluate(SymTab &symTab) {
    if(debug)
        std::cout << "DecimalNumber::evaluate: returning " << token().getDoubleNumber() << std::endl;
    double value = token().getDoubleNumber();
    TypeDescriptor desc(TypeDescriptor::DOUBLE);
    desc.setValue(value);
    return desc;
}

TypeDescriptor StringValue::evaluate(SymTab &symTab) {
    if(debug)
        std::cout << "DecimalNumber::evaluate: returning " << token().getDoubleNumber() << std::endl;
    std::string value = token().getName();
    TypeDescriptor desc(TypeDescriptor::STRING);
    if( token().isComa()){
        desc.setValue(" ");
        return desc;
    }
    desc.setValue(value);
    return desc;
}

void StringValue::print() {
    token().print();
}

StringValue::StringValue(Token token): ExprNode{token} {}
