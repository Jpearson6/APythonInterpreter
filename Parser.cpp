//
// Created by Ali Kooshesh on 4/4/23.
//


#include<vector>
#include<iostream>

#include "Token.hpp"
#include "Parser.hpp"
#include "Statements.hpp"

// Parser functions

void Parser::die(std::string where, std::string message, Token &token) {
    std::cout << where << " " << message << std::endl;
    token.print();
    std::cout << std::endl;
    std::cout << "\nThe following is a list of tokens that have been identified up to this point.\n";
    tokenizer.printProcessedTokens();
    exit(1);
}

Statements *Parser::statements() {
    // This function is called when we KNOW that we are about to parse
    // a series of assignment statements.

    // This function parses the grammar rules:

    // <statement> -> <assignStatement> <statement>
    // <statement> -> Epsilon


    Statements *stmts = new Statements();
    Token tok = tokenizer.getToken();
    while (tok.isName() || tok.isKeyWord() || tok.eol() || tok.isComment()) {

        if(tok.isPrint()){
            tokenizer.ungetToken();
            PrintStatement *printStmt = printStatement();
            stmts->addStatement(printStmt);
        }
        else if(tok.isFor()){
            tokenizer.ungetToken();
            ForStatement *forStmt = forStatement();
            stmts->addStatement(forStmt);
        }
        else if (tok.isName()){
            tokenizer.ungetToken();
            AssignmentStatement *assignStmt = assignStatement();
            stmts->addStatement(assignStmt);
        }
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return stmts;
}

PrintStatement *Parser::printStatement() {
    // Parses the following grammar rule
    //
    // <print-statement> -> print <id>
    Token print = tokenizer.getToken();
    if(!print.isPrint())
        die("Parser::printStatement", "Expected a print token, instead got", print);
    Token openParen = tokenizer.getToken();
    if(!openParen.isOpenParen())
        die("Parser::printStatement", "Expected a open parenthesis token, instead got", openParen);

    Token tok = tokenizer.getToken();
    std::vector<ExprNode*> print_statements;
    while(!tok.isCloseParen() && !tok.eol() && !tok.eof()){
        if(tok.isComa()){
            print_statements.push_back(new StringValue(tok));
        }
        else{
            tokenizer.ungetToken();
            print_statements.push_back(relTerm());
        }
        tok = tokenizer.getToken();
    }


    if(! tok.isCloseParen())
        die("Parser::printStatement", "Expected a close parenthesis token, instead got", tok);
    
    return new PrintStatement(print_statements);
}

ForStatement *Parser::forStatement() {
    // Parses the following grammar rule
    //
    // <for-statement> -> for ( < assign-statement> ; < rel-expr > ; < assign-statement > ) { < statements > }
    Token isFor = tokenizer.getToken();
    if(!isFor.isFor())
        die("Parser::forStatement", "Expected a for token, instead got", isFor);
    Token openParen = tokenizer.getToken();
    if(!openParen.isOpenParen())
        die("Parser::forStatement", "Expected a open parenthesis token, instead got", openParen);

    AssignmentStatement *initialAssignment = assignStatement();

    Token semiColon = tokenizer.getToken();
    if(!semiColon.isSemiColon())
        die("Parser::forStatement", "Expected a semi colon token, instead got", semiColon);
    
    ExprNode *comparison = relTerm();

    semiColon = tokenizer.getToken();
    if(!semiColon.isSemiColon())
        die("Parser::forStatement", "Expected a semi colon token, instead got", semiColon);
    
    AssignmentStatement *counter = assignStatement();

    Token closeParen = tokenizer.getToken();
    if(!closeParen.isCloseParen())
        die("Parser::forStatement", "Expected a closed parenthesis token, instead got", closeParen);
    
    Token openBrace = tokenizer.getToken();
    if(!openBrace.isOpenBraket())
        die("Parser::forStatement", "Expected a open bracket token, instead got", openBrace);

    Token tok = tokenizer.getToken();
    if (!tok.eol())
        die("Parser::forStatement", "Expected an EOL, instead got", tok);
    
    Statements *_statements = statements();

    Token closeBrace = tokenizer.getToken();
    if(!closeBrace.isCloseBraket())
        die("Parser::forStatement", "Expected a close braket token, instead got", closeBrace);

    tok = tokenizer.getToken();
    if (!tok.eol())
        die("Parser::forStatement", "Expected an EOL, instead got", tok);

    return new ForStatement(initialAssignment, comparison, counter, _statements);
}

AssignmentStatement *Parser::assignStatement() {
    // Parses the following grammar rule
    //
    // <assign-stmtement> -> <id> = <expr>

    Token varName = tokenizer.getToken();
    if (!varName.isName())
        die("Parser::assignStatement", "Expected a name token, instead got", varName);

    Token assignOp = tokenizer.getToken();
    if (!assignOp.isAssignmentOperator())
        die("Parser::assignStatement", "Expected an equal sign, instead got", assignOp);

    ExprNode *rightHandSideExpr = relTerm();

    return new AssignmentStatement(varName.getName(), rightHandSideExpr);
}

ExprNode *Parser::relTerm() {
    // This function parses the grammar rules:

    // <expr> -> <term> { <rel_op> <term> }
    // <re_op> -> > | <

    // However, it makes the <rel_op> left associative.

    ExprNode *left = artihExpr();
    Token tok = tokenizer.getToken();
    while (tok.isRelationalOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = artihExpr();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;

}

ExprNode *Parser::artihExpr() {
    // This function parses the grammar rules:

    // <expr> -> <term> { <add_op> <term> }
    // <add_op> -> + | -

    // However, it makes the <add_op> left associative.

    ExprNode *left = term();
    Token tok = tokenizer.getToken();
    while (tok.isAdditionOperator() || tok.isSubtractionOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = term();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}


ExprNode *Parser::term() {
    // This function parses the grammar rules:

    // <term> -> <primary> { <mult_op> <primary> }
    // <mult_op> -> * | / | % | //

    // However, the implementation makes the <mult-op> left associate.
    ExprNode *left = primary();
    Token tok = tokenizer.getToken();

    while (tok.isMultiplicationOperator() || tok.isDivisionOperator() || tok.isModuloOperator() || tok.isIntegerDivision()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = primary();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::primary() {
    // This function parses the grammar rules:

    // <primary> -> [0-9]+
    // <primary> -> [_a-zA-Z]+
    // <primary> -> (<expr>)

    Token tok = tokenizer.getToken();

    if (tok.isStringValue() )
        return new StringValue(tok);
    if (tok.isDoubleNumber() )
        return new DecimalNumber(tok);
    else if( tok.isWholeNumber() )
        return new WholeNumber(tok);
    else if( tok.isName() )
        return new Variable(tok);
    else if (tok.isOpenParen()) {
        ExprNode *p = relTerm();
        Token token = tokenizer.getToken();
        if (!token.isCloseParen())
            die("Parser::primary", "Expected close-parenthesis, instead got", token);
        return p;
    }
    die("Parser::primary", "Unexpected token", tok);

    return nullptr;  // Will not reach this statement!
}




