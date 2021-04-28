# include "token.h"
#include "tokenstrings.h"

    tokenType Token::getType()
    {
        return type;
    }
    string Token::getText()
    {
        return text;
    }
    void Token::printToken()
    {
        if (type < 258)
        {
            cout << (char)type << '\t' << text << endl;
        }else
        {
            int index_of_enum = type - 258;
            cout << tokenStrings[index_of_enum] << '\t' << text << endl;
        }
        
    }
    void varToken::add_line(int l) 
    {
        lines->insert(l);
    }
    shared_ptr<set<int>> varToken::getLines() 
    {
        return lines;
    }

