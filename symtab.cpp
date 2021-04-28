#include "symtab.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <map>

void SymbolTable::initReserved()
{

   ifstream myFile("reserved.txt");
    string line, firstWord, secondWord;
    int number;
   while ( getline (myFile, line) )
   {
      stringstream ss(line);
      ss >> firstWord;
      ss >> secondWord;
      number = stoi(secondWord);
      tokenType type = static_cast<tokenType>(number);
      shared_ptr<Token> tokenPtr = make_shared<Token>(type,firstWord);
      symMap[firstWord] = tokenPtr;
    //  symMap.insert(firstWord, tokenPtr);
          
  }
    //printMap();


}

shared_ptr<Token> SymbolTable::lookupToken(string text)
{
    if(symMap[text] != nullptr)
    {
     return symMap[text];
    }
    else
    {
    shared_ptr<Token> varTokenPtr = make_shared<varToken>(text);
    insertToken(text, varTokenPtr);
    return symMap[text];
    }
}

void SymbolTable::insertToken(string text, shared_ptr<Token> tokenp)
{

    //symMap.insert(pair<string, shared_ptr<Token>>(text,tokenp));
    symMap[text] = tokenp;
}

void SymbolTable::xref()
{
    shared_ptr<set<int>> lines;
     for(auto i : symMap)
     {
         if (i.second->getType() == IDENTIFIER){
             cout << i.second->getText() << '\t';
             lines = i.second->getLines();
             set<int>::iterator it;
            for (it = lines->begin(); it != lines->end(); ++it) 
            {
                cout << *it << " ";
            }
            cout << endl; 
         }
     }
}

// void SymbolTable::printMap()
// {
//  for(auto i : symMap){
//        cout<< "key: " <<i.first<<"   Value: "<< " type- "<< i.second->getType() 
//        << " text- " << i.second->getText() <<"\n";
//     }

// }