#include "scanner.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include<ctype.h>

shared_ptr<Token> Scanner::nextToken(){
    
    start_again: 
    string currentString = "";
    bool run_while = true;
    if(nextChar())  //if exits a char
    {
                                                      // cout << ch << " 0.1 " << endl; // ****************************** DEBUG **************************
        while((isspace(ch) || ch == '/' || ch == '\0') && (run_while))
        {
                                                       // cout << ch << " 1.0 " << endl; // ****************************** DEBUG **************************
            if(ch == '/')
            {
                                                       // cout << ch << " 1.1 " << endl; // ****************************** DEBUG **************************
                if(nextChar() && ch == '*' || ch == '/')   //we have a note of // or /*
                {
                                                        //cout << ch << " 1.2 " << endl; // ****************************** DEBUG **************************
                    if(ch == '*') //  we have /*
                    {
                                                        //cout << ch << " 1.3 " << endl; // ****************************** DEBUG **************************
                        bool stop = true;
                        while(stop)
                        {  
                            nextChar();                         
                            if(ch == '*')
                            {
                                                        //cout << ch << " 1.4 " << endl; // ****************************** DEBUG **************************
                                nextChar();
                                while(ch == '*' || ch == '/')
                                {
                                                        //cout << ch << " 1.5 " << endl; // ****************************** DEBUG **************************
                                    if (ch == '/')
                                    {
                                                      //  cout << ch << " 1.6 " << endl; // ****************************** DEBUG **************************
                                    stop = false;
                                    goto start_again;
                                    }else
                                    {
                                    nextChar();
                                                       //cout << ch << " 1.7 " << endl; // ****************************** DEBUG **************************
                                    }
                                    
                                }
                            }
                        }                    
                    }else // we have //
                    {
                        int previousLine = lineno;
                        while(previousLine == lineno) // as long as we are on the same line (note) continue
                        {
                            //cout << ch << " 1.7.1 " << endl; // ****************************** DEBUG **************************
                            nextChar();
                        }
                    }
                    continue;   // go to beginging of while to check if there are more spaces or notes
                }else  // we have a single '/' so it needs to be returned:
                {
                     return shared_ptr<Token>(new Token(static_cast<tokenType>(ch),string(1,ch)));   //return single '/'
                }
            }else
            {
                                        //cout << ch << " 1.8.1 " << endl; // ****************************** DEBUG **************************
                run_while = nextChar();
                                       // cout << ch << " 1.8.2 " << endl; // ****************************** DEBUG **************************
            }
            // if(!nextChar())
            // {
            //     return nullptr;
            // }           
        }            
                                        //cout << ch << " 1.9 " << endl; // ****************************** DEBUG **************************
    switch (ch)  // each character represents itself
    { 
                        
        case '=' : case '&' : case ';' : case '{' : case '}' : case ',' : case ':' : 
        case '(' : case ')' : case '[' : case ']' : case '~' : 
        case '*' : case '%' : case '^' : case '?' : case '/': 
        return shared_ptr<Token>(new Token(static_cast<tokenType>(ch),string(1,ch)));
        break;
    }
                                   //  cout << ch << " 2.0 " << endl; // ****************************** DEBUG **************************                                          
    char previous = ch;
    if (nextChar())
    {
       
        currentString = string(1,previous);
        currentString += string(1,ch); 
                                    // cout << currentString << " currentstring 2.1 " << endl; // ****************************** DEBUG **************************
        if (currentString == "++") return make_shared<Token>(INC_OP, currentString);
        if (currentString == "--") return make_shared<Token>(DEC_OP, currentString);
        if (currentString == "->") return make_shared<Token>(PTR_OP, currentString);
        if (currentString == "&&") return make_shared<Token>(AND_OP, currentString);
        if (currentString == "||") return make_shared<Token>(OR_OP, currentString);
        if (currentString == "<=") return make_shared<Token>(LE_OP, currentString);
        if (currentString == ">=") return make_shared<Token>(GE_OP, currentString);
        if (currentString == "==") return make_shared<Token>(EQ_OP, currentString);
        if (currentString == "!=") return make_shared<Token>(NE_OP, currentString);
    }
    ch = previous;
    inputFile.unget();
    
                                         //  cout << ch << " 2.1 " << endl; // ****************************** DEBUG **************************
                    
        if(isdigit(ch) || ch == '+' || ch == '-' || ch == '.')
        {
                                        //  cout << ch << " 2.2 " << endl; // ****************************** DEBUG **************************                                          
            currentString = string(1,ch);
                                       //   cout << currentString << " currentstring 2.2 " << endl; // ****************************** DEBUG **************************
            previous = ch;                              
            nextChar();
            int counterPoint = 0;
            int counterE = 0;
            while(isdigit(ch) || ch == 'e' || ch == 'E' || ch == '.')
            {
                                         //  cout << ch << " 2.3 " << endl; // ****************************** DEBUG **************************                                           
                currentString.push_back(ch);
                                            // cout << currentString << " currentstring 2.3 " << endl; // ****************************** DEBUG **************************
                if (ch == '.')
                {
                    counterPoint++;
                }
                  if (ch == 'e' || ch == 'E')
                {
                    counterE++;
                }   
                previous = ch;
                nextChar();           
            }
            inputFile.unget();
            ch = previous;
                                                    //cout << currentString << " currentstring 2.4 " << endl; // ****************************** DEBUG **************************
            if (currentString == ".") //checks if it is '.'
            {  
                                                      // cout << ch << " 2.4 " << endl; // ****************************** DEBUG **************************
                 return shared_ptr<Token>(new Token(static_cast<tokenType>('.'),currentString));  
            }
            else if(counterPoint > 1 || counterE > 1)  //check if its has more then two '.' or two 'e'
            {
                                                       //  cout << ch << " 2.5 " << endl; // ****************************** DEBUG **************************
                return make_shared<Token>(ERROR, currentString);
            }
            else // check if valid number
            {
                                                         //  cout << ch << " 2.6 " << endl; // ****************************** DEBUG **************************
                                                         //  cout << currentString << " currentstring 2.6 " << endl; // ****************************** DEBUG **************************
                return make_shared<Token>(CONSTANT, currentString);
            }
                                         //  cout <<  " current string 1.5.2:" << currentString << endl; // ****************************** DEBUG **************************

        }
                                          //  cout << ch << " 1.5.2 " << endl; // ****************************** DEBUG **************************

        if(isalpha(ch) || ch == '_')   //check if we have a varilabe (valid word without @#$%^&.....)
        {
                                                     // cout << ch << " 1.5.3 " << endl; // ****************************** DEBUG **************************

            currentString = string(1,ch);
                                                       // cout <<  " current string 1.5.3:" << currentString << endl; // ****************************** DEBUG **************************

            nextChar();
                                            // cout << ch << " 1.6 " << endl; // ****************************** DEBUG **************************
            while(isalpha(ch) || ch == '_' || isdigit(ch))
            {
                currentString+= ch;
                nextChar();
                                           // cout << ch << " 1.7 " << endl; // ****************************** DEBUG **************************
            }
                                           //  cout <<  " current string 1.7 " << currentString << endl; // ****************************** DEBUG **************************
            shared_ptr<Token> token;
			token = symTab.lookupToken(currentString); //checks if the word is in the map and inserts it if its wasnt there
            token->add_line(lineno);  //add line number
            inputFile.unget();   //need to go one back and update ch

            return token;  
        }

        if(ch == '\'')
        {
            currentString = string(1,ch);    //same function as in the task (string of one char)
            for(int i = 0; i < 2; i++)
            {
                if(!nextChar())
                {
                    return make_shared<Token>(ERROR,currentString);
                }
                else
                {
                currentString.push_back(ch);
                }                
            }
            if(currentString[0] == currentString[2] && isalpha(currentString[1]))
            {
                    return make_shared<Token>(CONSTANT,string(1,currentString[1]));

            }
        }
                if(ch == '\"')
                {
                    bool enterd = false;
                    currentString = "";
                    while(nextChar() && ch != '\"')
                    {
                        currentString.push_back(ch);
                        enterd = true;
                    }
                    if (enterd)
                    {
                    return make_shared<Token>(STRING_LITERAL,currentString);
                    }
                    else
                    {
                    return make_shared<Token>(ERROR,currentString);
                    }
                }         
    }else return nullptr; // if theres no char...
    //return nullptr;
}

  




    
