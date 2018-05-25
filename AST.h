/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AST.h
 * Author: Butan
 *
 * Created on 17 May 2018, 22:07
 */

#ifndef AST_H
#define AST_H


enum TokenType 
{
   Error,
   PackageToken,
   StringToken,
   importToken,
   ImportsToken,
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

enum ASTNodeType 
{
   Undefined,
   SourceNode,
   ImportNode,
   importsNode,
   PackageNode,
   StringValue
};

class ASTNode
{
public:
   ASTNodeType Type;
   double      Value;
   ASTNode*    Left;
   ASTNode*    Right;
   char       Symbol;
 
   ASTNode()
   {
      Type = Undefined;
      Value = 0;
      Left = 0; // NULL
      Right = 0; // NULL
       Symbol = 0;
   }
 
   ~ASTNode()
   {
      delete Left;
      delete Right;
   }
};

#endif /* AST_H */

