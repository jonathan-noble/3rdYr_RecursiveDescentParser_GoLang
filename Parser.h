/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: Butan
 *
 * Created on 30 April 2018, 03:23
 */

#ifndef PARSER_H
#define PARSER_H

enum TokenType 
{
   Error,
   Import,
   String,
   QuoteMarks,
   EndOfText,
   OpenParenthesis,
   ClosedParenthesis,
};
 
struct Token 
{
   TokenType   Type;
   double      Value;
   char      Symbol;
 
   Token():Type(Error), Value(0), Symbol(0)
   {}
};

#endif /* PARSER_H */

