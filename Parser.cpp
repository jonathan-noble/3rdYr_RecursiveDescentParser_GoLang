#include "Parser.h"
#include <stdio.h>
#include "iostream"
#include <sstream>
#include <string.h>

class Parser
{
   Token crtToken;
   const char* m_Text;
   size_t m_Index;
 
private:
 
   void Source()
   {
      switch(crtToken.Type)
      {
      case String:
      GetNextToken();
      Decls();
      break;
      }
      // Decls();
      // Package();
   }
 
   void Decls()
   {
      switch(crtToken.Type)
      {
      case QuoteMarks:
         GetNextToken();
         GetString();
         Match('"');
         break;
         
      case OpenParenthesis:
         GetNextToken();
         Parenthesis();
         Match(')');
         break;
      }
   }
 
   void Import()
   {
       GetString();
   }
 
   void Parenthesis()
   {
      switch(crtToken.Type)
      {
      case QuoteMarks: 
         GetNextToken();
         GetString();
         Match('"');
         Parenthesis();
         break;
 
      case EndOfText:
         GetNextToken();
         break;
      }
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
         crtToken.Type = String;
         crtToken.Value = GetString();
         return;
      }
 
      crtToken.Type = Error;
 
      // check if the current character is an operator or parentheses
      switch(m_Text[m_Index])
      {
      case 'import': crtToken.Type = String; break;
      case 'fmt': crtToken.Type = String; break;
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
   void Parse(const char* text)
   {
      m_Text = text;
      m_Index = 0;
      GetNextToken();
 
      Source();
   }
};