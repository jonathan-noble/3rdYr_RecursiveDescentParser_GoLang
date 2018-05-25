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

#include "ctype.h"
#include <stdio.h>
#include <sstream>
#include <assert.h>
#include <exception>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include "AST.h"

using namespace std;

class Parser
{
   Token crtToken;
   const char* m_Text;
   size_t m_Index;
 
private:
 
   ASTNode* Source()
   {
       string nodeName("Source");
       cout << nodeName << "->\n";
       
       ASTNode* pnode = Package();
       ASTNode* inode = Imports();
       
       return CreateNode(SourceNode, pnode, inode);
       

       
//      switch(crtToken.Type)
//      {
//      Package();
//      Imports();
//      break;
//      }
      // Decls();
      // Package();
   }
   
   ASTNode* Package() {
       
       string nodeName("Package");
       cout << nodeName << "\t->\n";
       
    if(crtToken.Type == PackageToken)
    {
        GetNextToken(); 
    }
       
    if(crtToken.Type == StringToken) {
    ASTNode* packageNode = new ASTNode();
    packageNode->Type = PackageNode;
    return packageNode;
       
      }
   }

 
   ASTNode* Imports()
   {
       
       string nodeName("Imports");
       cout << nodeName << "\t->\n";
       
       if(crtToken.Type == importToken) 
       {
           GetNextToken();
       }
       
       if(crtToken.Type == ImportsToken) {
           ASTNode* iNode = new ASTNode();
           iNode->Type = ImportNode;
           return iNode;
       }
   }
       
   
    ASTNode* import()
   {
       string nodeName("import");
       cout << nodeName << "\t->\n";
       
       if(crtToken.Type == ImportsToken) 
       {
           GetNextToken();
       }
       
       if(crtToken.Type == StringToken) {
           ASTNode* iNode = new ASTNode();
           iNode->Type = importsNode;
           return iNode;
       }
   }
 
   
//    void Decls()
//   {
//      switch(crtToken.Type)
//      {
//      case QuoteMarks:
//         GetNextToken();
//         GetString();
//         Match('"');
//         break;
//         
//      case OpenParenthesis:
//         GetNextToken();
//         Parenthesis();
//         Match(')');
//         break;
//      }
//   }
   
 ASTNode* CreateNode(ASTNodeType type, ASTNode* left, ASTNode* right)
   {
      ASTNode* node = new ASTNode;
      node->Type = type;
      node->Left = left;
      node->Right = right;
 
      return node;
   }
 
  
 
   ASTNode* CreateNodeString(double value)
   {
      ASTNode* node = new ASTNode;
      node->Type = StringValue;
      node->Value = value;
 
      return node;
   }
   
   void Match(char expected)
   {
      if(m_Text[m_Index-1] == expected)
         GetNextToken();
      else
      {
         std::stringstream sstr;
         sstr << "Expected crtToken '" << expected << "' at position " << m_Index;
      }
   }
 
   void SkipWhitespaces()
   {
      while(isspace(m_Text[m_Index])) m_Index++;
   }
 
   void GetNextToken()
   {
      // ignore white spaces
      SkipWhitespaces();
 
      crtToken.Value = 0;
      crtToken.Symbol = 0;
 
      // test for the end of text
      if(m_Text[m_Index] == 0)
      {
         crtToken.Type = EndOfText;
         return;
      }
 
      // if the current character is an alphabet read a string
      if(isalpha(m_Text[m_Index]))
      {
         crtToken.Type = StringToken;
         crtToken.Value = GetString();
         return;
      }
 
      crtToken.Type = Error;
 
      // check if the current character is an operator or parentheses
      switch(m_Text[m_Index])
      {
      //case 'import': crtToken.Type = String; break;
      case '"': crtToken.Type = QuoteMarks; break;
      case '(': crtToken.Type = OpenParenthesis; break;
      case ')': crtToken.Type = ClosedParenthesis; break;
      }
 
      if(crtToken.Type != Error)
      {
         crtToken.Symbol = m_Text[m_Index];
         m_Index++;
      }
      else
      {
         std::stringstream sstr; 
         sstr << "Unexpected crtToken '" << m_Text[m_Index] << "' at position " << m_Index;
      }
   }
 
   double GetString()
   {
      SkipWhitespaces();
 
      int index = m_Index;
      while(isalpha(m_Text[m_Index])) m_Index++;
      if(m_Text[m_Index] == '.') m_Index++;
      while(isalpha(m_Text[m_Index])) m_Index++;
 
//      if(m_Index - index == 0)
//         throw std::exception ("String expected but not found!", m_Index);
 
      char buffer[32] = {0};
      memcpy(buffer, &m_Text[index], m_Index - index);
 
      return atof(buffer);
   }
 
public:
   ASTNode* Parse(const char* text)  //fstream&)
   {
   // ifstream myfile("astgo.txt");
    m_Text = text;
    m_Index = 0;
    GetNextToken();
          
    return Source();
   }
};


#endif /* PARSER_H */

