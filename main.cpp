/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Butan
 *
 * Created on 01 May 2018, 19:44
 */

#include <cstdlib>
#include "Parser.cpp"

using namespace std;

void Test(const char* text)
{
   Parser parser;
   try 
   {
      parser.Parse(text);
      std::cout << "Parsing successful!" << std::endl;
   }
   catch(std::exception& ex)
   {
      std::cout << """ Parsing failed! " << ex.what() << std::endl;
   }   
}
 
int main()
{
   Test("import 'fmt' ");
   return 0;
}

