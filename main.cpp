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
#include<iostream>
#include <fstream>
#include "Parser.h"

using namespace std;

void Test(const char* text) // (myfile parameter) - fstream&)
{
   Parser parser;
   string line;
   ifstream myfile ("astgo.txt");
    
   
   try 
   {

        if (myfile.is_open())
        {     
            while( getline(myfile, line) )
            {
            parser.Parse(text); //myfile); 
            std::cout << "Parsing successful!" << std::endl;
            cout << line << '\n';
            }
          myfile.close(); 
         }

   }
   
   catch(std::exception& ex)
   {
      std::cout << """ Parsing failed! " << ex.what() << std::endl;
   }   
}
 
int main()
{
    fstream myfile("astgo.txt");
    Test(""); 
   return 0;
}

